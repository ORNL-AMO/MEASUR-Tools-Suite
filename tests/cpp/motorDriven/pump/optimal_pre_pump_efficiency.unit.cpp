#include "motorDriven/pump/optimal_pre_pump_efficiency.h"

#include <cmath>
#include <limits>
#include <iterator>

#include "catch.hpp"
#include "motorDriven/pump/pump_efficiency.h"

namespace {
constexpr double relative_percent_tolerance = 1e-14;
constexpr double absolute_percent_tolerance = 1e-12;
constexpr double relative_fraction_tolerance = 1e-14;
constexpr double absolute_fraction_tolerance = 1e-15;
const double infinity = std::numeric_limits<double>::infinity();
const double quiet_nan = std::numeric_limits<double>::quiet_NaN();

void check_percent(double actual, double expected) {
    if (std::isnan(expected)) {
        CHECK(std::isnan(actual));
    } else if (std::isinf(expected)) {
        CHECK(actual == expected);
    } else {
        CHECK(std::abs(actual - expected) <= absolute_percent_tolerance + std::abs(expected) * relative_percent_tolerance);
    }
}
} // namespace

TEST_CASE("Pre-pump efficiency preserves all styles and numeric boundaries", "[optimal_pre_pump_efficiency]") {
    // Immutable legacy captures: 666f224, Apple clang 21, arm64, -O3 -DNDEBUG -std=gnu++20.
    // Portable acceptance is separate from exact legacy/current comparisons on each platform.
    const double flows[] = {0.001, 1, 100, 500, 1000, 2000, 5000, 10000, 100000, 0.0, -0.0, -1, -1000, 1e-300, 2.2250738585072014e-308, 4.9406564584124654e-324, 1.7976931348623157e+308, infinity, -infinity, quiet_nan};
    struct Fixture { Pump::Style style; double expected[20]; };
    const Fixture fixtures[] = {
        {Pump::Style::END_SUCTION_SLURRY, {
            23.990318897386416, 24.166542914393645, 37.604958139262777, 57.18821716442406, 65.271534555431273,
            72.997867334984136, 79.577936321323904, 83.339755523798303, 85.957483662816884, 23.990141999999992,
            23.990141999999992, 23.812745033010032, -15226.473089786881, 23.990141999999992, 23.990141999999992,
            23.990141999999992, 85.957483999999994, 85.957483999999994, -infinity, quiet_nan}},
        {Pump::Style::END_SUCTION_SEWAGE, {
            22.400209134352373, 22.634470009438807, 40.581413990584061, 64.987909448342862, 71.87699271025599,
            77.872881242496064, 83.126723112034895, 85.63699468136879, 89.681425194978274, 22.399974,
            22.399974, 22.164197565131261, -12495.729639822215, 22.399974, 22.399974,
            22.399974, 89.704526000000001, 89.704526000000001, -infinity, quiet_nan}},
        {Pump::Style::END_SUCTION_STOCK, {
            52.834059739884374, 52.88170936957691, 57.207475269099447, 68.719154239133118, 75.575287270852812,
            80.59094257557372, 84.536770890235928, 86.726233689948316, 90.121186232840785, 52.834012000000001,
            52.834012000000001, 52.786229462647711, -83.145910557428081, 52.834012000000001, 52.834012000000001,
            52.834012000000001, 90.158463999999995, 90.158463999999995, -infinity, quiet_nan}},
        {Pump::Style::END_SUCTION_SUBMERSIBLE_SEWAGE, {
            22.400209134352373, 22.634470009438807, 40.581413990584061, 64.987909448342862, 71.87699271025599,
            77.872881242496064, 83.126723112034895, 85.63699468136879, 89.681425194978274, 22.399974,
            22.399974, 22.164197565131261, -12495.729639822215, 22.399974, 22.399974,
            22.399974, 89.704526000000001, 89.704526000000001, -infinity, quiet_nan}},
        {Pump::Style::API_DOUBLE_SUCTION, {
            52.834059739884374, 52.88170936957691, 57.207475269099447, 68.719154239133118, 75.575287270852812,
            80.59094257557372, 84.536770890235928, 86.726233689948316, 90.121186232840785, 52.834012000000001,
            52.834012000000001, 52.786229462647711, -83.145910557428081, 52.834012000000001, 52.834012000000001,
            52.834012000000001, 90.158463999999995, 90.158463999999995, -infinity, quiet_nan}},
        {Pump::Style::MULTISTAGE_BOILER_FEED, {
            39.49864857241014, 39.705372025798091, 55.042345907214809, 74.196725779157518, 79.533102946097571,
            83.026286383998098, 85.77136500528448, 86.893672109662376, 87.129683999999997, 39.498441,
            39.498441, 39.290223047896994, -24809.723424731757, 39.498441, 39.498441,
            39.498441, 87.129683999999997, 87.129683999999997, -infinity, quiet_nan}},
        {Pump::Style::END_SUCTION_ANSI_API, {
            45.293354756795964, 45.490211310462627, 59.55315850632195, 75.917583906682609, 80.893890555730152,
            83.970844379551124, 86.563517859353837, 87.565777275803356, 87.748473000000004, 45.293157000000008,
            45.293157000000008, 45.094692596657467, -69416.904220929922, 45.293157000000008, 45.293157000000008,
            45.293157000000008, 87.748473000000004, 87.748473000000004, -infinity, quiet_nan}},
        {Pump::Style::AXIAL_FLOW, {
            68.669608886435569, 68.712877004526504, 72.344666163754042, 79.449461614546152, 82.49098752707944,
            85.009592728133512, 87.60387559206886, 89.011767712603586, 90.124014639823841, 68.669565500000004,
            68.669565500000004, 68.626103790777663, -413.07652228725851, 68.669565500000004, 68.669565500000004,
            68.669565500000004, 90.124015999999997, 90.124015999999997, -infinity, quiet_nan}},
        {Pump::Style::DOUBLE_SUCTION, {
            74.247056696214159, 74.271299320677613, 76.407288404218136, 81.437568326854944, 84.032600232095177,
            86.145509250195346, 88.718275611425099, 89.954519635493838, 90.99998817272899, 74.247032399999995,
            74.247032399999995, 74.222706782182257, -37.72331497644187, 74.247032399999995, 74.247032399999995,
            74.247032399999995, 91, 91, -infinity, quiet_nan}},
        {Pump::Style::VERTICAL_TURBINE, {
            68.669608886435569, 68.712877004526504, 72.344666163754042, 79.449461614546152, 82.49098752707944,
            85.009592728133512, 87.60387559206886, 89.011767712603586, 90.124014639823841, 68.669565500000004,
            68.669565500000004, 68.626103790777663, -413.07652228725851, 68.669565500000004, 68.669565500000004,
            68.669565500000004, 90.124015999999997, 90.124015999999997, -infinity, quiet_nan}},
        {Pump::Style::LARGE_END_SUCTION, {
            82.560292021695815, 82.56131260644139, 82.661571380762723, 83.049453117618981, 83.497852838537767,
            84.286619547930314, 85.992734267123993, 87.529969773203803, 90.279678492972991, 82.560290999999992,
            82.560290999999992, 82.559269214601571, 81.443238583447624, 82.560290999999992, 82.560290999999992,
            82.560290999999992, 90.379273999999995, 90.379273999999995, -infinity, quiet_nan}},
        {Pump::Style::SPECIFIED_OPTIMAL_EFFICIENCY, {
            0, 0, 0, 0, 0,
            0, 0, 0, 0, 0,
            0, 0, 0, 0, 0,
            0, 0, 0, 0, 0}},
        {Pump::Style::POSITIVE_DISPLACEMENT, {
            0, 0, 0, 0, 0,
            0, 0, 0, 0, 0,
            0, 0, 0, 0, 0,
            0, 0, 0, 0, 0}},
    };
    for (const auto& fixture : fixtures) {
        for (unsigned i = 0; i < std::size(flows); ++i) {
            const optimal_pre_pump_efficiency::Input input{fixture.style, flows[i]};
            const double actual = optimal_pre_pump_efficiency::calculate(input);
            CAPTURE(fixture.style, flows[i], actual, fixture.expected[i]);
            check_percent(actual, fixture.expected[i]);
            // A second call after an unrelated nonfinite duty must be independent of earlier calls.
            optimal_pre_pump_efficiency::calculate({Pump::Style::DOUBLE_SUCTION, quiet_nan});
            check_percent(optimal_pre_pump_efficiency::calculate(input), fixture.expected[i]);
        }
    }
    for (const auto style : {static_cast<Pump::Style>(-1), static_cast<Pump::Style>(13)}) {
        for (const double flow : flows) {
            CHECK(optimal_pre_pump_efficiency::calculate({style, flow}) == 0.0);
        }
    }
}

