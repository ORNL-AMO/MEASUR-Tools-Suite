#include "compressedAir/dryer_operating_cost.h"

#include <emscripten/bind.h>

using namespace std;
using namespace emscripten;

EMSCRIPTEN_BINDINGS(dryer_operating_cost_class) {
    enum_<DryerOperatingCost::DryerType>("DryerType")
        .value("Heatless", DryerOperatingCost::DryerType::Heatless)
        .value("HeatedExternally", DryerOperatingCost::DryerType::HeatedExternally)
        .value("BlowerPurgeWithSweep", DryerOperatingCost::DryerType::BlowerPurgeWithSweep)
        .value("BlowerPurgeWithoutSweep", DryerOperatingCost::DryerType::BlowerPurgeWithoutSweep)
        .value("HeatOfCompressionHC", DryerOperatingCost::DryerType::HeatOfCompressionHC)
        .value("HeatOfCompressionSP", DryerOperatingCost::DryerType::HeatOfCompressionSP)
        .value("Refrigerated", DryerOperatingCost::DryerType::Refrigerated);

    class_<DryerOperatingCost::Output>("DryerOperatingCostOutput")
        .property("waterRemoved", &DryerOperatingCost::Output::waterRemoved)
        .property("totalCostPerYear", &DryerOperatingCost::Output::totalCostPerYear)
        .property("heaterPower", &DryerOperatingCost::Output::heaterPower)
        .property("heatingHoursPerDay", &DryerOperatingCost::Output::heatingHoursPerDay)
        .property("purgeRate", &DryerOperatingCost::Output::purgeRate)
        .property("designDDCPercentage", &DryerOperatingCost::Output::designDDCPercentage);

    /*
    Use the first constructor that does not require heater power, heating hours per day, purge rate and design DDC percentage
    as input for bindings, as these four parameters can be calculated within the class if not provided.
    The second constructor is also bound to allow users to provide heater power, heating hours per day, purge rate and design DDC percentage
    if these parameters information is available.
    Parameters of constructors:
        @param flowRate double, Flow Rate in SCFM (1 - 50,000 SCFM)
        @param pressure double, Pressure in psig (25 - 150 psig)
        @param temperature double, Temperature F (50 - 120 F)
        @param operatingHoursPerDay double, Hours for which the dryer operates per day - hours (1 - 24 hours)
        @param operatingDaysPerWeek double, Days for which the dryer operates per week - days ( 1 - 7 days)
        @param operatingWeeksPerYear double, Weeks for which the dryer operates per year - weeks (1 - 52 weeks)
        @param costOfElectricity double, Cost of electricity per kWh - $ ($0.01 - $0.20 per kWh)
        @param costOfCompressedAir double, Cost of compressed air per 1000 SCF - $ ($0.20 - $0.50 per 1000 SCF)
        @param costOfCoolingWater double, Cost of cooling water per 1000 gallons - $ ($0.25 - $10.00 per 1000 gallons)

        Additional parameter in second constructor:
        @param heaterPower double, Heater power rating in kW (0 - 1000 kW).
                If heater power is not known or needs to be computed set it to 0.
        @param heatingHoursPerDay double, Hours for which the dryer heater operates per day - hours (1 - 24 hours)
                If heating hours per day is not known or needs to be calculator default set it to 0.
                Calculator default for heating hours per day is
                18 hours for Heated Externally, Blower Purge With Sweep and Blower Purge Without Sweep dryers, and
                3 hours for Heat of Compression - HC dryer.
        @param purgeRate double, Purge rate for the dryer - percentage (0 - 100%)
                If purge rate is not known or needs to be calculated default set it to 0.
                Calculator default for purge rate is
                15% for Heatless dryer,
                7% for Heated Externally, Blower Purge With Sweep and Blower Purge Without Sweep dryers, and
                2% for Heat of Compression - HC dryer.
        @param designDDCPercentage double, Design DDC percentage for the dryer - percentage (0 - 100%)
                If design DDC percentage is not known or needs to be calculated default set it to 0.
               Calculator default for design DDC percentage is 16.33% for desiccant dryers.
     */
    class_<DryerOperatingCost>("DryerOperatingCost")
        .constructor<double, double, double, double, double, double, double, double, double>()
        .constructor<double, double, double, double, double, double, double, double, double, double, double, double, double>()
        .function("calculate", &DryerOperatingCost::calculate);
}