#ifndef TOOLS_SUITE_MOTORDATA_H
#define TOOLS_SUITE_MOTORDATA_H

#include <string>

struct Motor {
    enum class EfficiencyClass {
        STANDARD,
        ENERGY_EFFICIENT,
        PREMIUM,
        SPECIFIED,
    };

    enum class LineFrequency {
        FREQ60,
        FREQ50
    };

    enum class Drive {
        DIRECT_DRIVE,
        V_BELT_DRIVE,
        N_V_BELT_DRIVE,
        S_BELT_DRIVE,
        SPECIFIED
    };

    enum class LoadEstimationMethod {
        POWER,
        CURRENT
    };

    /**
     * Constructor
     * @param lineFrequency LineFrequency, main supply frequency at either 50Hz or 60Hz
     * @param motorRatedPower double, rated power for the motor in hp
     * @param motorRpm double, motor RPM
     * @param efficiencyClass EfficiencyClass, classification of motor efficiency
     * @param specifiedEfficiency double, specified % Efficiency of motor, unused unless efficiency class is SPECIFIED
     * @param motorRatedVoltage double, motor nameplate design voltage in volts
     * @param fullLoadAmps double, current at full load in amps
     * @param sizeMargin double, size margin as defined in %
     */
    Motor(const LineFrequency lineFrequency, const double motorRatedPower, const double motorRpm,
          const EfficiencyClass efficiencyClass, const double specifiedEfficiency, const double motorRatedVoltage,
          const double fullLoadAmps, const double sizeMargin = 1)
            : lineFrequency(lineFrequency), motorRatedPower(motorRatedPower), motorRpm(motorRpm),
              efficiencyClass(efficiencyClass), specifiedEfficiency(specifiedEfficiency),
              motorRatedVoltage(motorRatedVoltage), fullLoadAmps(fullLoadAmps), sizeMargin(sizeMargin)
    {};

    const LineFrequency lineFrequency;
    const double motorRatedPower, motorRpm;
    const Motor::EfficiencyClass efficiencyClass;
    const double specifiedEfficiency, motorRatedVoltage, fullLoadAmps, sizeMargin;
};

/*
TODO: Merge these columns with the current columns (Ask Alex/Kristine for help)
NOTE: Storing all this data in MEASUR
MotorData(std::string manufacturer, std::string model, std::string catalog, std::string motorType, int hp, int speed, int fullLoadSpeed, std::string enclosureType, std::string frameNumber,
	          int voltageRating, std::string purpose, int uFrame, int cFace, int verticalShaft, int dFlange, double serviceFactor, std::string insulationClass, double weight, double listPrice,
	          double windingResistance, double warranty, int rotorBars, int statorSlots, double efficiency100, double efficiency75, double efficiency50, double efficiency25, double powerFactor100,
	          double powerFactor75, double powerFactor50, double powerFactor25, double torqueFullLoad, double torqueBreakDown, double torqueLockedRotor, double ampsFullLoad, double ampsIdle,
	          double ampsLockedRotor, double stalledRotorTimeHot, double stalledRotorTimeCold, double peakVoltage0ms, double peakVoltage5ms);
*/
class MotorData
{
public:
    MotorData(double hp, int synchronousSpeed, int poles, double nominalEfficiency, Motor::EfficiencyClass efficiencyClass, std::string nemaTable,
                         std::string enclosureType,  Motor::LineFrequency lineFrequency, int voltageLimit, std::string catalog)
            : hp(hp), synchronousSpeed(synchronousSpeed), poles(poles), nominalEfficiency(nominalEfficiency),
              efficiencyClass(efficiencyClass), nemaTable(std::move(nemaTable)), enclosureType(std::move(enclosureType)),
              lineFrequency(lineFrequency), voltageLimit(voltageLimit), catalog(std::move(catalog))
    {}

    Motor::EfficiencyClass getEfficiencyClass() const {
        return efficiencyClass;
    }

    std::string getNemaTable() const {
        return nemaTable;
    }

    std::string getEnclosureType() const {
        return enclosureType;
    }

    std::string getCatalog() const {
        return catalog;
    }

    int getSynchronousSpeed() const {
        return synchronousSpeed;
    }

    int getPoles() const {
        return poles;
    }

    Motor::LineFrequency getLineFrequency() const {
        return lineFrequency;
    }

    int getVoltageLimit() const {
        return voltageLimit;
    }

    double getHp() const {
        return hp;
    }

    double getNominalEfficiency() const {
        return nominalEfficiency;
    }

    void setEfficiencyClass(const Motor::EfficiencyClass &efficiencyClass) {
        this->efficiencyClass = efficiencyClass;
    }

    void setNemaTable(const std::string &nemaTable) {
        this->nemaTable = nemaTable;
    }

    void setEnclosureType(const std::string &enclosureType) {
        this->enclosureType = enclosureType;
    }

    void setCatalog(const std::string &catalog) {
        this->catalog = catalog;
    }

    void setSynchronousSpeed(int synchronousSpeed) {
        this->synchronousSpeed = synchronousSpeed;
    }

    void setPoles(int poles) {
        this->poles = poles;
    }

    void setLineFrequency(const Motor::LineFrequency lineFrequency) {
        this->lineFrequency = lineFrequency;
    }

    void setVoltageLimit(int voltageLimit) {
        this->voltageLimit = voltageLimit;
    }

    void setHp(double hp) {
        this->hp = hp;
    }

    void setNominalEfficiency(double nominalEfficiency) {
        this->nominalEfficiency = nominalEfficiency;
    }

    int getId() const {
        return id;
    }

    void setId(int id) {
        this->id = id;
    }

private:
	double hp;
	int synchronousSpeed, poles;
	double nominalEfficiency;
    Motor::EfficiencyClass efficiencyClass;
    std::string nemaTable, enclosureType;
    Motor::LineFrequency lineFrequency;
    int voltageLimit;
    std::string catalog;
    int id; // used for the database

	friend class SQLite;
};

#endif //TOOLS_SUITE_MOTORDATA_H
