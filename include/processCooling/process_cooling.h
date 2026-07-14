#pragma once

/**
 * @file Header file for Process Fluid Cooling Energy Calculations
 *
 * @brief Originally (CWSAT) written in VB by University of Massachusetts - Amherst with funding from the U.S. Department
 * of Energy Calculator estimates energy consumption of operating Chillers, Pumps and Towers in a cooling system (both
 * air & water). Allows: Input multiple & varying capacity and types of Chillers that are operating together. Flexible
 * input for operating schedule for each Chiller. Apply changes ( improvements / measures) and compare & examine,
 * quantifying energy and cost savings. Changes: Increasing the chilled water temperature Decreasing the condenser water
 * temperature Replacing the chillers Applying variable speed control to circulation pump motors Upgrade Tower Cell Fan
 * Motor controls Upgrades: Replace chiller refrigerant Install Variable Speed Drive (VSD) on Centrifugal compressors
 *                      Use Free Cooling
 *
 * @extends This converted implementation version removes the limit on number of Pumps and Chillers.
 *
 * @author Converted by Omer Aziz from VB to C++ (omerb).
 * @bug No known bugs.
 *
 */

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

using namespace std;

constexpr int MONTHS             = 12;
constexpr int LOAD_NUM           = 11;
constexpr int HOURS_IN_YEAR      = 8760;
constexpr int CHILLER_COEFFS_CNT = 7; // 7 columns for each chiller, polynomial to either 3rd (for FullLoadEffKnown or custom chiller) or 5th degree

/**
 * @class ProcessCooling
 * @ingroup ProcessCooling
 * @brief Calculator estimates energy consumption of operating Chillers, Pumps and Towers in a cooling system (both
 * air & water). Allows: Input multiple & varying capacity and types of Chillers that are operating together. Flexible
 * input for operating schedule for each Chiller. Apply changes ( improvements / measures) and compare & examine,
 * quantifying energy and cost savings. Changes: Increasing the chilled water temperature Decreasing the condenser water
 * temperature Replacing the chillers Applying variable speed control to circulation pump motors Upgrade Tower Cell Fan
 * Motor controls Upgrades: Replace chiller refrigerant Install Variable Speed Drive (VSD) on Centrifugal compressors
 *                      Use Free Cooling
 */

class ProcessCooling {
  public:
    enum RefrigerantType { R_11, R_123, R_12, R_134a, R_22, R_717 };

    enum ACSourceLocation { Inside, Outside };

    enum CoolingSystemType { Water, Air };

    enum CellFanType { AxialFan, CentrifugalFan };

    enum TowerSizedBy { Tonnage, Fan_HP, Unknown };

    enum ChillerCompressorType { Centrifugal, Screw, Reciprocating };

    enum FanMotorSpeedType { One, Two, Variable };

    struct ChillerOutput {
        /**
         *
         * @returns arrays of double corresponding to 11 % load bins (0,10,20,30,40,50,60,70,80,90,100)
         *
         * @param efficiency array of double, @unit{\kW\ton}
         * @param hours array of double, @unit{\hours}
         * @param power array of double, @unit{\kW}
         * @param energy array of double, @unit{\kWh}
         */
        ChillerOutput(vector<vector<double>> efficiency, vector<vector<double>> hours, vector<vector<double>> power,
                      vector<vector<double>> energy)
            : efficiency(std::move(efficiency)), hours(std::move(hours)), power(std::move(power)),
              energy(std::move(energy)) {}

        vector<vector<double>> efficiency;
        vector<vector<double>> hours;
        vector<vector<double>> power;
        vector<vector<double>> energy;
    };

    struct ChillerPumpingEnergyOutput {
        /**
         *
         * @returns array of double (Pumps Energy), size corresponding to the # of chillers
         *
         * @param pumpingEnergy double, @unit{\kWh}
         */
        explicit ChillerPumpingEnergyOutput(vector<double> pumpingEnergy)
            : chillerPumpingEnergy(std::move(pumpingEnergy)) {}

        vector<double> chillerPumpingEnergy;
    };

    struct TowerOutput {
        /**
         *
         * @param no arguments
         */
        TowerOutput() = default;

        /**
         *
         * @returns arrays of double corresponding to 6 wet bulb temp bins => <35, 35-44, 45-54, 55-64, 65-74, >=75;
         *
         * @param hours array of double, @unit{\hours}
         * @param energy array of double, @unit{\kWh}
         */
        TowerOutput(vector<double> hours, vector<double> energy) : hours(std::move(hours)), energy(std::move(energy)) {}

