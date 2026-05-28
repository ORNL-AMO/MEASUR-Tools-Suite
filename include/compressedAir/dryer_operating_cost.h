#pragma once

/**
 * @file
 * @brief Implementations of Desiccant Dryer Operating Cost of a compressed air system
 *      Compute operating cost of a desiccant dryer based on type of dryer, hours and cost of operation.
 *      Desiccant dryers types supported:
 *          a. Heatless
 *          b. Heated Externally
 *          c. Blower Purge With Sweep
 *          d. Blower Purge Without Sweep
 *          e. Heat of Compression - HC
 *          f. Heat of Compression - SP
 *          g. Refrigerated
 *
 * @author Omer Aziz
 * @bug No known bugs.
 *
 */

#include <map>
#include <stdexcept>

#include "physics/constants.h"

class DryerOperatingCost {
  public:
    enum DryerType {
        Heatless,
        HeatedExternally,
        BlowerPurgeWithSweep,
        BlowerPurgeWithoutSweep,
        HeatOfCompressionHC,
        HeatOfCompressionSP,
        Refrigerated
    };

    /**
     * @brief Output struct for DryerOperatingCost
     * @var waterRemoved double, flow rate of water removed by the dryer in pounds per hour (PPH)
     * @var totalCostPerYear double, Total cost of operation of the dryer per year in $
     * @var heaterPower double, Heater power rating in kW (0 - 1000 kW)
     * @var heatingHoursPerDay double, Hours for which the dryer heater operates per day - hours (1 - 24 hours)
     * @var purgeRate double, Purge rate for the dryer - percentage (0 - 100%)
     * @var designDDCPercentage double, Design DDC percentage for the dryer - percentage (0 - 100%)
     */
    struct Output {
        Output(const double waterRemoved, const double totalCostPerYear,
            const double heaterPower, const double heatingHoursPerDay, const double purgeRate, const double designDDCPercentage):
            waterRemoved(waterRemoved), totalCostPerYear(totalCostPerYear),
            heaterPower(heaterPower), heatingHoursPerDay(heatingHoursPerDay), purgeRate(purgeRate), designDDCPercentage(designDDCPercentage){}

        const double waterRemoved, totalCostPerYear, heaterPower, heatingHoursPerDay, purgeRate, designDDCPercentage;
    };

    /**
    * Constructor for DryerOperatingCost - Use this constructor when heater power rating, heating hours per day, purge rate and design DDC percentage is not known or needs to be computed.
     * @param flowRate double, Flow Rate in SCFM (1 - 50,000 SCFM)
     * @param pressure double, Pressure in psig (25 - 150 psig)
     * @param temperature double, Temperature F (50 - 120 F)
     * @param operatingHoursPerDay double, Hours for which the dryer operates per day - hours (1 - 24 hours)
     * @param operatingDaysPerWeek double, Days for which the dryer operates per week - days ( 1 - 7 days)
     * @param operatingWeeksPerYear double, Weeks for which the dryer operates per year - weeks (1 - 52 weeks)
     * @param costOfElectricity double, Cost of electricity per kWh - $ ($0.01 - $0.20 per kWh)
     * @param costOfCompressedAir double, Cost of compressed air per 1000 SCF - $ ($0.20 - $0.50 per 1000 SCF)
     * @param costOfCoolingWater double, Cost of cooling water per 1000 gallons - $ ($0.25 - $10.00 per 1000 gallons)
     */
    DryerOperatingCost(const double flowRate, const double pressure, const double temperature,
        const double operatingHoursPerDay, const double operatingDaysPerWeek, const double operatingWeeksPerYear,
        const double costOfElectricity, const double costOfCompressedAir, const double costOfCoolingWater) :
            DryerOperatingCost(flowRate, pressure, temperature,
            operatingHoursPerDay, operatingDaysPerWeek, operatingWeeksPerYear,
            costOfElectricity, costOfCompressedAir, costOfCoolingWater,
            0.0, 0.0, 0.0, 0.0) {}

