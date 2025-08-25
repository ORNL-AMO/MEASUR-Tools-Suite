/**
 * @file wall_losses.h
 * @authors Gina Accawi, Liam White
 * @ingroup losses
 * @brief Contains the WallLosses class for calculating wall heat losses (convective and radiative).
 */
#pragma once

#include <string>

/**
 * @class WallLosses
 * @ingroup losses
 * @brief A class for calculating wall heat losses (convective and radiative).
 */
class WallLosses {
  public:
    /**
     * @brief Default constructor.
     * @details Constructs a wall with an ID of 0 and surface description of "Unknown".
     */
    WallLosses() = default;

    /**
     * @brief Constructs a wall with specified parameters for heat loss calculations.
     * @details Constructs a wall with the provided parameters, an ID of 0, and a surface description of "Unknown".
     * @param[in] surface_area Total exterior surface area of the wall @unit{\foot\squared}.
     * @param[in] ambient_temperature Ambient temperature measured on the exterior of the wall @unit{\degreeFahrenheit}.
     * @param[in] surface_temperature Average surface temperature measured on the exterior of the wall
     * @unit{\degreeFahrenheit}.
     * @param[in] wind_speed Average wind speed measured on the exterior of the wall @unit{\mile\per\hour}.
     * @param[in] surface_emissivity Surface emissivity of the wall @unit{\unitless}.
     * @param[in] shape_factor The surface shape/orientation factor used in heat loss calculations @unit{\unitless}.
     * @param[in] correction_factor Correction factor for the wall heat loss calculations @unit{\unitless}.
     */
    WallLosses(double surface_area, double ambient_temperature, double surface_temperature, double wind_speed,
               double surface_emissivity, double shape_factor, double correction_factor)
        : surface_area_(surface_area), ambient_temperature_(ambient_temperature),
          surface_temperature_(surface_temperature), wind_speed_(wind_speed), surface_emissivity_(surface_emissivity),
          shape_factor_(shape_factor), correction_factor_(correction_factor) {}

    /**
     * @brief Gets the ID of the wall.
     * @return ID of the wall.
     */
    int ID() const { return this->id_; }

    /**
     * @brief Sets the ID of the wall.
     * @details Used for default data initialization.
     * @param[in] id ID to set for the wall.
     */
    void setID(int id) { this->id_ = id; }

    /**
     * @brief Gets the description of the wall surface.
     * @return Description of the wall surface.
     */
    std::string surfaceDescription() const { return surface_description_; }

    /**
     * @brief Sets the description of the wall surface.
     * @details Used for default data initialization.
     * @param[in] surface_description Description to set for the wall surface.
     */
    void setSurfaceDescription(std::string surface_description) {
        this->surface_description_ = std::move(surface_description);
    }

    /**
     * @brief Gets the shape factor of the wall surface.
     * @details The shape factor is the surface shape/orientation factor used in heat loss calculations.
     * @return Shape factor of the wall surface @unit{\unitless}.
     */
    double shapeFactor() const { return shape_factor_; }

    /**
     * @brief Sets the shape factor of the wall surface.
     * @details The shape factor is the surface shape/orientation factor used in heat loss calculations. Used for
     * default data initialization.
     * @param[in] shape_factor Shape factor to set for the wall surface @unit{\unitless}.
     */
    void setShapeFactor(double shape_factor) { this->shape_factor_ = shape_factor; }

    /**
     * @brief Calculates the total heat loss from the wall to the ambient (convective + radiative).
     * @details Combines convective and radiative heat loss calculations to provide the total heat loss:
     *
     * @formula{wall-total-heat-loss; Q_\text{total} = Q_\text{conv} + Q_\text{rad}}
     *
     * @b Symbols
     * - @symbol{Q_\text{total}; is the total heat loss} @unit{\btu\per\hour}
     * - @symbol{Q_\text{conv}; is the convective heat loss} @unit{\btu\per\hour}
     *   \eqref{eq:wall-convective-heat-loss}
     * - @symbol{Q_\text{rad}; is the radiative heat loss} @unit{\btu\per\hour}
     *   \eqref{eq:wall-radiative-heat-loss}
     *
     * @return Total heat loss @unit{\btu\per\hour}.
     */
    double totalHeatLoss() const;

    /**
     * @brief Compares two walls for equality.
     * @details Two walls are considered equal if their shape factor, surface description, and ID are the same.
     * @param[in] rhs The wall to compare against.
     * @return True if the walls are equal, false otherwise.
     * @note This is used for testing purposes to verify that the wall data matches expected values.
     */
    bool operator==(const WallLosses& rhs) const {
        return shape_factor_ == rhs.shape_factor_ && surface_description_ == rhs.surface_description_ && id_ == rhs.id_;
    }

