#include "../stdafx.h"
#include "sonic_refiner_dsp.h"
#include "biquad.h"

#ifdef _WIN32
#include <helpers/DarkMode.h>
#include "resource.h"
#endif

namespace {

constexpr double depth_standard_max_boost_db = 8.0;
constexpr double depth_extreme_max_boost_db = 16.0;
constexpr double depth_shelf_frequency_hz = 120.0;

constexpr double clarity_standard_max_boost_db = 7.0;
constexpr double clarity_extreme_max_boost_db = 14.0;
constexpr double clarity_shelf_frequency_hz = 3500.0;

constexpr double width_standard_maximum_side_gain = 3.5;
constexpr double width_extreme_maximum_side_gain = 6.0;
constexpr double width_low_frequency_protection_hz = 180.0;

constexpr double ambience_standard_maximum_wet_mix = 0.55;
constexpr double ambience_extreme_maximum_wet_mix = 0.85;
constexpr double ambience_standard_maximum_dry_reduction = 0.18;
constexpr double ambience_extreme_maximum_dry_reduction = 0.28;
constexpr double ambience_first_reflection_ms = 11.0;
constexpr double ambience_second_reflection_ms = 19.0;

constexpr double auto_headroom_ceiling = 0.98;
constexpr double auto_headroom_release_seconds = 1.5;

constexpr double level_match_meter_seconds = 0.75;
constexpr double level_match_attack_seconds = 0.10;
constexpr double level_match_release_seconds = 0.80;
constexpr double level_match_minimum_gain = 0.25;
constexpr double level_match_silence_power = 1.0e-10;

constexpr double output_gain_minimum_db = -12.0;
constexpr double output_gain_maximum_db = 6.0;
constexpr double output_gain_step_db = 0.5;

constexpr double two_pi = 6.283185307179586476925286766559;

double normalized_parameter(float value) noexcept {
    return std::clamp(
        static_cast<double>(value) / 100.0,
        0.0,
        1.0
    );
}

double expanded_parameter_value(
    float value,
    double standard_maximum,
    double extreme_maximum
) noexcept {
    const double normalized = normalized_parameter(value);

    if (normalized <= 0.60) {
        // Preserve the v0.2.0 response throughout the normal-use range.
        return normalized * standard_maximum;
    }

    if (normalized <= 0.80) {
        const double phase = (normalized - 0.60) / 0.20;
        const double start = standard_maximum * 0.60;
        const double end = extreme_maximum * 0.65;
        return start + ((end - start) * phase);
    }

    const double phase = (normalized - 0.80) / 0.20;
    const double start = extreme_maximum * 0.65;
    return start + ((extreme_maximum - start) * phase);
}

double parameter_to_gain_db(
    float value,
    double standard_maximum_gain_db,
    double extreme_maximum_gain_db
) noexcept {
    return expanded_parameter_value(
        value,
        standard_maximum_gain_db,
        extreme_maximum_gain_db
    );
}

double depth_to_gain_db(float depth) noexcept {
    return parameter_to_gain_db(
        depth,
        depth_standard_max_boost_db,
        depth_extreme_max_boost_db
    );
}

double clarity_to_gain_db(float clarity) noexcept {
    return parameter_to_gain_db(
        clarity,
        clarity_standard_max_boost_db,
        clarity_extreme_max_boost_db
    );
}

double width_to_side_gain(float width) noexcept {
    return 1.0 + expanded_parameter_value(
        width,
        width_standard_maximum_side_gain - 1.0,
        width_extreme_maximum_side_gain - 1.0
    );
}

double ambience_to_wet_mix(float ambience) noexcept {
    return expanded_parameter_value(
        ambience,
        ambience_standard_maximum_wet_mix,
        ambience_extreme_maximum_wet_mix
    );
}

double ambience_to_dry_reduction(float ambience) noexcept {
    return expanded_parameter_value(
        ambience,
        ambience_standard_maximum_dry_reduction,
        ambience_extreme_maximum_dry_reduction
    );
}

double master_strength_factor(float master_strength) noexcept {
    return normalized_parameter(master_strength);
}

double effective_depth_gain_db(
    float depth,
    float master_strength
) noexcept {
    return depth_to_gain_db(depth) *
        master_strength_factor(master_strength);
}

double effective_clarity_gain_db(
    float clarity,
    float master_strength
) noexcept {
    return clarity_to_gain_db(clarity) *
        master_strength_factor(master_strength);
}

double effective_width_side_gain(
    float width,
    float master_strength
) noexcept {
    const double configured_gain = width_to_side_gain(width);
    return 1.0 +
        ((configured_gain - 1.0) *
         master_strength_factor(master_strength));
}

double effective_ambience_wet_mix(
    float ambience,
    float master_strength
) noexcept {
    return ambience_to_wet_mix(ambience) *
        master_strength_factor(master_strength);
}

double effective_ambience_dry_reduction(
    float ambience,
    float master_strength
) noexcept {
    return ambience_to_dry_reduction(ambience) *
        master_strength_factor(master_strength);
}

double output_gain_to_linear(float output_gain_db) noexcept {
    const double safe_gain_db = std::clamp(
        static_cast<double>(output_gain_db),
        output_gain_minimum_db,
        output_gain_maximum_db
    );

    const double gain = std::pow(10.0, safe_gain_db / 20.0);
    return std::isfinite(gain) ? gain : 1.0;
}

void apply_output_gain(
    audio_sample* data,
    t_size sample_count,
    float output_gain_db
) noexcept {
    if (data == nullptr || sample_count == 0) {
        return;
    }

    const double gain = output_gain_to_linear(output_gain_db);

    if (std::abs(gain - 1.0) <= 1.0e-9) {
        return;
    }

    for (t_size index = 0; index < sample_count; ++index) {
        const double value = static_cast<double>(data[index]);

        if (!std::isfinite(value)) {
            data[index] = static_cast<audio_sample>(0);
            continue;
        }

        data[index] = static_cast<audio_sample>(value * gain);
    }
}

#ifdef _WIN32
void run_config_popup(
    const dsp_preset& preset,
    HWND parent,
    dsp_preset_edit_callback& callback
);
#endif

struct channel_filters {
    sonic_refiner::biquad depth;
    sonic_refiner::biquad clarity;

    void reset() noexcept {
        depth.reset();
        clarity.reset();
    }

    audio_sample process(audio_sample input) noexcept {
        return clarity.process(depth.process(input));
    }
};

class stereo_width_processor {
public:
    void configure(
        double sample_rate,
        float width,
        float master_strength
    ) noexcept {
        reset();

        side_gain_ = effective_width_side_gain(
            width,
            master_strength
        );

        if (!std::isfinite(sample_rate) || sample_rate <= 0.0) {
            lowpass_coefficient_ = 0.0;
            return;
        }

        const double frequency = std::clamp(
            width_low_frequency_protection_hz,
            10.0,
            sample_rate * 0.45
        );

        lowpass_coefficient_ =
            std::exp((-two_pi * frequency) / sample_rate);

        if (!std::isfinite(lowpass_coefficient_)) {
            lowpass_coefficient_ = 0.0;
        }

        lowpass_coefficient_ =
            std::clamp(lowpass_coefficient_, 0.0, 1.0);
    }

    void reset() noexcept {
        low_side_state_ = 0.0;
    }

    void process(audio_sample& left, audio_sample& right) noexcept {
        const double input_left = static_cast<double>(left);
        const double input_right = static_cast<double>(right);

        if (!std::isfinite(input_left) || !std::isfinite(input_right)) {
            reset();
            return;
        }

        const double mid = (input_left + input_right) * 0.5;
        const double side = (input_left - input_right) * 0.5;

        const double next_low_side =
            ((1.0 - lowpass_coefficient_) * side) +
            (lowpass_coefficient_ * low_side_state_);

        const double high_side = side - next_low_side;
        const double widened_side =
            next_low_side + (high_side * side_gain_);

        const double output_left = mid + widened_side;
        const double output_right = mid - widened_side;

        if (!std::isfinite(next_low_side) ||
            !std::isfinite(output_left) ||
            !std::isfinite(output_right)) {
            reset();
            return;
        }

        low_side_state_ = next_low_side;
        left = static_cast<audio_sample>(output_left);
        right = static_cast<audio_sample>(output_right);
    }

private:
    double side_gain_ = 1.0;
    double lowpass_coefficient_ = 0.0;
    double low_side_state_ = 0.0;
};

class ambience_processor {
public:
    void configure(
        double sample_rate,
        unsigned channels,
        float ambience,
        float master_strength
    ) {
        channels_ = channels;
        wet_mix_ = effective_ambience_wet_mix(
            ambience,
            master_strength
        );
        dry_gain_ = 1.0 -
            effective_ambience_dry_reduction(
                ambience,
                master_strength
            );

        if (!std::isfinite(sample_rate) ||
            sample_rate <= 0.0 ||
            channels == 0 ||
            wet_mix_ <= 0.0) {
            clear_configuration();
            return;
        }

        first_delay_ = milliseconds_to_samples(
            sample_rate,
            ambience_first_reflection_ms
        );
        second_delay_ = milliseconds_to_samples(
            sample_rate,
            ambience_second_reflection_ms
        );

        buffer_size_ = std::max<t_size>(
            second_delay_ + 1,
            static_cast<t_size>(2)
        );

        delay_buffer_.assign(
            buffer_size_ * static_cast<t_size>(channels_),
            static_cast<audio_sample>(0)
        );
        write_index_ = 0;
    }

    void reset() noexcept {
        std::fill(
            delay_buffer_.begin(),
            delay_buffer_.end(),
            static_cast<audio_sample>(0)
        );
        write_index_ = 0;
    }

    void process_frame(audio_sample* frame, unsigned channels) noexcept {
        if (frame == nullptr ||
            wet_mix_ <= 0.0 ||
            channels == 0 ||
            channels != channels_ ||
            buffer_size_ == 0 ||
            delay_buffer_.empty()) {
            return;
        }

        const t_size first_read =
            (write_index_ + buffer_size_ - first_delay_) % buffer_size_;
        const t_size second_read =
            (write_index_ + buffer_size_ - second_delay_) % buffer_size_;

        for (unsigned channel = 0; channel < channels_; ++channel) {
            const double input = static_cast<double>(frame[channel]);

            if (!std::isfinite(input)) {
                reset();
                return;
            }

            const t_size channel_base =
                static_cast<t_size>(channel) * buffer_size_;

            const double same_first = static_cast<double>(
                delay_buffer_[channel_base + first_read]
            );
            const double same_second = static_cast<double>(
                delay_buffer_[channel_base + second_read]
            );

            double cross_second = 0.0;

            if (channels_ >= 2 && channel < 2) {
                const unsigned other_channel = channel == 0 ? 1 : 0;
                const t_size other_base =
                    static_cast<t_size>(other_channel) * buffer_size_;

                cross_second = static_cast<double>(
                    delay_buffer_[other_base + second_read]
                );
            }

            const double reflection =
                (same_first * 0.58) +
                (same_second * 0.27) +
                (cross_second * 0.15);

            const double output =
                (input * dry_gain_) +
                (reflection * wet_mix_);

            if (!std::isfinite(output)) {
                reset();
                return;
            }

            delay_buffer_[channel_base + write_index_] =
                static_cast<audio_sample>(input);
            frame[channel] = static_cast<audio_sample>(output);
        }

        write_index_ = (write_index_ + 1) % buffer_size_;
    }

private:
    static t_size milliseconds_to_samples(
        double sample_rate,
        double milliseconds
    ) noexcept {
        const double samples =
            sample_rate * milliseconds * 0.001;

        if (!std::isfinite(samples) || samples < 1.0) {
            return 1;
        }

        return static_cast<t_size>(std::lround(samples));
    }

    void clear_configuration() noexcept {
        channels_ = 0;
        buffer_size_ = 0;
        first_delay_ = 0;
        second_delay_ = 0;
        write_index_ = 0;
        wet_mix_ = 0.0;
        dry_gain_ = 1.0;
        delay_buffer_.clear();
    }

    unsigned channels_ = 0;
    t_size buffer_size_ = 0;
    t_size first_delay_ = 0;
    t_size second_delay_ = 0;
    t_size write_index_ = 0;

    double wet_mix_ = 0.0;
    double dry_gain_ = 1.0;

    std::vector<audio_sample> delay_buffer_;
};



class level_match_processor {
public:
    void configure(double sample_rate, bool enabled) noexcept {
        sample_rate_ = sample_rate;
        enabled_ = enabled;
        reset();
    }

    void reset() noexcept {
        smoothed_input_power_ = 0.0;
        smoothed_output_power_ = 0.0;
        current_gain_ = 1.0;
        initialized_ = false;
        gain_initialized_ = false;
    }

    double measure_power(
        const audio_sample* data,
        t_size sample_count
    ) const noexcept {
        if (data == nullptr || sample_count == 0) {
            return 0.0;
        }

        double sum = 0.0;
        t_size valid_samples = 0;

        for (t_size index = 0; index < sample_count; ++index) {
            const double value = static_cast<double>(data[index]);

            if (!std::isfinite(value)) {
                continue;
            }

            sum += value * value;
            ++valid_samples;
        }

        if (valid_samples == 0) {
            return 0.0;
        }

        return sum / static_cast<double>(valid_samples);
    }