        vector<double> tempBins = {35, 45, 55, 65, 75, 75};
        vector<double> hours;
        vector<double> energy;
    };

    struct WaterCooledSystemInput {
        /**
         *
         * @param no arguments
         */
        WaterCooledSystemInput() = default;

        /**
         *
         * @param CHWT double, @unit{\F}, 35 - 55 Default 44, Chilled Water Supply Temperature
         * @param useFreeCooling boolean
         * @param HEXApproachTemp double, @unit{\F},  5 - 20, heat exchange temp when free cooling and heat exchanger used
         * @param constantCWT boolean, Is CW temperature constant
         * @param CWT double, @unit{\F}, 70 - 90, CW temperature constant
         * @param CWVariableFlow boolean
         * @param CWFlowRate double, @unit{\gpm\ton}
         * @param CWTFollow double, @unit{\F}, when CW temperature not constant
         */
        WaterCooledSystemInput(double CHWT, bool useFreeCooling, double HEXApproachTemp, bool constantCWT, double CWT,
                               bool CWVariableFlow, double CWFlowRate, double CWTFollow)
            : CHWT(CHWT), useFreeCooling(useFreeCooling), HEXApproachTemp(HEXApproachTemp), constantCWT(constantCWT),
              CWT(CWT), CWVariableFlow(CWVariableFlow), CWFlowRate(CWFlowRate), CWTFollow(CWTFollow) {
            isWaterCooled = true;
        }

        double CHWT            = 44;
        bool   useFreeCooling  = false;
        double HEXApproachTemp = 0;
        bool   constantCWT     = true;
        double CWT             = 85;
        bool   CWVariableFlow  = true;
        double CWFlowRate      = 3;
        double CWTFollow       = 0;
        bool   isWaterCooled   = false;
    };

    struct AirCooledSystemInput {
        /**
         *
         * @param no arguments
         */
        AirCooledSystemInput() = default;

        /**
         *
         * @param CHWT double, @unit{\F}, 35 - 55 Default 44, Chilled Water Supply Temperature
         * @param OADT double, @unit{\F}, 80 - 110 Standard 95, Outdoor Air Design Temperature
         * @param ACSource Enumeration ACSourceLocation, Cooling Air Source, Indoor or Outside
         * @param indoorTemp double, @unit{\F}, if Air Source Indoor 60 - 90
         * @param CWTFollow double, @unit{\F}, if Air Source Outside 5 - 20
         */
        AirCooledSystemInput(double CHWT, double OADT, ACSourceLocation ACSource, double indoorTemp, double CWTFollow)
            : CHWT(CHWT), OADT(OADT), ACSource(ACSource), indoorTemp(indoorTemp), CWTFollow(CWTFollow) {
            isAirCooled = true;
        }

        double           CHWT        = 44;
        double           OADT        = 95;
        ACSourceLocation ACSource    = ACSourceLocation::Outside;
        double           indoorTemp  = 75;
        double           CWTFollow   = 0;
        bool             isAirCooled = false;
    };

    struct PumpInput {
        /**
         *
         * @param variableFlow boolean
         * @param flowRate double, @unit{\gpm\ton}
         * @param efficiency double, percentage as fraction
         * @param motorSize double, @unit{\hp}, if size is unknown set size to 0, and it will be estimated based on flow rate and efficiency
         * @param motorEfficiency double, percentage as fraction
         */
        PumpInput(bool variableFlow, double flowRate, double efficiency, double motorSize, double motorEfficiency)
            : variableFlow(variableFlow), flowRate(flowRate), efficiency(efficiency * 100), motorSize(motorSize),
              motorEfficiency(motorEfficiency * 100) {}

        bool   variableFlow;
        double flowRate;
        double efficiency;
        double motorSize;
        double motorEfficiency;
    };

    struct TowerInput {
        /**
         *
         * @param no arguments
         */
        TowerInput() = default;

