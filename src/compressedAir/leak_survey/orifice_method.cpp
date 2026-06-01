#include "compressedAir/leak_survey/orifice_method.h"

namespace orifice_method {

Result calculate(const Input& input) {
    const double air_temp_rankine = input.air_temp + physics::conversions::kFahrenheitToRankineOffset;
    const double abs_supply_pressure = input.atm_pressure + input.supply_pressure;

    // Ideal gas densities: rho = P * 144 / (R_air * T_R)
    // Factor 144 converts psia (lbf/in²) to lbf/ft²
    const double ca_density =
        abs_supply_pressure * physics::conversions::kIn2PerFt2 /
        (physics::us::kSpecificGasConstantAir * air_temp_rankine);

    const double standard_density =
        input.atm_pressure * physics::conversions::kIn2PerFt2 /
        (physics::us::kSpecificGasConstantAir * air_temp_rankine);

    // Isentropic choked-flow relations (gamma = 1.4 for dry air)
    const double sonic_density =
        ca_density *
        std::pow(2.0 / (physics::us::kGammaAir + 1.0),
                 1.0 / (physics::us::kGammaAir - 1.0));

    const double leak_velocity =
        std::sqrt((2.0 * physics::us::kGammaAir / (physics::us::kGammaAir + 1.0)) *
                  physics::us::kSpecificGasConstantAir * air_temp_rankine *
                  physics::us::kStandardGravityApprox);

    // Orifice area in ft²: A = pi * d² / (4 * 144)   (d in inches)
    const double orifice_area =
        physics::kPi * input.diameter * input.diameter /
        (4.0 * physics::conversions::kIn2PerFt2);

    // Mass flow per orifice [lbm/min]: rho* * A * V* * 60 * Cd
    const double leak_rate_lbm_min =
        sonic_density * orifice_area * leak_velocity *
        physics::conversions::kSecondsPerMinute * input.discharge_coef;

    const double leak_rate_scfm     = leak_rate_lbm_min / standard_density;
    const double leak_rate_estimate = leak_rate_scfm * static_cast<double>(input.num_orifices);
    const double annual_consumption =
        (input.operating_time * leak_rate_estimate * physics::conversions::kMinutesPerHour) / 1000.0;

    return {standard_density, sonic_density,      leak_velocity,
            leak_rate_lbm_min, leak_rate_scfm, leak_rate_estimate,
            annual_consumption};
}

} // namespace orifice_method