    void process(
        audio_sample* data,
        t_size frames,
        unsigned channels,
        double input_power
    ) noexcept {
        if (!enabled_ ||
            data == nullptr ||
            frames == 0 ||
            channels == 0 ||
            !std::isfinite(sample_rate_) ||
            sample_rate_ <= 0.0 ||
            !std::isfinite(input_power) ||
            input_power <= level_match_silence_power) {
            return;
        }

        const t_size sample_count =
            frames * static_cast<t_size>(channels);
        const double output_power =
            measure_power(data, sample_count);

        if (!std::isfinite(output_power) ||
            output_power <= level_match_silence_power) {
            return;
        }

        const double elapsed_seconds =
            static_cast<double>(frames) / sample_rate_;
        const double meter_coefficient = std::exp(
            -elapsed_seconds / level_match_meter_seconds
        );

        if (!initialized_) {
            smoothed_input_power_ = input_power;
            smoothed_output_power_ = output_power;
            initialized_ = true;
        } else {
            smoothed_input_power_ =
                input_power +
                ((smoothed_input_power_ - input_power) *
                 meter_coefficient);
            smoothed_output_power_ =
                output_power +
                ((smoothed_output_power_ - output_power) *
                 meter_coefficient);
        }

        if (smoothed_input_power_ <= level_match_silence_power ||
            smoothed_output_power_ <= level_match_silence_power) {
            return;
        }

        double target_gain = std::sqrt(
            smoothed_input_power_ / smoothed_output_power_
        );

        // Level matching only attenuates enhancement gain.
        // It never boosts the processed signal above unity.
        target_gain = std::clamp(
            target_gain,
            level_match_minimum_gain,
            1.0
        );

        if (!std::isfinite(target_gain)) {
            return;
        }

        if (current_gain_ == 1.0 && !gain_initialized_) {
            current_gain_ = target_gain;
            gain_initialized_ = true;
        } else {
            const double time_constant =
                target_gain < current_gain_
                    ? level_match_attack_seconds
                    : level_match_release_seconds;

            const double gain_coefficient = std::exp(
                -elapsed_seconds / time_constant
            );

            current_gain_ =
                target_gain +
                ((current_gain_ - target_gain) * gain_coefficient);

            current_gain_ = std::clamp(
                current_gain_,
                level_match_minimum_gain,
                1.0
            );
        }

        if (current_gain_ >= 0.999999) {
            return;
        }

        for (t_size index = 0; index < sample_count; ++index) {
            const double value = static_cast<double>(data[index]);

            if (!std::isfinite(value)) {
                data[index] = static_cast<audio_sample>(0);
                continue;
            }

            data[index] = static_cast<audio_sample>(
                value * current_gain_
            );
        }
    }

private:
    bool enabled_ = true;
    bool initialized_ = false;
    bool gain_initialized_ = false;

    double sample_rate_ = 0.0;
    double smoothed_input_power_ = 0.0;
    double smoothed_output_power_ = 0.0;
    double current_gain_ = 1.0;
};

class auto_headroom_processor {
public:
    void configure(double sample_rate, bool enabled) noexcept {
        enabled_ = enabled;
        sample_rate_ = sample_rate;
        reset();
    }

    void reset() noexcept {
        current_gain_ = 1.0;
    }

    void process(
        audio_sample* data,
        t_size frames,
        unsigned channels
    ) noexcept {
        if (!enabled_ ||
            data == nullptr ||
            frames == 0 ||
            channels == 0 ||
            !std::isfinite(sample_rate_) ||
            sample_rate_ <= 0.0) {
            return;
        }

        const t_size sample_count =
            frames * static_cast<t_size>(channels);

        double peak = 0.0;

        for (t_size index = 0; index < sample_count; ++index) {
            const double value = static_cast<double>(data[index]);

            if (!std::isfinite(value)) {
                data[index] = static_cast<audio_sample>(0);
                continue;
            }

            peak = (std::max)(peak, std::abs(value));
        }

        double target_gain = 1.0;

        if (peak > auto_headroom_ceiling) {
            target_gain = auto_headroom_ceiling / peak;
        }

        target_gain = std::clamp(target_gain, 0.0, 1.0);

        if (target_gain < current_gain_) {
            current_gain_ = target_gain;
        } else {
            const double elapsed_seconds =
                static_cast<double>(frames) / sample_rate_;
            const double release_coefficient = std::exp(
                -elapsed_seconds / auto_headroom_release_seconds
            );

            current_gain_ =
                target_gain +
                ((current_gain_ - target_gain) * release_coefficient);

            current_gain_ = std::clamp(
                current_gain_,
                0.0,
                target_gain
            );
        }

        if (current_gain_ >= 0.999999) {
            return;
        }

        for (t_size index = 0; index < sample_count; ++index) {
            data[index] = static_cast<audio_sample>(
                static_cast<double>(data[index]) * current_gain_
            );
        }
    }

private:
    bool enabled_ = true;
    double sample_rate_ = 0.0;
    double current_gain_ = 1.0;
};

class dsp_sonic_refiner : public dsp_impl_base {
public:
    explicit dsp_sonic_refiner(const dsp_preset& preset)
        : settings_(sonic_refiner::parse_preset(preset)) {
    }

    static GUID g_get_guid() {
        return sonic_refiner::guid;
    }

    static void g_get_name(pfc::string_base& out) {
        out = "Sonic Refiner";
    }

    static bool g_get_default_preset(dsp_preset& out) {
        sonic_refiner::make_preset(sonic_refiner::settings{}, out);
        return true;
    }

#ifdef _WIN32
    static void g_show_config_popup(
        const dsp_preset& preset,
        HWND parent,
        dsp_preset_edit_callback& callback
    ) {
        run_config_popup(preset, parent, callback);
    }
#endif

    static bool g_have_config_popup() {
        return true;
    }

    bool on_chunk(audio_chunk* chunk, abort_callback& abort) override {
        abort.check();

        const bool enhancement_active =
            settings_.master_strength > 0.0f &&
            (settings_.depth > 0.0f ||
             settings_.clarity > 0.0f ||
             settings_.width > 0.0f ||
             settings_.ambience > 0.0f);

        if (chunk == nullptr ||
            chunk->is_empty() ||
            !settings_.enabled ||
            (!enhancement_active &&
             std::abs(settings_.output_gain_db) <= 0.0001f)) {
            return true;
        }

        const unsigned sample_rate = chunk->get_srate();
        const unsigned channels = chunk->get_channels();

        if (sample_rate == 0 || channels == 0) {
            return true;
        }

        if (sample_rate != sample_rate_ || channels != channels_) {
            configure_processors(sample_rate, channels);
        }

        audio_sample* data = chunk->get_data();
        const t_size frames = chunk->get_sample_count();

        if (data == nullptr || filters_.size() != channels) {
            return true;
        }

        const t_size sample_count =
            frames * static_cast<t_size>(channels);
        const double input_power =
            settings_.level_matched_bypass
                ? level_match_processor_.measure_power(
                    data,
                    sample_count
                )
                : 0.0;

        for (t_size frame = 0; frame < frames; ++frame) {
            const t_size frame_offset = frame * channels;

            for (unsigned channel = 0; channel < channels; ++channel) {
                const t_size index = frame_offset + channel;
                data[index] = filters_[channel].process(data[index]);
            }

            if (channels >= 2 &&
                settings_.master_strength > 0.0f &&
                settings_.width > 0.0f) {
                audio_sample& left = data[frame_offset];
                audio_sample& right = data[frame_offset + 1];
                width_processor_.process(left, right);
            }

            if (settings_.master_strength > 0.0f &&
                settings_.ambience > 0.0f) {
                ambience_processor_.process_frame(
                    data + frame_offset,
                    channels
                );
            }
        }

        if (settings_.level_matched_bypass) {
            level_match_processor_.process(
                data,
                frames,
                channels,
                input_power
            );
        }

        apply_output_gain(
            data,
            sample_count,
            settings_.output_gain_db
        );

        if (settings_.auto_headroom) {
            auto_headroom_processor_.process(
                data,
                frames,
                channels
            );
        }

        return true;
    }

    void on_endofplayback(abort_callback&) override {
        reset_processors();
    }

    void on_endoftrack(abort_callback&) override {
    }

    void flush() override {
        reset_processors();
    }

    double get_latency() override {
        return 0.0;
    }

    bool need_track_change_mark() override {
        return false;
    }

private:
    void configure_processors(unsigned sample_rate, unsigned channels) {
        sample_rate_ = sample_rate;
        channels_ = channels;

        filters_.assign(channels, channel_filters{});

        const double depth_gain_db = effective_depth_gain_db(
            settings_.depth,
            settings_.master_strength
        );
        const double clarity_gain_db = effective_clarity_gain_db(
            settings_.clarity,
            settings_.master_strength
        );

        for (auto& filters : filters_) {
            filters.depth.set_low_shelf(
                static_cast<double>(sample_rate),
                depth_shelf_frequency_hz,
                depth_gain_db
            );

            filters.clarity.set_high_shelf(
                static_cast<double>(sample_rate),
                clarity_shelf_frequency_hz,
                clarity_gain_db
            );
        }

        width_processor_.configure(
            static_cast<double>(sample_rate),
            settings_.width,
            settings_.master_strength
        );

        ambience_processor_.configure(
            static_cast<double>(sample_rate),
            channels,
            settings_.ambience,
            settings_.master_strength
        );

        level_match_processor_.configure(
            static_cast<double>(sample_rate),
            settings_.level_matched_bypass
        );

        auto_headroom_processor_.configure(
            static_cast<double>(sample_rate),
            settings_.auto_headroom
        );
    }

    void reset_processors() noexcept {
        for (auto& filters : filters_) {
            filters.reset();
        }

        width_processor_.reset();
        ambience_processor_.reset();
        level_match_processor_.reset();
        auto_headroom_processor_.reset();
    }

