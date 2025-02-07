#ifndef TOOLS_SUITE_PUMPDATA_H
#define TOOLS_SUITE_PUMPDATA_H

#include <string>
#include "motorDriven/motor/MotorData.h"

namespace Pump {
    enum class SpecificSpeed {
        FIXED_SPEED,
        NOT_FIXED_SPEED
    };

    enum class Style {
        END_SUCTION_SLURRY,
        END_SUCTION_SEWAGE,
        END_SUCTION_STOCK,
        END_SUCTION_SUBMERSIBLE_SEWAGE,
        API_DOUBLE_SUCTION,
        MULTISTAGE_BOILER_FEED,
        END_SUCTION_ANSI_API,
        AXIAL_FLOW,
        DOUBLE_SUCTION,
        VERTICAL_TURBINE,
        LARGE_END_SUCTION,
        SPECIFIED_OPTIMAL_EFFICIENCY
    };

    struct FieldData {
        /**
         * Constructor
         * @param flowRate double, rate of flow. Units are gpm
         * @param head double, pump head measured in feet
         * @param loadEstimationMethod LoadEstimationMethod, classification of load estimation method
         * @param motorPower double, power output of the pump's motor in hp.
         * @param motorAmps double, current measured from the pump's motor in amps
         * @param voltage double, the measured bus voltage in volts
         */
        FieldData(const double flowRate, const double head, const Motor::LoadEstimationMethod loadEstimationMethod, const double motorPower,
                  const double motorAmps, const double voltage)
                : flowRate(flowRate), head(head), loadEstimationMethod(loadEstimationMethod),  motorPower(motorPower),
                  motorAmps(motorAmps), voltage(voltage)
        {}

        const double flowRate, head;
        const Motor::LoadEstimationMethod loadEstimationMethod;
        const double motorPower, motorAmps, voltage;
    };

    struct Input {
        /**
         * Constructor
         * @param style Style, classification of style of pump being used.
         * @param pumpEfficiency double, pump % efficiency at the specified operating conditions
         * @param rpm double, pump RPM to define its operating speed
         * @param drive Drive, type of drive the pump uses from either direct or belt drive.
         * @param kviscosity double, kinematic viscosity of the fluid being pumped in centistokes.
         * @param specificGravity double, specific gravity- unitless
         * @param stageCount int, the number of pump stages
         * @param speed Speed, type of pump speed from either fixed or not fixed.
         */
        Input(const Style style, double pumpEfficiency, const double rpm, const Motor::Drive drive,
              const double kviscosity,
              const double specificGravity, const int stageCount, const SpecificSpeed speed, double specifiedEfficiency)
                : style(style), pumpEfficiency(pumpEfficiency), rpm(rpm), drive(drive),
                  kviscosity(kviscosity),
                  specificGravity(specificGravity), stageCount(stageCount), speed(speed), specifiedEfficiency(specifiedEfficiency) {
            /**
             * Convert percent values to fractions for proper calculation
             */
            //   this->specifiedEfficiency = Conversion(specifiedEfficiency).percentToFraction();
            //   this->pumpEfficiency = Conversion(pumpEfficiency).percentToFraction();
            //   this->specifiedEfficiency = specifiedEfficiency / 100.0;
            //   this->pumpEfficiency = pumpEfficiency / 100.0;
        };

        const Style style;
        double pumpEfficiency, rpm;
        const Motor::Drive drive;
        const double kviscosity, specificGravity;
        const int stageCount;
        const SpecificSpeed speed;
        double specifiedEfficiency;

    };
}

