/**
 * @file
 * @brief Implementations of Orifice Method of a compressed air system
 *
 * @author Omer Aziz
 * @bug No known bugs.
 *
 */

#ifndef TOOLS_SUITE_ORIFICEMETHOD_H
#define TOOLS_SUITE_ORIFICEMETHOD_H

#include <vector>
#include <cmath>
#include <stdexcept>
#include <functional>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class OrificeMethod {
public:
    struct Output {
        Output(const double standardDensity, const double sonicDensity, const double leakVelocity, const double leakRateLBMmin,
               const double leakRateScfm, const double leakRateEstimate, const double annualConsumption)
                : standardDensity(standardDensity), sonicDensity(sonicDensity), leakVelocity(leakVelocity),
                  leakRateLBMmin(leakRateLBMmin), leakRateScfm(leakRateScfm), leakRateEstimate(leakRateEstimate),
                  annualConsumption(annualConsumption)
        {}

        const double standardDensity, sonicDensity, leakVelocity, leakRateLBMmin, leakRateScfm, leakRateEstimate, annualConsumption;
    };

    /**
     * Constructor for OrificeMethod - The orifice method estimates the air loss by using the pressure and diameter of the orifice
    * @param operatingTime double, operating time of the system per year - hours
    * @param airTemp double, compressor air temperature (usually between 200 and 300 degrees F)
    * @param atmPressure double, atmospheric temperature (standard pressure is 14.7 psia)
    * @param dischargeCoef double, discharge coefficient used to capture the effect of the shape of the outlet on air loss
    * @param parameter double, diameter of the orifice in inches
    * @param supplyPressure double, supply pressure to the orifice in psi
    * @param numOrifices int, number of orifices
     */
    OrificeMethod(const double operatingTime, const double airTemp, const double atmPressure, const double dischargeCoef,
                  const double diameter, const double supplyPressure, const int numOrifices)
            : operatingTime(operatingTime), airTemp(airTemp), atmPressure(atmPressure), dischargeCoef(dischargeCoef), diameter(diameter),
              supplyPressure(supplyPressure), numOrifices(numOrifices)
    {}

    /**
     * @return OrificeMethod::Output, standard density, sonic density, leak velocity, leak rate LBMmin, leak rate Scfm, leak rate estimate, annual consumption
     */
    Output calculate() {
        const double standardDensity = (atmPressure + supplyPressure) * (144 / (53.34 * airTemp));
        const double sonicDensity = std::pow(standardDensity * (2 / (1.4 + 1)), 1/(1.4 - 1));
        const double leakVelocity = std::pow(((2 * 1.4) / (1.4 + 1)) * 53.34 * airTemp * 32.2, 0.5);
        const double leakRateLBMmin = sonicDensity * (diameter * diameter) * (M_PI/(4 * 144)) * leakVelocity * 60 * dischargeCoef;
        const double leakRateScfm = leakRateLBMmin / standardDensity;
        const double leakRateEstimate = leakRateScfm * numOrifices;
        const double annualConsumption = (operatingTime * leakRateEstimate * 60) / 1000;
        OrificeMethod::Output output(standardDensity, sonicDensity, leakVelocity, leakRateLBMmin, leakRateScfm, leakRateEstimate, annualConsumption);

        return output;
    }

private:
    double operatingTime, airTemp, atmPressure, dischargeCoef, diameter, supplyPressure;
    int numOrifices;

};

#endif