    /**
     * Constructor for DryerOperatingCost - Use this constructor when heater power rating, heating hours per day, purge rate and design DDC percentage is known.
     * @param flowRate double, Flow Rate in SCFM (1 - 50,000 SCFM)
     * @param pressure double, Pressure in psig (25 - 150 psig)
     * @param temperature double, Temperature F (50 - 120 F)
     * @param operatingHoursPerDay double, Hours for which the dryer operates per day - hours (1 - 24 hours)
     * @param operatingDaysPerWeek double, Days for which the dryer operates per week - days ( 1 - 7 days)
     * @param operatingWeeksPerYear double, Weeks for which the dryer operates per year - weeks (1 - 52 weeks)
     * @param costOfElectricity double, Cost of electricity per kWh - $ ($0.01 - $0.20 per kWh)
     * @param costOfCompressedAir double, Cost of compressed air per 1000 SCF - $ ($0.20 - $0.50 per 1000 SCF)
     * @param costOfCoolingWater double, Cost of cooling water per 1000 gallons - $ ($0.25 - $10.00 per 1000 gallons)
     *
     * @param heaterPower double, Heater power rating in kW (0 - 1000 kW).
     *          If heater power is not known or needs to be computed set it to 0.
     * @param heatingHoursPerDay double, Hours for which the dryer heater operates per day - hours (1 - 24 hours)
     *          If heating hours per day is not known or needs to be calculator default set it to 0.
     *          Calculator default for heating hours per day is
     *          18 hours for Heated Externally, Blower Purge With Sweep and Blower Purge Without Sweep dryers, and
     *          3 hours for Heat of Compression - HC dryer.
     * @param purgeRate double, Purge rate for the dryer - percentage (0 - 100%)
     *          If purge rate is not known or needs to be calculated default set it to 0.
     *          Calculator default for purge rate is
     *          15% for Heatless dryer,
     *          7% for Heated Externally, Blower Purge With Sweep and Blower Purge Without Sweep dryers, and
     *          2% for Heat of Compression - HC dryer.
     * @param designDDCPercentage double, Design DDC percentage for the dryer - percentage (0 - 100%)
     *          If design DDC percentage is not known or needs to be calculated default set it to 0.
     *          Calculator default for design DDC percentage is 16.33% for desiccant dryers.
     */
    DryerOperatingCost(const double flowRate, const double pressure, const double temperature,
        const double operatingHoursPerDay, const double operatingDaysPerWeek, const double operatingWeeksPerYear,
        const double costOfElectricity, const double costOfCompressedAir, const double costOfCoolingWater,
        const double heaterPower, const double heatingHoursPerDay, const double purgeRate, const double designDDCPercentage) :
            flowRate(flowRate), pressure(pressure), temperature(temperature),
            operatingHoursPerDay(operatingHoursPerDay), operatingDaysPerWeek(operatingDaysPerWeek), operatingWeeksPerYear(operatingWeeksPerYear),
            costOfElectricity(costOfElectricity), costOfCompressedAir(costOfCompressedAir), costOfCoolingWater(costOfCoolingWater),
            heaterPower(heaterPower), heatingHoursPerDay(heatingHoursPerDay), purgeRate(purgeRate), designDDCPercentage(designDDCPercentage) {
        if (flowRate < 1 || flowRate > 50000) {
            throw std::invalid_argument("Flow rate must be between 1 and 50,000 SCFM.");
        }
        if (pressure < 25 || pressure > 150) {
            throw std::invalid_argument("Pressure must be between 25 and 150 psig.");
        }
        if (temperature < 50 || temperature > 120) {
            throw std::invalid_argument("Temperature must be between 50 and 120 F.");
        }
        if (operatingHoursPerDay < 1 || operatingHoursPerDay > 24) {
            throw std::invalid_argument("Operating hours per day must be between 1 and 24.");
        }
        if (operatingDaysPerWeek < 1 || operatingDaysPerWeek > 7) {
            throw std::invalid_argument("Operating days per week must be between 1 and 7.");
        }
        if (operatingWeeksPerYear < 1 || operatingWeeksPerYear > 52) {
            throw std::invalid_argument("Operating weeks per year must be between 1 and 52.");
        }
        if (costOfElectricity < 0.01 || costOfElectricity > 0.20) {
            throw std::invalid_argument("Cost of electricity must be between $0.01 and $0.20 per kWh.");
        }
        if (costOfCompressedAir < 0.20 || costOfCompressedAir > 0.50) {
            throw std::invalid_argument("Cost of compressed air must be between $0.20 and $0.50 per 1000 SCF.");
        }
        if (costOfCoolingWater < 0.25 || costOfCoolingWater > 10.00) {
            throw std::invalid_argument("Cost of cooling water must be between $0.25 and $10.00 per 1000 gallons.");
        }

        if (designDDCPercentage == 0) {
            this->designDDCPercentage = 0.1633;
        } else {
            this->designDDCPercentage = designDDCPercentage / 100;
        }
    }

