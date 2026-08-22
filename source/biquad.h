#pragma once

namespace sonic_refiner {

class biquad {
public:
    void reset() noexcept {
        z1_ = 0.0;
        z2_ = 0.0;
    }

    void set_low_shelf(double sample_rate, double frequency_hz, double gain_db, bool reset_state = true) noexcept {
        if (!prepare_frequency(sample_rate, frequency_hz)) {
            set_identity(reset_state);
            return;
        }

        constexpr double slope = 1.0;

        const double a = std::pow(10.0, gain_db / 40.0);
        const double omega = two_pi_ * frequency_hz / sample_rate;
        const double cos_omega = std::cos(omega);
        const double sin_omega = std::sin(omega);
        const double alpha = shelf_alpha(a, sin_omega, slope);
        const double two_sqrt_a_alpha = 2.0 * std::sqrt(a) * alpha;

        const double b0 = a * ((a + 1.0) - (a - 1.0) * cos_omega + two_sqrt_a_alpha);
        const double b1 = 2.0 * a * ((a - 1.0) - (a + 1.0) * cos_omega);
        const double b2 = a * ((a + 1.0) - (a - 1.0) * cos_omega - two_sqrt_a_alpha);
        const double a0 = (a + 1.0) + (a - 1.0) * cos_omega + two_sqrt_a_alpha;
        const double a1 = -2.0 * ((a - 1.0) + (a + 1.0) * cos_omega);
        const double a2 = (a + 1.0) + (a - 1.0) * cos_omega - two_sqrt_a_alpha;

        set_coefficients(b0, b1, b2, a0, a1, a2, reset_state);
    }

    void set_high_shelf(double sample_rate, double frequency_hz, double gain_db, bool reset_state = true) noexcept {
        if (!prepare_frequency(sample_rate, frequency_hz)) {
            set_identity(reset_state);
            return;
        }

        constexpr double slope = 1.0;

        const double a = std::pow(10.0, gain_db / 40.0);
        const double omega = two_pi_ * frequency_hz / sample_rate;
        const double cos_omega = std::cos(omega);
        const double sin_omega = std::sin(omega);
        const double alpha = shelf_alpha(a, sin_omega, slope);
        const double two_sqrt_a_alpha = 2.0 * std::sqrt(a) * alpha;

        const double b0 = a * ((a + 1.0) + (a - 1.0) * cos_omega + two_sqrt_a_alpha);
        const double b1 = -2.0 * a * ((a - 1.0) + (a + 1.0) * cos_omega);
        const double b2 = a * ((a + 1.0) + (a - 1.0) * cos_omega - two_sqrt_a_alpha);
        const double a0 = (a + 1.0) - (a - 1.0) * cos_omega + two_sqrt_a_alpha;
        const double a1 = 2.0 * ((a - 1.0) - (a + 1.0) * cos_omega);
        const double a2 = (a + 1.0) - (a - 1.0) * cos_omega - two_sqrt_a_alpha;

        set_coefficients(b0, b1, b2, a0, a1, a2, reset_state);
    }

    void set_peaking_eq(
        double sample_rate,
        double frequency_hz,
        double gain_db,
        double q = 1.0,
        bool reset_state = true
    ) noexcept {
        if (!prepare_frequency(sample_rate, frequency_hz) ||
            !std::isfinite(gain_db) ||
            !std::isfinite(q) ||
            q <= 0.0) {
            set_identity(reset_state);
            return;
        }

        const double a = std::pow(10.0, gain_db / 40.0);
        const double omega =
            two_pi_ * frequency_hz / sample_rate;
        const double cos_omega = std::cos(omega);
        const double sin_omega = std::sin(omega);
        const double alpha = sin_omega / (2.0 * q);

        const double b0 = 1.0 + (alpha * a);
        const double b1 = -2.0 * cos_omega;
        const double b2 = 1.0 - (alpha * a);
        const double a0 = 1.0 + (alpha / a);
        const double a1 = -2.0 * cos_omega;
        const double a2 = 1.0 - (alpha / a);

        set_coefficients(
            b0, b1, b2,
            a0, a1, a2,
            reset_state
        );
    }