    sonic_refiner::settings settings_;
    unsigned sample_rate_ = 0;
    unsigned channels_ = 0;
    std::vector<channel_filters> filters_;
    stereo_width_processor width_processor_;
    ambience_processor ambience_processor_;
    level_match_processor level_match_processor_;
    auto_headroom_processor auto_headroom_processor_;
};

dsp_factory_t<dsp_sonic_refiner> g_dsp_factory;

#ifdef _WIN32

#pragma comment(lib, "Comdlg32.lib")

constexpr GUID guid_user_presets = {
    0x245f4c3a, 0x9b9e, 0x4f61,
    { 0x91, 0x6b, 0x2a, 0x77, 0x3e, 0x45, 0x19, 0xd2 }
};

constexpr t_size maximum_user_presets = 20;
constexpr t_size maximum_preset_name_characters = 40;

cfg_string g_user_presets(guid_user_presets, "");


constexpr GUID guid_ui_language = {
    0x7c189419, 0xe2e1, 0x4a1d,
    { 0xa5, 0x35, 0x1d, 0x63, 0xa4, 0x6c, 0x28, 0xf1 }
};

enum class ui_language : t_int32 {
    japanese = 0,
    english = 1
};

cfg_string g_ui_language(guid_ui_language, "");

// v0.4.0: modeless direct settings window opened from Playback.
// These HWNDs are runtime-only and are never serialized.
HWND g_direct_sonic_refiner_settings_window = nullptr;
HWND g_standard_sonic_refiner_settings_window = nullptr;
constexpr UINT wm_sonic_refiner_direct_chain_invalidated = WM_APP + 0x04A1;

bool is_english(ui_language language) noexcept {
    return language == ui_language::english;
}

const wchar_t* localized(
    ui_language language,
    const wchar_t* japanese,
    const wchar_t* english
) noexcept {
    return is_english(language) ? english : japanese;
}

const char* localized_utf8(
    ui_language language,
    const char* japanese,
    const char* english
) noexcept {
    return is_english(language) ? english : japanese;
}

ui_language detect_default_ui_language() noexcept {
    const LANGID language_id = ::GetUserDefaultUILanguage();
    return PRIMARYLANGID(language_id) == LANG_JAPANESE
        ? ui_language::japanese
        : ui_language::english;
}

ui_language load_ui_language() noexcept {
    const char* saved = g_ui_language.get_ptr();

    if (saved != nullptr && std::strcmp(saved, "ja") == 0) {
        return ui_language::japanese;
    }

    if (saved != nullptr && std::strcmp(saved, "en") == 0) {
        return ui_language::english;
    }

    const ui_language detected = detect_default_ui_language();
    g_ui_language = is_english(detected) ? "en" : "ja";
    return detected;
}

void save_ui_language(ui_language language) noexcept {
    g_ui_language = is_english(language) ? "en" : "ja";
}

struct user_preset {
    pfc::string8 name;
    sonic_refiner::settings value;
};

struct ab_comparison_value {
    float depth = 55.0f;
    float clarity = 45.0f;
    float width = 50.0f;
    float ambience = 40.0f;
    float master_strength = 100.0f;
};

struct ab_comparison_slot {
    bool has_value = false;
    ab_comparison_value value;
};

ab_comparison_slot g_ab_slot_a;
ab_comparison_slot g_ab_slot_b;

ab_comparison_value capture_ab_comparison_value(
    const sonic_refiner::settings& settings
) noexcept {
    return {
        settings.depth,
        settings.clarity,
        settings.width,
        settings.ambience,
        settings.master_strength
    };
}

void apply_ab_comparison_value(
    const ab_comparison_value& value,
    sonic_refiner::settings& settings
) noexcept {
    settings.depth = value.depth;
    settings.clarity = value.clarity;
    settings.width = value.width;
    settings.ambience = value.ambience;
    settings.master_strength = value.master_strength;
    settings = sonic_refiner::sanitize(settings);
}

struct built_in_preset {
    const wchar_t* name_japanese;
    const wchar_t* name_english;
    sonic_refiner::settings value;
};

const built_in_preset g_built_in_presets[] = {
    {
        L"標準", L"Standard",
        { 55.0f, 45.0f, 50.0f, 40.0f, 100.0f, 0.0f, true, true, true }
    },
    {
        L"低域強化", L"Bass Boost",
        { 90.0f, 30.0f, 30.0f, 25.0f, 100.0f, 0.0f, true, true, true }
    },
    {
        L"ボーカル重視", L"Vocal Focus",
        { 35.0f, 90.0f, 25.0f, 25.0f, 100.0f, 0.0f, true, true, true }
    },
    {
        L"ワイド", L"Wide",
        { 40.0f, 45.0f, 90.0f, 30.0f, 100.0f, 0.0f, true, true, true }
    },
    {
        L"ライブ", L"Live",
        { 55.0f, 50.0f, 70.0f, 80.0f, 100.0f, 0.0f, true, true, true }
    },
    {
        L"ヘッドホン", L"Headphones",
        { 45.0f, 50.0f, 65.0f, 40.0f, 100.0f, 0.0f, true, true, true }
    },
    {
        L"超低域強化", L"Extreme Bass",
        { 100.0f, 35.0f, 30.0f, 20.0f, 100.0f, 0.0f, true, true, true }
    },
    {
        L"超明瞭", L"Extreme Clarity",
        { 30.0f, 100.0f, 25.0f, 20.0f, 100.0f, 0.0f, true, true, true }
    },
    {
        L"超ワイド", L"Extreme Wide",
        { 30.0f, 40.0f, 100.0f, 25.0f, 100.0f, 0.0f, true, true, true }
    },
    {
        L"大ホール", L"Large Hall",
        { 45.0f, 45.0f, 75.0f, 100.0f, 100.0f, 0.0f, true, true, true }
    },
    {
        L"フルブースト", L"Full Boost",
        { 100.0f, 100.0f, 100.0f, 100.0f, 100.0f, 0.0f, true, true, true }
    },
};

const wchar_t* built_in_preset_name(
    const built_in_preset& preset,
    ui_language language
) noexcept {
    return is_english(language)
        ? preset.name_english
        : preset.name_japanese;
}

constexpr t_size built_in_preset_count =
    sizeof(g_built_in_presets) /
    sizeof(g_built_in_presets[0]);

int hex_value(char value) noexcept {
    if (value >= '0' && value <= '9') {
        return value - '0';
    }

    if (value >= 'a' && value <= 'f') {
        return 10 + (value - 'a');
    }

    if (value >= 'A' && value <= 'F') {
        return 10 + (value - 'A');
    }

    return -1;
}

std::string encode_preset_name(const char* value) {
    static constexpr char digits[] = "0123456789ABCDEF";

    std::string encoded;

    if (value == nullptr) {
        return encoded;
    }

    const auto* bytes =
        reinterpret_cast<const unsigned char*>(value);

    while (*bytes != 0) {
        encoded.push_back(digits[(*bytes >> 4) & 0x0f]);
        encoded.push_back(digits[*bytes & 0x0f]);
        ++bytes;
    }

    return encoded;
}

bool decode_preset_name(
    const std::string& encoded,
    pfc::string8& output
) {
    if (encoded.empty() || (encoded.size() % 2) != 0) {
        return false;
    }

    std::string decoded;
    decoded.reserve(encoded.size() / 2);

    for (std::size_t index = 0;
         index < encoded.size();
         index += 2) {
        const int high = hex_value(encoded[index]);
        const int low = hex_value(encoded[index + 1]);

        if (high < 0 || low < 0) {
            return false;
        }

        decoded.push_back(
            static_cast<char>((high << 4) | low)
        );
    }

    if (decoded.empty() ||
        decoded.find('\0') != std::string::npos) {
        return false;
    }

    output.set_string(decoded.c_str(), decoded.size());
    return true;
}

std::vector<std::string> split_tab_fields(
    const std::string& line
) {
    std::vector<std::string> fields;
    std::size_t begin = 0;

    while (true) {
        const std::size_t separator = line.find('\t', begin);

        if (separator == std::string::npos) {
            fields.push_back(line.substr(begin));
            break;
        }

        fields.push_back(
            line.substr(begin, separator - begin)
        );
        begin = separator + 1;
    }

    return fields;
}

bool parse_integer(
    const std::string& text,
    int& output
) noexcept {
    if (text.empty()) {
        return false;
    }

    char* end = nullptr;
    const long value = std::strtol(text.c_str(), &end, 10);

    if (end == text.c_str() ||
        end == nullptr ||
        *end != '\0') {
        return false;
    }

    output = static_cast<int>(value);
    return true;
}

bool is_boolean_integer(int value) noexcept {
    return value == 0 || value == 1;
}

std::string serialize_user_presets(
    const std::vector<user_preset>& presets
) {
    std::ostringstream stream;
    stream << "SRP3\n";

    const std::size_t count = (std::min)(
        presets.size(),
        static_cast<std::size_t>(maximum_user_presets)
    );

    for (std::size_t index = 0; index < count; ++index) {
        const user_preset& preset = presets[index];
        const sonic_refiner::settings value =
            sonic_refiner::sanitize(preset.value);

        stream
            << encode_preset_name(preset.name.get_ptr())
            << '\t'
            << static_cast<int>(std::lround(value.depth))
            << '\t'
            << static_cast<int>(std::lround(value.clarity))
            << '\t'
            << static_cast<int>(std::lround(value.width))
            << '\t'
            << static_cast<int>(std::lround(value.ambience))
            << '\t'
            << static_cast<int>(
                std::lround(value.master_strength)
            )
            << '\t'
            << static_cast<int>(
                std::lround(value.output_gain_db * 2.0f)
            )
            << '\t'
            << (value.auto_headroom ? 1 : 0)
            << '\t'
            << (value.level_matched_bypass ? 1 : 0)
            << '\t'
            << (value.enabled ? 1 : 0)
            << '\n';
    }

    return stream.str();
}

bool parse_user_presets(
    const std::string& serialized,
    std::vector<user_preset>& presets,
    bool strict
) {
    presets.clear();

    std::istringstream stream(serialized);
    std::string line;

    if (!std::getline(stream, line)) {
        return false;
    }

    if (!line.empty() && line.back() == '\r') {
        line.pop_back();
    }

    const bool srp1_format = line == "SRP1";
    const bool srp2_format = line == "SRP2";
    const bool srp3_format = line == "SRP3";

    if (!srp1_format && !srp2_format && !srp3_format) {
        return false;
    }

    while (std::getline(stream, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        if (line.empty()) {
            continue;
        }

        if (presets.size() >= maximum_user_presets) {
            return strict ? false : true;
        }

        const std::vector<std::string> fields =
            split_tab_fields(line);
        const std::size_t expected_fields =
            srp3_format ? 10 : (srp2_format ? 9 : 8);

        if (fields.size() != expected_fields) {
            if (strict) {
                return false;
            }
            continue;
        }

        user_preset preset;

        if (!decode_preset_name(fields[0], preset.name)) {
            if (strict) {
                return false;
            }
            continue;
        }

        int depth = 0;
        int clarity = 0;
        int width = 0;
        int ambience = 0;
        int master_strength = 100;
        int output_gain_steps = 0;
        int auto_headroom = 0;
        int level_match = 0;
        int enabled = 0;

        bool parsed =
            parse_integer(fields[1], depth) &&
            parse_integer(fields[2], clarity) &&
            parse_integer(fields[3], width) &&
            parse_integer(fields[4], ambience);

        if (srp3_format) {
            parsed = parsed &&
                parse_integer(fields[5], master_strength) &&
                parse_integer(fields[6], output_gain_steps) &&
                parse_integer(fields[7], auto_headroom) &&
                parse_integer(fields[8], level_match) &&
                parse_integer(fields[9], enabled);
        } else if (srp2_format) {
            parsed = parsed &&
                parse_integer(fields[5], output_gain_steps) &&
                parse_integer(fields[6], auto_headroom) &&
                parse_integer(fields[7], level_match) &&
                parse_integer(fields[8], enabled);
        } else {
            parsed = parsed &&
                parse_integer(fields[5], auto_headroom) &&
                parse_integer(fields[6], level_match) &&
                parse_integer(fields[7], enabled);
        }

        const bool values_valid =
            parsed &&
            depth >= 0 && depth <= 100 &&
            clarity >= 0 && clarity <= 100 &&
            width >= 0 && width <= 100 &&
            ambience >= 0 && ambience <= 100 &&
            (!srp3_format ||
                (master_strength >= 0 &&
                 master_strength <= 100)) &&
            (srp1_format ||
                (output_gain_steps >= -24 &&
                 output_gain_steps <= 12)) &&
            is_boolean_integer(auto_headroom) &&
            is_boolean_integer(level_match) &&
            is_boolean_integer(enabled);

        if (!values_valid) {
            if (strict) {
                return false;
            }
            continue;
        }

        preset.value.depth = static_cast<float>(depth);
        preset.value.clarity = static_cast<float>(clarity);
        preset.value.width = static_cast<float>(width);
        preset.value.ambience = static_cast<float>(ambience);
        preset.value.master_strength = srp3_format
            ? static_cast<float>(master_strength)
            : 100.0f;
        preset.value.output_gain_db = srp1_format
            ? 0.0f
            : static_cast<float>(output_gain_steps) * 0.5f;
        preset.value.auto_headroom = auto_headroom != 0;
        preset.value.level_matched_bypass = level_match != 0;
        preset.value.enabled = enabled != 0;
        preset.value = sonic_refiner::sanitize(preset.value);

        bool duplicate = false;

        for (const auto& existing : presets) {
            if (std::strcmp(
                    existing.name.get_ptr(),
                    preset.name.get_ptr()
                ) == 0) {
                duplicate = true;
                break;
            }
        }

        if (duplicate) {
            if (strict) {
                return false;
            }
            continue;
        }

        presets.push_back(preset);
    }

    return true;
}

std::vector<user_preset> load_user_presets() {
    std::vector<user_preset> presets;

    parse_user_presets(
        g_user_presets.get_ptr(),
        presets,
        false
    );

    return presets;
}

void save_user_presets(
    const std::vector<user_preset>& presets
) {
    const std::string serialized =
        serialize_user_presets(presets);

    g_user_presets = serialized.c_str();
}

std::string make_preset_backup(
    const std::vector<user_preset>& presets
) {
    return std::string("SONIC_REFINER_PRESET_BACKUP_V1\n") +
        serialize_user_presets(presets);
}

bool parse_preset_backup(
    std::string backup,
    std::vector<user_preset>& presets
) {
    if (backup.size() >= 3 &&
        static_cast<unsigned char>(backup[0]) == 0xef &&
        static_cast<unsigned char>(backup[1]) == 0xbb &&
        static_cast<unsigned char>(backup[2]) == 0xbf) {
        backup.erase(0, 3);
    }

    constexpr char magic[] =
        "SONIC_REFINER_PRESET_BACKUP_V1\n";
    constexpr std::size_t magic_length =
        sizeof(magic) - 1;

    if (backup.size() < magic_length ||
        backup.compare(0, magic_length, magic) != 0) {
        return false;
    }

    return parse_user_presets(
        backup.substr(magic_length),
        presets,
        true
    );
}

bool choose_preset_export_path(
    HWND parent,
    ui_language language,
    std::wstring& path
) {
    wchar_t file_name[32768] =
        L"Sonic_Refiner_User_Presets.srpbackup";

    constexpr wchar_t japanese_filter[] =
        L"Sonic Refiner プリセット (*.srpbackup)\0"
        L"*.srpbackup\0"
        L"すべてのファイル (*.*)\0"
        L"*.*\0\0";
    constexpr wchar_t english_filter[] =
        L"Sonic Refiner Presets (*.srpbackup)\0"
        L"*.srpbackup\0"
        L"All Files (*.*)\0"
        L"*.*\0\0";

    OPENFILENAMEW dialog = {};
    dialog.lStructSize = sizeof(dialog);
    dialog.hwndOwner = parent;
    dialog.lpstrFilter = is_english(language)
        ? english_filter
        : japanese_filter;
    dialog.lpstrFile = file_name;
    dialog.nMaxFile = static_cast<DWORD>(_countof(file_name));
    dialog.lpstrDefExt = L"srpbackup";
    dialog.lpstrTitle = localized(
        language,
        L"任意プリセットを書き出す",
        L"Export User Presets"
    );
    dialog.Flags =
        OFN_OVERWRITEPROMPT |
        OFN_PATHMUSTEXIST |
        OFN_HIDEREADONLY |
        OFN_NOCHANGEDIR;

    if (!::GetSaveFileNameW(&dialog)) {
        return false;
    }

    path = file_name;
    return true;
}

bool choose_preset_import_path(
    HWND parent,
    ui_language language,
    std::wstring& path
) {
    wchar_t file_name[32768] = {};

    constexpr wchar_t japanese_filter[] =
        L"Sonic Refiner プリセット (*.srpbackup)\0"
        L"*.srpbackup\0"
        L"すべてのファイル (*.*)\0"
        L"*.*\0\0";
    constexpr wchar_t english_filter[] =
        L"Sonic Refiner Presets (*.srpbackup)\0"
        L"*.srpbackup\0"
        L"All Files (*.*)\0"
        L"*.*\0\0";

    OPENFILENAMEW dialog = {};
    dialog.lStructSize = sizeof(dialog);
    dialog.hwndOwner = parent;
    dialog.lpstrFilter = is_english(language)
        ? english_filter
        : japanese_filter;
    dialog.lpstrFile = file_name;
    dialog.nMaxFile = static_cast<DWORD>(_countof(file_name));
    dialog.lpstrDefExt = L"srpbackup";
    dialog.lpstrTitle = localized(
        language,
        L"任意プリセットを読み込む",
        L"Import User Presets"
    );
    dialog.Flags =
        OFN_FILEMUSTEXIST |
        OFN_PATHMUSTEXIST |
        OFN_HIDEREADONLY |
        OFN_NOCHANGEDIR;

    if (!::GetOpenFileNameW(&dialog)) {
        return false;
    }

    path = file_name;
    return true;
}

bool write_preset_backup_file(
    const std::wstring& path,
    const std::string& data
) noexcept {
    if (data.empty() || data.size() > 1024 * 1024) {
        return false;
    }

    HANDLE file = ::CreateFileW(
        path.c_str(),
        GENERIC_WRITE,
        0,
        nullptr,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        nullptr
    );

    if (file == INVALID_HANDLE_VALUE) {
        return false;
    }

    DWORD bytes_written = 0;
    const BOOL written = ::WriteFile(
        file,
        data.data(),
        static_cast<DWORD>(data.size()),
        &bytes_written,
        nullptr
    );

    const BOOL closed = ::CloseHandle(file);

    return written &&
        closed &&
        bytes_written == static_cast<DWORD>(data.size());
}

bool read_preset_backup_file(
    const std::wstring& path,
    std::string& data
) noexcept {
    data.clear();

    HANDLE file = ::CreateFileW(
        path.c_str(),
        GENERIC_READ,
        FILE_SHARE_READ,
        nullptr,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        nullptr
    );

    if (file == INVALID_HANDLE_VALUE) {
        return false;
    }

    LARGE_INTEGER size = {};

    if (!::GetFileSizeEx(file, &size) ||
        size.QuadPart <= 0 ||
        size.QuadPart > 1024 * 1024) {
        ::CloseHandle(file);
        return false;
    }

    data.resize(static_cast<std::size_t>(size.QuadPart));

    DWORD bytes_read = 0;
    const BOOL read = ::ReadFile(
        file,
        data.data(),
        static_cast<DWORD>(data.size()),
        &bytes_read,
        nullptr
    );

    const BOOL closed = ::CloseHandle(file);

    if (!read ||
        !closed ||
        bytes_read != static_cast<DWORD>(data.size())) {
        data.clear();
        return false;
    }

    return true;
}

int find_user_preset(
    const std::vector<user_preset>& presets,
    const char* name
) noexcept {
    if (name == nullptr) {
        return -1;
    }

    for (std::size_t index = 0;
         index < presets.size();
         ++index) {
        if (std::strcmp(
                presets[index].name.get_ptr(),
                name
            ) == 0) {
            return static_cast<int>(index);
        }
    }

    return -1;
}

std::wstring preset_name_to_wide(const char* name) {
    pfc::stringcvt::string_wide_from_utf8 converted(
        name != nullptr ? name : ""
    );

    return converted.get_ptr();
}

class preset_name_dialog final :
    public CDialogImpl<preset_name_dialog> {
public:
    preset_name_dialog(
        const char* initial_name,
        ui_language language
    )
        : initial_name_(
            initial_name != nullptr ? initial_name : ""
        ),
          language_(language) {
    }

    enum { IDD = IDD_PRESET_NAME };

    BEGIN_MSG_MAP_EX(preset_name_dialog)
        MSG_WM_INITDIALOG(on_init_dialog)
        COMMAND_HANDLER_EX(IDOK, BN_CLICKED, on_button)
        COMMAND_HANDLER_EX(IDCANCEL, BN_CLICKED, on_button)
    END_MSG_MAP()

    const pfc::string8& result() const noexcept {
        return result_;
    }

private:
    BOOL on_init_dialog(CWindow, LPARAM) {
        dark_mode_.AddDialogWithControls(m_hWnd);

        ::SetWindowTextW(
            m_hWnd,
            localized(
                language_,
                L"任意プリセットを保存",
                L"Save User Preset"
            )
        );
        ::SetDlgItemTextW(
            m_hWnd,
            IDC_PRESET_NAME_LABEL,
            localized(
                language_,
                L"プリセット名（40文字以内）",
                L"Preset name (up to 40 characters)"
            )
        );
        ::SetDlgItemTextW(m_hWnd, IDOK, L"OK");
        ::SetDlgItemTextW(
            m_hWnd,
            IDCANCEL,
            localized(language_, L"キャンセル", L"Cancel")
        );

        const std::wstring initial =
            preset_name_to_wide(initial_name_.get_ptr());

        ::SetDlgItemTextW(
            m_hWnd,
            IDC_PRESET_NAME_EDIT,
            initial.c_str()
        );

        ::SendDlgItemMessageW(
            m_hWnd,
            IDC_PRESET_NAME_EDIT,
            EM_LIMITTEXT,
            static_cast<WPARAM>(
                maximum_preset_name_characters
            ),
            0
        );

        CWindow edit = GetDlgItem(IDC_PRESET_NAME_EDIT);
        edit.SetFocus();
        edit.SendMessage(
            EM_SETSEL,
            0,
            static_cast<LPARAM>(-1)
        );

        return FALSE;
    }

    void on_button(UINT, int id, CWindow) {
        if (id == IDCANCEL) {
            EndDialog(IDCANCEL);
            return;
        }

        wchar_t buffer[
            maximum_preset_name_characters + 1
        ] = {};

        ::GetDlgItemTextW(
            m_hWnd,
            IDC_PRESET_NAME_EDIT,
            buffer,
            static_cast<int>(
                maximum_preset_name_characters + 1
            )
        );

        std::wstring name(buffer);

        while (!name.empty() &&
               std::iswspace(name.front())) {
            name.erase(name.begin());
        }

        while (!name.empty() &&
               std::iswspace(name.back())) {
            name.pop_back();
        }

        if (name.empty()) {
            ::MessageBoxW(
                m_hWnd,
                localized(
                    language_,
                    L"プリセット名を入力してください。",
                    L"Enter a preset name."
                ),
                L"Sonic Refiner",
                MB_OK | MB_ICONINFORMATION
            );
            return;
        }

        pfc::stringcvt::string_utf8_from_wide utf8(
            name.c_str()
        );
        result_ = utf8.get_ptr();
        EndDialog(IDOK);
    }

    pfc::string8 initial_name_;
    pfc::string8 result_;
    ui_language language_ = ui_language::english;
    fb2k::CDarkModeHooks dark_mode_;
};

constexpr const wchar_t* sonic_refiner_help_text_japanese = LR"INFO(
Sonic Refiner ヘルプ

■ 概要
Sonic Refinerは、foobar2000用の適応型音質補正DSPです。
低域の厚み、明瞭感、ステレオの広がり、短い初期反射による
奥行きを調整できます。

■ 推奨するDSP順序
Sonic Refiner
↓
R128 Real-time Loudness Normalizer
↓
出力

Sonic Refinerは音色と音場を整えます。
R128 Real-time Loudness Normalizerは、ラウドネス、True Peak、
リミッターなどの最終的な音量管理を担当します。

■ 基本操作
1. 内蔵プリセットを呼び出します。
2. Depth、Clarity、Width、Ambienceを好みに合わせて調整します。
3. Master Strengthで4項目の効果を一括調整します。
4. 必要に応じて出力ゲインを調整します。
5. 調整結果を任意プリセットとして保存します。

■ スライダーの範囲
0～60%：通常の調整域
60～80%：強い補正域
80～100%：極端な演出・確認用

■ プリセット
内蔵プリセットは変更・削除できません。
内蔵プリセットを呼び出して調整した後、任意プリセットとして
別名保存できます。任意プリセットは最大20件です。

■ バックアップ
「書出...」で任意プリセット全件を.srpbackupファイルへ保存します。
「読込...」では、現在の任意プリセット一覧をバックアップ内の
一覧で置き換えます。内蔵プリセットと現在の音質設定は変わりません。

■ A/B比較
「Aへ保存」「Bへ保存」でDepth、Clarity、Width、Ambience、
Master Strengthを一時保存できます。「Aを試聴」「Bを試聴」で
即時に切り替え、「比較終了」で比較開始直前の全設定へ戻ります。
A/Bスロットはfoobar2000起動中だけ保持され、再起動すると空になります。
任意プリセットや.srpbackupには保存されません。

■ Playbackメニューから直接開く
Playbackメニューの「Sonic Refiner の設定...」から、DSP Managerを
経由せず設定画面を直接開けます。直接起動画面を開いたまま
foobar2000本体を操作できます。Preferences → Keyboard Shortcutsから
このコマンドへ任意のショートカットキーを割り当てることもできます。
Sonic RefinerがDSPチェーンにない場合や複数登録されている場合は、
誤編集防止のため直接編集を開始しません。

■ 比較
レベルマッチ・バイパスを有効にすると、補正で増えた平均音量を
穏やかに抑え、単なる音量差に惑わされにくくなります。
)INFO";

constexpr const wchar_t* sonic_refiner_help_text_english = LR"INFO(
Sonic Refiner Help

■ Overview
Sonic Refiner is an adaptive audio enhancement DSP for foobar2000.
It adjusts low-frequency body, clarity, stereo width, and depth created
by short early reflections.

■ Recommended DSP Order
Sonic Refiner
↓
R128 Real-time Loudness Normalizer
↓
Output

Sonic Refiner shapes tone and soundstage.
R128 Real-time Loudness Normalizer handles final loudness management,
including loudness control, True Peak protection, and limiting.

■ Basic Operation
1. Load a built-in preset.
2. Adjust Depth, Clarity, Width, and Ambience to taste.
3. Use Master Strength to adjust all four effects together.
4. Adjust Output Gain when necessary.
5. Save the result as a user preset.

■ Slider Ranges
0–60%: Normal adjustment range
60–80%: Strong enhancement range
80–100%: Extreme effects and testing

■ Presets
Built-in presets cannot be changed or deleted.
After loading and adjusting one, you can save the result under a new
name as a user preset. Up to 20 user presets can be stored.

■ Backup
"Export..." saves all user presets to an .srpbackup file.
"Import..." replaces the current user preset list with the list in the
backup. Built-in presets and the current sound settings are unchanged.

■ A/B Comparison
Store A and Store B temporarily save Depth, Clarity, Width, Ambience, and
Master Strength. Listen A and Listen B switch instantly. End Comparison
restores the complete settings from immediately before comparison began.
A/B slots remain only while foobar2000 is running and are cleared after a
restart. They are not stored in user presets or .srpbackup files.

■ Open Directly from the Playback Menu
Use Playback → Sonic Refiner Settings... to open the settings window without
going through DSP Manager. The direct window is modeless, so foobar2000 remains
usable while it is open. You can also assign this command to any key in
Preferences → Keyboard Shortcuts. If Sonic Refiner is missing from the active
DSP chain or appears more than once, direct editing is not started for safety.

■ Comparison
Level-Matched Bypass gently reduces average level added by processing,
helping you compare the sound without being misled by loudness alone.
)INFO";

