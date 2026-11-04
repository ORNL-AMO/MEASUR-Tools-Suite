/**
 * @file pchip.h
 * @brief Shape-preserving piecewise cubic Hermite interpolation without extrapolation.
 */
#pragma once

#include <span>
#include <vector>

/** @brief Reusable interpolation of finite, strictly increasing reference coordinates. */
namespace pchip {

/** @brief Inclusive bounds in the caller's independent-coordinate unit; NaNs mean unavailable. */
struct Range {
    double minimum; ///< Lower independent coordinate, in caller-defined units.
    double maximum; ///< Upper independent coordinate, in caller-defined units.
};

/** @brief Immutable interpolation table; coordinates retain their caller-defined units. */
class Interpolator {
  public:
    /**
     * @brief Copies reference points and computes SciPy-compatible PCHIP tangents.
     * @param x Independent coordinates, in a consistent caller-defined unit.
     * @param y Dependent coordinates, in a consistent caller-defined unit.
     * @throws std::invalid_argument Unless lengths match, at least two finite points exist,
     * x is strictly increasing, and interval widths and slopes are finite.
     */
    Interpolator(std::span<const double> x, std::span<const double> y);

    /**
     * @brief Interpolates a coordinate without extrapolating.
     * @param x Independent coordinate in the reference x unit.
     * @return Value in the reference y unit; NaN for nonfinite or out-of-range x.
     */
    double evaluate(double x) const;

    /** @return Inclusive lower independent coordinate, in the reference x unit. */
    double minimum() const;
    /** @return Inclusive upper independent coordinate, in the reference x unit. */
    double maximum() const;

  private:
    std::vector<double> x_;
    std::vector<double> y_;
    std::vector<double> tangents_;
};

} // namespace pchip
