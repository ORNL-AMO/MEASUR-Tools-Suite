/**
 * @file
 * @brief Implementations of Estimate Method of a compressed air system
 *
 * @author Omer Aziz
 * @bug No known bugs.
 *
 */

#ifndef TOOLS_SUITE_ESTIMATEMETHOD_H
#define TOOLS_SUITE_ESTIMATEMETHOD_H

class EstimateMethod {
public:
    struct Output {
        Output(const double annualConsumption) : annualConsumption(annualConsumption)
        {}

        const double annualConsumption;
    };

    /**
     * Constructor for EstimateMethod - The estimate method estimates the air loss by using visual and audible clues.
    * @param operatingTime double, operating time of the system per year - hours
    * @param leakRateEstimate double, estimated leak rate (determined by visual and audible clues)
     */
    EstimateMethod(const double operatingTime, const double leakRateEstimate)
            : operatingTime(operatingTime), leakRateEstimate(leakRateEstimate)
    {}

    /**
     * @return EstimateMethod::Output, annual consumption
     */
    Output calculate() {
        //return {flowRate, (flowRate * operatingTime * numberOfUnits * 60) / 1000 };
        //return {(leakRateEstimate * operatingTime * 60) / 1000};
        EstimateMethod::Output output((leakRateEstimate * operatingTime * 60) / 1000);
        return output;
    }

private:
    double operatingTime, leakRateEstimate;
};

#endif