constexpr const wchar_t* sonic_refiner_glossary_text_japanese = LR"INFO(
Sonic Refiner 用語集

■ Depth（音の厚み）
約120 Hzを中心とした低域シェルフ補正です。
最大値は約+16 dBです。低音、胴鳴り、低中域の存在感を増やします。

■ Clarity（明瞭感）
約3.5 kHzから上を持ち上げる高域シェルフ補正です。
最大値は約+14 dBです。ボーカルや楽器の輪郭、抜けを強調します。

■ Width（音場の広がり）
Mid/Side方式でステレオのSide成分を広げます。
約180 Hz以下は保護され、最大Side 600%です。
モノラル音源には広がり効果がありません。

■ Ambience（空間・奥行き感）
約11 msと19 msの短い初期反射を加えます。
最大Wet Mixは85%です。長いリバーブではなく、近い反射音によって
空間の広さや奥行きを作ります。

■ Master Strength（全体効果量）
Depth、Clarity、Width、Ambienceのバランスを保ったまま、
4項目の実効効果を0～100%で一括調整します。
0%では4項目が無補正、100%では各スライダーの設定どおりになります。
Output Gain、自動ヘッドルーム保護、レベルマッチは対象外です。

■ Output Gain（出力ゲイン）
すべての音質・音場補正とレベルマッチの後で音量を調整します。
範囲は-12.0～+6.0 dB、0.5 dB刻みです。

■ 自動ヘッドルーム保護
補正後のブロックピークが約-0.2 dBFSを超えそうな場合に、
即座に減衰します。約1.5秒かけて元のレベルへ戻ります。
これは軽量なサンプルピーク保護であり、True Peakリミッターではありません。

■ レベルマッチ・バイパス
処理前後の平均電力を約0.75秒で測定します。
補正によって増えた平均音量だけを下げ、音量を持ち上げません。
オン／オフ比較を公平にしやすくする機能です。

■ 内蔵プリセット
Sonic Refinerに固定で収録された設定です。
上書きや削除はできません。

■ 任意プリセット
ユーザーが名前を付けて保存する設定です。
補正値、Master Strength、出力ゲイン、保護、レベル一致、
本体の有効状態を保存します。

■ A/B比較
Depth、Clarity、Width、Ambience、Master Strengthの5項目だけを
A/Bへ一時保存して比較する機能です。Output Gain、保護、レベル一致、
本体の有効状態はA/Bへ保存しません。A/B内容は再起動後に消去されます。

■ R128 Real-time Loudness Normalizer
Sonic Refinerとは別の後段DSPです。
ラウドネス正規化、True Peak保護、リミッターなどを担当します。
)INFO";

constexpr const wchar_t* sonic_refiner_glossary_text_english = LR"INFO(
Sonic Refiner Glossary

■ Depth
A low-shelf adjustment centered around 120 Hz.
The maximum boost is approximately +16 dB. It adds bass weight, body,
and low-mid presence.

■ Clarity
A high-shelf adjustment above approximately 3.5 kHz.
The maximum boost is approximately +14 dB. It emphasizes vocal and
instrument definition and presence.

■ Width
Expands the stereo Side component using Mid/Side processing.
Frequencies below approximately 180 Hz are protected, and the maximum
Side level is 600%. Mono sources are not widened.

■ Ambience
Adds short early reflections at approximately 11 ms and 19 ms.
The maximum Wet Mix is 85%. It creates space and depth with nearby
reflections rather than a long reverb tail.

■ Master Strength
Adjusts the effective amount of Depth, Clarity, Width, and Ambience
from 0% to 100% while preserving their balance.
At 0%, all four are neutral. At 100%, each slider works at its full
configured value. Output Gain, Auto Headroom Protection, and Level
Match are not affected.

■ Output Gain
Adjusts level after all tone, soundstage, and level-match processing.
The range is -12.0 to +6.0 dB in 0.5 dB steps.

■ Auto Headroom Protection
Immediately reduces gain when the processed block peak would exceed
approximately -0.2 dBFS, then releases over approximately 1.5 seconds.
This is lightweight sample/block peak protection, not a True Peak limiter.

■ Level-Matched Bypass
Measures average power before and after processing over approximately
0.75 seconds. It only reduces average level added by processing and
never raises level, making on/off comparison fairer.

■ Built-in Presets
Fixed settings included with Sonic Refiner.
They cannot be overwritten or deleted.

■ User Presets
Settings saved under a user-defined name.
They store the enhancement values, Master Strength, Output Gain,
protection, level match, and the enabled state.

■ A/B Comparison
Temporarily stores only Depth, Clarity, Width, Ambience, and Master Strength
in A or B. Output Gain, protection, level match, and the enabled state are not
stored in A/B. The slots are cleared when foobar2000 restarts.

■ R128 Real-time Loudness Normalizer
A separate downstream DSP used after Sonic Refiner.
It handles loudness normalization, True Peak protection, and limiting.
)INFO";

constexpr const wchar_t* sonic_refiner_notice_text_japanese = LR"INFO(
Sonic Refiner 使用上の注意

■ 80%以上の拡張レンジ
80～100%は極端な演出・効果確認用です。
常用を前提とした自然な補正範囲ではありません。

■ Depth
強い低域補正は、スピーカー、サブウーファー、アンプへ大きな負担を
かける場合があります。音量を下げてから調整してください。

■ Clarity
高い設定では、サ行、シンバル、録音ノイズ、歪みまで強調されます。
耳に刺さる場合は値を下げてください。

■ Width
高い設定では、中央のボーカルが薄くなる、左右の定位が不安定になる、
モノラル互換性が低下する場合があります。

■ Ambience
高い設定では、反射音がエコーのように分離する、ボーカルが遠くなる、
音が濁る場合があります。