    /**
     *
     * @param dryerType DryerType enum, type of dryer for which operating cost is to be calculated
     * @return Output
     */
    Output calculate(const DryerType dryerType) const {
        auto purgeRatePercentage = purgeRate / 100.0;
        auto heaterKW = heaterPower;
        auto heatingHrsPerDay = heatingHoursPerDay;

        auto tempLookup = lookupTemp.find(static_cast<int>(temperature))->second;
        if (dryerType == Refrigerated) {
            const auto tempLookup40 = lookupTemp.find(40)->second;
            tempLookup -= tempLookup40;
        }
        auto const waterRemovedPPH = flowRate * 60 * 18.016 * tempLookup / ((pressure + physics::us::kAtmosphericPressurePsi) * 379);
        auto const waterRemovedPer4Hrs = waterRemovedPPH * 4;

        double theoreticalDryerSizeRequired = 0.0;
        if (dryerType == Heatless) {
            theoreticalDryerSizeRequired = flowRate * (114.7 / (pressure + physics::us::kAtmosphericPressurePsi));
        } else if (dryerType == Refrigerated) {
        } else {
            const auto desiccantRequired = waterRemovedPer4Hrs / designDDCPercentage;
            theoreticalDryerSizeRequired = desiccantRequired / 0.5784;
        }

        if (purgeRatePercentage == 0) {
            if (dryerType == Heatless) {
                purgeRatePercentage = 0.15;
            } else if (dryerType == HeatedExternally || dryerType == BlowerPurgeWithSweep || dryerType == BlowerPurgeWithoutSweep) {
                purgeRatePercentage = 0.07;
            } else if (dryerType == HeatOfCompressionHC) {
                purgeRatePercentage = 0.02;
            }
        }
        auto const purgeSCFM = theoreticalDryerSizeRequired * purgeRatePercentage;

        if (heaterKW == 0.0) {
            if (dryerType == HeatedExternally) {
                heaterKW = purgeSCFM * 60 * 0.0764 * 0.241 * (375 - temperature) / 3412;
            } else if (dryerType == HeatOfCompressionHC) {
                heaterKW = flowRate * 0.02 * 1.08 * 275 / 3412;
            } else if (dryerType == BlowerPurgeWithSweep || dryerType == BlowerPurgeWithoutSweep) {
                heaterKW = theoreticalDryerSizeRequired * 0.25 * 60 * 0.0764 * 0.241 * (375 - temperature) / 3412;
            }
        }
        if (heatingHrsPerDay == 0) {
            if (dryerType == HeatedExternally || dryerType == BlowerPurgeWithSweep || dryerType == BlowerPurgeWithoutSweep) {
                heatingHrsPerDay = 18;
            } else if (dryerType == HeatOfCompressionHC) {
                heatingHrsPerDay = 3;
            }
        }

        auto const kwhPerDay = heaterKW * heatingHrsPerDay;

        double heaterElectricCostPerDay = 0.0;
        if (dryerType == HeatedExternally || dryerType == HeatOfCompressionHC || dryerType == BlowerPurgeWithSweep || dryerType == BlowerPurgeWithoutSweep) {
            heaterElectricCostPerDay = kwhPerDay * costOfElectricity;
        }

        double motorElectricCostPerDay = 0.0;
        if (dryerType == BlowerPurgeWithSweep || dryerType == BlowerPurgeWithoutSweep) {
            motorElectricCostPerDay = theoreticalDryerSizeRequired * 0.25 / 50 * 24 * costOfElectricity;

            if (dryerType == BlowerPurgeWithSweep) {
                motorElectricCostPerDay *= 0.75;
            }
        } else if (dryerType == Refrigerated) {
            motorElectricCostPerDay = flowRate / 180 * 24 * costOfElectricity;
        }

        double controlsElectricCostPerDay = 100 * 0.024 * costOfElectricity;
        if (dryerType == Refrigerated) {
            controlsElectricCostPerDay = 0;
        }

        double compressedAirPurgeCostPerDay =0;
        if (dryerType == BlowerPurgeWithoutSweep || dryerType == Refrigerated) {
        } else {
            const double costOfElectricityOnly = costOfElectricity * (1000.0 / 60 / 4.5 * 0.7457 / 0.9);
            compressedAirPurgeCostPerDay = purgeSCFM * 60 * 24 * (costOfCompressedAir > costOfElectricityOnly ? costOfCompressedAir : costOfElectricityOnly) / 1000;

            if (dryerType == BlowerPurgeWithSweep) {
                compressedAirPurgeCostPerDay /= 4;
            } else if (dryerType == HeatOfCompressionHC) {
                compressedAirPurgeCostPerDay *=  1.5/4;
            }
        }

        double coolingWaterCostPerDay = 0.0;
        if (dryerType == Refrigerated) {
            coolingWaterCostPerDay = flowRate / 1000 * 8 * 60 * 24 * costOfCoolingWater / 1000;
        }

        auto const totalDailyCost = heaterElectricCostPerDay + motorElectricCostPerDay + controlsElectricCostPerDay + compressedAirPurgeCostPerDay + coolingWaterCostPerDay;

        auto const totalCostPerDay = totalDailyCost * operatingHoursPerDay / 24;
        auto const totalCostPerWeek = totalCostPerDay * operatingDaysPerWeek;
        auto const totalCostPerYear = totalCostPerWeek * operatingWeeksPerYear;

        return {waterRemovedPPH, totalCostPerYear, heaterKW, heatingHrsPerDay, purgeRatePercentage*100, designDDCPercentage*100};
    }