        /**
         *
         * @param numTower integer, # of Towers
         * @param numFanPerTower_Cells integer, # Cells
         * @param fanSpeedType Enumeration FanMotorSpeedType
         * @param towerSizing Enumeration TowerSizedBy, sized by tonnage or fan hp,
         *          if unknown
         *              use tonnage and set tonnage to sum of all chillers capacity
         *              or set to unknown, and it will be sized to match the capacity of chillers by the calculator
         * @param towerCellFanType Enumeration CellFanType, axial or centrifugal, if unknown assume axial
         * @param cellFanHP double, @unit{\hp}, 1 -100 hp
         * @param tonnage double, @unit{\ton}, 20 - 3000
         */
        TowerInput(int numTower, int numFanPerTower_Cells, FanMotorSpeedType fanSpeedType, TowerSizedBy towerSizing,
                   CellFanType towerCellFanType, double cellFanHP, double tonnage)
            : numTower(numTower), numFanPerTower_Cells(numFanPerTower_Cells), fanSpeedType(fanSpeedType), towerSizing(towerSizing),
              towerCellFanType(towerCellFanType), fanHP(cellFanHP), tonnage(tonnage) {}

        int               numTower;
        int               numFanPerTower_Cells;
        FanMotorSpeedType fanSpeedType;
        TowerSizedBy      towerSizing;
        CellFanType       towerCellFanType;
        double            fanHP;
        double            tonnage;
    };

    struct ChillerInput {
        /**
         *
         * @details Use this constructor when not defining custom Chiller and not replacing chiller refrigerant
         *
         * @param chillerType Enumeration ChillerCompressorType
         * @param capacity double, @unit{\ton}
         * @param isFullLoadEffKnown boolean, Is full load efficiency known? for this Chiller
         * @param fullLoadEff double, fraction, 0.2 - 2.5 increments of .01
         * @param age double # of years, 0 - 20, (can be 1.5 for eighteen months), assumption chiller efficiency is
         * degraded by 1% / year
         * @param installVSD boolean, Install a VSD on each Centrifugal Compressor Motor
         * @param useARIMonthlyLoadSchedule boolean, if true monthlyLoads not needed and can be set to empty
         * @param monthlyLoads double, 12x11 array of 11 %load bins (0,10,20,30,40,50,60,70,80,90,100) for 12 calendar
         * months In case of non varying monthly loads expects a 1X11 array of 11 %load bins
         */
        ChillerInput(ChillerCompressorType chillerType, double capacity, bool isFullLoadEffKnown, double fullLoadEff,
                     double age, bool installVSD, bool useARIMonthlyLoadSchedule, vector<vector<double>> monthlyLoads)
            : chillerType(chillerType), capacity(capacity), isFullLoadEffKnown(isFullLoadEffKnown),
              fullLoadEff(fullLoadEff), age(age), installVSD(installVSD),
              useARIMonthlyLoadSchedule(useARIMonthlyLoadSchedule), monthlyLoads(std::move(monthlyLoads)),
              isCustomChiller(false), loadAtPercent({}), kwPerTonLoads({}), changeRefrig(false),
              currentRefrig(RefrigerantType::R_11), proposedRefrig(RefrigerantType::R_11) {
            InitNonVaryingMonthlyLoad();
        }

        /**
         *
         * @details Use this constructor when replacing chiller refrigerant
         *
         * @param chillerType Enumeration ChillerCompressorType
         * @param capacity double, @unit{\ton}
         * @param isFullLoadEffKnown boolean, Is full load efficiency known? for this Chiller
         * @param fullLoadEff double, fraction, 0.2 - 2.5 increments of .01
         * @param age double # of years, 0 - 20, (can be 1.5 for eighteen months), assumption chiller efficiency is
         * degraded by 1% / year
         * @param installVSD boolean, Install a VSD on each Centrifugal Compressor Motor
         * @param useARIMonthlyLoadSchedule boolean, if true monthlyLoads not needed and can be set to empty
         * @param monthlyLoads double, 12x11 array of 11 %load bins (0,10,20,30,40,50,60,70,80,90,100) for 12 calendar
         * months In case of non varying monthly loads expects a 1X11 array of 11 %load bins
         *
         * @param changeRefrig boolean
         * @param currentRefrig Enumeration RefrigerantType
         * @param proposedRefrig Enumeration RefrigerantType
         */
        ChillerInput(ChillerCompressorType chillerType, double capacity, bool isFullLoadEffKnown, double fullLoadEff,
                     double age, bool installVSD, bool useARIMonthlyLoadSchedule, vector<vector<double>> monthlyLoads,
                     bool changeRefrig, RefrigerantType currentRefrig, RefrigerantType proposedRefrig)
            : chillerType(chillerType), capacity(capacity), isFullLoadEffKnown(isFullLoadEffKnown),
              fullLoadEff(fullLoadEff), age(age), installVSD(installVSD),
              useARIMonthlyLoadSchedule(useARIMonthlyLoadSchedule), monthlyLoads(std::move(monthlyLoads)),
              isCustomChiller(false), loadAtPercent({}), kwPerTonLoads({}), changeRefrig(changeRefrig),
              currentRefrig(currentRefrig), proposedRefrig(proposedRefrig) {
            InitNonVaryingMonthlyLoad();
        }

