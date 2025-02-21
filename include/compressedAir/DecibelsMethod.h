/**
 * @file
 * @brief Implementations of Decibels Method of a compressed air system
 *
 * @author Omer Aziz
 * @bug No known bugs.
 *
 */

#ifndef TOOLS_SUITE_DECIBELSMETHOD_H
#define TOOLS_SUITE_DECIBELSMETHOD_H

class DecibelsMethod {
public:
    struct Output {
        Output(const double leakRateEstimate, const double annualConsumption)
                : leakRateEstimate(leakRateEstimate), annualConsumption(annualConsumption)
        {}

        const double leakRateEstimate, annualConsumption;
    };

    /**
    * Constructor for DecibelsMethod - The decibels method estimates the air loss by using decibel and line pressure measurements
    * @param operatingTime double, operating time of the system per year - hours
    * @param linePressure double,
    * @param decibels double,
    * @param decibelRatingA double,
    * @param pressureA double,
    * @param firstFlowA double,
    * @param secondFlowA double,
    * @param decibelRatingB double,
    * @param pressureB double,
    * @param firstFlowB double,
    * @param secondFlowB double,
    */
    DecibelsMethod(const double operatingTime, const double linePressure, const double decibels,
                   const double decibelRatingA, const double pressureA, const double firstFlowA, const double secondFlowA,
                   const double decibelRatingB, const double pressureB, const double firstFlowB, const double secondFlowB)
            : operatingTime(operatingTime), linePressure(linePressure), decibels(decibels),
              decibelRatingA(decibelRatingA), pressureA(pressureA), firstFlowA(firstFlowA), secondFlowA(secondFlowA),
              decibelRatingB(decibelRatingB), pressureB(pressureB), firstFlowB(firstFlowB), secondFlowB(secondFlowB)
    {}

    /**
	* @return DecibelsMethod::Output, leak rate estimate, annual consumption
	*/
    Output calculate() {
        /*
        double operatingTime;
        double linePressure; // X
        double decibels; // Y
        double decibelRatingA; // Y1
        double pressureA; // X1
        double firstFlowA; // Q11
        double secondFlowA; // Q21
        double decibelRatingB; // Y2
        double pressureB; // X2
        double firstFlowB; // Q12
        double secondFlowB; // Q22
        */

        const double denominator = (pressureB - pressureA) * (decibelRatingB - decibelRatingA);
        const double leakRateEstimate = ((pressureB - linePressure) * (decibelRatingB - decibels)) / denominator * firstFlowA
                                        + ((linePressure - pressureA) * (decibelRatingB - decibels)) / denominator * secondFlowA
                                        + ((pressureB - linePressure) * (decibels - decibelRatingA)) / denominator * firstFlowB
                                        + ((linePressure - pressureA) * (decibels - decibelRatingA)) / denominator * secondFlowB;
        const double annualConsumption = (leakRateEstimate * operatingTime * 60) / 1000;
        DecibelsMethod::Output output(leakRateEstimate, annualConsumption);

        return output;
    }

private:
    double operatingTime;
    double linePressure; // X
    double decibels; // Y
    double decibelRatingA; // Y1
    double pressureA; // X1
    double firstFlowA; // Q11
    double secondFlowA; // Q21
    double decibelRatingB; // Y2
    double pressureB; // X2
    double firstFlowB; // Q12
    double secondFlowB; // Q22
};

#endif
