#pragma once

namespace sonic_refiner {

struct settings {
    float depth = 55.0f;
    float clarity = 45.0f;
    float width = 50.0f;
    float ambience = 40.0f;
    float output_gain_db = 0.0f;
    bool auto_headroom = true;
    bool level_matched_bypass = true;
    bool enabled = true;
};

inline constexpr GUID guid = {
    0x4a475126, 0x3a54, 0x4ccf,
    { 0x9e, 0x8a, 0xf8, 0x27, 0xee, 0xc2, 0x9e, 0x93 }
};

inline constexpr t_uint32 preset_version = 7;

inline settings sanitize(settings value) {
    value.depth = std::clamp(value.depth, 0.0f, 100.0f);
    value.clarity = std::clamp(value.clarity, 0.0f, 100.0f);
    value.width = std::clamp(value.width, 0.0f, 100.0f);
    value.ambience = std::clamp(value.ambience, 0.0f, 100.0f);

    const double clamped_output_gain = std::clamp(
        static_cast<double>(value.output_gain_db),
        -12.0,
        6.0
    );
    value.output_gain_db = static_cast<float>(
        std::round(clamped_output_gain * 2.0) / 2.0
    );

    return value;
}

inline void make_preset(const settings& value, dsp_preset& out) {
    const settings safe = sanitize(value);

    dsp_preset_builder builder;
    builder << preset_version;
    builder << safe.depth;
    builder << safe.clarity;
    builder << safe.width;
    builder << safe.ambience;
    builder << safe.output_gain_db;
    builder << static_cast<t_uint32>(safe.auto_headroom ? 1 : 0);
    builder << static_cast<t_uint32>(
        safe.level_matched_bypass ? 1 : 0
    );
    builder << static_cast<t_uint32>(safe.enabled ? 1 : 0);
    builder.finish(guid, out);
}

inline settings parse_preset(const dsp_preset& in) {
    settings value;

    try {
        t_uint32 version = 0;
        t_uint32 enabled = 1;
        t_uint32 auto_headroom = 1;
        t_uint32 level_matched_bypass = 1;

        dsp_preset_parser parser(in);
        parser >> version;

        if (version == 1) {
            parser >> value.depth;
            parser >> enabled;
            value.enabled = enabled != 0;
            return sanitize(value);
        }

        if (version == 2) {
            parser >> value.depth;
            parser >> value.clarity;
            parser >> enabled;
            value.enabled = enabled != 0;
            return sanitize(value);
        }

        if (version == 3) {
            parser >> value.depth;
            parser >> value.clarity;
            parser >> value.width;
            parser >> enabled;
            value.enabled = enabled != 0;
            return sanitize(value);
        }

        if (version == 4) {
            parser >> value.depth;
            parser >> value.clarity;
            parser >> value.width;
            parser >> value.ambience;
            parser >> enabled;
            value.enabled = enabled != 0;
            return sanitize(value);
        }

        if (version == 5) {
            parser >> value.depth;
            parser >> value.clarity;
            parser >> value.width;
            parser >> value.ambience;
            parser >> auto_headroom;
            parser >> enabled;
            value.auto_headroom = auto_headroom != 0;
            value.enabled = enabled != 0;
            return sanitize(value);
        }

        if (version == 6) {
            // Compatibility with legacy preview DSP preset data.
            // Output gain defaults to 0.0 dB.
            parser >> value.depth;
            parser >> value.clarity;
            parser >> value.width;
            parser >> value.ambience;
            parser >> auto_headroom;
            parser >> level_matched_bypass;
            parser >> enabled;
            value.auto_headroom = auto_headroom != 0;
            value.level_matched_bypass =
                level_matched_bypass != 0;
            value.enabled = enabled != 0;
            return sanitize(value);
        }

        if (version == preset_version) {
            parser >> value.depth;
            parser >> value.clarity;
            parser >> value.width;
            parser >> value.ambience;
            parser >> value.output_gain_db;
            parser >> auto_headroom;
            parser >> level_matched_bypass;
            parser >> enabled;
            value.auto_headroom = auto_headroom != 0;
            value.level_matched_bypass =
                level_matched_bypass != 0;
            value.enabled = enabled != 0;
            return sanitize(value);
        }

        return settings{};
    } catch (const exception_io_data&) {
        return settings{};
    }
}

} // namespace sonic_refiner