■ Master Strength
0%にするとDepth、Clarity、Width、Ambienceは無補正になります。
Output Gainと保護・比較機能の設定値は変更されません。

■ 出力ゲイン
正の出力ゲインを使用し、自動ヘッドルーム保護を無効にすると、
0 dBFSを超えるピークが発生する可能性があります。

■ 自動ヘッドルーム保護
軽量なブロックピーク保護です。
インターサンプルピークを保証するTrue Peakリミッターではありません。
通常使用では、後段のR128 Real-time Loudness Normalizerも有効にしてください。

■ 聴覚と機器の保護
フルブーストなどの極端な設定を試す際は、再生音量を十分に下げてください。
長時間の大音量再生は避けてください。

■ A/B比較
A/Bスロットは一時比較専用で、foobar2000終了時に消去されます。
残したい設定は任意プリセットとして保存してください。

■ プリセット読み込み
バックアップの読み込みは、現在の任意プリセット一覧を全件置換します。
必要なプリセットは、読み込み前に書き出してください。

■ 動作上の注意
音源や再生環境によって補正結果は異なります。
重要な用途では、実際の出力レベルと音質を確認してください。
)INFO";

constexpr const wchar_t* sonic_refiner_notice_text_english = LR"INFO(
Sonic Refiner Important Notes

■ Extended Range Above 80%
The 80–100% range is intended for extreme effects and testing.
It is not a natural adjustment range intended for continuous use.

■ Depth
Strong bass enhancement can place a heavy load on speakers,
subwoofers, and amplifiers. Lower the playback volume before adjusting it.

■ Clarity
High settings can emphasize sibilance, cymbals, recording noise,
and distortion. Reduce the value if the sound becomes harsh.

■ Width
High settings can weaken centered vocals, destabilize left/right imaging,
and reduce mono compatibility.

■ Ambience
High settings can make reflections sound like separate echoes, move vocals
farther away, or make the sound muddy.

■ Master Strength
At 0%, Depth, Clarity, Width, and Ambience are neutral.
Output Gain and protection/comparison settings are unchanged.

■ Output Gain
Using positive Output Gain with Auto Headroom Protection disabled may
produce peaks above 0 dBFS.

■ Auto Headroom Protection
This is lightweight block-peak protection, not a True Peak limiter that
guarantees control of inter-sample peaks. For normal use, also enable the
downstream R128 Real-time Loudness Normalizer.

■ Hearing and Equipment Safety
Lower the playback volume before trying extreme settings such as Full Boost.
Avoid prolonged listening at high volume.

■ A/B Comparison
A/B slots are temporary and are cleared when foobar2000 exits. Save settings
you want to keep as a user preset.

■ Preset Import
Importing a backup replaces the entire current user preset list.
Export any presets you need before importing.

■ Operating Notes
Results vary with the source material and playback system.
For critical use, check the actual output level and sound quality.
)INFO";

constexpr const wchar_t* sonic_refiner_license_text_japanese = LR"INFO(
Sonic Refiner ライセンス

MIT License

Copyright (c) 2026 Maximum

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

このライセンス表示はSonic Refiner自身のソースコードに対するものです。
foobar2000およびfoobar2000 SDKには、それぞれの権利と利用条件が適用されます。
)INFO";

constexpr const wchar_t* sonic_refiner_license_text_english = LR"INFO(
Sonic Refiner License

MIT License

Copyright (c) 2026 Maximum

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

This license notice applies to the Sonic Refiner source code itself.
foobar2000 and the foobar2000 SDK are subject to their respective rights and
terms of use.
)INFO";

class sonic_refiner_information_dialog final :
    public CDialogImpl<sonic_refiner_information_dialog> {
public:
    sonic_refiner_information_dialog(
        const wchar_t* title,
        const wchar_t* text,
        ui_language language
    )
        : title_(title != nullptr ? title : L"Sonic Refiner"),
          text_(text != nullptr ? text : L""),
          language_(language) {
    }

    enum { IDD = IDD_INFORMATION };

    BEGIN_MSG_MAP_EX(sonic_refiner_information_dialog)
        MSG_WM_INITDIALOG(on_init_dialog)
        COMMAND_HANDLER_EX(IDOK, BN_CLICKED, on_close)
        COMMAND_HANDLER_EX(IDCANCEL, BN_CLICKED, on_close)
    END_MSG_MAP()

private:
    BOOL on_init_dialog(CWindow, LPARAM) {
        dark_mode_.AddDialogWithControls(m_hWnd);

        ::SetWindowTextW(m_hWnd, title_.c_str());
        ::SetDlgItemTextW(
            m_hWnd,
            IDOK,
            localized(language_, L"閉じる", L"Close")
        );

        std::wstring display_text;
        display_text.reserve(text_.size() + 64);

        for (std::size_t index = 0;
             index < text_.size();
             ++index) {
            const wchar_t character = text_[index];

            if (character == L'\n') {
                if (display_text.empty() ||
                    display_text.back() != L'\r') {
                    display_text.push_back(L'\r');
                }

                display_text.push_back(L'\n');
                continue;
            }

            display_text.push_back(character);
        }

        ::SetDlgItemTextW(
            m_hWnd,
            IDC_INFORMATION_TEXT,
            display_text.c_str()
        );
        ::SendDlgItemMessageW(
            m_hWnd,
            IDC_INFORMATION_TEXT,
            EM_SETSEL,
            0,
            0
        );
        ::SendDlgItemMessageW(
            m_hWnd,
            IDC_INFORMATION_TEXT,
            EM_SCROLLCARET,
            0,
            0
        );

        CWindow close_button = GetDlgItem(IDOK);
        close_button.SetFocus();

        return FALSE;
    }

    void on_close(UINT, int, CWindow) {
        EndDialog(IDOK);
    }

    std::wstring title_;
    std::wstring text_;
    ui_language language_ = ui_language::english;
    fb2k::CDarkModeHooks dark_mode_;
};

