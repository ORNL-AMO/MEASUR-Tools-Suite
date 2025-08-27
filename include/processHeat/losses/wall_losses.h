/**
 * @file wall_losses.h
 * @authors Gina Accawi, Liam White
 * @ingroup heat_loss_calculators
 * @brief Contains the WallLosses class for calculating wall heat losses (convective and radiative).
 */
#pragma once

#include <string>

/**
 * @class WallLosses
 * @ingroup heat_loss_calculators
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
     * @param[in] surface_area Total exterior surface area of the wall @unitb{\foot\squared}.
     * @param[in] ambient_temperature Ambient temperature measured on the exterior of the wall
     * @unitb{\degreeFahrenheit}.
     * @param[in] surface_temperature Average surface temperature measured on the exterior of the wall
     * @unitb{\degreeFahrenheit}.
     * @param[in] wind_speed Average wind speed measured on the exterior of the wall @unitb{\mile\per\hour}.
     * @param[in] surface_emissivity Surface emissivity of the wall @unitb{\unitless}.
     * @param[in] shape_factor The surface shape/orientation factor used in heat loss calculations @unitb{\unitless}.
     * @param[in] correction_factor Correction factor for the wall heat loss calculations @unitb{\unitless}.
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
    int id() const { return this->id_; }

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
     * @return Shape factor of the wall surface @unitb{\unitless}.
     */
    double shapeFactor() const { return shape_factor_; }

    /**
     * @brief Sets the shape factor of the wall surface.
     * @details The shape factor is the surface shape/orientation factor used in heat loss calculations. Used for
     * default data initialization.
     * @param[in] shape_factor Shape factor to set for the wall surface @unitb{\unitless}.
     */
    void setShapeFactor(double shape_factor) { this->shape_factor_ = shape_factor; }

    /**
     * @brief Calculates the total heat loss from the wall to the ambient (convective + radiative).
     * @details Combines convective and radiative heat loss calculations to provide the total heat loss:
     *
     * @par Governing equation
     * @formula{wall-total-heat-loss; Q_\text{total} = Q_\text{conv} + Q_\text{rad}}
     *
     * @par Symbols
     * @symtable
     * @symrow{Q_\text{total}; Total heat loss; \btu\per\hour}
     * @symrow{Q_\text{conv}; Convective heat loss; \btu\per\hour}
     * @symrow{Q_\text{rad}; Radiative heat loss ; \btu\per\hour}
     * @endsymtable
     *
     * @see convectiveHeatLoss(), radiativeHeatLoss()
     *
     * @return Total heat loss @unitb{\btu\per\hour}.
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
     * @param[in] shape_factor The surface shape/orientation factor used in heat loss calculations @unitb{\unitless}.
     */
    WallLosses(std::string surface_description, double shape_factor)
        : surface_description_(std::move(surface_description)), shape_factor_(shape_factor) {}

    /**
     * @brief Computes the convective heat loss from the wall to the ambient.
     * @details Calculates the convective heat loss using an empirical correlation that accounts for surface shape,
     * duty factor, temperature difference, mean temperature, and wind speed.
     *
     * @par Governing equation
     * @formula{wall-qconv; Q_\text{conv} = h A \Delta T}
     *
     * @par Convection coefficient
     * @formula{wall-h; h = f_\text{shape} \cdot f_\text{duty} \cdot f_{\Delta T} \cdot f_{\bar{T}} \cdot f_\text{wind}}
     *
     * @par Factors
     * @formula{wall-duty; f_\text{duty} = \left(\frac{1}{24}\right)^{0.2}}
     * @formula{wall-dTfactor; f_{\Delta T} = (\Delta T)^{0.266}}
     * @formula{wall-Tbarfactor; f_{\bar{T}} = \left(\frac{1}{\bar{T}}\right)^{0.181}}
     * @formula{wall-windfactor; f_\text{wind} = \sqrt{1 + 1.277 \cdot V_\text{wind}}}
     *
     * @par Temperature relations
     * @formula{wall-dT; \Delta T = T_s - T_a}
     * @formula{wall-Tbar; \bar{T} = \frac{T_s + T_a}{2}}
     *
     * @par Symbols
     * @symtable
     * @symrow{Q_\text{conv}; Convective heat loss; \btu\per\hour}
     * @symrow{h; Convection coefficient; \btu\per\hour\foot\squared\degreeFahrenheit}
     * @symrow{A; Surface area; \foot\squared}
     * @symrow{\Delta T; Temperature difference between surface and ambient; \degreeFahrenheit}
     * @symrow{f_\text{shape}; Surface shape factor; \unitless}
     * @symrow{f_\text{duty}; Duty factor; \unitless}
     * @symrow{f_{\Delta T}; Temperature difference factor; \unitless}
     * @symrow{f_{\bar{T}}; Mean temperature factor; \unitless}
     * @symrow{f_\text{wind}; Wind factor; \unitless}
     * @symrow{T_s; Surface temperature; \degreeFahrenheit}
     * @symrow{T_a; Ambient temperature; \degreeFahrenheit}
     * @endsymtable
     *
     * @return Convective heat loss @unitb{\btu\per\hour}.
     */
    double convectiveHeatLoss() const;

    /**
     * @brief Calculates the radiative heat loss from the wall to the ambient.
     * @details Calculates the radiative heat loss using the Stefan-Boltzmann law, based on the fourth power of the
     * absolute temperatures of the surface and ambient, the surface area, and the surface emissivity.
     *
     * @par Governing equation
     * @formula{wall-qrad; Q_\text{rad} = \varepsilon \sigma A (T_s^4 - T_a^4)}
     *
     * @par Symbols
     * @symtable
     * @symrow{Q_\text{rad}; Radiative heat loss; \btu\per\hour}
     * @symrow{\sigma; Stefan-Boltzmann constant; \btu\per\hour\foot\squared\degreeRankine\tothe{4}}
     * @symrow{\varepsilon; Surface emissivity; \unitless}
     * @symrow{A; Surface area; \foot\squared}
     * @symrow{T_s; Surface temperature; \degreeRankine}
     * @symrow{T_a; Ambient temperature; \degreeRankine}
     * @endsymtable
     *
     * @return Radiative heat loss @unitb{\btu\per\hour}.
     */
    double radiativeHeatLoss() const;

    int         id_                  = 0;         ///< Unique identifier for the wall.
    std::string surface_description_ = "Unknown"; ///< Description of the wall surface.

    double surface_area_; ///< Total exterior surface area of the wall @unitb{\foot\squared}.
    double
        ambient_temperature_; ///< Ambient temperature measured on the exterior of the wall @unitb{\degreeFahrenheit}.
    double surface_temperature_; ///< Average surface temperature measured on the exterior of the wall.
                                 ///< @unitb{\degreeFahrenheit}.
    double wind_speed_;          ///< Average wind speed measured on the exterior of the wall @unitb{\mile\per\hour}.
    double surface_emissivity_;  ///< Surface emissivity of the wall @unitb{\unitless}.
    double shape_factor_; ///< The surface shape/orientation factor used in heat loss calculations @unitb{\unitless}.
    double correction_factor_; ///< Correction factor for the wall heat loss calculations @unitb{\unitless}.

    friend class DefaultData; ///< Friend class for testing and default data initialization.
};