class PumpData {
public:
    PumpData(std::string manufacturer,
             std::string model,
             std::string serialNumber,
             std::string status,
             std::string pumpType,
             std::string shaftOrientation,
             std::string shaftSealType,
             std::string fluidType,
             std::string priority,
             std::string driveType,
             std::string flangeConnectionClass,
             std::string flangeConnectionSize,
             std::string componentId,
             std::string system,
             std::string location,
             std::string motorEfficiencyClass,
             int speed,
             int numStages,
             int yearlyOperatingHours,
             int yearInstalled,
             int finalMotorRpm,
             int motorRatedVoltage,
             double inletDiameter,
             double outletDiameter,
             double staticSuctionHead,
             double staticDischargeHead,
             double fluidDensity,
             double maxWorkingPressure,
             double maxAmbientTemperature,
             double maxSuctionLift,
             double displacement,
             double startingTorque,
             double ratedSpeed,
             double impellerDiameter,
             double efficiency,
             double lineFrequency,
             double minFlowSize,
             double pumpSize,
             double designHead,
             double designFlow,
             double designEfficiency,
             double motorRatedPower,
             double motorFullLoadAmps,
             double operatingFlowRate,
             double operatingHead,
             double measuredCurrent,
             double measuredPower,
             double measuredVoltage,
             double motorEfficiency)
            : manufacturer(std::move(manufacturer)),
              model(std::move(model)),
              serialNumber(std::move(serialNumber)),
              status(std::move(status)),
              pumpType(std::move(pumpType)),
              shaftOrientation(std::move(shaftOrientation)),
              shaftSealType(std::move(shaftSealType)),
              fluidType(std::move(fluidType)),
              priority(std::move(priority)),
              driveType(std::move(driveType)),
              flangeConnectionClass(std::move(flangeConnectionClass)),
              flangeConnectionSize(std::move(flangeConnectionSize)),
              componentId(std::move(componentId)),
              system(std::move(system)),
              location(std::move(location)),
              motorEfficiencyClass(std::move(motorEfficiencyClass)),
              speed(speed),
              numStages(numStages),
              yearlyOperatingHours(yearlyOperatingHours),
              yearInstalled(yearInstalled),
              finalMotorRpm(finalMotorRpm),
              motorRatedVoltage(motorRatedVoltage),
              inletDiameter(inletDiameter),
              outletDiameter(outletDiameter),
              staticSuctionHead(staticSuctionHead),
              staticDischargeHead(staticDischargeHead),
              fluidDensity(fluidDensity),
              maxWorkingPressure(maxWorkingPressure),
              maxAmbientTemperature(maxAmbientTemperature),
              maxSuctionLift(maxSuctionLift),
              displacement(displacement),
              startingTorque(startingTorque),
              ratedSpeed(ratedSpeed),
              impellerDiameter(impellerDiameter),
              efficiency(efficiency),
              lineFrequency(lineFrequency),
              minFlowSize(minFlowSize),
              pumpSize(pumpSize),
              designHead(designHead),
              designFlow(designFlow),
              designEfficiency(designEfficiency),
              motorRatedPower(motorRatedPower),
              motorFullLoadAmps(motorFullLoadAmps),
              operatingFlowRate(operatingFlowRate),
              operatingHead(operatingHead),
              measuredCurrent(measuredCurrent),
              measuredPower(measuredPower),
              measuredVoltage(measuredVoltage),
              motorEfficiency(motorEfficiency),
              id(-1){}

    double getInletDiameter() const {
        return inletDiameter;
    }

    void setInletDiameter(const double &inletDiameter) {
        this->inletDiameter = inletDiameter;
    }

    double getOutletDiameter() const {
        return outletDiameter;
    }

    void setOutletDiameter(const double &outletDiameter) {
        this->outletDiameter = outletDiameter;
    }

    double getStaticSuctionHead() const {
        return staticSuctionHead;
    }

    void setStaticSuctionHead(const double &staticSuctionHead) {
        this->staticSuctionHead = staticSuctionHead;
    }

    double getStaticDischargeHead() const {
        return staticDischargeHead;
    }

    void setStaticDischargeHead(const double &staticDischargeHead) {
        this->staticDischargeHead = staticDischargeHead;
    }

    double getFluidDensity() const {
        return fluidDensity;
    }

    void setFluidDensity(const double &fluidDensity) {
        this->fluidDensity = fluidDensity;
    }

    double getMaxWorkingPressure() const {
        return maxWorkingPressure;
    }

    void setMaxWorkingPressure(const double &maxWorkingPressure) {
        this->maxWorkingPressure = maxWorkingPressure;
    }

    double getMaxAmbientTemperature() const {
        return maxAmbientTemperature;
    }

    void setMaxAmbientTemperature(const double &maxAmbientTemperature) {
        this->maxAmbientTemperature = maxAmbientTemperature;
    }

    double getMaxSuctionLift() const {
        return maxSuctionLift;
    }