class sonic_refiner_dialog final :
    public CDialogImpl<sonic_refiner_dialog> {
public:
    sonic_refiner_dialog(
        const dsp_preset& initial_preset,
        dsp_preset_edit_callback& callback,
        bool modeless = false,
        HWND* tracked_window = nullptr
    )
        : initial_preset_(initial_preset),
          callback_(callback),
          settings_(sonic_refiner::parse_preset(initial_preset)),
          modeless_(modeless),
          tracked_window_(tracked_window) {
    }

    void OnFinalMessage(HWND window) override {
        if (tracked_window_ != nullptr &&
            *tracked_window_ == window) {
            *tracked_window_ = nullptr;
        }

        if (modeless_) {
            delete this;
        }
    }

    enum { IDD = IDD_SONIC_REFINER };

    BEGIN_MSG_MAP_EX(sonic_refiner_dialog)
        MSG_WM_INITDIALOG(on_init_dialog)
        MSG_WM_HSCROLL(on_hscroll)
        COMMAND_HANDLER_EX(
            IDC_LANGUAGE_COMBO,
            CBN_SELCHANGE,
            on_language_changed
        )
        COMMAND_HANDLER_EX(
            IDC_ENABLE,
            BN_CLICKED,
            on_enable_changed
        )
        COMMAND_HANDLER_EX(
            IDC_AUTO_HEADROOM,
            BN_CLICKED,
            on_auto_headroom_changed
        )
        COMMAND_HANDLER_EX(
            IDC_LEVEL_MATCH,
            BN_CLICKED,
            on_level_match_changed
        )
        COMMAND_HANDLER_EX(
            IDC_HELP_BUTTON,
            BN_CLICKED,
            on_help
        )
        COMMAND_HANDLER_EX(
            IDC_GLOSSARY_BUTTON,
            BN_CLICKED,
            on_glossary
        )
        COMMAND_HANDLER_EX(
            IDC_NOTICE_BUTTON,
            BN_CLICKED,
            on_notice
        )
        COMMAND_HANDLER_EX(
            IDC_LICENSE_BUTTON,
            BN_CLICKED,
            on_license
        )
        COMMAND_HANDLER_EX(
            IDC_BUILTIN_PRESET_LOAD,
            BN_CLICKED,
            on_builtin_preset_load
        )
        COMMAND_HANDLER_EX(
            IDC_BUILTIN_PRESET_COMBO,
            CBN_SELCHANGE,
            on_builtin_preset_selection_changed
        )
        COMMAND_HANDLER_EX(
            IDC_PRESET_SAVE,
            BN_CLICKED,
            on_preset_save
        )
        COMMAND_HANDLER_EX(
            IDC_PRESET_LOAD,
            BN_CLICKED,
            on_preset_load
        )
        COMMAND_HANDLER_EX(
            IDC_PRESET_DELETE,
            BN_CLICKED,
            on_preset_delete
        )
        COMMAND_HANDLER_EX(
            IDC_PRESET_EXPORT,
            BN_CLICKED,
            on_preset_export
        )
        COMMAND_HANDLER_EX(
            IDC_PRESET_IMPORT,
            BN_CLICKED,
            on_preset_import
        )
        COMMAND_HANDLER_EX(
            IDC_PRESET_COMBO,
            CBN_SELCHANGE,
            on_preset_selection_changed
        )
        COMMAND_HANDLER_EX(
            IDC_AB_STORE_A,
            BN_CLICKED,
            on_ab_store_a
        )
        COMMAND_HANDLER_EX(
            IDC_AB_LISTEN_A,
            BN_CLICKED,
            on_ab_listen_a
        )
        COMMAND_HANDLER_EX(
            IDC_AB_STORE_B,
            BN_CLICKED,
            on_ab_store_b
        )
        COMMAND_HANDLER_EX(
            IDC_AB_LISTEN_B,
            BN_CLICKED,
            on_ab_listen_b
        )
        COMMAND_HANDLER_EX(
            IDC_AB_END,
            BN_CLICKED,
            on_ab_end
        )
        COMMAND_HANDLER_EX(IDOK, BN_CLICKED, on_button)
        COMMAND_HANDLER_EX(IDCANCEL, BN_CLICKED, on_button)
        MSG_WM_CLOSE(on_close)
        MESSAGE_HANDLER(
            wm_sonic_refiner_direct_chain_invalidated,
            on_direct_chain_invalidated
        )
    END_MSG_MAP()

private:
    BOOL on_init_dialog(CWindow, LPARAM) {
        if (tracked_window_ != nullptr) {
            *tracked_window_ = m_hWnd;
        }

        dark_mode_.AddDialogWithControls(m_hWnd);

        depth_slider_ = GetDlgItem(IDC_DEPTH_SLIDER);
        clarity_slider_ = GetDlgItem(IDC_CLARITY_SLIDER);
        width_slider_ = GetDlgItem(IDC_WIDTH_SLIDER);
        ambience_slider_ = GetDlgItem(IDC_AMBIENCE_SLIDER);
        master_strength_slider_ =
            GetDlgItem(IDC_MASTER_STRENGTH_SLIDER);
        output_gain_slider_ =
            GetDlgItem(IDC_OUTPUT_GAIN_SLIDER);
        enable_checkbox_ = GetDlgItem(IDC_ENABLE);
        auto_headroom_checkbox_ =
            GetDlgItem(IDC_AUTO_HEADROOM);
        level_match_checkbox_ =
            GetDlgItem(IDC_LEVEL_MATCH);
        built_in_preset_combo_ =
            GetDlgItem(IDC_BUILTIN_PRESET_COMBO);
        preset_combo_ = GetDlgItem(IDC_PRESET_COMBO);
        language_combo_ = GetDlgItem(IDC_LANGUAGE_COMBO);
        language_ = load_ui_language();
        comparison_state_ = comparison_state::none;
        comparison_start_valid_ = false;

        ::SendMessageW(
            language_combo_,
            CB_ADDSTRING,
            0,
            reinterpret_cast<LPARAM>(L"日本語")
        );
        ::SendMessageW(
            language_combo_,
            CB_ADDSTRING,
            0,
            reinterpret_cast<LPARAM>(L"English")
        );
        language_combo_.SetCurSel(
            is_english(language_) ? 1 : 0
        );

        configure_slider(
            depth_slider_,
            static_cast<int>(std::lround(settings_.depth))
        );
        configure_slider(
            clarity_slider_,
            static_cast<int>(std::lround(settings_.clarity))
        );
        configure_slider(
            width_slider_,
            static_cast<int>(std::lround(settings_.width))
        );
        configure_slider(
            ambience_slider_,
            static_cast<int>(std::lround(settings_.ambience))
        );
        configure_slider(
            master_strength_slider_,
            static_cast<int>(
                std::lround(settings_.master_strength)
            )
        );
        configure_output_gain_slider(
            output_gain_slider_,
            settings_.output_gain_db
        );

        apply_settings_to_controls();

        user_presets_ = load_user_presets();
        refresh_preset_combo(
            user_presets_.empty() ? -1 : 0
        );

        apply_language();
        refresh_labels();
        return TRUE;
    }

    static void configure_slider(
        CTrackBarCtrl& slider,
        int position
    ) {
        slider.SetRange(0, 100);
        slider.SetTicFreq(10);
        slider.SetPos(position);
    }

    static int output_gain_to_slider_position(
        float output_gain_db
    ) noexcept {
        const double safe_gain = std::clamp(
            static_cast<double>(output_gain_db),
            output_gain_minimum_db,
            output_gain_maximum_db
        );

        return static_cast<int>(std::lround(
            (safe_gain - output_gain_minimum_db) /
            output_gain_step_db
        ));
    }

    static float slider_position_to_output_gain(
        int position
    ) noexcept {
        const int maximum_position = static_cast<int>(
            std::lround(
                (output_gain_maximum_db -
                 output_gain_minimum_db) /
                output_gain_step_db
            )
        );
        const int safe_position = std::clamp(
            position,
            0,
            maximum_position
        );

        return static_cast<float>(
            output_gain_minimum_db +
            (static_cast<double>(safe_position) *
             output_gain_step_db)
        );
    }

    static void configure_output_gain_slider(
        CTrackBarCtrl& slider,
        float output_gain_db
    ) {
        const int maximum_position = static_cast<int>(
            std::lround(
                (output_gain_maximum_db -
                 output_gain_minimum_db) /
                output_gain_step_db
            )
        );

        slider.SetRange(0, maximum_position);
        slider.SetTicFreq(2);
        slider.SetPos(
            output_gain_to_slider_position(output_gain_db)
        );
    }

    void apply_language() {
        const int selected_builtin =
            selected_builtin_preset_index();

        ::SetWindowTextW(
            m_hWnd,
            L"Sonic Refiner - 0.4.0"
        );
        ::SetDlgItemTextW(
            m_hWnd,
            IDC_ENABLE,
            localized(
                language_,
                L"Sonic Refiner を有効にする",
                L"Enable Sonic Refiner"
            )
        );
        ::SetDlgItemTextW(
            m_hWnd,
            IDC_LANGUAGE_LABEL,
            localized(language_, L"言語:", L"Language:")
        );
        ::SetDlgItemTextW(
            m_hWnd,
            IDC_HELP_BUTTON,
            localized(language_, L"ヘルプ", L"Help")
        );
        ::SetDlgItemTextW(
            m_hWnd,
            IDC_GLOSSARY_BUTTON,
            localized(language_, L"用語集", L"Glossary")
        );
        ::SetDlgItemTextW(
            m_hWnd,
            IDC_NOTICE_BUTTON,
            localized(language_, L"注意事項", L"Important Notes")
        );
        ::SetDlgItemTextW(
            m_hWnd,
            IDC_LICENSE_BUTTON,
            localized(language_, L"ライセンス", L"License")
        );
        ::SetDlgItemTextW(
            m_hWnd,
            IDC_GROUP_TONE,
            localized(language_, L"音色・音場補正", L"Tone & Soundstage")
        );
        ::SetDlgItemTextW(
            m_hWnd,
            IDC_DEPTH_LABEL,
            localized(language_, L"音の厚み (Depth)", L"Depth")
        );
        ::SetDlgItemTextW(
            m_hWnd,
            IDC_DEPTH_DESCRIPTION,
            localized(
                language_,
                L"120 Hz付近を中心に、最大約+16 dBまで厚みを加えます。",
                L"Adds body around 120 Hz, up to approximately +16 dB."
            )
        );
        ::SetDlgItemTextW(
            m_hWnd,
            IDC_CLARITY_LABEL,
            localized(language_, L"明瞭感 (Clarity)", L"Clarity")
        );
        ::SetDlgItemTextW(
            m_hWnd,
            IDC_CLARITY_DESCRIPTION,
            localized(
                language_,
                L"3.5 kHz付近から最大約+14 dBまで輪郭を強調します。",
                L"Enhances definition above approximately 3.5 kHz, up to +14 dB."
            )
        );
        ::SetDlgItemTextW(
            m_hWnd,
            IDC_WIDTH_LABEL,
            localized(language_, L"音場の広がり (Width)", L"Width")
        );
        ::SetDlgItemTextW(
            m_hWnd,
            IDC_WIDTH_DESCRIPTION,
            localized(
                language_,
                L"約180 Hz以下を保護し、Side最大600%まで広げます。",
                L"Protects below approximately 180 Hz and expands Side up to 600%."
            )
        );
        ::SetDlgItemTextW(
            m_hWnd,
            IDC_AMBIENCE_LABEL,
            localized(
                language_,
                L"空間・奥行き感 (Ambience)",
                L"Ambience"
            )
        );
        ::SetDlgItemTextW(
            m_hWnd,
            IDC_AMBIENCE_DESCRIPTION,
            localized(
                language_,
                L"11 ms・19 msの初期反射を最大Mix 85%まで加えます。",
                L"Adds 11 ms and 19 ms early reflections, up to 85% Mix."
            )
        );
        ::SetDlgItemTextW(
            m_hWnd,
            IDC_GROUP_BUILTIN,
            localized(language_, L"内蔵プリセット", L"Built-in Presets")
        );
        ::SetDlgItemTextW(
            m_hWnd,
            IDC_BUILTIN_PRESET_LOAD,
            localized(language_, L"呼出", L"Load")
        );
        ::SetDlgItemTextW(
            m_hWnd,
            IDC_BUILTIN_DESCRIPTION,
            localized(
                language_,
                L"固定プリセット。調整後は任意プリセットへ保存できます。",
                L"Fixed presets. Adjust and save as a user preset."
            )
        );
        ::SetDlgItemTextW(
            m_hWnd,
            IDC_GROUP_USER,
            localized(
                language_,
                L"任意プリセット（最大20件）",
                L"User Presets (Max. 20)"
            )
        );
        ::SetDlgItemTextW(
            m_hWnd,
            IDC_PRESET_SAVE,
            localized(language_, L"保存...", L"Save...")
        );
        ::SetDlgItemTextW(
            m_hWnd,
            IDC_PRESET_LOAD,
            localized(language_, L"呼出", L"Load")
        );
        ::SetDlgItemTextW(
            m_hWnd,
            IDC_PRESET_DELETE,
            localized(language_, L"削除", L"Delete")
        );
        ::SetDlgItemTextW(
            m_hWnd,
            IDC_PRESET_EXPORT,
            localized(language_, L"書出...", L"Export...")
        );
        ::SetDlgItemTextW(
            m_hWnd,
            IDC_PRESET_IMPORT,
            localized(language_, L"読込...", L"Import...")
        );
        ::SetDlgItemTextW(
            m_hWnd,
            IDC_USER_DESCRIPTION,
            localized(
                language_,
                L"全件をバックアップし、読み込み時は現在の一覧を置換します。",
                L"Exports all. Import replaces the current list."
            )
        );
        ::SetDlgItemTextW(
            m_hWnd,
            IDC_GROUP_AB,
            localized(language_, L"A/B比較", L"A/B Comparison")
        );
        ::SetDlgItemTextW(
            m_hWnd,
            IDC_AB_STORE_A,
            localized(language_, L"Aへ保存", L"Store A")
        );
        ::SetDlgItemTextW(
            m_hWnd,
            IDC_AB_LISTEN_A,
            localized(language_, L"Aを試聴", L"Listen A")
        );
        ::SetDlgItemTextW(
            m_hWnd,
            IDC_AB_STORE_B,
            localized(language_, L"Bへ保存", L"Store B")
        );
        ::SetDlgItemTextW(
            m_hWnd,
            IDC_AB_LISTEN_B,
            localized(language_, L"Bを試聴", L"Listen B")
        );
        ::SetDlgItemTextW(
            m_hWnd,
            IDC_AB_END,
            localized(language_, L"比較終了", L"End Comparison")
        );
        ::SetDlgItemTextW(
            m_hWnd,
            IDC_GROUP_MASTER,
            localized(
                language_,
                L"全体効果・出力・保護",
                L"Master, Output & Protection"
            )
        );
        ::SetDlgItemTextW(
            m_hWnd,
            IDC_MASTER_STRENGTH_LABEL,
            localized(
                language_,
                L"全体効果量 (Master Strength)",
                L"Master Strength"
            )
        );
        ::SetDlgItemTextW(
            m_hWnd,
            IDC_OUTPUT_GAIN_LABEL,
            localized(
                language_,
                L"出力ゲイン (Output Gain)",
                L"Output Gain"
            )
        );
        ::SetDlgItemTextW(
            m_hWnd,
            IDC_AUTO_HEADROOM,
            localized(
                language_,
                L"自動ヘッドルーム保護（約-0.2 dBFS）",
                L"Auto Headroom Protection (approx. -0.2 dBFS)"
            )
        );
        ::SetDlgItemTextW(
            m_hWnd,
            IDC_LEVEL_MATCH,
            localized(
                language_,
                L"レベルマッチ・バイパス（平均音量差を補正）",
                L"Level-Matched Bypass (average level compensation)"
            )
        );
        ::SetDlgItemTextW(
            m_hWnd,
            IDC_EXTREME_NOTICE,
            localized(
                language_,
                L"80%以上は強い演出用：定位・残響の変化に注意",
                L"80% and above is for extreme effects: check imaging and ambience."
            )
        );
        ::SetDlgItemTextW(m_hWnd, IDOK, L"OK");
        ::SetDlgItemTextW(
            m_hWnd,
            IDCANCEL,
            localized(language_, L"キャンセル", L"Cancel")
        );

        refresh_builtin_preset_combo(selected_builtin);
        refresh_ab_controls();
    }

    void apply_settings_to_controls() {
        depth_slider_.SetPos(
            static_cast<int>(std::lround(settings_.depth))
        );
        clarity_slider_.SetPos(
            static_cast<int>(std::lround(settings_.clarity))
        );
        width_slider_.SetPos(
            static_cast<int>(std::lround(settings_.width))
        );
        ambience_slider_.SetPos(
            static_cast<int>(std::lround(settings_.ambience))
        );
        master_strength_slider_.SetPos(
            static_cast<int>(
                std::lround(settings_.master_strength)
            )
        );
        output_gain_slider_.SetPos(
            output_gain_to_slider_position(
                settings_.output_gain_db
            )
        );

        enable_checkbox_.SetCheck(
            settings_.enabled ? BST_CHECKED : BST_UNCHECKED
        );
        auto_headroom_checkbox_.SetCheck(
            settings_.auto_headroom
                ? BST_CHECKED
                : BST_UNCHECKED
        );
        level_match_checkbox_.SetCheck(
            settings_.level_matched_bypass
                ? BST_CHECKED
                : BST_UNCHECKED
        );
    }

    int selected_builtin_preset_index() const noexcept {
        const int selected = built_in_preset_combo_.GetCurSel();

        if (selected < 0 ||
            static_cast<t_size>(selected) >=
                built_in_preset_count) {
            return -1;
        }

        return selected;
    }

    void refresh_builtin_preset_combo(
        int selected_index = -1
    ) {
        if (selected_index < 0) {
            selected_index = selected_builtin_preset_index();
        }

        built_in_preset_combo_.ResetContent();

        for (t_size index = 0;
             index < built_in_preset_count;
             ++index) {
            ::SendMessageW(
                built_in_preset_combo_,
                CB_ADDSTRING,
                0,
                reinterpret_cast<LPARAM>(
                    built_in_preset_name(
                        g_built_in_presets[index],
                        language_
                    )
                )
            );
        }

        if (selected_index < 0 ||
            static_cast<t_size>(selected_index) >=
                built_in_preset_count) {
            selected_index = 0;
        }

        built_in_preset_combo_.SetCurSel(selected_index);
        refresh_builtin_preset_button();
    }

    void refresh_builtin_preset_button() {
        const BOOL selected =
            selected_builtin_preset_index() >= 0
                ? TRUE
                : FALSE;

        GetDlgItem(IDC_BUILTIN_PRESET_LOAD)
            .EnableWindow(selected);
    }

    int selected_preset_index() const noexcept {
        const int selected = preset_combo_.GetCurSel();

        if (selected < 0 ||
            static_cast<std::size_t>(selected) >=
                user_presets_.size()) {
            return -1;
        }

        return selected;
    }

    void refresh_preset_combo(int selected_index) {
        preset_combo_.ResetContent();

        for (const auto& preset : user_presets_) {
            const std::wstring name =
                preset_name_to_wide(preset.name.get_ptr());

            ::SendMessageW(
                preset_combo_,
                CB_ADDSTRING,
                0,
                reinterpret_cast<LPARAM>(name.c_str())
            );
        }

        if (selected_index >= 0 &&
            static_cast<std::size_t>(selected_index) <
                user_presets_.size()) {
            preset_combo_.SetCurSel(selected_index);
        } else {
            preset_combo_.SetCurSel(-1);
        }

        refresh_preset_buttons();
    }

    void refresh_preset_buttons() {
        const BOOL selected =
            selected_preset_index() >= 0 ? TRUE : FALSE;

        GetDlgItem(IDC_PRESET_LOAD).EnableWindow(selected);
        GetDlgItem(IDC_PRESET_DELETE).EnableWindow(selected);
        GetDlgItem(IDC_PRESET_EXPORT).EnableWindow(
            user_presets_.empty() ? FALSE : TRUE
        );
    }

    enum class comparison_state {
        none,
        slot_a,
        slot_b
    };

    void begin_comparison_if_needed() {
        if (comparison_state_ != comparison_state::none) {
            return;
        }

        comparison_start_settings_ = settings_;
        comparison_start_valid_ = true;
    }

    void store_ab_slot(ab_comparison_slot& slot) {
        slot.value = capture_ab_comparison_value(settings_);
        slot.has_value = true;
        refresh_ab_controls();
    }

    void listen_ab_slot(
        const ab_comparison_slot& slot,
        comparison_state state
    ) {
        if (!slot.has_value) {
            return;
        }

        begin_comparison_if_needed();
        apply_ab_comparison_value(slot.value, settings_);
        comparison_state_ = state;
        apply_settings_to_controls();
        notify_changed();
        refresh_labels();
    }

    void on_ab_store_a(UINT, int, CWindow) {
        store_ab_slot(g_ab_slot_a);
    }

    void on_ab_listen_a(UINT, int, CWindow) {
        listen_ab_slot(g_ab_slot_a, comparison_state::slot_a);
    }

    void on_ab_store_b(UINT, int, CWindow) {
        store_ab_slot(g_ab_slot_b);
    }

    void on_ab_listen_b(UINT, int, CWindow) {
        listen_ab_slot(g_ab_slot_b, comparison_state::slot_b);
    }

    void on_ab_end(UINT, int, CWindow) {
        if (comparison_state_ == comparison_state::none ||
            !comparison_start_valid_) {
            return;
        }

        settings_ = comparison_start_settings_;
        comparison_state_ = comparison_state::none;
        comparison_start_valid_ = false;
        apply_settings_to_controls();
        notify_changed();
        refresh_labels();
    }

    void refresh_ab_controls() {
        ::SetDlgItemTextW(
            m_hWnd,
            IDC_AB_STATUS_A,
            g_ab_slot_a.has_value
                ? localized(language_, L"保存済み", L"Saved")
                : localized(language_, L"未保存", L"Empty")
        );
        ::SetDlgItemTextW(
            m_hWnd,
            IDC_AB_STATUS_B,
            g_ab_slot_b.has_value
                ? localized(language_, L"保存済み", L"Saved")
                : localized(language_, L"未保存", L"Empty")
        );

        const wchar_t* current = localized(
            language_,
            L"現在：比較なし",
            L"Current: None"
        );

        if (comparison_state_ == comparison_state::slot_a) {
            current = localized(language_, L"現在：A", L"Current: A");
        } else if (comparison_state_ == comparison_state::slot_b) {
            current = localized(language_, L"現在：B", L"Current: B");
        }

        ::SetDlgItemTextW(m_hWnd, IDC_AB_CURRENT, current);
        ::CheckDlgButton(
            m_hWnd,
            IDC_AB_LISTEN_A,
            comparison_state_ == comparison_state::slot_a
                ? BST_CHECKED
                : BST_UNCHECKED
        );
        ::CheckDlgButton(
            m_hWnd,
            IDC_AB_LISTEN_B,
            comparison_state_ == comparison_state::slot_b
                ? BST_CHECKED
                : BST_UNCHECKED
        );
        ::CheckDlgButton(
            m_hWnd,
            IDC_AB_END,
            BST_UNCHECKED
        );

        GetDlgItem(IDC_AB_LISTEN_A).EnableWindow(
            g_ab_slot_a.has_value ? TRUE : FALSE
        );
        GetDlgItem(IDC_AB_LISTEN_B).EnableWindow(
            g_ab_slot_b.has_value ? TRUE : FALSE
        );
        GetDlgItem(IDC_AB_END).EnableWindow(
            comparison_state_ != comparison_state::none
                ? TRUE
                : FALSE
        );
    }

    void on_language_changed(UINT, int, CWindow) {
        const int selected = language_combo_.GetCurSel();

        if (selected != 0 && selected != 1) {
            return;
        }

        const ui_language selected_language = selected == 1
            ? ui_language::english
            : ui_language::japanese;

        if (selected_language == language_) {
            return;
        }

        language_ = selected_language;
        save_ui_language(language_);
        apply_language();
        refresh_labels();
    }

    void on_hscroll(UINT, UINT, CScrollBar) {
        settings_.depth =
            static_cast<float>(depth_slider_.GetPos());
        settings_.clarity =
            static_cast<float>(clarity_slider_.GetPos());
        settings_.width =
            static_cast<float>(width_slider_.GetPos());
        settings_.ambience =
            static_cast<float>(ambience_slider_.GetPos());
        settings_.master_strength =
            static_cast<float>(
                master_strength_slider_.GetPos()
            );
        settings_.output_gain_db =
            slider_position_to_output_gain(
                output_gain_slider_.GetPos()
            );

        notify_changed();
        refresh_labels();
    }

    void on_enable_changed(UINT, int, CWindow) {
        settings_.enabled =
            enable_checkbox_.GetCheck() == BST_CHECKED;
        notify_changed();
        refresh_labels();
    }

    void on_auto_headroom_changed(UINT, int, CWindow) {
        settings_.auto_headroom =
            auto_headroom_checkbox_.GetCheck() ==
                BST_CHECKED;
        notify_changed();
        refresh_labels();
    }

    void on_level_match_changed(UINT, int, CWindow) {
        settings_.level_matched_bypass =
            level_match_checkbox_.GetCheck() ==
                BST_CHECKED;
        notify_changed();
        refresh_labels();
    }

    void show_information(
        const wchar_t* title,
        const wchar_t* text
    ) {
        sonic_refiner_information_dialog dialog(
            title,
            text,
            language_
        );
        dialog.DoModal(m_hWnd);
    }

    void on_help(UINT, int, CWindow) {
        show_information(
            localized(
                language_,
                L"Sonic Refiner ヘルプ",
                L"Sonic Refiner Help"
            ),
            localized(
                language_,
                sonic_refiner_help_text_japanese,
                sonic_refiner_help_text_english
            )
        );
    }

    void on_glossary(UINT, int, CWindow) {
        show_information(
            localized(
                language_,
                L"Sonic Refiner 用語集",
                L"Sonic Refiner Glossary"
            ),
            localized(
                language_,
                sonic_refiner_glossary_text_japanese,
                sonic_refiner_glossary_text_english
            )
        );
    }

    void on_notice(UINT, int, CWindow) {
        show_information(
            localized(
                language_,
                L"Sonic Refiner 使用上の注意",
                L"Sonic Refiner Important Notes"
            ),
            localized(
                language_,
                sonic_refiner_notice_text_japanese,
                sonic_refiner_notice_text_english
            )
        );
    }

    void on_license(UINT, int, CWindow) {
        show_information(
            localized(
                language_,
                L"Sonic Refiner ライセンス",
                L"Sonic Refiner License"
            ),
            localized(
                language_,
                sonic_refiner_license_text_japanese,
                sonic_refiner_license_text_english
            )
        );
    }

    void on_builtin_preset_selection_changed(
        UINT,
        int,
        CWindow
    ) {
        refresh_builtin_preset_button();
    }

    void on_builtin_preset_load(UINT, int, CWindow) {
        const int selected =
            selected_builtin_preset_index();

        if (selected < 0) {
            return;
        }

        settings_ = g_built_in_presets[
            static_cast<t_size>(selected)
        ].value;
        settings_ = sonic_refiner::sanitize(settings_);

        apply_settings_to_controls();
        notify_changed();
        refresh_labels();
    }

    void on_preset_selection_changed(
        UINT,
        int,
        CWindow
    ) {
        refresh_preset_buttons();
    }

    void on_preset_save(UINT, int, CWindow) {
        const int selected = selected_preset_index();
        const char* initial_name = "";

        if (selected >= 0) {
            initial_name =
                user_presets_[
                    static_cast<std::size_t>(selected)
                ].name.get_ptr();
        }

        preset_name_dialog dialog(initial_name, language_);

        if (dialog.DoModal(m_hWnd) != IDOK) {
            return;
        }

        const pfc::string8 name = dialog.result();
        int existing = find_user_preset(
            user_presets_,
            name.get_ptr()
        );

        if (existing >= 0) {
            const std::wstring wide_name =
                preset_name_to_wide(name.get_ptr());
            const std::wstring message = is_english(language_)
                ? L"Overwrite “" + wide_name +
                    L"” with the current settings?"
                : L"「" + wide_name +
                    L"」を現在の設定で上書きしますか？";

            if (::MessageBoxW(
                    m_hWnd,
                    message.c_str(),
                    L"Sonic Refiner",
                    MB_YESNO |
                    MB_ICONQUESTION |
                    MB_DEFBUTTON2
                ) != IDYES) {
                return;
            }

            user_presets_[
                static_cast<std::size_t>(existing)
            ].value = settings_;
        } else {
            if (user_presets_.size() >=
                maximum_user_presets) {
                ::MessageBoxW(
                    m_hWnd,
                    localized(
                        language_,
                        L"任意プリセットは最大20件まで保存できます。",
                        L"You can save up to 20 user presets."
                    ),
                    L"Sonic Refiner",
                    MB_OK | MB_ICONINFORMATION
                );
                return;
            }

            user_preset preset;
            preset.name = name;
            preset.value = settings_;
            user_presets_.push_back(preset);
            existing = static_cast<int>(
                user_presets_.size() - 1
            );
        }

        save_user_presets(user_presets_);
        refresh_preset_combo(existing);
    }

    void on_preset_load(UINT, int, CWindow) {
        const int selected = selected_preset_index();

        if (selected < 0) {
            return;
        }

        settings_ = user_presets_[
            static_cast<std::size_t>(selected)
        ].value;
        settings_ = sonic_refiner::sanitize(settings_);

        apply_settings_to_controls();
        notify_changed();
        refresh_labels();
    }

    void on_preset_delete(UINT, int, CWindow) {
        const int selected = selected_preset_index();

        if (selected < 0) {
            return;
        }

        const std::wstring wide_name = preset_name_to_wide(
            user_presets_[
                static_cast<std::size_t>(selected)
            ].name.get_ptr()
        );
        const std::wstring message = is_english(language_)
            ? L"Delete the user preset “" + wide_name + L"”?"
            : L"「" + wide_name + L"」を削除しますか？";

        if (::MessageBoxW(
                m_hWnd,
                message.c_str(),
                L"Sonic Refiner",
                MB_YESNO |
                MB_ICONWARNING |
                MB_DEFBUTTON2
            ) != IDYES) {
            return;
        }

        user_presets_.erase(
            user_presets_.begin() + selected
        );
        save_user_presets(user_presets_);

        int next_selection = selected;

        if (next_selection >=
            static_cast<int>(user_presets_.size())) {
            next_selection =
                static_cast<int>(user_presets_.size()) - 1;
        }

        refresh_preset_combo(next_selection);
    }

    void on_preset_export(UINT, int, CWindow) {
        if (user_presets_.empty()) {
            ::MessageBoxW(
                m_hWnd,
                localized(
                    language_,
                    L"書き出す任意プリセットがありません。",
                    L"There are no user presets to export."
                ),
                L"Sonic Refiner",
                MB_OK | MB_ICONINFORMATION
            );
            return;
        }

        std::wstring path;

        if (!choose_preset_export_path(
                m_hWnd,
                language_,
                path
            )) {
            return;
        }

        const std::string backup =
            make_preset_backup(user_presets_);

        if (!write_preset_backup_file(path, backup)) {
            ::MessageBoxW(
                m_hWnd,
                localized(
                    language_,
                    L"プリセットの書き出しに失敗しました。",
                    L"Could not export the preset backup."
                ),
                L"Sonic Refiner",
                MB_OK | MB_ICONERROR
            );
            return;
        }

        std::wstring message;
        const std::size_t count = user_presets_.size();

        if (is_english(language_)) {
            message = L"Exported " + std::to_wstring(count) +
                (count == 1
                    ? L" user preset."
                    : L" user presets.");
        } else {
            message = std::to_wstring(count) +
                L"件の任意プリセットを書き出しました。";
        }

        ::MessageBoxW(
            m_hWnd,
            message.c_str(),
            L"Sonic Refiner",
            MB_OK | MB_ICONINFORMATION
        );
    }

    void on_preset_import(UINT, int, CWindow) {
        std::wstring path;

        if (!choose_preset_import_path(
                m_hWnd,
                language_,
                path
            )) {
            return;
        }

        std::string backup;

        if (!read_preset_backup_file(path, backup)) {
            ::MessageBoxW(
                m_hWnd,
                localized(
                    language_,
                    L"バックアップファイルを読み込めませんでした。",
                    L"Could not read the backup file."
                ),
                L"Sonic Refiner",
                MB_OK | MB_ICONERROR
            );
            return;
        }

        std::vector<user_preset> imported;

        if (!parse_preset_backup(backup, imported)) {
            ::MessageBoxW(
                m_hWnd,
                localized(
                    language_,
                    L"有効なSonic Refinerプリセットバックアップではありません。",
                    L"This is not a valid Sonic Refiner preset backup."
                ),
                L"Sonic Refiner",
                MB_OK | MB_ICONERROR
            );
            return;
        }

        std::wstring confirmation;
        const std::size_t count = imported.size();

        if (is_english(language_)) {
            confirmation =
                L"Replace the current user preset list with " +
                std::to_wstring(count) +
                (count == 1
                    ? L" preset from the backup?\n\n"
                    : L" presets from the backup?\n\n") +
                L"Built-in presets and the current sound settings "
                L"will not be changed.";
        } else {
            confirmation =
                L"現在の任意プリセットを、バックアップ内の" +
                std::to_wstring(count) +
                L"件で置き換えますか？\n\n"
                L"内蔵プリセットと現在の音質設定は変更されません。";
        }

        if (::MessageBoxW(
                m_hWnd,
                confirmation.c_str(),
                L"Sonic Refiner",
                MB_YESNO |
                MB_ICONWARNING |
                MB_DEFBUTTON2
            ) != IDYES) {
            return;
        }

        user_presets_ = imported;
        save_user_presets(user_presets_);
        refresh_preset_combo(
            user_presets_.empty() ? -1 : 0
        );

        std::wstring message;

        if (is_english(language_)) {
            message = L"Imported " + std::to_wstring(count) +
                (count == 1
                    ? L" user preset."
                    : L" user presets.");
        } else {
            message = std::to_wstring(count) +
                L"件の任意プリセットを読み込みました。";
        }

        ::MessageBoxW(
            m_hWnd,
            message.c_str(),
            L"Sonic Refiner",
            MB_OK | MB_ICONINFORMATION
        );
    }

    void on_button(UINT, int id, CWindow) {
        close_settings_dialog(id);
    }

    void on_close() {
        close_settings_dialog(IDCANCEL);
    }

    void close_settings_dialog(int id) {
        if (id == IDCANCEL) {
            callback_.on_preset_changed(initial_preset_);
        }

        if (modeless_) {
            DestroyWindow();
        } else {
            EndDialog(id);
        }
    }

    LRESULT on_direct_chain_invalidated(
        UINT,
        WPARAM,
        LPARAM,
        BOOL&
    ) {
        direct_invalidated_ = true;
        refresh_labels();
        return 0;
    }

    void notify_changed() {
        if (direct_invalidated_) {
            return;
        }
        dsp_preset_impl preset;
        sonic_refiner::make_preset(settings_, preset);
        callback_.on_preset_changed(preset);
    }

    void refresh_labels() {
        const int depth =
            static_cast<int>(std::lround(settings_.depth));
        const int clarity =
            static_cast<int>(std::lround(settings_.clarity));
        const int width =
            static_cast<int>(std::lround(settings_.width));
        const int ambience =
            static_cast<int>(std::lround(settings_.ambience));
        const int master_strength = static_cast<int>(
            std::lround(settings_.master_strength)
        );
        const int side_percent = static_cast<int>(
            std::lround(
                effective_width_side_gain(
                    settings_.width,
                    settings_.master_strength
                ) * 100.0
            )
        );
        const int wet_percent = static_cast<int>(
            std::lround(
                effective_ambience_wet_mix(
                    settings_.ambience,
                    settings_.master_strength
                ) * 100.0
            )
        );

        pfc::string_formatter depth_text;
        depth_text
            << depth
            << localized_utf8(
                language_,
                "%  /  約 +",
                "%  /  approx. +"
            )
            << pfc::format_float(
                effective_depth_gain_db(
                    settings_.depth,
                    settings_.master_strength
                ),
                0,
                1
            )
            << " dB";
        uSetDlgItemText(
            m_hWnd,
            IDC_DEPTH_VALUE,
            depth_text
        );

        pfc::string_formatter clarity_text;
        clarity_text
            << clarity
            << localized_utf8(
                language_,
                "%  /  約 +",
                "%  /  approx. +"
            )
            << pfc::format_float(
                effective_clarity_gain_db(
                    settings_.clarity,
                    settings_.master_strength
                ),
                0,
                1
            )
            << " dB";
        uSetDlgItemText(
            m_hWnd,
            IDC_CLARITY_VALUE,
            clarity_text
        );

        pfc::string_formatter width_text;
        width_text
            << width
            << "%  /  Side "
            << side_percent
            << "%";
        uSetDlgItemText(
            m_hWnd,
            IDC_WIDTH_VALUE,
            width_text
        );

        pfc::string_formatter ambience_text;
        ambience_text
            << ambience
            << "%  /  Mix "
            << wet_percent
            << "%";
        uSetDlgItemText(
            m_hWnd,
            IDC_AMBIENCE_VALUE,
            ambience_text
        );

        pfc::string_formatter master_strength_text;
        master_strength_text
            << master_strength
            << "%";
        uSetDlgItemText(
            m_hWnd,
            IDC_MASTER_STRENGTH_VALUE,
            master_strength_text
        );

        pfc::string_formatter output_gain_text;
        if (settings_.output_gain_db >= 0.0f) {
            output_gain_text << "+";
        }
        output_gain_text
            << pfc::format_float(
                settings_.output_gain_db,
                0,
                1
            )
            << " dB";
        uSetDlgItemText(
            m_hWnd,
            IDC_OUTPUT_GAIN_VALUE,
            output_gain_text
        );

        const BOOL enabled =
            settings_.enabled ? TRUE : FALSE;

        GetDlgItem(IDC_DEPTH_SLIDER).EnableWindow(enabled);
        GetDlgItem(IDC_DEPTH_VALUE).EnableWindow(enabled);
        GetDlgItem(IDC_CLARITY_SLIDER).EnableWindow(enabled);
        GetDlgItem(IDC_CLARITY_VALUE).EnableWindow(enabled);
        GetDlgItem(IDC_WIDTH_SLIDER).EnableWindow(enabled);
        GetDlgItem(IDC_WIDTH_VALUE).EnableWindow(enabled);
        GetDlgItem(IDC_AMBIENCE_SLIDER).EnableWindow(enabled);
        GetDlgItem(IDC_AMBIENCE_VALUE).EnableWindow(enabled);
        GetDlgItem(IDC_MASTER_STRENGTH_SLIDER)
            .EnableWindow(enabled);
        GetDlgItem(IDC_MASTER_STRENGTH_VALUE)
            .EnableWindow(enabled);
        GetDlgItem(IDC_OUTPUT_GAIN_SLIDER).EnableWindow(enabled);
        GetDlgItem(IDC_OUTPUT_GAIN_VALUE).EnableWindow(enabled);
        GetDlgItem(IDC_AUTO_HEADROOM).EnableWindow(enabled);
        GetDlgItem(IDC_LEVEL_MATCH).EnableWindow(enabled);

        const char* status_text = localized_utf8(
            language_,
            "処理状態: バイパス",
            "Status: Bypassed"
        );

        if (settings_.enabled) {
            if (settings_.auto_headroom &&
                settings_.level_matched_bypass) {
                status_text = localized_utf8(
                    language_,
                    "処理状態: 有効 / 保護オン / レベル一致オン",
                    "Status: Active / Protection On / Level Match On"
                );
            } else if (settings_.auto_headroom) {
                status_text = localized_utf8(
                    language_,
                    "処理状態: 有効 / 保護オン / レベル一致オフ",
                    "Status: Active / Protection On / Level Match Off"
                );
            } else if (settings_.level_matched_bypass) {
                status_text = localized_utf8(
                    language_,
                    "処理状態: 有効 / 保護オフ / レベル一致オン",
                    "Status: Active / Protection Off / Level Match On"
                );
            } else {
                status_text = localized_utf8(
                    language_,
                    "処理状態: 有効 / 保護オフ / レベル一致オフ",
                    "Status: Active / Protection Off / Level Match Off"
                );
            }
        }

        uSetDlgItemText(
            m_hWnd,
            IDC_STATUS,
            status_text
        );

        refresh_builtin_preset_button();
        refresh_preset_buttons();
        refresh_ab_controls();

        if (direct_invalidated_) {
            const int edit_control_ids[] = {
                IDC_ENABLE,
                IDC_DEPTH_SLIDER, IDC_DEPTH_VALUE,
                IDC_CLARITY_SLIDER, IDC_CLARITY_VALUE,
                IDC_WIDTH_SLIDER, IDC_WIDTH_VALUE,
                IDC_AMBIENCE_SLIDER, IDC_AMBIENCE_VALUE,
                IDC_BUILTIN_PRESET_COMBO, IDC_BUILTIN_PRESET_LOAD,
                IDC_PRESET_COMBO, IDC_PRESET_SAVE, IDC_PRESET_LOAD,
                IDC_PRESET_DELETE, IDC_PRESET_EXPORT, IDC_PRESET_IMPORT,
                IDC_AB_STORE_A, IDC_AB_LISTEN_A,
                IDC_AB_STORE_B, IDC_AB_LISTEN_B, IDC_AB_END,
                IDC_MASTER_STRENGTH_SLIDER, IDC_MASTER_STRENGTH_VALUE,
                IDC_OUTPUT_GAIN_SLIDER, IDC_OUTPUT_GAIN_VALUE,
                IDC_AUTO_HEADROOM, IDC_LEVEL_MATCH
            };

            for (const int control_id : edit_control_ids) {
                GetDlgItem(control_id).EnableWindow(FALSE);
            }

            uSetDlgItemText(
                m_hWnd,
                IDC_STATUS,
                localized_utf8(
                    language_,
                    "処理状態: 直接編集を停止しました",
                    "Status: Direct editing stopped"
                )
            );
        }
    }

    dsp_preset_impl initial_preset_;
    dsp_preset_edit_callback& callback_;
    sonic_refiner::settings settings_;
    std::vector<user_preset> user_presets_;
    comparison_state comparison_state_ = comparison_state::none;
    bool comparison_start_valid_ = false;
    sonic_refiner::settings comparison_start_settings_;

    CTrackBarCtrl depth_slider_;
    CTrackBarCtrl clarity_slider_;
    CTrackBarCtrl width_slider_;
    CTrackBarCtrl ambience_slider_;
    CTrackBarCtrl master_strength_slider_;
    CTrackBarCtrl output_gain_slider_;
    CButton enable_checkbox_;
    CButton auto_headroom_checkbox_;
    CButton level_match_checkbox_;
    CComboBox built_in_preset_combo_;
    CComboBox preset_combo_;
    CComboBox language_combo_;
    ui_language language_ = ui_language::english;
    fb2k::CDarkModeHooks dark_mode_;
    bool modeless_ = false;
    HWND* tracked_window_ = nullptr;
    bool direct_invalidated_ = false;
};