TEST_CASE("Pre-pump efficiency retains strict curve boundaries", "[optimal_pre_pump_efficiency]") {
    struct Fixture { Pump::Style style; double threshold; double below; double at; double above; };
    const Fixture fixtures[] = {
        {Pump::Style::DOUBLE_SUCTION, 9000, 89.802851476388838, 89.804162620322515, 89.804162620322515},
        {Pump::Style::VERTICAL_TURBINE, 2550, 85.767055860241015, 85.768012551311003, 85.768012551311003},
        {Pump::Style::AXIAL_FLOW, 2550, 85.767055860241015, 85.768012551311003, 85.768012551311003},
        {Pump::Style::VERTICAL_TURBINE, 7220, 88.431019933984075, 88.429924607793865, 88.429924607793865},
        {Pump::Style::AXIAL_FLOW, 7220, 88.431019933984075, 88.429924607793865, 88.429924607793865},
        {Pump::Style::END_SUCTION_ANSI_API, 1030, 81.071829771252183, 81.071493631455823, 81.071493631455823},
        {Pump::Style::MULTISTAGE_BOILER_FEED, 890, 78.733213659923905, 78.733425728709335, 78.733425728709335},
        {Pump::Style::API_DOUBLE_SUCTION, 4440, 84.125657475720729, 84.125701188488691, 84.125701188488691},
        {Pump::Style::END_SUCTION_STOCK, 4440, 84.125657475720729, 84.125701188488691, 84.125701188488691},
        {Pump::Style::END_SUCTION_SEWAGE, 2170, 78.518747493498751, 78.519292317337801, 78.519292317337801},
        {Pump::Style::END_SUCTION_SUBMERSIBLE_SEWAGE, 2170, 78.518747493498751, 78.519292317337801, 78.519292317337801},
        {Pump::Style::END_SUCTION_SLURRY, 1690, 71.382670018721427, 71.382430878931473, 71.382430878931473},
    };
    for (const auto& fixture : fixtures) {
        CAPTURE(fixture.style, fixture.threshold);
        check_percent(optimal_pre_pump_efficiency::calculate({fixture.style, std::nextafter(fixture.threshold, -infinity)}), fixture.below);
        check_percent(optimal_pre_pump_efficiency::calculate({fixture.style, fixture.threshold}), fixture.at);
        check_percent(optimal_pre_pump_efficiency::calculate({fixture.style, std::nextafter(fixture.threshold, infinity)}), fixture.above);
    }
}

