#pragma once

/**
 * @file
 * @brief Implementations of Steam Leak of a boiler system using one of the three methods
 *         1. Estimate Method
 *            a. Pressure Reducing Valve (PRV)
 *            a. Backpressure Turbine
 *         2. Orifice Method
 *         3. Plume Method
 *
 * @author Omer Aziz
 * @bug No known bugs.
 *
 */

#include <cmath>
#include <stdexcept>
#include <string>

#include "quantify_steam_leak_by_plume_length.h"
#include "physics/constants.h"
#include "steamModeler/SteamProperties.h"

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

class SteamLeakSurvey {
public:
    enum class UtilityType { steam, electric, natural_gas };

    struct SteamLeakSurveyResults {
        SteamLeakSurveyResults(const double leakRate, const double steamLoss, const double energyLoss, const double leakCost)
            : leakRate(leakRate), steamLoss(steamLoss), energyLoss(energyLoss), leakCost(leakCost) {}

        const double leakRate, steamLoss, energyLoss, leakCost;
    };

    /**
     * Constructor for SteamLeakSurvey, when utility type is steam
     * @param operatingTime double, operating time of the system hours per year
     * @param steamTemp double, steam temperature F (must be greater than 212F)
     * @param steamPressure double, steam pressure in psig
     * @param costOfElectricity double, $/kWh, default 0
     * @param leakPressure double, leak pressure in psig
     * @param leakTemp double, leak temperature F
     * @param feedwaterTemp double, feedwater temperature in F (must be bellow boiling point of water, max 212F)
     * @param steamCost double, $/lb
     */
    SteamLeakSurvey(const double operatingTime, const double steamTemp, const double steamPressure, const double costOfElectricity,
        const double leakPressure, const double leakTemp, const double feedwaterTemp,
        const double steamCost) :
            SteamLeakSurvey(operatingTime, steamTemp, steamPressure, costOfElectricity,
                leakPressure, leakTemp, feedwaterTemp,
                0, 0, UtilityType::steam, 0, 1, steamCost) {}

    /**
     * Constructor for SteamLeakSurvey, when utility type is electric
     * @param operatingTime double, operating time of the system hours per year
     * @param steamTemp double, steam temperature F (must be greater than 212F)
     * @param steamPressure double, steam pressure in psig
     * @param costOfElectricity double, $/kWh, default 0
     * @param leakPressure double, leak pressure in psig
     * @param leakTemp double, leak temperature F
     * @param feedwaterTemp double, feedwater temperature in F (must be bellow boiling point of water, max 212F)
     * @param boilerEfficiency double, boiler efficiency percentage (0 - 100 %)
     * @param systemEfficiency double, system efficiency percentage (0 - 100 %)
     */
    SteamLeakSurvey(const double operatingTime, const double steamTemp, const double steamPressure, const double costOfElectricity,
        const double leakPressure, const double leakTemp, const double feedwaterTemp,
        const double boilerEfficiency, const double systemEfficiency) :
            SteamLeakSurvey(operatingTime, steamTemp, steamPressure, costOfElectricity,
                leakPressure, leakTemp, feedwaterTemp,
                boilerEfficiency, systemEfficiency, UtilityType::electric){}

    /**
     * Constructor for SteamLeakSurvey, when utility type is natural gas
     * @param operatingTime double, operating time of the system hours per year
     * @param steamTemp double, steam temperature F (must be greater than 212F)
     * @param steamPressure double, steam pressure in psig
     * @param costOfElectricity double, $/kWh, default 0
     * @param leakPressure double, leak pressure in psig
     * @param leakTemp double, leak temperature F
     * @param feedwaterTemp double, feedwater temperature in F (must be bellow boiling point of water, max 212F)
     * @param boilerEfficiency double, boiler efficiency percentage (1 - 100 %)
     * @param systemEfficiency double, system efficiency percentage (1 - 100 %)
     * @param fuelCost double, per MCF (unit cost of fuel for the boiler system), when utility type Natural Gas
     * @param fuelEnergyFactor double, MMBtu/MCF (energy content for a given volume of fuel, when unit is in $/volume)
     */
    SteamLeakSurvey(const double operatingTime, const double steamTemp, const double steamPressure, const double costOfElectricity,
        const double leakPressure, const double leakTemp, const double feedwaterTemp,
        const double boilerEfficiency, const double systemEfficiency,
        const double fuelCost, const double fuelEnergyFactor = 1) :
            SteamLeakSurvey(operatingTime, steamTemp, steamPressure, costOfElectricity,
                leakPressure, leakTemp, feedwaterTemp,
                boilerEfficiency, systemEfficiency, UtilityType::natural_gas, fuelCost, fuelEnergyFactor){}