    void set_low_pass(
        double sample_rate,
        double frequency_hz,
        double q = 0.7071067811865476,
        bool reset_state = true
    ) noexcept {
        if (!prepare_frequency(sample_rate, frequency_hz) ||
            !std::isfinite(q) || q <= 0.0) {
            set_identity(reset_state);
            return;
        }

        const double omega = two_pi_ * frequency_hz / sample_rate;
        const double cos_omega = std::cos(omega);
        const double sin_omega = std::sin(omega);
        const double alpha = sin_omega / (2.0 * q);

        const double b0 = (1.0 - cos_omega) * 0.5;
        const double b1 = 1.0 - cos_omega;
        const double b2 = (1.0 - cos_omega) * 0.5;
        const double a0 = 1.0 + alpha;
        const double a1 = -2.0 * cos_omega;
        const double a2 = 1.0 - alpha;

        set_coefficients(
            b0, b1, b2, a0, a1, a2, reset_state
        );
    }

    void set_high_pass(
        double sample_rate,
        double frequency_hz,
        double q = 0.7071067811865476,
        bool reset_state = true
    ) noexcept {
        if (!prepare_frequency(sample_rate, frequency_hz) ||
            !std::isfinite(q) || q <= 0.0) {
            set_identity(reset_state);
            return;
        }

        const double omega = two_pi_ * frequency_hz / sample_rate;
        const double cos_omega = std::cos(omega);
        const double sin_omega = std::sin(omega);
        const double alpha = sin_omega / (2.0 * q);

        const double b0 = (1.0 + cos_omega) * 0.5;
        const double b1 = -(1.0 + cos_omega);
        const double b2 = (1.0 + cos_omega) * 0.5;
        const double a0 = 1.0 + alpha;
        const double a1 = -2.0 * cos_omega;
        const double a2 = 1.0 - alpha;

        set_coefficients(
            b0, b1, b2, a0, a1, a2, reset_state
        );
    }

    audio_sample process(audio_sample input) noexcept {
        const double x = static_cast<double>(input);
        const double output = (b0_ * x) + z1_;

        z1_ = (b1_ * x) - (a1_ * output) + z2_;
        z2_ = (b2_ * x) - (a2_ * output);

        if (!std::isfinite(output) || !std::isfinite(z1_) || !std::isfinite(z2_)) {
            reset();
            return input;
        }

        return static_cast<audio_sample>(output);
    }

private:
    bool prepare_frequency(double sample_rate, double& frequency_hz) const noexcept {
        if (!std::isfinite(sample_rate) || !std::isfinite(frequency_hz) ||
            sample_rate <= 0.0 || frequency_hz <= 0.0) {
            return false;
        }

        const double nyquist = sample_rate * 0.5;
        if (nyquist <= 10.0) {
            return false;
        }

        frequency_hz = std::clamp(frequency_hz, 10.0, nyquist * 0.95);
        return true;
    }

    static double shelf_alpha(double a, double sin_omega, double slope) noexcept {
        const double expression =
            (a + (1.0 / a)) * ((1.0 / slope) - 1.0) + 2.0;

        if (!std::isfinite(expression) || expression < 0.0) {
            return 0.0;
        }

        return (sin_omega * 0.5) * std::sqrt(expression);
    }

    void set_coefficients(
        double b0,
        double b1,
        double b2,
        double a0,
        double a1,
        double a2,
        bool reset_state
    ) noexcept {
        if (!std::isfinite(a0) || std::abs(a0) < 1.0e-20 ||
            !std::isfinite(b0) || !std::isfinite(b1) || !std::isfinite(b2) ||
            !std::isfinite(a1) || !std::isfinite(a2)) {
            set_identity(reset_state);
            return;
        }

        b0_ = b0 / a0;
        b1_ = b1 / a0;
        b2_ = b2 / a0;
        a1_ = a1 / a0;
        a2_ = a2 / a0;
        if (reset_state) {
            reset();
        }
    }

    void set_identity(bool reset_state = true) noexcept {
        b0_ = 1.0;
        b1_ = 0.0;
        b2_ = 0.0;
        a1_ = 0.0;
        a2_ = 0.0;
        if (reset_state) {
            reset();
        }
    }

    static constexpr double two_pi_ =
        6.283185307179586476925286766559;

    double b0_ = 1.0;
    double b1_ = 0.0;
    double b2_ = 0.0;
    double a1_ = 0.0;
    double a2_ = 0.0;

    double z1_ = 0.0;
    double z2_ = 0.0;
};

} // namespace sonic_refiner
