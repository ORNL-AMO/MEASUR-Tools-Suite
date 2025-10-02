/**
 * @file Data structure for Compressors default data
 *
 * @author Omer Aziz (omerb)
 *
 */

#ifndef MEASUR_TOOLS_SUITE_COMPRESSORSDATA_H
#define MEASUR_TOOLS_SUITE_COMPRESSORSDATA_H

#include <string>

class CompressorsData {
public:
    /**
     * @brief Constructs a compressor's data record with specified parameters.
     * @details Constructs a compressor's data with the provided parameters, with an data ID of 0.
     * @param[in] id_comp_lib Library's compressor id as integer @unit{\unitless}.
     * @param[in] id_comp_type compressor type as integer @unit{\unitless}.
     * @param[in] model compressor model @unit{\unitless}.
     * @param[in] hp compressor horsepower @unit{\watt}.
     * @param[in] rated_capacity compressor rated capacity @unit{\cubicfeet\minute}.
     * @param[in] rated_pressure compressor rated pressure @unit{\pounds\squareinch}.
     * @param[in] max_fll_flow_pressure compressor max full flow pressure @unit{\pounds\squareinch}.
     * @param[in] id_control_type compressor control type as integer @unit{\unitless}.
     * @param[in] unload_point compressor unload point @unit{\pounds\squareinch}.
     * @param[in] min_ul_sump_pressure compressor min unload sump pressure @unit{\pounds\squareinch}.
     * @param[in] blowdown_time compressor blowdown time @unit{\minute}.
     * @param[in] unload_steps compressor unload steps @unit{\percentage}.
     * @param[in] modulating_press_range compressor modulating pressure range @unit{\pounds\squareinch}.
     * @param[in] power_fl_bhp compressor power fl bhp @unit{\kW}.
     * @param[in] tot_package_input_power compressor total package input power @unit{\kW}.
     * @param[in] spec_package_power compressor spec package power @unit{\kW}.
     * @param[in] no_load_power_fm compressor no load power fm @unit{\kW}.
     * @param[in] no_load_power_ul compressor no load power ul @unit{\kW}.
     * @param[in] max_surge_pressure compressor max surge pressure @unit{\pounds\squareinch}.
     * @param[in] max_press_surge_flow compressor max press surge flow @unit{\pounds\squareinch}.
     * @param[in] min_stonewall_pressure compressor min stonewall pressure @unit{\pounds\squareinch}.
     * @param[in] min_press_stonewall_flow compressor min press stonewall flow @unit{\pounds\squareinch}.
     * @param[in] design_surge_flow compressor design surge flow @unit{\pounds\squareinch}.
     * @param[in] design_in_temp compressor design in temp @unit{\degreeFahrenheit}.
     * @param[in] design_in_pressure compressor design input pressure @unit{\pounds\squareinch}.
     * @param[in] amps_fl Total exterior amps fl @unit{\amps}.
     * @param[in] eff_fl Total exterior eff fl @unit{\percentage}.
     */
    CompressorsData(int id_comp_type, std::string model, double hp,
                    double rated_capacity, double rated_pressure, double max_fll_flow_pressure, int id_control_type,
                    double unload_point, double min_ul_sump_pressure, double blowdown_time, double unload_steps,
                    double modulating_press_range, double power_fl_bhp, double tot_package_input_power,
                    double spec_package_power, double no_load_power_fm, double no_load_power_ul,
                    double max_surge_pressure, double max_press_surge_flow, double min_stonewall_pressure,
                    double min_press_stonewall_flow, double design_surge_flow, double design_in_temp,
                    double design_in_pressure, double amps_fl, double eff_fl) :
                    id_comp_type_(id_comp_type), model_(std::move(model)), hp_(hp),
                    rated_capacity_(rated_capacity), rated_pressure_(rated_pressure), max_fll_flow_pressure_(max_fll_flow_pressure), id_control_type_(id_control_type),
                    unload_point_(unload_point), min_ul_sump_pressure_(min_ul_sump_pressure), blowdown_time_(blowdown_time), unload_steps_(unload_steps),
                    modulating_press_range_(modulating_press_range), power_fl_bhp_(power_fl_bhp), tot_package_input_power_(tot_package_input_power),
                    spec_package_power_(spec_package_power), no_load_power_fm_(no_load_power_fm), no_load_power_ul_(no_load_power_ul),
                    max_surge_pressure_(max_surge_pressure), max_press_surge_flow_(max_press_surge_flow), min_stonewall_pressure_(min_stonewall_pressure),
                    min_press_stonewall_flow_(min_press_stonewall_flow), design_surge_flow_(design_surge_flow), design_in_temp_(design_in_temp),
                    design_in_pressure_(design_in_pressure), amps_fl_(amps_fl), eff_fl_(eff_fl) { this->id_ = 0;}

    /**
     * @brief Sequential ID of the compressors default data.
     * @details Used for default data initialization by adding a sequential data ID.
     * @param[in] id Sequential ID of the compressors default data.
    */
    void setID(int id) { this->id_ = id; }

    /**
     * @brief Gets the data sequential ID of the compressors default data.
     * @return Sequential ID of the compressors default data.
    */
    int ID() const { return this->id_; }

    /**
     * @brief Gets the ID Comp Type for the compressor as integer.
     * @return IDCompType for the compressor as integer.
    */
    int idCompType() const { return this->id_comp_type_; }

    /**
     * @brief Gets the model of the compressor.
     * @return Model of the compressor.
     */
    std::string model() const { return this->model_; }

