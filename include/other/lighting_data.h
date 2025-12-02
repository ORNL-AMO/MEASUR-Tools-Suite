#pragma once

/**
 * @file Data structure for Lighting default data
 *
 * @author Omer Aziz (omerb)
 *
 */

#include <string>

class LightingData {
public:
    /**
     * @brief Constructs a Lighting's data record with specified parameters.
     * @details Constructs a Lighting's data with the provided parameters, with an data ID of 0.
     * @param[in] category lighting system category @unit{\unitless}.
     * @param[in] type lighting system type @unit{\unitless}.
     * @param[in] lamps_per_fixture lighting system lamps per fixture @unit{\unitless}.
     * @param[in] lamp_wattage lighting system lamp wattage @unit{\watt}.
     * @param[in] lamp_output lighting system lamp output @unit{\lumens}.
     * @param[in] lamp_life lighting system lamp life @unit{\hours}.
     * @param[in] lamp_cri lighting system lamp cri @unit{\unitless}.
     * @param[in] coefficient_of_utilization lighting system coefficient of utilization @unit{\percentage}.
     * @param[in] ballast_factor lighting system ballast factor @unit{\unitless}.
     * @param[in] lumen_degradation_factor lighting system lumen degradation factor @unit{\unitless}.
     */
    LightingData(std::string category, std::string type,
                 int lamps_per_fixture, double lamp_wattage, int lamp_output, int lamp_life, int lamp_cri,
                 double coefficient_of_utilization, double ballast_factor, double lumen_degradation_factor) :
                 category_(category), type_(type),
                 lamps_per_fixture_(lamps_per_fixture), lamp_wattage_(lamp_wattage), lamp_output_(lamp_output), lamp_life_(lamp_life), lamp_cri_(lamp_cri),
                 coefficient_of_utilization_(coefficient_of_utilization), ballast_factor_(ballast_factor), lumen_degradation_factor_(lumen_degradation_factor) {}

    /**
     * @brief Sequential ID of the lighting default data.
     * @details Used for default data initialization by adding a sequential data ID.
     * @param[in] id Sequential ID of the lighting default data.
    */
    void setID(int id) { this->id_ = id; }

    /**
     * @brief Gets the data sequential ID of the lighting default data.
     * @return Sequential ID of the lighting default data.
    */
    int ID() const { return this->id_; }

    /**
     * @brief Gets the Category of the lighting.
     * @return category of the lighting.
     */
    std::string category() const { return this->category_; }

    /**
     * @brief Gets the Type of the lighting.
     * @return type of the lighting.
     */
    std::string type() const { return this->type_; }

    /**
     * @brief Gets the Lamps per Fixture of the lighting system.
     * @return lampsPerFixture of the lighting system.
     */
    int lampsPerFixture() const { return this->lamps_per_fixture_; }

    /**
     * @brief Gets the Lamp Wattage of the lighting system.
     * @return lampWattage of the lighting system.
     */
    double lampWattage() const { return this->lamp_wattage_; }

    /**
     * @brief Gets the Lamp Output of the lighting system.
     * @return lampOutput of the lighting system.
     */
    int lampOutput() const { return this->lamp_output_; }

    /**
     * @brief Gets the Lamp Life of the lighting system.
     * @return lampLife of the lighting system.
     */
    int lampLife() const { return this->lamp_life_; }

    /**
     * @brief Gets the Lamp CRI of the lighting system.
     * @return lampCRI of the lighting system.
     */
    int lampCRI() const { return this->lamp_cri_; }

    /**
     * @brief Gets the Coefficient of Utilization of the lighting system.
     * @return coefficientOfUtilization of the lighting system.
     */
    double coefficientOfUtilization() const { return this->coefficient_of_utilization_; }

    /**
     * @brief Gets the Ballast Factor of the lighting system.
     * @return ballastFactor of the lighting system.
     */
    double ballastFactor() const { return this->ballast_factor_; }

    /**
     * @brief Gets the Lumen Degradation Factor of the lighting system.
     * @return lumenDegradationFactor of the lighting system.
     */
    double lumenDegradationFactor() const { return this->lumen_degradation_factor_; }

private:
    int id_;

    std::string category_;
    std::string type_;
    int lamps_per_fixture_;
    double lamp_wattage_;
    int lamp_output_;
    int lamp_life_;
    int lamp_cri_;
    double coefficient_of_utilization_;
    double ballast_factor_;
    double lumen_degradation_factor_;

    friend class DefaultData;
};