    /**
     * Constructor for SteamLeakSurvey, generic
     * @param operatingTime double, operating time of the system hours per year
     * @param steamTemp double, steam temperature F (must be greater than 212F)
     * @param steamPressure double, steam pressure in psig
     * @param costOfElectricity double, $/kWh, default 0
     * @param leakPressure double, leak pressure in psig
     * @param leakTemp double, leak temperature F
     * @param feedwaterTemp double, feedwater temperature in F (must be bellow boiling point of water, max 212F)
     * @param boilerEfficiency double, boiler efficiency percentage (0 - 100 %)
     * @param systemEfficiency double, system efficiency percentage (0 - 100 %)
     * @param utilityType utility type enumeration
     * @param fuelCost double, per MCF (unit cost of fuel for the boiler system), when utility type Natural Gas
     * @param fuelEnergyFactor double, MMBtu/MCF (energy content for a given volume of fuel, when unit is in $/volume)
     * @param steamCost double, $/lb
     */
    SteamLeakSurvey(const double operatingTime, const double steamTemp, const double steamPressure, const double costOfElectricity,
        const double leakPressure, const double leakTemp, const double feedwaterTemp,
        const double boilerEfficiency, const double systemEfficiency, const UtilityType utilityType,
        const double fuelCost = 0, const double fuelEnergyFactor = 1, const double steamCost = 0) :
    operatingTime(operatingTime), steamPressure(steamPressure), leakPressure(leakPressure), costOfElectricity(costOfElectricity) {
        constexpr auto feedWaterPressureMPa = (14.6 + 14.7)  * 0.00689476;     // psig -> MPa
        const auto steamPressureMPa = (steamPressure + 14.7) * 0.00689476;     // psig -> MPa
        const auto leakPressureMPa = (leakPressure + 14.7)   * 0.00689476;     // psig -> MPa
        const auto steamTempK =physics::conversions::fahrenheitToKelvin(steamTemp);
        const auto leakTempK = physics::conversions::fahrenheitToKelvin(leakTemp);
        const auto feedwaterTempK = physics::conversions::fahrenheitToKelvin(feedwaterTemp);

        const auto steamProperties = SteamProperties(steamPressureMPa, SteamProperties::ThermodynamicQuantity::TEMPERATURE, steamTempK).calculate();
        specificHeatRatio = steamProperties.isentropicExponent;
        steamSpecificEnthalpy = steamProperties.specificEnthalpy;
        isentropicEnthalpy = SteamProperties(leakPressureMPa, SteamProperties::ThermodynamicQuantity::ENTROPY,steamProperties.specificEntropy).calculate().specificEnthalpy;
        leakEnthalpy = SteamProperties(leakPressureMPa, SteamProperties::ThermodynamicQuantity::TEMPERATURE,leakTempK).calculate().specificEnthalpy;
        feedwaterEnthalpy = SteamProperties(feedWaterPressureMPa, SteamProperties::ThermodynamicQuantity::TEMPERATURE, feedwaterTempK).calculate().specificEnthalpy;

        double leakSpecificVolume = SteamProperties(leakPressureMPa, SteamProperties::ThermodynamicQuantity::TEMPERATURE, leakTempK).calculate().specificVolume;
        leakSpecificVolume *= 16.0185;         // m3/kg -> ft3/lb
        leakSpecificVolume *= 1728;            // ft3/lb -> in3/lb

        feedwaterEnthalpy *= 0.429923;         // kJ/kg -> btu/lb
        steamSpecificEnthalpy *= 0.429923;     // kJ/kg -> btu/lb
        isentropicEnthalpy *= 0.429923;        // kJ/kg -> btu/lb
        leakEnthalpy *= 0.429923;              // kJ/kg -> btu/lb
        leakDensity = 1 / leakSpecificVolume;  // lb/in3

        switch (utilityType) {
            case UtilityType::natural_gas:
                this->steamCost = fuelCost * fuelEnergyFactor * (steamSpecificEnthalpy - feedwaterEnthalpy) / 1000000 / (boilerEfficiency/100) / (systemEfficiency/100);
                break;
                case UtilityType::electric:
                this->steamCost = costOfElectricity * 293.071 * (steamSpecificEnthalpy - feedwaterEnthalpy) / 1000000 / (boilerEfficiency/100) / (systemEfficiency/100);
                break;
            case UtilityType::steam :
                this->steamCost = steamCost;
                break;
        }
    }

    /**
     * @param leakRate double, lb/hr
     *
     * @return SteamLeakSurvey::Output, leakRate lb/hr, steamLoss klb/yr, energyLoss MMBtu/yr, leakCost MMBtu/lb-MCF
     */
    SteamLeakSurveyResults estimateMethodPRVCalc(const double leakRate) const {
        return calculate(leakRate);
    }

