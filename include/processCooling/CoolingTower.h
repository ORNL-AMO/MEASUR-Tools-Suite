/**
 * @brief Contains the Consumption (Water / Power / Energy) & Savings calculators for
 *  Cooling Tower
 *          Makeup Water
 *          Basin Heater Energy
 *          Fan Energy
 *
 * @author Omer Aziz (omerb)
 * @bug No known bugs.
 *
 */

#ifndef TOOLS_SUITE_COOLING_TOWER_H
#define TOOLS_SUITE_COOLING_TOWER_H

#include <math.h>
#include <vector>

class CoolingTowerOperatingConditionsData
{
    public:
        /**
        * @param flowRate double, water flow rate in gpm
        * @param coolingLoad double, in MMBtu/h 
        * @param operationalHours int, number of hours cooling tower operates
        * @param lossCorrectionFactor double, correction factor for evaporation loss
        */
        CoolingTowerOperatingConditionsData(const double flowRate, const double coolingLoad, const int operationalHours, 
                                            const double lossCorrectionFactor)
                                            : flowRate(flowRate), coolingLoad(coolingLoad), operationalHours(operationalHours),
                                              lossCorrectionFactor(lossCorrectionFactor) {}

        double getFlowRate() const { return flowRate; }
        double getCoolingLoad() const { return coolingLoad; }
        int getOperationalHours() const { return operationalHours; }
        double getLossCorrectionFactor() const { return lossCorrectionFactor; }

        void setFlowRate(double flowRate);
        void setCoolingLoad(double coolingLoad);
        void setOperationalHours(int operationalHours);
        void setLossCorrectionFactor(double lossCorrectionFactor);

    private:
        double flowRate;
        double coolingLoad;
        int operationalHours;
        double lossCorrectionFactor = 0.85;
};

class CoolingTowerWaterConservationData
{
    public:
        /**
        * @param cyclesOfConcentration int
        * @param driftLossFactor double, correction factor for drift loss
        */
        CoolingTowerWaterConservationData(const int cyclesOfConcentration, const double driftLossFactor)
                                            : cyclesOfConcentration(cyclesOfConcentration), driftLossFactor(driftLossFactor) {}

    int getCyclesOfConcentration() const { return cyclesOfConcentration; }
    double getDriftLossFactor() const { return driftLossFactor; }

    void setCyclesOfConcentration(int cyclesOfConcentration);
    void setDriftLossFactor(double driftLossFactor);

    private:
        int cyclesOfConcentration;
        double driftLossFactor;
};

class CoolingTowerMakeupWaterCalculator
{
    public:
        struct Output
        {
            /**
            * @param wcBaseline double, water consumption before modifications in gallons
            * @param wcModification double, water consumption after modifications in gallons
            * @param waterSavings double, water saved in gallons
            */
            Output(double wcBaseline, double wcModification, double waterSavings)
                    : wcBaseline(wcBaseline), wcModification(wcModification), waterSavings(waterSavings) {}

            double wcBaseline     = 0;
            double wcModification = 0;
            double waterSavings   = 0;
        };

        CoolingTowerMakeupWaterCalculator(const CoolingTowerOperatingConditionsData &operatingConditionsData, 
                                          const CoolingTowerWaterConservationData &waterConservationBaselineData,
                                          const CoolingTowerWaterConservationData &waterConservationModificationData)
                                          : operatingConditionsData(operatingConditionsData), 
                                            waterConservationBaselineData(waterConservationBaselineData),
                                            waterConservationModificationData(waterConservationModificationData)
        {}

        CoolingTowerMakeupWaterCalculator::Output calculate();

        CoolingTowerOperatingConditionsData getOperatingConditionsData() const { return operatingConditionsData; }
        CoolingTowerWaterConservationData getWaterConservationBaselineData() const { return waterConservationBaselineData; }
        CoolingTowerWaterConservationData getWaterConservationModificationData() const { return waterConservationModificationData; }