    /**
     * @brief Gets the hp for the compressor.
     * @return HP for the compressor.
    */
    double hp() const { return this->hp_; }

    /**
     * @brief Gets the Rated Capacity for the compressor.
     * @return RatedCapacity for the compressor.
    */
    double ratedCapacity() const { return this->rated_capacity_; }

    /**
     * @brief Gets the Rated Pressure for the compressor.
     * @return RatedPressure for the compressor.
    */
    double ratedPressure() const { return this->rated_pressure_; }

    /**
     * @brief Gets the Max Full Flow Pressure for the compressor.
     * @return MaxFullFlowPressure for the compressor.
    */
    double maxFullFlowPressure() const { return this->max_fll_flow_pressure_; }

    /**
     * @brief Gets the ID Control Type for the compressor.
     * @return IDControlType for the compressor.
    */
    int idControlType() const { return this->id_control_type_; }

    /**
     * @brief Gets the Unload Point for the compressor.
     * @return UnloadPoint for the compressor.
    */
    double unloadPoint() const { return this->unload_point_; }

    /**
     * @brief Gets the Min UL Sump Pressure for the compressor.
     * @return MinULSumpPressure for the compressor.
    */
    double minULSumpPressure() const { return this->min_ul_sump_pressure_; }

    /**
     * @brief Gets the Blowdown Time for the compressor.
     * @return BlowdownTime for the compressor.
    */
    double blowdownTime() const { return this->blowdown_time_; }

    /**
     * @brief Gets the Unload Steps for the compressor.
     * @return UnloadSteps for the compressor.
    */
    double unloadSteps() const { return this->unload_steps_; }

    /**
     * @brief Gets the Modulating Press Range for the compressor.
     * @return ModulatingPressRange for the compressor.
    */
    double modulatingPressRange() const { return this->modulating_press_range_; }

    /**
     * @brief Gets the Power FL BHP for the compressor.
     * @return PowerFLBHP for the compressor.
    */
    double powerFLBHP() const { return this->power_fl_bhp_; }

    /**
     * @brief Gets the Total  Package Input Power for the compressor.
     * @return TotPackageInputPower for the compressor.
    */
    double totPackageInputPower() const { return this->tot_package_input_power_; }

    /**
     * @brief Gets the Spec Package Power for the compressor.
     * @return SpecPackagePower for the compressor.
    */
    double specPackagePower() const { return this->spec_package_power_; }

    /**
     * @brief Gets the No Load Power FM for the compressor.
     * @return NoLoadPowerFM for the compressor.
    */
    double noLoadPowerFM() const { return this->no_load_power_fm_; }

    /**
     * @brief Gets the No Load Power UL for the compressor.
     * @return NoLoadPowerUL for the compressor.
    */
    double noLoadPowerUL() const { return this->no_load_power_ul_; }

    /**
     * @brief Gets the Max Surge Pressure for the compressor.
     * @return MaxSurgePressure for the compressor.
    */
    double maxSurgePressure() const { return this->max_surge_pressure_; }

    /**
     * @brief Gets the Max Press Surge Flow for the compressor.
     * @return MaxPressSurgeFlow for the compressor.
    */
    double maxPressSurgeFlow() const { return this->max_press_surge_flow_; }

    /**
     * @brief Gets the Min Stonewall Pressure for the compressor.
     * @return MinStonewallPressure for the compressor.
    */
    double minStonewallPressure() const { return this->min_stonewall_pressure_; }

    /**
     * @brief Gets the Min Press Stonewall Flow for the compressor.
     * @return MinPressStonewallFlow for the compressor.
    */
    double minPressStonewallFlow() const { return this->min_press_stonewall_flow_; }

    /**
     * @brief Gets the Design Surge Flow for the compressor.
     * @return DesignSurgeFlow for the compressor.
    */
    double designSurgeFlow() const { return this->design_surge_flow_; }

    /**
     * @brief Gets the Design In Temp for the compressor.
     * @return DesignInTemp for the compressor.
    */
    double designInTemp() const { return this->design_in_temp_; }

    /**
     * @brief Gets the Design In Pressure for the compressor.
     * @return DesignInPressure for the compressor.
    */
    double designInPressure() const { return this->design_in_pressure_; }

    /**
     * @brief Gets the Amps FL for the compressor.
     * @return AmpsFL for the compressor.
    */
    double ampsFL() const { return this->amps_fl_; }

    /**
     * @brief Gets the Eff FL for the compressor.
     * @return EffFL for the compressor.
    */
    double effFL() const { return this->eff_fl_; }

private:
    int id_;

    int id_comp_type_;
    std::string model_;
    double hp_;
    double rated_capacity_;
    double rated_pressure_;
    double max_fll_flow_pressure_;
    int id_control_type_;
    double unload_point_;
    double min_ul_sump_pressure_;
    double blowdown_time_;
    double unload_steps_;
    double modulating_press_range_;
    double power_fl_bhp_;
    double tot_package_input_power_;
    double spec_package_power_;
    double no_load_power_fm_;
    double no_load_power_ul_;
    double max_surge_pressure_;
    double max_press_surge_flow_;
    double min_stonewall_pressure_;
    double min_press_stonewall_flow_;
    double design_surge_flow_;
    double design_in_temp_;
    double design_in_pressure_;
    double amps_fl_;
    double eff_fl_;

    friend class DefaultData;
};

#endif //MEASUR_TOOLS_SUITE_COMPRESSORSDATA_H
