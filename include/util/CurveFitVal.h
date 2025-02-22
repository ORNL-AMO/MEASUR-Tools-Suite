/**
 * @brief Curve Fit class
 *
 * This contains the prototypes for the Curve Fit Value calculator.
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @author Mark Root (mroot)
 * @bug No known bugs.
 *
 */

#ifndef TOOLS_SUITE_CURVEFITVAL_H
#define TOOLS_SUITE_CURVEFITVAL_H

#include <vector>
#include <exception>
#include <stdexcept>
#include <iostream>
class CurveFitVal
{
public:
    /**
     * Constructor
     * @param xcoord vector of x coordinates as doubles
     * @param ycoord vector of y coordinates as doubles
     * @param pdegree int, degree of polynomial curve
     * @param loadFactor double, load factor - unitless
     */
    CurveFitVal(
        std::vector<double> xcoord,
        std::vector<double> ycoord,
        const std::size_t pdegree,
        const double loadFactor = 0) : pdegree(pdegree),
                                       xcoord(std::move(xcoord)),
                                       ycoord(std::move(ycoord)),
                                       loadFactor(loadFactor)
    {
        if (this->xcoord.size() != this->ycoord.size())
        {
            throw std::runtime_error("X and Y coordinate vectors must be the same size");
        }

        coeff = Fit_Coefficients();
    }

    /**
     * Calculates the curve fit value at required load factor
     * @return double, curve fit value
     */
    double calculate() const;
    double calculate(double) const;

public:
    // coeff public so quadratic equation can be used
    std::vector<double> coeff;

private:
    /**
     * Degree of polynomial curve
     */
    std::size_t pdegree;
    /**
     * x and y coordinates
     */
    std::vector<double> xcoord, ycoord;
    /**
     * load factor (here is the x coordinate, whose corresponding y coordinate is returned.
     */
    double loadFactor;

    /**
     * Array to store the coefficients of the curve.
     */
    std::vector<double> Fit_Coefficients();
};

#endif // TOOLS_SUITE_CURVEFITVAL_H
