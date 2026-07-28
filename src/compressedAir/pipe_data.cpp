#include "compressedAir/pipe_data.h"

namespace pipe_data {

PipeData::PipeData(double one_half, double three_fourths, double one, double one_and_one_fourth,
                   double one_and_one_half, double two, double two_and_one_half, double three,
                   double three_and_one_half, double four, double five, double six, double eight, double ten,
                   double twelve, double fourteen, double sixteen, double eighteen, double twenty,
                   double twenty_four)
    : oneHalf(one_half * 0.0021),
      threeFourths(three_fourths * 0.0037),
      one(one * 0.006),
      oneAndOneFourth(one_and_one_fourth * 0.0104),
      oneAndOneHalf(one_and_one_half * 0.0141),
      two(two * 0.0233),
      twoAndOneHalf(two_and_one_half * 0.0333),
      three(three * 0.0513),
      threeAndOneHalf(three_and_one_half * 0.0687),
      four(four * 0.0884),
      five(five * 0.1389),
      six(six * 0.2006),
      eight(eight * 0.3442),
      ten(ten * 0.5476),
      twelve(twelve * 0.7763),
      fourteen(fourteen * 0.9354),
      sixteen(sixteen * 1.223),
      eighteen(eighteen * 1.555),
      twenty(twenty * 1.926),
      twentyFour(twenty_four * 2.793),
      totalPipeVolume(this->oneHalf + this->threeFourths + this->one + this->oneAndOneFourth +
                      this->oneAndOneHalf + this->two + this->twoAndOneHalf + this->three +
                      this->threeAndOneHalf + this->four + this->five + this->six + this->eight + this->ten +
                      this->twelve + this->fourteen + this->sixteen + this->eighteen + this->twenty +
                      this->twentyFour) {}

PipeData::PipeData(const std::function<double(double)>& velocity_from_area)
    : oneHalf(velocity_from_area(0.3)),
      threeFourths(velocity_from_area(0.53)),
      one(velocity_from_area(0.86)),
      oneAndOneFourth(velocity_from_area(1.5)),
      oneAndOneHalf(velocity_from_area(2.04)),
      two(velocity_from_area(3.36)),
      twoAndOneHalf(velocity_from_area(4.79)),
      three(velocity_from_area(7.39)),
      threeAndOneHalf(velocity_from_area(9.89)),
      four(velocity_from_area(12.73)),
      five(velocity_from_area(20)),
      six(velocity_from_area(28.89)),
      eight(velocity_from_area(50.02)),
      ten(velocity_from_area(78.85)),
      twelve(velocity_from_area(111.9)),
      fourteen(velocity_from_area(135.3)),
      sixteen(velocity_from_area(176.7)),
      eighteen(velocity_from_area(224)),
      twenty(velocity_from_area(278)),
      twentyFour(velocity_from_area(402.10)) {}

} // namespace pipe_data