        void setOperatingConditionsData(CoolingTowerOperatingConditionsData operatingConditionsData);
        void setWaterConservationBaselineData(CoolingTowerWaterConservationData waterConservationBaselineData);
        void setWaterConservationModificationData(CoolingTowerWaterConservationData waterConservationModificationData);

    private:
        CoolingTowerOperatingConditionsData operatingConditionsData;
        CoolingTowerWaterConservationData waterConservationBaselineData;
        CoolingTowerWaterConservationData waterConservationModificationData;
};


class CoolingTower{
public:
    enum FanControlSpeedType {
        One,
        Two,
        Variable
    };

    struct PowerEnergyConsumptionOutput
    {
        PowerEnergyConsumptionOutput(double baselinePower, double baselineEnergy, double modPower, double modEnergy, double savingsEnergy) :
                baselinePower(baselinePower), baselineEnergy(baselineEnergy), modPower(modPower), modEnergy(modEnergy), savingsEnergy(savingsEnergy){}

        PowerEnergyConsumptionOutput() = default;
        double baselinePower = 0, baselineEnergy = 0, modPower = 0, modEnergy = 0, savingsEnergy = 0;
    };

    /**
     *
     * @param ratedCapacity double, units ton
     * @param ratedTempSetPoint double, units F
     * @param ratedTempDryBulb double, units F
     * @param ratedWindSpeed double, units mph
     *
     * @param operatingTempDryBulb double, units F
     * @param operatingWindSpeed double, units mph
     * @param operatingHours double, units hours
     *
     * @param baselineTempSetPoint double, units F
     * @param modTempSetPoint double, units F
     * @param panLossRatio double, fraction
     *
     * @return
     *      @param baselinePower double, units kW
     *      @param baselineEnergy double, units kWh
     *      @param modPower double, units, kW
     *      @param modEnergy double, units, kWh
     *      @param savingsEnergy double, units kWh
     *
     */
    static PowerEnergyConsumptionOutput BasinHeaterEnergyConsumption(
            const double ratedCapacity, const double ratedTempSetPoint, const double ratedTempDryBulb, const double ratedWindSpeed,
            const double operatingTempDryBulb, const double operatingWindSpeed, const double operatingHours,
            const double baselineTempSetPoint, const double modTempSetPoint, const double panLossRatio){
        const double calc1 = ratedCapacity * 4.394960445356 * panLossRatio /        /*4.394960445356 = 15000 btu/hr/ton  / 3413 kW/btu*/
                (ratedTempSetPoint - ratedTempDryBulb) /
                pow((ratedTempSetPoint + ratedTempDryBulb) / 2,-0.181) /
                pow((ratedTempSetPoint - ratedTempDryBulb),0.266) /
                pow((1.277 * ratedWindSpeed + 1),0.5) *
                pow((1.277 * operatingWindSpeed + 1),0.5);

        double baselinePower = CalculatePower(operatingTempDryBulb, baselineTempSetPoint, calc1);
        double modPower = CalculatePower(operatingTempDryBulb, modTempSetPoint, calc1);

        const double baselineEnergy = baselinePower * operatingHours;
        const double modEnergy = modPower * operatingHours;

        return PowerEnergyConsumptionOutput(baselinePower, baselineEnergy, modPower, modEnergy, baselineEnergy - modEnergy);
    }