  private:
    const double flowRate, pressure, temperature;
    const double operatingHoursPerDay, operatingDaysPerWeek, operatingWeeksPerYear;
    const double costOfElectricity, costOfCompressedAir, costOfCoolingWater;
    const double heaterPower, heatingHoursPerDay, purgeRate;
    double designDDCPercentage = 0.1633;

    const std::map<int, double> lookupTemp = {
        {36, 0.10396}, {37, 0.10815}, {38, 0.11249}, {39, 0.11699}, {40, 0.12164},
        {41, 0.12646}, {42, 0.13145}, {43, 0.1366}, {44, 0.14194}, {45, 0.14746},
        {46, 0.15317}, {47, 0.15907}, {48, 0.16517}, {49, 0.17148}, {50, 0.17799},
        {51, 0.18473}, {52, 0.19169}, {53, 0.19888}, {54, 0.2063}, {55, 0.21397},
        {56, 0.22188}, {57, 0.23006}, {58, 0.23849}, {59, 0.2472}, {60, 0.25618},
        {61, 0.26545}, {62, 0.27502}, {63, 0.28488}, {64, 0.29505}, {65, 0.30554},
        {66, 0.31636}, {67, 0.3275}, {68, 0.339}, {69, 0.35084}, {70, 0.36304},
        {71, 0.37561}, {72, 0.38856}, {73, 0.4019}, {74, 0.41564}, {75, 0.42979},
        {76, 0.44435}, {77, 0.45935}, {78, 0.47478}, {79, 0.49066}, {80, 0.50701},
        {81, 0.52382}, {82, 0.54112}, {83, 0.55892}, {84, 0.57722}, {85, 0.59604},
        {86, 0.6154}, {87, 0.6353}, {88, 0.65575}, {89, 0.67678}, {90, 0.69838},
        {91, 0.72059}, {92, 0.7434}, {93, 0.76684}, {94, 0.79091}, {95, 0.81564},
        {96, 0.84103}, {97, 0.86711}, {98, 0.89388}, {99, 0.92137}, {100, 0.94959},
        {101, 0.97854}, {102, 1.0083}, {103, 1.0388}, {104, 1.07}, {105, 1.1021},
        {106, 1.1351}, {107, 1.1688}, {108, 1.2035}, {109, 1.239}, {110, 1.2754},
        {111, 1.3128}, {112, 1.351}, {113, 1.3902}, {114, 1.4305}, {115, 1.4717},
        {116, 1.5139}, {117, 1.5571}, {118, 1.6014}, {119, 1.6468}, {120, 1.6933},
        {121, 1.7409}, {122, 1.7897}, {123, 1.8396}, {124, 1.8907}, {125, 1.943},
        {126, 1.9966}, {127, 2.0514}, {128, 2.1075}, {129, 2.1649}, {130, 2.2237}
    };
};