        /**
         *
         * @details Use this constructor when replacing chiller refrigerant
         *
         * @param chillerType Enumeration ChillerCompressorType
         * @param capacity double, @unit{\ton}
         * @param isFullLoadEffKnown boolean, Is full load efficiency known? for this Chiller
         * @param fullLoadEff double, fraction, 0.2 - 2.5 increments of .01
         * @param age double # of years, 0 - 20, (can be 1.5 for eighteen months), assumption chiller efficiency is
         * degraded by 1% / year
         * @param installVSD boolean, Install a VSD on each Centrifugal Compressor Motor
         * @param useARIMonthlyLoadSchedule boolean, if true monthlyLoads not needed and can be set to empty
         * @param monthlyLoads double, 12x11 array of 11 %load bins (0,10,20,30,40,50,60,70,80,90,100) for 12 calendar
         * months In case of non varying monthly loads expects a 1X11 array of 11 %load bins
         *
         * @param currentRefrig Enumeration RefrigerantType
         * @param proposedRefrig Enumeration RefrigerantType
         */
        ChillerInput(ChillerCompressorType chillerType, double capacity, bool isFullLoadEffKnown, double fullLoadEff,
                     double age, bool installVSD, bool useARIMonthlyLoadSchedule, vector<vector<double>> monthlyLoads,
                     RefrigerantType currentRefrig, RefrigerantType proposedRefrig)
            : chillerType(chillerType), capacity(capacity), isFullLoadEffKnown(isFullLoadEffKnown),
              fullLoadEff(fullLoadEff), age(age), installVSD(installVSD),
              useARIMonthlyLoadSchedule(useARIMonthlyLoadSchedule), monthlyLoads(std::move(monthlyLoads)),
              isCustomChiller(false), loadAtPercent({}), kwPerTonLoads({}), changeRefrig(true),
              currentRefrig(currentRefrig), proposedRefrig(proposedRefrig) {
            InitNonVaryingMonthlyLoad();
        }

        /**
         *
         * @details Use this constructor to define custom Chiller
         *
         * @param chillerType Enumeration ChillerCompressorType
         * @param capacity double, @unit{\ton}
         * @param isFullLoadEffKnown boolean, Is full load efficiency known? for this Chiller
         * @param fullLoadEff double, fraction, 0.2 - 2.5 increments of .01
         * @param age double # of years, 0 - 20, (can be 1.5 for eighteen months), assumption chiller efficiency is
         * degraded by 1% / year
         * @param installVSD boolean, Install a VSD on each Centrifugal Compressor Motor
         * @param useARIMonthlyLoadSchedule boolean, if true monthlyLoads not needed and can be set to empty
         * @param monthlyLoads double, 12x11 array of 11 %load bins (0,10,20,30,40,50,60,70,80,90,100) for 12 calendar
         * months In case of non varying monthly loads expects a 1X11 array of 11 %load bins
         *
         * @param loadAtPercent double array, % loading in ascending order (25, 50, 75, 100)
         * @param kwPerTonLoads double array, kW/ton at the corresponding % loading
         */
        ChillerInput(ChillerCompressorType chillerType, double capacity, bool isFullLoadEffKnown, double fullLoadEff,
                     double age, bool installVSD, bool useARIMonthlyLoadSchedule, vector<vector<double>> monthlyLoads,
                     vector<double> loadAtPercent, vector<double> kwPerTonLoads)
            : chillerType(chillerType), capacity(capacity), isFullLoadEffKnown(isFullLoadEffKnown),
              fullLoadEff(fullLoadEff), age(age), installVSD(installVSD),
              useARIMonthlyLoadSchedule(useARIMonthlyLoadSchedule), monthlyLoads(std::move(monthlyLoads)),
              isCustomChiller(true), loadAtPercent(std::move(loadAtPercent)), kwPerTonLoads(std::move(kwPerTonLoads)),
              changeRefrig(false), currentRefrig(RefrigerantType::R_11), proposedRefrig(RefrigerantType::R_11) {
            InitNonVaryingMonthlyLoad();
            SetCustomCoefficient();
        }