class direct_sonic_refiner_preset_callback final
    : public dsp_preset_edit_callback {
public:
    void prepare(HWND dialog) noexcept {
        dialog_ = dialog;
        invalidated_ = false;
    }

    void on_preset_changed(
        const dsp_preset& new_preset
    ) override {
        if (invalidated_) {
            return;
        }

        static_api_ptr_t<dsp_config_manager> manager;
        dsp_chain_config_impl chain;
        manager->get_core_settings(chain);

        t_size match_count = 0;
        t_size match_index = 0;

        for (t_size index = 0;
             index < chain.get_count();
             ++index) {
            if (chain.get_item(index).get_owner() ==
                sonic_refiner::guid) {
                match_index = index;
                ++match_count;
            }
        }

        if (match_count != 1) {
            invalidated_ = true;
            const ui_language language = load_ui_language();

            const wchar_t* message = match_count == 0
                ? localized(
                    language,
                    L"Sonic RefinerがDSPチェーンから削除されました。\n"
                    L"この設定画面からの変更はこれ以上適用できません。",
                    L"Sonic Refiner has been removed from the DSP chain.\n"
                    L"Further changes from this window cannot be applied."
                )
                : localized(
                    language,
                    L"Sonic Refinerが複数登録されたため、\n"
                    L"直接編集を続行できません。",
                    L"Multiple Sonic Refiner instances are now present in the DSP chain.\n"
                    L"Direct editing cannot continue."
                );

            ::MessageBoxW(
                IsWindow(dialog_) ? dialog_ : core_api::get_main_window(),
                message,
                L"Sonic Refiner",
                MB_OK | MB_ICONWARNING
            );

            if (IsWindow(dialog_)) {
                ::PostMessageW(
                    dialog_,
                    wm_sonic_refiner_direct_chain_invalidated,
                    0,
                    0
                );
            }
            return;
        }

        chain.replace_item(new_preset, match_index);
        manager->set_core_settings(chain);
    }

private:
    HWND dialog_ = nullptr;
    bool invalidated_ = false;
};