    /**
     *
     * @param ratedFanPower double, units HP
     * @param noOfCells integer, between 1 and 10
     *
     * @param waterLeavingTemp double, units F
     * @param waterEnteringTemp double, units F
     * @param waterFlowRate double, units gpm
     * @param operatingTempWetBulb double, units F
     * @param operatingHours double, units hours
     *
     * @param baselineSpeedType enum, One / Two / Variable
     * @param modSpeedType enum, One / Two / Variable
     *
     * @return
     *      @param baselinePower double, units HP
     *      @param baselineEnergy double, units kWh
     *      @param modPower double, units, HP
     *      @param modEnergy double, units, kWh
     *      @param savingsEnergy double, units kWh
     *
     */
    static PowerEnergyConsumptionOutput FanEnergyConsumption(const double ratedFanPower,
            const double waterLeavingTemp, const double waterEnteringTemp, const double operatingTempWetBulb, const double operatingHours,
            const FanControlSpeedType baselineSpeedType, const FanControlSpeedType modSpeedType){
        const double a = -0.09646816;
        const double b = 1.04669762;
        const double c = 0.04976825 -
                CalculateFactor(std::vector<double> {0.08352359,0.11247273,-0.00135847,0.00003417,0.00003125,-0.00034001}, operatingTempWetBulb, waterEnteringTemp - waterLeavingTemp) /
                CalculateFactor(std::vector<double> {0.50061393,0.00588251,0.0002163,-0.01913189,0.00022360,0.00106108}, operatingTempWetBulb, waterLeavingTemp - operatingTempWetBulb);
        const double airFlow = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);

        const double powerFactorFlow = CalculatePowerFactor(airFlow);
        const double powerFactorFull = CalculatePowerFactor(1);
        const double powerFactorHalf = CalculatePowerFactor(0.5);
        const double powerFactorZero = CalculatePowerFactor(0);

        const double highSpeedTime = airFlow < 0.5 ? airFlow / 0.5 : (airFlow - 0.5) / 0.5;
        const double twoSpeedPower = airFlow < 0.5 ?
                ratedFanPower * powerFactorHalf * highSpeedTime +
                ratedFanPower * powerFactorZero * (1 - highSpeedTime):
                ratedFanPower * powerFactorFull * highSpeedTime +
                ratedFanPower * powerFactorHalf * (1 - highSpeedTime);

        const double oneSpeedPower =
                ratedFanPower * powerFactorFull * airFlow +
                ratedFanPower * powerFactorZero * (1 - airFlow);

        const double vfdPower =
                ratedFanPower * powerFactorFlow;

        const double baselinePower =
                baselineSpeedType == FanControlSpeedType::Variable ? vfdPower :
                baselineSpeedType == FanControlSpeedType::Two ? twoSpeedPower :
                baselineSpeedType == FanControlSpeedType::One ? oneSpeedPower : 0;
        const double modPower =
                modSpeedType == FanControlSpeedType::Variable ? vfdPower :
                modSpeedType == FanControlSpeedType::Two ? twoSpeedPower :
                modSpeedType == FanControlSpeedType::One ? oneSpeedPower : 0;

        const double baselineEnergy = baselinePower * 0.746 * operatingHours;
        const double modEnergy = modPower * 0.746 * operatingHours;

        return PowerEnergyConsumptionOutput(baselinePower, baselineEnergy, modPower, modEnergy, baselineEnergy - modEnergy);
    }

private:
    static double CalculatePowerFactor(const double var) { return (0.01055507 - 0.05704023 * var + 0.14686301 * var * var + 0.92961746 * var * var * var); }

    static double CalculateFactor(const std::vector<double> &cf, const double operatingTempWetBulb, const double deltaTemp) {
        return cf[0] +
               cf[1] * deltaTemp + cf[2] * deltaTemp * deltaTemp +
               cf[3] * operatingTempWetBulb + cf[4] * operatingTempWetBulb * operatingTempWetBulb +
               cf[5] * deltaTemp * operatingTempWetBulb;
    }

    static double CalculatePower(const double operatingTempDryBulb, const double tempSetPoint, const double calc1) {
        return operatingTempDryBulb > tempSetPoint ? 0 :
               calc1 * (tempSetPoint - operatingTempDryBulb) *
               pow((tempSetPoint + operatingTempDryBulb) / 2, -0.181) *
               pow((tempSetPoint - operatingTempDryBulb),0.266);
    }
};

#endif //TOOLS_SUITE_COOLING_TOWER_H