        /**
         *
         * @details Use this constructor for custom Chiller with replacing refrigerant
         *
         * @param chillerType Enumeration ChillerCompressorType
         * @param capacity double, @unit{\ton}
         * @param isFullLoadEffKnown boolean, Is full load efficiency known? for this Chiller
         * @param fullLoadEff double, fraction, 0.2 - 2.5 increments of .01
         * @param age double # of years, 0 - 20, (can be 1.5 for eighteen months), assumption chiller efficiency is
         * degraded by 1% / year
         * @param installVSD boolean, Install a VSD on each Centrifugal Compressor Motor
         * @param useARIMonthlyLoadSchedule boolean, if true monthlyLoads not needed and can be set to empty
         * @param monthlyLoads double, 12x11 array of 11 %load bins (0,10,20,30,40,50,60,70,80,90,100) for 12 calendar
         * months In case of non varying monthly loads expects a 1X11 array of 11 %load bins
         *
         * @param loadAtPercent double array, % loading in ascending order (25, 50, 75, 100)
         * @param kwPerTonLoads double array, kW/ton at the corresponding % loading
         *
         * @param currentRefrig Enumeration RefrigerantType
         * @param proposedRefrig Enumeration RefrigerantType
         */
        ChillerInput(ChillerCompressorType chillerType, double capacity, bool isFullLoadEffKnown, double fullLoadEff,
                     double age, bool installVSD, bool useARIMonthlyLoadSchedule, vector<vector<double>> monthlyLoads,
                     vector<double> loadAtPercent, vector<double> kwPerTonLoads, RefrigerantType currentRefrig,
                     RefrigerantType proposedRefrig)
            : chillerType(chillerType), capacity(capacity), isFullLoadEffKnown(isFullLoadEffKnown),
              fullLoadEff(fullLoadEff), age(age), installVSD(installVSD),
              useARIMonthlyLoadSchedule(useARIMonthlyLoadSchedule), monthlyLoads(std::move(monthlyLoads)),
              isCustomChiller(true), loadAtPercent(std::move(loadAtPercent)), kwPerTonLoads(std::move(kwPerTonLoads)),
              changeRefrig(true), currentRefrig(currentRefrig), proposedRefrig(proposedRefrig) {
            InitNonVaryingMonthlyLoad();
            SetCustomCoefficient();
        }

        ChillerCompressorType  chillerType;
        double                 capacity;
        bool                   isFullLoadEffKnown;
        double                 fullLoadEff;
        double                 age;
        bool                   installVSD;
        bool                   useARIMonthlyLoadSchedule;
        vector<vector<double>> monthlyLoads;

        bool           isCustomChiller;
        vector<double> loadAtPercent;
        vector<double> kwPerTonLoads;

        bool            changeRefrig = false;
        RefrigerantType currentRefrig;
        RefrigerantType proposedRefrig;

        vector<double> customCoeffs;
        vector<double> customCoeffs_eff;

      private:
        void InitNonVaryingMonthlyLoad() {
            if (monthlyLoads.size() == 1) {
                auto monthlyLoad = monthlyLoads[0];

                for (int i = 0; i < 11; i++) {
                    monthlyLoads.push_back(monthlyLoad);
                }
            }
        }

