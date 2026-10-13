#include "motorDriven/motor/estimate_fla.h"

#include <array>
#include <cstddef>
#include <cmath>

#include "motorDriven/motor/motor_efficiency.h"
#include "motorDriven/motor/poles.h"

namespace estimate_fla {
namespace {

using Coefficients = std::array<std::array<double, 6>, 5>;
using CurrentAnchors = std::array<double, 6>;

enum CurveCoefficient : std::size_t {
    kCoefficientA = 0,
    kCoefficientB,
    kCoefficientD,
    kCoefficientE,
    kCoefficientF,
};

// The coefficient curves are calibrated at this line voltage. It is a
// model-specific reference value, rather than a physical conversion constant.
constexpr double kReferenceVoltage = 460.0;
constexpr std::size_t kFullLoadIntervalIndex = 4;

const Coefficients kBasicCurrentCurveCoefficients = {{
    {{1.07000005, 1.07860196, 1.11131799, 1.20000005, 1.25399995, 1.296}},
    {{0.04457, 0.06776789, 0.1038059, 0.09800907, 0.10241948, 0.1058498}},
    {{0.00075042, 0.00112793, 0.00208467, 0.00239285, 0.00239285, 0.00239285}},
    {{0.1177211, 0.1706723, 0.3346993, 0.44619089, 0.46626949, 0.48188618}},
    {{0.0328443, 0.03456966, 0.1037901, 0.07508431, 0.07508431, 0.07508431}},
}};

const Coefficients kEnergyEfficientCurrentMultiplierCoefficients = {{
    {{0.99800003, 0.99959999, 0.99800003, 0.995, 0.995, 0.995}},
    {{-0.00686105, -0.00768858, -0.01313299, -0.02334039, -0.02334039, -0.02334039}},
    {{0.00086324, 0.00471104, 0.01482941, 0.05637734, 0.05637734, 0.05637734}},
    {{-0.02477271, -0.01760195, -0.2489823, -0.79541528, -0.79541528, -0.79541528}},
    {{0.07267418, 0.04482816, 0.63720071, 0.59844083, 0.59844083, 0.59844083}},
}};

const Coefficients kStandardCurrentMultiplierCoefficients = {{
    {{1.00199997, 1.00150001, 1.00399995, 1.005, 1.005, 1.005}},
    {{0.0305805, 0.02305459, 0.06148619, 0.04535436, 0.04535436, 0.04535436}},
    {{0.00538086, 0.00630689, 0.01415263, 0.01991553, 0.01991553, 0.01991553}},
    {{0.02411943, 0.02706193, 1.247298, 24.98793983, 24.98793983, 24.98793983}},
    {{0.03430828, 0.01757208, 0.72734421, 1.14514899, 1.14514899, 1.14514899}},
}};

const std::array<std::array<double, 3>, 5> kPremiumCurrentMultiplierCoefficients = {{
    {{0.972803032, 0.988822468, 0.990453682}},
    {{2.132557437, 0.385982899, -0.775656291}},
    {{0.013323999, 0.410275377, 0.078563841}},
    {{-2.145127031, -0.045828557, 0.735405576}},
    {{0.013678436, 0.057848012, 0.071461107}},
}};

Coefficients calculate_partial_load_coefficients(const int pole) {
    if (pole == 0) {
        return {{{{0.2385152, 0.31999999, 0.51999998, 0.75400001, 1, 1.253}},
                 {{0.04319932, 0.03559835, 0.02311537, 0.00837315, 0, 0}},
                 {{0.01191111, 0.00243387, 0.00018377, 0.00013998, 0, 0}},
                 {{0.176818, 0.1282783, 0.08376596, 0.03318606, 0, 0}},
                 {{0.1847319, 0.1831789, 0.16219489, 0.1855139, 0, 0}}}};
    }
    else if (pole == 1) {
        return {{{{0.26803651, 0.3535319, 0.54000002, 0.76428652, 1, 1.251}},
                 {{0.08, 0.06387088, 0.02691548, 0.0081415, 0, 0}},
                 {{0.01172604, 0.01068725, 0.00297117, 0.00686711, 0, 0}},
                 {{0.2029126, 0.1705882, 0.09793611, 0.0471422, 0, 0}},
                 {{0.15413959, 0.1315202, 0.09374535, 0.1191377, 0, 0}}}};
    }
    else if (pole == 2) {
        return {{{{0.28999999, 0.39519981, 0.55500001, 0.76973772, 1, 1.254}},
                 {{0.07532283, 0.06387088, 0.03, 0.02362101, 0, 0}},
                 {{0.00291026, 0.01068725, 0.00380051, 0.08841167, 0, 0}},
                 {{0.2405144, 0.1705882, 0.13686571, 0.02321446, 0, 0}},
                 {{0.09842682, 0.1315202, 0.15484551, 0.08854395, 0, 0}}}};
    }
    else if (pole == 3) {
        return {{{{0.33000001, 0.43000001, 0.56062472, 0.78429687, 1, 1.237}},
                 {{0.06, 0.1060414, 0.04872012, 0.00763685, 0, 0}},
                 {{0.00125301, 0.031788, 0.00041673, 0.0023581, 0, 0}},
                 {{0.1939563, 0.115, 0.0841061, 0.00756603, 0, 0}},
                 {{0.05575958, 0.15824869, 0.05538078, 0.00250876, 0, 0}}}};
    }
    else if (pole == 4) {
        return {{{{0.37, 0.44, 0.57857579, 0.78581947, 1, 1.233}},
                 {{0.04507853, 0.04205693, 0.06270286, 0.01749944, 0, 0}},
                 {{0.00098519, 0.00121622, 0.0005819, 0.00068763, 0, 0}},
                 {{0.20683549, 0.1764105, 0.08895831, 0.01809594, 0, 0}},
                 {{0.0551472, 0.05516704, 0.05197735, 0.03981217, 0, 0}}}};
    }
    // pole == 5 here
    return {{{{0.41999999, 0.5, 0.61000001, 0.80000001, 1, 1.215}},
             {{0.04507853, 0.04205693, 0.06270286, 0.01749944, 0, 0}},
             {{0.00098519, 0.00121622, 0.0005819, 0.00068763, 0, 0}},
             {{0.20683549, 0.1764105, 0.08895831, 0.01809594, 0, 0}},
             {{0.0551472, 0.05516704, 0.05197735, 0.03981217, 0, 0}}}};
}

template <std::size_t Width>
double evaluate_curve(const std::array<std::array<double, Width>, 5>& coefficients, const int pole,
                      const double motor_rated_power) {
    return coefficients[kCoefficientA][pole] +
           coefficients[kCoefficientB][pole] * std::exp(-coefficients[kCoefficientD][pole] * motor_rated_power) +
           coefficients[kCoefficientE][pole] * std::exp(-coefficients[kCoefficientF][pole] * motor_rated_power);
}

CurrentAnchors calculate_partial_load_multipliers(const Coefficients& coefficients, const double motor_rated_power) {
    CurrentAnchors multipliers {};
    for (std::size_t interval = 0; interval < multipliers.size(); ++interval) {
        multipliers[interval] = coefficients[kCoefficientA][interval] +
                                coefficients[kCoefficientB][interval] *
                                    std::exp(-coefficients[kCoefficientD][interval] * motor_rated_power) +
                                coefficients[kCoefficientE][interval] *
                                    std::exp(-coefficients[kCoefficientF][interval] * motor_rated_power);
    }
    return multipliers;
}

CurrentAnchors calculate_partial_load_currents(const double reference_current,
                                               const CurrentAnchors& partial_load_multipliers) {
    CurrentAnchors currents {};
    for (std::size_t interval = 0; interval < currents.size(); ++interval) {
        currents[interval] = reference_current * partial_load_multipliers[interval];
    }
    return currents;
}

struct CurrentModel {
    CurrentAnchors partial_load_currents;
    double specified_efficiency_baseline;
};

CurrentModel make_current_model(const double reference_class_current,
                                const CurrentAnchors& partial_load_multipliers,
                                const double specified_efficiency_baseline = 0.0) {
    return {calculate_partial_load_currents(reference_class_current, partial_load_multipliers),
            specified_efficiency_baseline};
}

CurrentModel select_current_model(const Input& input, const int pole,
                                  const CurrentAnchors& partial_load_multipliers) {
    const double basic_reference_current =
        input.motor_rated_power * evaluate_curve(kBasicCurrentCurveCoefficients, pole, input.motor_rated_power);
    const double standard_reference_current =
        basic_reference_current * evaluate_curve(kStandardCurrentMultiplierCoefficients, pole, input.motor_rated_power);
    const double energy_efficient_reference_current = basic_reference_current *
                                                      evaluate_curve(kEnergyEfficientCurrentMultiplierCoefficients, pole,
                                                                     input.motor_rated_power);

    switch (input.efficiency_class) {
    case Motor::EfficiencyClass::PREMIUM:
        return make_current_model(
            basic_reference_current *
                evaluate_curve(kPremiumCurrentMultiplierCoefficients, pole, input.motor_rated_power),
            partial_load_multipliers);
    case Motor::EfficiencyClass::ENERGY_EFFICIENT:
        return make_current_model(energy_efficient_reference_current, partial_load_multipliers);
    case Motor::EfficiencyClass::STANDARD:
        return make_current_model(standard_reference_current, partial_load_multipliers);
    case Motor::EfficiencyClass::SPECIFIED: {
        const double standard_efficiency = motor_efficiency::calculate(
                                               {input.line_frequency, input.motor_rpm,
                                                Motor::EfficiencyClass::STANDARD, input.motor_rated_power, 1,
                                                input.specified_efficiency})
                                               .efficiency;
        const double energy_efficient_efficiency = motor_efficiency::calculate(
                                                       {input.line_frequency, input.motor_rpm,
                                                        Motor::EfficiencyClass::ENERGY_EFFICIENT,
                                                        input.motor_rated_power, 1, input.specified_efficiency})
                                                       .efficiency;
        if (std::fabs(standard_efficiency - input.specified_efficiency) <
            std::fabs(energy_efficient_efficiency - input.specified_efficiency)) {
            return make_current_model(standard_reference_current, partial_load_multipliers, standard_efficiency);
        }
        return make_current_model(energy_efficient_reference_current, partial_load_multipliers,
                                  energy_efficient_efficiency);
    }
    }

    return {};
}

double adjust_full_load_current(const Input& input, const CurrentModel& model) {
    double estimated_fla =
        model.partial_load_currents[kFullLoadIntervalIndex] * kReferenceVoltage / input.rated_voltage;
    if (input.efficiency_class == Motor::EfficiencyClass::SPECIFIED) {
        estimated_fla *= model.specified_efficiency_baseline / input.specified_efficiency;
    }
    return estimated_fla;
}

} // namespace

Result calculate(const Input& input) {
    const int pole = (poles::calculate(input.motor_rpm, input.line_frequency) / 2) - 1;
    const CurrentAnchors partial_load_multipliers =
        calculate_partial_load_multipliers(calculate_partial_load_coefficients(pole), input.motor_rated_power);
    const CurrentModel model = select_current_model(input, pole, partial_load_multipliers);

    // Preserve the legacy semantics: voltage and specified-efficiency corrections
    // apply only to the estimated full-load current, not to the six curve anchors.
    return {adjust_full_load_current(input, model), model.partial_load_currents};
}

} // namespace estimate_fla