    void setMaxSuctionLift(const double &maxSuctionLift) {
        this->maxSuctionLift = maxSuctionLift;
    }

    double getDisplacement() const {
        return displacement;
    }

    void setDisplacement(const double &displacement) {
        this->displacement = displacement;
    }

    double getStartingTorque() const {
        return startingTorque;
    }

    void setStartingTorque(const double &startingTorque) {
        this->startingTorque = startingTorque;
    }

    double getRatedSpeed() const {
        return ratedSpeed;
    }

    void setRatedSpeed(const double &ratedSpeed)  {
        this->ratedSpeed = ratedSpeed;
    }

    double getMinFlowSize() const {
        return minFlowSize;
    }

    void setMinFlowSize(const double &minFlowSize)  {
        this->minFlowSize = minFlowSize;
    }

    double getPumpSize() const {
        return pumpSize;
    }

    void setPumpSize(const double &pumpSize)  {
        this->pumpSize = pumpSize;
    }

    double getImpellerDiameter() const {
        return impellerDiameter;
    }

    void setImpellerDiameter(const double &impellerDiameter)  {
        this->impellerDiameter = impellerDiameter;
    }

    double getEfficiency() const {
        return efficiency;
    }

    void setEfficiency(const double &efficiency)  {
        this->efficiency = efficiency;
    }

    double getLineFrequency() const {
        return lineFrequency;
    }

    void setLineFrequency(const double &lineFrequency)  {
        this->lineFrequency = lineFrequency;
    }

    double getDesignHead() const {
        return designHead;
    }

    void setDesignHead(const double &designHead)  {
        this->designHead = designHead;
    }

    double getDesignFlow() const {
        return designFlow;
    }

    void setDesignFlow(const double &designFlow)  {
        this->designFlow = designFlow;
    }

    double getDesignEfficiency() const {
        return designFlow;
    }

    void setDesignEfficiency(const double &designEfficiency)  {
        this->designEfficiency = designEfficiency;
    }

    double getMotorRatedPower() const {
        return motorRatedPower;
    }

    void setMotorRatedPower(const double &motorRatedPower)  {
        this->motorRatedPower = motorRatedPower;
    }

    double getMotorFullLoadAmps() const {
        return motorFullLoadAmps;
    }

    void setMotorFullLoadAmps(const double &motorFullLoadAmps)  {
        this->motorFullLoadAmps = motorFullLoadAmps;
    }

    double getOperatingFlowRate() const {
        return operatingFlowRate;
    }

    void setOperatingFlowRate(const double &operatingFlowRate)  {
        this->operatingFlowRate = operatingFlowRate;
    }

    double getOperatingHead() const {
        return operatingHead;
    }

    void setOperatingHead(const double &operatingHead)  {
        this->operatingHead = operatingHead;
    }

    double getMeasuredCurrent() const {
        return measuredCurrent;
    }

    void setMeasuredCurrent(const double &measuredCurrent)  {
        this->measuredCurrent = measuredCurrent;
    }

    double getMeasuredPower() const {
        return measuredPower;
    }

    void setMeasuredPower(const double &measuredPower)  {
        this->measuredPower = measuredPower;
    }

    double getMeasuredVoltage() const {
        return measuredVoltage;
    }

    void setMeasuredVoltage(const double &measuredVoltage)  {
        this->measuredVoltage = measuredVoltage;
    }

    double getMotorEfficiency() const {
        return motorEfficiency;
    }

    void setMotorEfficiency(const double &motorEfficiency)  {
        this->motorEfficiency = motorEfficiency;
    }

    int getSpeed() const {
        return speed;
    }

    void setSpeed(const int &speed)  {
        this->speed = speed;
    }

    int getNumStages() const {
        return numStages;
    }

    void setNumStages(const int &numStages)  {
        this->numStages = numStages;
    }

    int getYearlyOperatingHours() const {
        return yearlyOperatingHours;
    }

    void setYearlyOperatingHours(const int &yearlyOperatingHours)  {
        this->yearlyOperatingHours = yearlyOperatingHours;
    }

    int getYearInstalled() const {
        return yearInstalled;
    }

    void setYearInstalled(const int &yearInstalled)  {
        this->yearInstalled = yearInstalled;
    }