        void SetCustomCoefficient() {
            if (loadAtPercent.empty() || kwPerTonLoads.empty() || loadAtPercent.size() != kwPerTonLoads.size()) {
                throw std::runtime_error("Invalid input provided for loadAtPercent or kwPerTonLoads, should be non empty and have same number of elements.");
            }

            auto size = static_cast<int>(loadAtPercent.size());

            // % loading in ascending order (25, 50, 75, 100)
            if (loadAtPercent[0] > loadAtPercent[size-1]) {
                std::reverse(loadAtPercent.begin(), loadAtPercent.end());
                std::reverse(kwPerTonLoads.begin(), kwPerTonLoads.end());
            }

            vector<double> x(size, 0);
            vector<double> y(size, 0);
            const auto kwPerTonLoadAtMaxLoad = kwPerTonLoads[size-1];

            if (kwPerTonLoadAtMaxLoad == 0) {
                throw std::runtime_error("% loading @ 100 % cannot be zero.");
            }

            for (int i = 0; i < size; i++) {
                x[i] = loadAtPercent[i]/100.0;
                y[i] = kwPerTonLoads[i] * x[i] / kwPerTonLoadAtMaxLoad;
            }
            vector<double> coeff = solveForCoefficients(x, y);
            vector<double> coeff_eff = solveForCoefficients(x, kwPerTonLoads);

            size = static_cast<int>(coeff.size());
            customCoeffs.resize(size, 0);
            customCoeffs_eff.resize(size, 0);
            for (int i = 0; i < size; i++) {
                customCoeffs[i] = coeff[i];
                customCoeffs_eff[i] = coeff_eff[i];
            }
        }

        static vector<double> solveForCoefficients(const vector<double>& x, vector<double> y) {
            if (x.empty() || x.size() != y.size())
                return {};

            const int n = static_cast<int>(x.size());

            vector<vector<double>> a(n, vector<double>(n, 0));
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    a[i][j] = pow(x[i], n - 1 - j);
                }
            }

            // Forward Elimination
            for (int k = 0; k < n - 1; ++k) {
                for (int i = k + 1; i < n; ++i) {
                    double factor = a[i][k] / a[k][k];
                    for (int j = k + 1; j < n; ++j) {
                        a[i][j] -= factor * a[k][j];
                    }
                    y[i] -= factor * y[k];
                }
            }

            // Back Substitution
            vector<double> coeff(n, 0);
            coeff[n - 1] = y[n - 1] / a[n - 1][n - 1];
            for (int i = n - 2; i >= 0; --i) {
                double sum = y[i];
                for (int j = i + 1; j < n; ++j) {
                    sum -= a[i][j] * coeff[j];
                }
                coeff[i] = sum / a[i][i];
            }