TEST_CASE("Pre-pump efficiency retains equivalent style groups", "[optimal_pre_pump_efficiency]") {
    const Pump::Style groups[][2] = {
        {Pump::Style::VERTICAL_TURBINE, Pump::Style::AXIAL_FLOW},
        {Pump::Style::API_DOUBLE_SUCTION, Pump::Style::END_SUCTION_STOCK},
        {Pump::Style::END_SUCTION_SEWAGE, Pump::Style::END_SUCTION_SUBMERSIBLE_SEWAGE},
    };
    for (const auto& group : groups) {
        for (const double flow : {0.0, 100.0, 2000.0, 5000.0, 10000.0, infinity}) {
            CHECK(optimal_pre_pump_efficiency::calculate({group[0], flow}) ==
                  optimal_pre_pump_efficiency::calculate({group[1], flow}));
        }
    }
}

TEST_CASE("Pre-pump efficiency migration preserves composite fractions", "[optimal_pre_pump_efficiency]") {
    struct Fixture { Pump::Style style; double flow; double average; double maximum; };
    const Fixture fixtures[] = {
        {Pump::Style::END_SUCTION_SLURRY, 100, 0.30716859847864231, 0.33778841732326587},
        {Pump::Style::END_SUCTION_SLURRY, 2000, 0.72960709313227678, 0.75589073588267208},
        {Pump::Style::END_SUCTION_SLURRY, 10000, 0.82110213196336113, 0.83842443360912178},
        {Pump::Style::END_SUCTION_SEWAGE, 100, 0.3369133438188715, 0.37049824020855737},
        {Pump::Style::END_SUCTION_SEWAGE, 2000, 0.77835723220739605, 0.8063970684646028},
        {Pump::Style::END_SUCTION_SEWAGE, 10000, 0.84407452353906609, 0.86188146002001753},
        {Pump::Style::END_SUCTION_STOCK, 100, 0.50306328302289338, 0.55321068308212706},
        {Pump::Style::END_SUCTION_STOCK, 2000, 0.80553784553817265, 0.83455684652287099},
        {Pump::Style::END_SUCTION_STOCK, 10000, 0.85496691362486132, 0.873003640358894},
        {Pump::Style::END_SUCTION_SUBMERSIBLE_SEWAGE, 100, 0.3369133438188715, 0.37049824020855737},
        {Pump::Style::END_SUCTION_SUBMERSIBLE_SEWAGE, 2000, 0.77835723220739605, 0.8063970684646028},
        {Pump::Style::END_SUCTION_SUBMERSIBLE_SEWAGE, 10000, 0.84407452353906609, 0.86188146002001753},
        {Pump::Style::API_DOUBLE_SUCTION, 100, 0.50306328302289338, 0.55321068308212706},
        {Pump::Style::API_DOUBLE_SUCTION, 2000, 0.80553784553817265, 0.83455684652287099},
        {Pump::Style::API_DOUBLE_SUCTION, 10000, 0.85496691362486132, 0.873003640358894},
        {Pump::Style::MULTISTAGE_BOILER_FEED, 100, 0.48142640187469049, 0.52941694936370065},
        {Pump::Style::MULTISTAGE_BOILER_FEED, 2000, 0.82989128362241638, 0.85978760210083882},
        {Pump::Style::MULTISTAGE_BOILER_FEED, 10000, 0.85664129782200193, 0.87471334804017231},
        {Pump::Style::END_SUCTION_ANSI_API, 100, 0.52650450104366642, 0.57898861733251594},
        {Pump::Style::END_SUCTION_ANSI_API, 2000, 0.83933686357794668, 0.86957345321252744},
        {Pump::Style::END_SUCTION_ANSI_API, 10000, 0.86336234948341173, 0.88157618971737128},
        {Pump::Style::AXIAL_FLOW, 100, 0.65433442925140728, 0.71956115420542743},
        {Pump::Style::AXIAL_FLOW, 2000, 0.84972434706377054, 0.88033513934466179},
        {Pump::Style::AXIAL_FLOW, 10000, 0.87782225385141399, 0.89634114605818049},
        {Pump::Style::DOUBLE_SUCTION, 100, 0.69493360827249473, 0.76420742499638716},
        {Pump::Style::DOUBLE_SUCTION, 2000, 0.86108351228438895, 0.89210351144308031},
        {Pump::Style::DOUBLE_SUCTION, 10000, 0.8872497730803165, 0.90596755203392865},
        {Pump::Style::VERTICAL_TURBINE, 100, 0.65276583471768901, 0.71783619577025237},
        {Pump::Style::VERTICAL_TURBINE, 2000, 0.83981846558582396, 0.87007240463386581},
        {Pump::Style::VERTICAL_TURBINE, 10000, 0.89001741255622002, 0.90879357874813316},
        {Pump::Style::LARGE_END_SUCTION, 100, 0.75743480557413378, 0.83293899658897552},
        {Pump::Style::LARGE_END_SUCTION, 2000, 0.84249461526173863, 0.87284496094108999},
        {Pump::Style::LARGE_END_SUCTION, 10000, 0.86300427445741612, 0.8812105605962508},
        {Pump::Style::SPECIFIED_OPTIMAL_EFFICIENCY, 100, -0.068630660524582845, -0.075472044711826516},
        {Pump::Style::SPECIFIED_OPTIMAL_EFFICIENCY, 2000, -0.00037158021756460174, -0.00038496616430705135},
        {Pump::Style::SPECIFIED_OPTIMAL_EFFICIENCY, 10000, -0.012295423274621822, -0.012554812481560099},
        {Pump::Style::POSITIVE_DISPLACEMENT, 100, -0.068630660524582845, -0.075472044711826516},
        {Pump::Style::POSITIVE_DISPLACEMENT, 2000, -0.00037158021756460174, -0.00038496616430705135},
        {Pump::Style::POSITIVE_DISPLACEMENT, 10000, -0.012295423274621822, -0.012554812481560099},
    };
    for (const auto& fixture : fixtures) {
        const auto result = pump_efficiency::calculate({fixture.style, 2000, 1.107, 1, fixture.flow, 137});
        CAPTURE(fixture.style, fixture.flow, result.average, result.max);
        CHECK(std::abs(result.average - fixture.average) <=
              absolute_fraction_tolerance + std::abs(fixture.average) * relative_fraction_tolerance);
        CHECK(std::abs(result.max - fixture.maximum) <=
              absolute_fraction_tolerance + std::abs(fixture.maximum) * relative_fraction_tolerance);
    }
}