    std::string getSerialNumber() const {
        return serialNumber;
    }

    void setSerialNumber(const std::string &serialNumber)  {
        this->serialNumber = serialNumber;
    }

    std::string getStatus() const {
        return status;
    }

    void setStatus(const std::string &status)  {
        this->status = status;
    }

    std::string getPumpType() const {
        return pumpType;
    }

    void setPumpType(const std::string &pumpType)  {
        this->pumpType = pumpType;
    }

    std::string getShaftOrientation() const {
        return shaftOrientation;
    }

    void setShaftOrientation(const std::string &shaftOrientation)  {
        this->shaftOrientation = shaftOrientation;
    }

    std::string getShaftSealType() const {
        return shaftSealType;
    }

    void setShaftSealType(const std::string &shaftSealType)  {
        this->shaftSealType = shaftSealType;
    }

    std::string getFluidType() const {
        return fluidType;
    }

    void setFluidType(const std::string &fluidType)  {
        this->fluidType = fluidType;
    }

    std::string getDriveType() const {
        return driveType;
    }

    void setDriveType(const std::string &driveType)  {
        this->driveType = driveType;
    }

    std::string getFlangeConnectionClass() const {
        return flangeConnectionClass;
    }

    void setFlangeConnectionClass(const std::string &flangeConnectionClass)  {
        this->flangeConnectionClass = flangeConnectionClass;
    }

    std::string getFlangeConnectionSize() const {
        return flangeConnectionSize;
    }

    void setFlangeConnectionSize(const std::string &flangeConnectionSize)  {
        this->flangeConnectionSize = flangeConnectionSize;
    }

    std::string getManufacturer() const {
        return manufacturer;
    }

    void setManufacturer(const std::string &manufacturer)  {
        this->manufacturer = manufacturer;
    }

    std::string getModel() const {
        return model;
    }

    void setModel(const std::string &model)  {
        this->model = model;
    }

    std::string getMotorEfficiencyClass() const {
        return motorEfficiencyClass;
    }

    void setMotorEfficiencyClass(const std::string &motorEfficiencyClass)  {
        this->motorEfficiencyClass = motorEfficiencyClass;
    }

    std::string getComponentId() const {
        return componentId;
    }

    void setComponentId(const std::string &componentId)  {
        this->componentId = componentId;
    }

    std::string getSystem() const {
        return system;
    }

    void setSystem(const std::string &system)  {
        this->system = system;
    }

    std::string getLocation() const {
        return location;
    }

    void setLocation(const std::string &location)  {
        this->location = location;
    }

    int getMotorRatedVoltage() const {
        return motorRatedVoltage;
    }

    void setMotorRatedVoltage(const int &motorRatedVoltage)  {
        this->motorRatedVoltage = motorRatedVoltage;
    }

    std::string getPriority() const {
        return priority;
    }

    void setPriority(const std::string &priority)  {
        this->priority = priority;
    }

    int getFinalMotorRpm() const {
        return finalMotorRpm;
    }

    void setFinalMotorRpm(int finalMotorRpm)  {
        this->finalMotorRpm = finalMotorRpm;
    }

    int getId() const {
        return id;
    }

    void setId(int id)  {
        this->id = id;
    }

private:
    std::string manufacturer, model, serialNumber, status, pumpType;
    std::string shaftOrientation, shaftSealType, fluidType, priority, driveType, flangeConnectionClass;
    std::string flangeConnectionSize, componentId, system, location, motorEfficiencyClass;

    int speed, numStages, yearlyOperatingHours, yearInstalled, finalMotorRpm, motorRatedVoltage;

    double inletDiameter, outletDiameter, staticSuctionHead, staticDischargeHead, fluidDensity;
    double maxWorkingPressure, maxAmbientTemperature, maxSuctionLift, displacement, startingTorque, ratedSpeed;
    double impellerDiameter, efficiency, lineFrequency, minFlowSize, pumpSize, designHead, designFlow, designEfficiency;
    double motorRatedPower, motorFullLoadAmps, operatingFlowRate, operatingHead, measuredCurrent, measuredPower, measuredVoltage, motorEfficiency;

    int id; // used for the database

    friend class SQLite;
};

#endif //TOOLS_SUITE_PUMPDATA_H