            return coeff;
        }
    };

    ~ProcessCooling() = default;

    /**
     *
     * @details Use this constructor for water cooling system
     *
     * @param systemOperationAnnualHours integer array of 8760 hours of the year with values as 0 or 1
     * @param weatherDryBulbHourlyTemp double, @unit{\F}, array of 8760 hours of the year with dry bulb hourly recorded
     * temperature
     * @param weatherWetBulbHourlyTemp double, @unit{\F}, array of 8760 hours of the year with wet bulb hourly recorded
     * temperature
     * @param chillerInputList ChillerInput array
     *
     * @param towerInput TowerInput
     * @param waterCooledSystemInput WaterCooledSystemInput
     */
    ProcessCooling(const vector<int>& systemOperationAnnualHours, const vector<double>& weatherDryBulbHourlyTemp,
                   const vector<double>& weatherWetBulbHourlyTemp, const vector<ChillerInput>& chillerInputList,
                   const TowerInput& towerInput, const WaterCooledSystemInput& waterCooledSystemInput)
        : ProcessCooling(systemOperationAnnualHours, weatherDryBulbHourlyTemp, weatherWetBulbHourlyTemp,
                         chillerInputList, {}, towerInput, waterCooledSystemInput) {}

    /**
     *
     * @details Use this constructor for air cooled system
     *
     * @param systemOperationAnnualHours integer array of 8760 hours of the year with values as 0 or 1
     * @param weatherDryBulbHourlyTemp double array of 8760 hours of the year with dry bulb hourly recorded temperature
     * @param weatherWetBulbHourlyTemp double array of 8760 hours of the year with wet bulb hourly recorded temperature
     * @param chillerInputList ChillerInput array
     *
     * @param airCooledSystemInput AirCooledSystemInput
     */
    ProcessCooling(const vector<int>& systemOperationAnnualHours, const vector<double>& weatherDryBulbHourlyTemp,
                   const vector<double>& weatherWetBulbHourlyTemp, const vector<ChillerInput>& chillerInputList,
                   const AirCooledSystemInput& airCooledSystemInput)
        : ProcessCooling(systemOperationAnnualHours, weatherDryBulbHourlyTemp, weatherWetBulbHourlyTemp,
                         chillerInputList, airCooledSystemInput, {}, {}) {}

    /**
     *
     * @return TowerOutput
     */
    TowerOutput calculateTowerEnergy();

    /**
     *
     * @return ChillerOutput
     */
    ChillerOutput calculateChillerEnergy();

    /**
     *
     * @param pump PumpInput
     * @return ChillerPumpingEnergyOutput
     */
    ChillerPumpingEnergyOutput calculatePumpEnergy(PumpInput pump) const;

    /**
     *
     ** @details Use this method to generate system operation annual hours from weekly schedules and monthly max operation hours
     *
     * @param weeklyOpStartHour integer array of 7 with hours of the day of the week with start hour of operation (0-23)
     * @param weeklyOpStopHour integer array of 7 with hours of the day of the week with stop hour of operation (0-24)
     * @param monthlyOpMaxHour integer array of 12 with months of the year with max operation hours in that month (0-744)
     * 0 for no operation for that month. If monthlyOpMaxHour exceeds the total hours for a month, it will be capped to the max hours in that month and ending hour for that month will be set to non-operational after the max hours is reached.
     *
     * @return integer array of 8760 hours of the year with values as 0 or 1 set based on weekly and monthly schedules
     */
    static vector<int> getSysOpAnnualHours(const vector<int>& weeklyOpStartHour, const vector<int>& weeklyOpStopHour, const vector<int>& monthlyOpMaxHour);

    /**
     *
     * @param chillerIndex integer, zero based index of chiller from the chillers input provided
     *
     * @return an array of coefficients
     *          4 for 3rd degree polynomial(for FullLoadEffKnown or custom chiller) or
     *          7 for 5th degree polynomial
     */
    vector<double> getChillerEfficiencyCoeffs(int chillerIndex) const;

    /**
     *
     * @param chillerIndex integer, zero based index of chiller from the chillers input provided
     * @param loadAtPercent double array, % loading, between 0 and 100, can be either ascending or descending or in any order
     * @param applyFactoring boolean, whether to apply aging and full load effeciency factoring to the energy efficiency calculation
     *
     * @return an array of energy efficiency values for % loads, corresponding to the same order of input loadAtPercent array
     */
    vector<double> getChillerEnergyEfficiency(int chillerIndex, const vector<double>& loadAtPercent, bool applyFactoring) const;

  private:
    ProcessCooling(const vector<int>& systemOperationAnnualHours, const vector<double>& weatherDryBulbHourlyTemp,
                   const vector<double>& weatherWetBulbHourlyTemp, const vector<ChillerInput>& chillerInputList,
                   const AirCooledSystemInput& airCooledSystemInput, const TowerInput& towerInput,
                   const WaterCooledSystemInput& waterCooledSystemInput);

    vector<int> systemOperationAnnual;
    vector<double> dryBulbHourlyTemp;
    vector<double> wetBulbHourlyTemp;

    TowerInput             tower {};
    WaterCooledSystemInput waterCooledSystem;
    AirCooledSystemInput   airCooledSystem;
    CoolingSystemType      coolingType;

    double    FCTemp = 0; // Free Cooling Temperature
    vector<double> CWTHourly;

    int       numChillers;
    vector<ChillerInput> chillers;
    vector<vector<double>> chillerHourlyLoad;
    vector<vector<double>> chillerHourlyLoadOperational;
    vector<vector<double>> chillerEfficiencyCoeffs;
    vector<vector<double>> chillerHourlyEfficiencyARI;
    vector<vector<double>> chillerHourlyEfficiency;
    vector<vector<double>> chillerHourlyPower;

    int getChillerCapacityIndex(ChillerCompressorType chillerType, double capacity) const;

    void annualChillerLoadProfile();

    void annualChillerEfficiencyProfileARI();

    void annualChillerEfficiencyProfile();

    void annualChillerPowerProfile();

    void setTowerFanHPTonnage();

    double getChillerEffAtLoad(int c, double load, bool isFullLoadEffKnown, bool applyFactoring) const;

    double getPercentFanPower(double wetBulbTemp, double percentWaterFlow, double range, double desiredApproach, int yearHourIndex);

    double getPercentWaterFlow(int yearHourIndex) const;

    double getRange(int yearHourIndex) const;

    double getApproach(double wetBulbTemp) const;

    double modifyPercentFanPower(double percentFanPower) const;

    double getWeightedAverageChillerLoad(int yearHourIndex) const;

    double getChillerTonnageTotal() const;

    static double getCubeRoot(double number);

    static double getPumpHP(double power);
};