  private:
    /**
     * @brief Constructs a wall with specified parameters.
     * @details Constructs a wall with the provided parameters and an ID of 0.
     * @param[in] surface_description Description of the wall surface.
     * @param[in] shape_factor The surface shape/orientation factor used in heat loss calculations @unit{\unitless}.
     */
    WallLosses(std::string surface_description, double shape_factor)
        : surface_description_(std::move(surface_description)), shape_factor_(shape_factor) {}

    /**
     * @brief Computes the convective heat loss from the wall to the ambient.
     * @details Calculates the convective heat loss based on empirical constants and the temperature difference between
     * the surface and ambient, the mean temperature, and the wind speed:
     *
     * @formula{wall-convective-heat-loss; Q_\text{conv} = \left( \phi_\text{shape} \cdot \phi_\text{duty} \cdot
     * \phi_{\Delta T} \cdot \phi_{\bar{T}} \cdot \phi_\text{wind} \right) A \cdot \Delta T}
     *
     * @b Factors
     * - @symbol{\phi_\text{shape}; is the shape factor} @unit{\unitless}
     * - @symbol{\phi_\text{duty}; is the duty factor} @unit{\unitless}
     *   @formula{wall-duty-factor; \phi_\text{duty}=\left(\frac{1}{24}\right)^{0.2}} (here, 24 = hours per day)
     * - @symbol{\phi_{\Delta T}; is the temperature difference factor} @unit{\unitless}
     *   @formula{wall-delta-temp-factor; \phi_{\Delta T}=\left(\Delta T\right)^{0.266}}
     * - @symbol{\phi_{\bar{T}}; is the mean temperature factor} @unit{\unitless}
     *   @formula{wall-mean-temp-factor; \phi_{\bar{T}}=\left(\frac{1}{\bar{T}}\right)^{0.181}}
     * - @symbol{\phi_\text{wind}; is the wind factor} @unit{\unitless}
     *   @formula{wall-wind-factor; \phi_\text{wind}=\sqrt{1 + \left( 1.277 \cdot V_\text{wind} \right)}}
     *
     * @b Symbols
     * - @symbol{Q_\text{conv}; is the convective heat loss} @unit{\btu\per\hour}
     * - @symbol{A; is the surface area} @unit{\foot\squared}
     * - @symbol{\Delta T; is the temperature difference} @unit{\degreeFahrenheit}
     *   @formula{wall-delta-temp; \Delta T = T_s - T_a}
     * - @symbol{T_s; is the surface temperature} @unit{\degreeFahrenheit}
     * - @symbol{T_a; is the ambient temperature} @unit{\degreeFahrenheit}
     * - @symbol{\bar{T}; is the mean temperature} @unit{\degreeFahrenheit}
     * - @symbol{V_\text{wind}; is the wind speed} @unit{\mile\per\hour}
     *
     * @return Convective heat loss @unit{\btu\per\hour}.
     */
    double convectiveHeatLoss() const;

    /**
     * @brief Calculates the radiative heat loss from the wall to the ambient.
     * @details Calculates the radiative heat loss using the Stefan-Boltzmann law, based on the fourth power of the
     * absolute temperatures of the surface and ambient, the surface area, and the surface emissivity.
     *
     * @formula{wall-radiative-heat-loss; Q_\text{rad} = A \varepsilon \sigma (T_s^4 - T_a^4)}
     *
     * @b Symbols
     * - @symbol{Q_\text{rad}; is the radiative heat loss} @unit{\btu\per\hour}
     * - @symbol{A; is the surface area} @unit{\foot\squared}
     * - @symbol{\varepsilon; is the surface emissivity} @unit{\unitless}
     * - @symbol{\sigma; is the Stefan-Boltzmann constant} @unit{\btu\per\hour\foot\squared\degreeRankine\tothe{4}}
     * - @symbol{T_s; is the surface temperature} @unit{\degreeRankine}
     * - @symbol{T_a; is the ambient temperature} @unit{\degreeRankine}
     *
     * @return Radiative heat loss @unit{\btu\per\hour}.
     */
    double radiativeHeatLoss() const;

    int         id_                  = 0;         ///< Unique identifier for the wall.
    std::string surface_description_ = "Unknown"; ///< Description of the wall surface.

    double surface_area_;        ///< Total exterior surface area of the wall @unit{\foot\squared}.
    double ambient_temperature_; ///< Ambient temperature measured on the exterior of the wall @unit{\degreeFahrenheit}.
    double surface_temperature_; ///< Average surface temperature measured on the exterior of the wall.
                                 ///< @unit{\degreeFahrenheit}.
    double wind_speed_;          ///< Average wind speed measured on the exterior of the wall @unit{\mile\per\hour}.
    double surface_emissivity_;  ///< Surface emissivity of the wall @unit{\unitless}.
    double shape_factor_; ///< The surface shape/orientation factor used in heat loss calculations @unit{\unitless}.
    double correction_factor_; ///< Correction factor for the wall heat loss calculations @unit{\unitless}.

    friend class DefaultData; ///< Friend class for testing and default data initialization.
};
