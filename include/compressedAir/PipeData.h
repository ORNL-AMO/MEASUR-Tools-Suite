/**
 * @file
 * @brief Implementations of Pipe Data of a compressed air system
 *
 * @author Omer Aziz
 * @bug No known bugs.
 *
 */

#ifndef TOOLS_SUITE_PIPEDATA_H
#define TOOLS_SUITE_PIPEDATA_H

#include <vector>
#include <cmath>
#include <stdexcept>
#include <functional>

struct PipeData {
    /**
     * Constructor for PipeData - This is used to hold all the pipe lengths in the system
     * All params are the english spelling of their numeric equivalents, i.e. one half == 0.5, twoAndOneHalf == 2.5, etc.
     * Used in AirSystemCapacity input and output.
     */
    PipeData(const double oneHalf, const double threeFourths, const double one, const double oneAndOneFourth,
             const double oneAndOneHalf, const double two, const double twoAndOneHalf, const double three,
             const double threeAndOneHalf, const double four, const double five, const double six,
             const double eight,
             const double ten, const double twelve, const double fourteen, const double sixteen,
             const double eighteen,
             const double twenty, const double twentyFour)
            : oneHalf(oneHalf * 0.0021), threeFourths(threeFourths * 0.0037), one(one * 0.006),
              oneAndOneFourth(oneAndOneFourth * 0.0104), oneAndOneHalf(oneAndOneHalf * 0.0141),
              two(two * 0.0233), twoAndOneHalf(twoAndOneHalf * 0.0333), three(three * 0.0513),
              threeAndOneHalf(threeAndOneHalf * 0.0687), four(four * 0.0884), five(five * 0.1389),
              six(six * 0.2006), eight(eight * 0.3442), ten(ten * 0.5476), twelve(twelve * 0.7763),
              fourteen(fourteen * 0.9354), // **ten and twelve**
              sixteen(sixteen * 1.223), eighteen(eighteen * 1.555), twenty(twenty * 1.926),
              twentyFour(twentyFour * 2.793),
              totalPipeVolume(this->oneHalf + this->threeFourths + this->one + this->oneAndOneFourth
                              + this->oneAndOneHalf + this->two + this->twoAndOneHalf + this->three
                              + this->threeAndOneHalf + this->four + this->five + this->six
                              + this->eight + this->ten + this->twelve + this->fourteen + this->sixteen
                              + this->eighteen + this->twenty + this->twentyFour) {}

    /**
     * Constructor for PipeData - This is used to hold return values for air velocity estimations
     * @param compVel std::function<double (const double)>, compVel is the compressed air velocity function, it
     * calculates pipeline velocity given internal area of the pipe in square feet. An example of usage can be found
     * in AirVelocity::calculateThermalResistance()
     */
    explicit PipeData(std::function<double(const double)> const &compVel)
            : oneHalf(compVel(0.3)), threeFourths(compVel(0.53)), one(compVel(0.86)),
              oneAndOneFourth(compVel(1.5)), oneAndOneHalf(compVel(2.04)),
              two(compVel(3.36)), twoAndOneHalf(compVel(4.79)), three(compVel(7.39)),
              threeAndOneHalf(compVel(9.89)), four(compVel(12.73)), five(compVel(20)),
              six(compVel(28.89)), eight(compVel(50.02)), ten(compVel(78.85)), twelve(compVel(111.9)),
              fourteen(compVel(135.3)), sixteen(compVel(176.7)), eighteen(compVel(224)), twenty(compVel(278)),
              twentyFour(compVel(402.10)) {}

    const double oneHalf, threeFourths, one, oneAndOneFourth, oneAndOneHalf, two;
    const double twoAndOneHalf, three, threeAndOneHalf, four, five, six;
    const double eight, ten, twelve, fourteen, sixteen, eighteen, twenty, twentyFour;
    const double totalPipeVolume = 0;
};

#endif
