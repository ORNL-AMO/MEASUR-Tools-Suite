#pragma once
#include <string>

#include "physics/gas_constants.h"
#include "physics/gas_properties.h"
using namespace gas_properties;
using namespace gas_constants;

/**
 * @ingroup gas_composition
 * @file gas_composition.h
 * @authors Mark Root
 *
 * @copybrief gas_composition
 */

/**
 * @ingroup gas_composition
 * @namespace gas_composition
 * @brief Contains functions for gas composition calculations.
 */

namespace gas_composition {

struct GasFlueGasComponents {
    double mO2;
    double mN2;
    double mCO2;
    double mH2O;
    double mSO2;
};

/**
 * @ingroup gas_composition
 * @class GasComposition
 * @brief Represents a fuel gas mixture and its properties for process heat calculations.
 * @details Stores the composition and calculated properties for a fuel gas mixture, including constituent gases and
 * derived values.
 * @param[in] substance Name of the fuel gas mixture
 * @param[in] ch4_percent Methane (CH4) percent by volume @unitb{\percent}
 * @param[in] c2h6_percent Ethane (C2H6) percent by volume @unitb{\percent}
 * @param[in] n2_percent Nitrogen (N2) percent by volume @unitb{\percent}
 * @param[in] h2_percent Hydrogen (H2) percent by volume @unitb{\percent}
 * @param[in] c3h8_percent Propane (C3H8) percent by volume @unitb{\percent}
 * @param[in] c4h10_cnh2n_percent Butane/Paraffins (C4H10/CnH2n) percent by volume @unitb{\percent}
 * @param[in] h2o_percent Water vapor (H2O) percent by volume @unitb{\percent}
 * @param[in] co_percent Carbon monoxide (CO) percent by volume @unitb{\percent}
 * @param[in] co2_percent Carbon dioxide (CO2) percent by volume @unitb{\percent}
 * @param[in] so2_percent Sulfur dioxide (SO2) percent by volume @unitb{\percent}
 * @param[in] o2_percent Oxygen (O2) percent by volume @unitb{\percent}
 * @var substance Name of the fuel gas mixture
 * @var ch4 Properties for methane (CH4) constituent
 * @var c2h6 Properties for ethane (C2H6) constituent
 * @var n2 Properties for nitrogen (N2) constituent
 * @var h2 Properties for hydrogen (H2) constituent
 * @var c3h8 Properties for propane (C3H8) constituent
 * @var c4h10_cnh2n Properties for butane/paraffins (C4H10/CnH2n) constituent
 * @var h2o Properties for water vapor (H2O) constituent
 * @var co Properties for carbon monoxide (CO) constituent
 * @var co2 Properties for carbon dioxide (CO2) constituent
 * @var so2 Properties for sulfur dioxide (SO2) constituent
 * @var o2 Properties for oxygen (O2) constituent
 * @var total_composition_weight Total composition weight of the gas mixture @unitb{\percent}
 * @var heating_value Heating value of the fuel gas mixture @unitb{\btu/\scf}
 * @var heating_value_volume Heating value of the fuel gas mixture @unitb{\btu/\ft^3}
 * @var specific_gravity Specific gravity of the fuel gas mixture @unitb{\unitless}
 * @var stoichometric_air Stoichiometric air required for complete combustion @unitb{\scf\,air/\scf\,fuel}
 */
class GasComposition {
  public:
    std::string   substance;
    GasProperties ch4;
    GasProperties c2h6;
    GasProperties n2;
    GasProperties h2;
    GasProperties c3h8;
    GasProperties c4h10_cnh2n;
    GasProperties h2o;
    GasProperties co;
    GasProperties co2;
    GasProperties so2;
    GasProperties o2;
    double        total_composition_weight;
    double        heating_value;
    double        heating_value_volume;
    double        specific_gravity;
    double        stoichometric_air;
    GasComposition(const std::string substance, double ch4_percent, double c2h6_percent, double n2_percent,
                   double h2_percent, double c3h8_percent, double c4h10_cnh2n_percent, double h2o_percent,
                   double co_percent, double co2_percent, double so2_percent, double o2_percent)
        : substance(substance), ch4(specificHeatCH4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
          c2h6(specificHeatC2H6, 0, 0, 0, 0, 0, 0, 0, 0, 0), n2(specificHeatN2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
          h2(specificHeatH2, 0, 0, 0, 0, 0, 0, 0, 0, 0), c3h8(specificHeatC3H8, 0, 0, 0, 0, 0, 0, 0, 0, 0),
          c4h10_cnh2n(specificHeatC4H10CnH2n, 0, 0, 0, 0, 0, 0, 0, 0, 0),
          h2o(specificHeatH2O, 0, 0, 0, 0, 0, 0, 0, 0, 0), co(specificHeatCO, 0, 0, 0, 0, 0, 0, 0, 0, 0),
          co2(specificHeatCO2, 0, 0, 0, 0, 0, 0, 0, 0, 0), so2(specificHeatSO2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
          o2(specificHeatO2, 0, 0, 0, 0, 0, 0, 0, 0, 0) {
        double total_percent = ch4_percent + c2h6_percent + n2_percent + h2_percent + c3h8_percent +
                               c4h10_cnh2n_percent + h2o_percent + co_percent + co2_percent + so2_percent + o2_percent;
        setCH4(ch4_percent, ch4_percent / total_percent);
        setC2H6(c2h6_percent, c2h6_percent / total_percent);
        setN2(n2_percent, n2_percent / total_percent);
        setH2(h2_percent, h2_percent / total_percent);
        setC3H8(c3h8_percent, c3h8_percent / total_percent);
        setC4H10CnH2n(c4h10_cnh2n_percent, c4h10_cnh2n_percent / total_percent);
        setH2O(h2o_percent, h2o_percent / total_percent);
        setCO(co_percent, co_percent / total_percent);
        setCO2(co2_percent, co2_percent / total_percent);
        setSO2(so2_percent, so2_percent / total_percent);
        setO2(o2_percent, o2_percent / total_percent);
        setTotalCompositionWeight();
        setHeatingValue();
        setHeatingValueVolume();
        setSpecificGravity();
        setStoichometricAir();
    };

    /**
     * @brief Calculates excess air percentage from flue gas oxygen percentage.
     * @param[in] flue_gas_o2_percentage Oxygen percentage in flue gas @unitb{\percent}
     * @return Excess air percentage @unitb{\percent}
     */
    double excessAirFromO2(double flue_gas_o2_percentage);

    /**
     * @brief Calculates flue gas oxygen percentage from excess air percentage.
     * @param[in] excess_air Excess air percentage @unitb{\percent}
     * @return Oxygen percentage in flue gas @unitb{\percent}
     */
    double o2PercentageFromExcessAir(double excess_air);

    /**
     * @brief Estimates excess air percentage from flue gas oxygen percentage.
     * @param[in] flue_gas_o2_percentage Oxygen percentage in flue gas @unitb{\percent}
     * @return Estimated excess air percentage @unitb{\percent}
     */
    double estimateExcessAirFromO2(double flue_gas_o2_percentage);

    /**
     * @brief Calculates enthalpy at saturation for a given partial pressure of water vapor.
     * @param[in] partial_pressure_water_vapor Partial pressure of water vapor @unitb{\psia}
     * @return Enthalpy at saturation @unitb{\btu/\lb}
     */
    double calculateEnthalpyAtSaturation(double partial_pressure_water_vapor);

    /**
     * @brief Calculates saturation temperature for a given partial pressure of water vapor.
     * @param[in] partial_pressure_water_vapor Partial pressure of water vapor @unitb{\psia}
     * @return Saturation temperature @unitb{\degreeFahrenheit}
     */
    double calculateSaturationTemperature(double partial_pressure_water_vapor);

    std::array<GasProperties*, 11> getConstituents() {
        return {&ch4, &c2h6, &n2, &h2, &c3h8, &c4h10_cnh2n, &h2o, &co, &co2, &so2, &o2};
    };

    double adjustedFlueGasO2ForCalcError(double excess_air, double flue_gas_o2);

  private:
    void setCH4(double composition_percent, double composition_by_volume) {
        ch4 = GasProperties(specificHeatCH4, CH4_MOLECULAR_WEIGHT, CH4_SPECIFIC_WEIGHT, composition_percent,
                            composition_by_volume, CH4_O2_GENERATED, CH4_HEATING_VALUE, CH4_HEATING_VALUE_VOLUME,
                            CH4_H2O_GENERATED, CH4_CO2_GENERATED);
    }

    void setC2H6(double composition_percent, double composition_by_volume) {
        c2h6 = GasProperties(specificHeatC2H6, C2H6_MOLECULAR_WEIGHT, C2H6_SPECIFIC_WEIGHT, composition_percent,
                             composition_by_volume, C2H6_O2_GENERATED, C2H6_HEATING_VALUE, C2H6_HEATING_VALUE_VOLUME,
                             C2H6_H2O_GENERATED, C2H6_CO2_GENERATED);
    }

    void setN2(double composition_percent, double composition_by_volume) {
        n2 = GasProperties(specificHeatN2, N2_MOLECULAR_WEIGHT, N2_SPECIFIC_WEIGHT, composition_percent,
                           composition_by_volume, 0, 0, 0, 0, 0);
    }

    void setH2(double composition_percent, double composition_by_volume) {
        h2 = GasProperties(specificHeatH2, H2_MOLECULAR_WEIGHT, H2_SPECIFIC_WEIGHT, composition_percent,
                           composition_by_volume, H2_O2_GENERATED, H2_HEATING_VALUE, H2_HEATING_VALUE_VOLUME,
                           H2_H2O_GENERATED, 0);
    }

    void setC3H8(double composition_percent, double composition_by_volume) {
        c3h8 = GasProperties(specificHeatC3H8, C3H8_MOLECULAR_WEIGHT, C3H8_SPECIFIC_WEIGHT, composition_percent,
                             composition_by_volume, C3H8_O2_GENERATED, C3H8_HEATING_VALUE, C3H8_HEATING_VALUE_VOLUME,
                             C3H8_H2O_GENERATED, C3H8_CO2_GENERATED);
    }

    void setC4H10CnH2n(double composition_percent, double composition_by_volume) {
        c4h10_cnh2n = GasProperties(specificHeatC4H10CnH2n, C4H10_CNH2N_MOLECULAR_WEIGHT, C4H10_CNH2N_SPECIFIC_WEIGHT,
                                    composition_percent, composition_by_volume, C4H10_CNH2N_O2_GENERATED,
                                    C4H10_CNH2N_HEATING_VALUE, C4H10_CNH2N_HEATING_VALUE_VOLUME,
                                    C4H10_CNH2N_H2O_GENERATED, C4H10_CNH2N_CO2_GENERATED);
    }

    void setH2O(double composition_percent, double composition_by_volume) {
        h2o = GasProperties(specificHeatH2O, H2O_MOLECULAR_WEIGHT, H2O_SPECIFIC_WEIGHT, composition_percent,
                            composition_by_volume, 0, 0, 0, H2O_H2O_GENERATED, 0);
    }

    void setCO(double composition_percent, double composition_by_volume) {
        co = GasProperties(specificHeatCO, CO_MOLECULAR_WEIGHT, CO_SPECIFIC_WEIGHT, composition_percent,
                           composition_by_volume, CO_O2_GENERATED, CO_HEATING_VALUE, CO_HEATING_VALUE_VOLUME, 0,
                           CO_CO2_GENERATED);
    }

    void setCO2(double composition_percent, double composition_by_volume) {
        co2 = GasProperties(specificHeatCO2, CO2_MOLECULAR_WEIGHT, CO2_SPECIFIC_WEIGHT, composition_percent,
                            composition_by_volume, 0, 0, 0, 0, CO2_CO2_GENERATED);
    }

    void setSO2(double composition_percent, double composition_by_volume) {
        so2 = GasProperties(specificHeatSO2, SO2_MOLECULAR_WEIGHT, SO2_SPECIFIC_WEIGHT, composition_percent,
                            composition_by_volume, 0, 0, 0, 0, 0);
    }

    void setO2(double composition_percent, double composition_by_volume) {
        o2 = GasProperties(specificHeatO2, O2_MOLECULAR_WEIGHT, O2_SPECIFIC_WEIGHT, composition_percent,
                           composition_by_volume, O2_O2_GENERATED, 0, 0, 0, 0);
    }

    void                 setTotalCompositionWeight();
    void                 setHeatingValue();
    void                 setHeatingValueVolume();
    void                 setSpecificGravity();
    void                 setStoichometricAir();
    GasFlueGasComponents getMassFlueGasComponents(double excess_air);
};
}; // namespace gas_composition