    /**
     * @param turbineEfficiency double, system efficiency percentage (0 - 100 %)
     * @param leakRate double, lb/hr
     *
     * @return SteamLeakSurvey::Output, leakRate lb/hr, leakEnthalpy btu/lb, steamLoss klb/yr, energyLoss MMBtu/yr, leakCost MMBtu/lb-MCF
     */
    SteamLeakSurveyResults estimateMethodTurbineCalc(const double turbineEfficiency, const double leakRate) const {
        return calculate(leakRate, turbineEfficiency);
    }

    /**
     * @param turbineEfficiency double, system efficiency percentage (0 - 100 %)
     * @param holeSize double, estimated diameter of orifice through which steam is leaking in inches
     * @param dischargeCoef double, discharge coefficient used to capture the effect of the shape of the leak rate as fraction (0 - 1)
     * @param atmPressure double, atmospheric pressure (standard pressure is 14.7 psia, range 0 - 20)
     *
     * @return SteamLeakSurvey::Output, leakRate lb/hr, leakEnthalpy btu/lb, steamLoss klb/yr, energyLoss MMBtu/yr, leakCost MMBtu/lb-MCF
     */
    SteamLeakSurveyResults orificeMethodCalc(const double turbineEfficiency, const double holeSize, const double dischargeCoef, const double atmPressure) const {
        const double criticalPressureRatio = std::pow(2 / (specificHeatRatio+1), (specificHeatRatio+1) / (specificHeatRatio-1));
        const double pressureRatio = atmPressure / (leakPressure + atmPressure);
        const double minPressure = atmPressure / (criticalPressureRatio - atmPressure);

        if (criticalPressureRatio <= pressureRatio) {
            throw std::runtime_error("Steam Leak with Orifice method, Leak pressure (" + std::to_string(leakPressure) +
                ") must be at least minimum pressure (" + std::to_string(minPressure) + ")");
        }

        const double leakRate = dischargeCoef * M_PI / 4 * holeSize * holeSize *
            std::sqrt(specificHeatRatio * leakDensity * (leakPressure + atmPressure) * 32.2 * 12 * criticalPressureRatio) * 3600;

        return calculate(leakRate, turbineEfficiency);
    }

    /**
     * @param turbineEfficiency double, system efficiency percentage (0 - 100 %)
     * @param plumeLength double, feet (range 3 - 12 feet)
     * @param ambTemp double, ambient temperature (usually between 45 and 90 degrees F)
     *
     * @return SteamLeakSurvey::Output, leakRate lb/hr, leakEnthalpy btu/lb, steamLoss klb/yr, energyLoss MMBtu/yr,
     * leakCost MMBtu/lb-MCF
     */
    SteamLeakSurveyResults plumeMethodCalc(const double turbineEfficiency, const double plumeLength, const double ambTemp) const {
        const double leakRate = QuantifySteamLeakByPlumeLength::estimate(steamPressure, plumeLength, ambTemp);    // lb/hr

        return calculate(leakRate, turbineEfficiency);
    }

    /**
     * @return steamCost computed based on fuel type steam or electric or natural gas and turbine (efficiency, energy is recovered from dropping the pressure)
     */
    double costOfSteam(const double turbineEfficiency) const {
        if (turbineEfficiency != 0) {
            return steamCost - costOfElectricity * 293.071 * (steamSpecificEnthalpy - isentropicEnthalpy) / 1000000 * (turbineEfficiency/100);
        }

        return steamCost;
    }

    /**
     * @return steamCost computed based on fuel type steam or electric or natural gas
     */
    double costOfSteam() const {
        return costOfSteam(0);
    }

  private:
    SteamLeakSurveyResults calculate(const double leakRate, const double turbineEfficiency = 0) const {
        const double steamLoss  = operatingTime * leakRate / 1000;
        const double energyLoss = leakEnthalpy * steamLoss / 1000;

        const double leakCost = steamLoss * costOfSteam(turbineEfficiency) * 1000 *
            (leakEnthalpy - feedwaterEnthalpy) / (steamSpecificEnthalpy - feedwaterEnthalpy);

        return {leakRate, steamLoss, energyLoss, leakCost};
    }

    double operatingTime = 0, steamPressure = 0, leakPressure = 0, costOfElectricity = 0, steamCost = 0;
    double steamSpecificEnthalpy = 1256.12;        // btu/lb
    double isentropicEnthalpy = 1220.35;           // btu/lb
    double feedwaterEnthalpy = 38.16;              // btu/lb
    double leakEnthalpy = 1208.07;                 // btu/lb
    double leakDensity = 0;                        // lb/in3
    double specificHeatRatio = 1.3;
};