static direct_sonic_refiner_preset_callback
    g_direct_sonic_refiner_preset_callback;

static const GUID guid_mainmenu_open_sonic_refiner_settings = {
    0x9d5ae2c4, 0x7fa1, 0x4ab9,
    { 0x86, 0x8d, 0x57, 0x6b, 0x0d, 0x4f, 0x2b, 0x91 }
};

void activate_existing_sonic_refiner_dialog(HWND dialog) {
    if (!IsWindow(dialog)) {
        return;
    }

    if (IsIconic(dialog)) {
        ::ShowWindow(dialog, SW_RESTORE);
    } else {
        ::ShowWindow(dialog, SW_SHOW);
    }

    ::SetForegroundWindow(dialog);
}

void show_sonic_refiner_settings_from_main_menu() {
    if (IsWindow(g_direct_sonic_refiner_settings_window)) {
        activate_existing_sonic_refiner_dialog(
            g_direct_sonic_refiner_settings_window
        );
        return;
    }

    if (IsWindow(g_standard_sonic_refiner_settings_window)) {
        activate_existing_sonic_refiner_dialog(
            g_standard_sonic_refiner_settings_window
        );
        return;
    }

    static_api_ptr_t<dsp_config_manager> manager;
    dsp_chain_config_impl chain;
    manager->get_core_settings(chain);

    t_size match_count = 0;
    t_size match_index = 0;

    for (t_size index = 0;
         index < chain.get_count();
         ++index) {
        if (chain.get_item(index).get_owner() ==
            sonic_refiner::guid) {
            match_index = index;
            ++match_count;
        }
    }

    const HWND owner = core_api::get_main_window();
    const ui_language language = load_ui_language();

    if (match_count == 0) {
        ::MessageBoxW(
            owner,
            localized(
                language,
                L"Sonic Refinerは現在のDSPチェーンに追加されていません。\n\n"
                L"DSP ManagerでSonic RefinerをActive DSPsへ追加してから、\n"
                L"もう一度お試しください。",
                L"Sonic Refiner is not currently in the active DSP chain.\n\n"
                L"Add Sonic Refiner to Active DSPs in DSP Manager,\n"
                L"then try again."
            ),
            L"Sonic Refiner",
            MB_OK | MB_ICONINFORMATION
        );
        return;
    }

    if (match_count > 1) {
        ::MessageBoxW(
            owner,
            localized(
                language,
                L"Sonic Refinerが複数のDSPスロットに登録されています。\n\n"
                L"安全のため直接編集できません。\n"
                L"DSP Managerから設定してください。",
                L"Multiple Sonic Refiner instances are present in the DSP chain.\n\n"
                L"Direct editing is unavailable for safety.\n"
                L"Configure the desired instance from DSP Manager."
            ),
            L"Sonic Refiner",
            MB_OK | MB_ICONWARNING
        );
        return;
    }

    const dsp_preset_impl preset(chain.get_item(match_index));

    auto* dialog = new sonic_refiner_dialog(
        preset,
        g_direct_sonic_refiner_preset_callback,
        true,
        &g_direct_sonic_refiner_settings_window
    );

    const HWND window = dialog->Create(owner);
    if (!IsWindow(window)) {
        delete dialog;
        ::MessageBoxW(
            owner,
            localized(
                language,
                L"Sonic Refinerの設定画面を開けませんでした。",
                L"Could not open the Sonic Refiner settings window."
            ),
            L"Sonic Refiner",
            MB_OK | MB_ICONERROR
        );
        return;
    }

    g_direct_sonic_refiner_preset_callback.prepare(window);
    ::ShowWindow(window, SW_SHOW);
    ::SetForegroundWindow(window);
}

void run_config_popup(
    const dsp_preset& preset,
    HWND parent,
    dsp_preset_edit_callback& callback
) {
    if (IsWindow(g_direct_sonic_refiner_settings_window)) {
        activate_existing_sonic_refiner_dialog(
            g_direct_sonic_refiner_settings_window
        );
        return;
    }

    sonic_refiner_dialog dialog(
        preset,
        callback,
        false,
        &g_standard_sonic_refiner_settings_window
    );

    if (dialog.DoModal(parent) != IDOK) {
        callback.on_preset_changed(preset);
    }
}

class mainmenu_commands_sonic_refiner_settings
    : public mainmenu_commands {
public:
    t_uint32 get_command_count() override {
        return 1;
    }

    GUID get_command(t_uint32 index) override {
        if (index != 0) {
            uBugCheck();
        }
        return guid_mainmenu_open_sonic_refiner_settings;
    }

    void get_name(
        t_uint32 index,
        pfc::string_base& out
    ) override {
        if (index != 0) {
            uBugCheck();
        }

        if (is_english(load_ui_language())) {
            out = "Sonic Refiner Settings...";
        } else {
            out = "Sonic Refiner の設定...";
        }
    }

    bool get_description(
        t_uint32 index,
        pfc::string_base& out
    ) override {
        if (index != 0) {
            uBugCheck();
        }

        if (is_english(load_ui_language())) {
            out = "Opens the Sonic Refiner settings dialog directly.";
        } else {
            out = "Sonic Refinerの設定画面を直接開きます。";
        }
        return true;
    }

    GUID get_parent() override {
        return mainmenu_groups::playback;
    }

    void execute(
        t_uint32 index,
        service_ptr_t<service_base>
    ) override {
        if (index != 0) {
            uBugCheck();
        }
        show_sonic_refiner_settings_from_main_menu();
    }
};

static mainmenu_commands_factory_t<
    mainmenu_commands_sonic_refiner_settings
> g_mainmenu_commands_sonic_refiner_settings_factory;

#endif

} // namespace
