#include "catch.hpp"

#include "compressedAir/pneumatic_air_requirement.h"

using namespace Catch;
using namespace pneumatic_air_requirement;

// Expected values use physics::kPi / 4.0 (≈ 0.78540) for the bore area factor,
// which is the exact quarter-circle area. Legacy code used 0.785 (a rounded constant),
// so expected values here differ slightly from the pre-refactor test data.

TEST_CASE("PneumaticAirRequirement - Single-Acting Piston", "[CompressedAir][PneumaticAirRequirement][SingleActing]") {
    // vol = (pi/4 * D^2 * L * n) / 1728
    // r_c = (P + 14.7) / 14.7
    // free = vol * r_c

    CHECK(calculateSingleActing({1.5, 6, 100, 60}).volume_air_intake_piston           == Approx(0.36815540));
    CHECK(calculateSingleActing({1.5, 6, 100, 60}).compression_ratio                  == Approx(7.80272109));
    CHECK(calculateSingleActing({1.5, 6, 100, 60}).air_requirement_pneumatic_cylinder  == Approx(2.87261366));

    CHECK(calculateSingleActing({3.5, 6, 100, 60}).volume_air_intake_piston           == Approx(2.00440129));
    CHECK(calculateSingleActing({3.5, 6, 100, 60}).compression_ratio                  == Approx(7.80272109));
    CHECK(calculateSingleActing({3.5, 6, 100, 60}).air_requirement_pneumatic_cylinder  == Approx(15.63978411));

    CHECK(calculateSingleActing({1.5, 9, 100, 60}).volume_air_intake_piston           == Approx(0.55223308));
    CHECK(calculateSingleActing({1.5, 9, 100, 60}).compression_ratio                  == Approx(7.80272109));
    CHECK(calculateSingleActing({1.5, 9, 100, 60}).air_requirement_pneumatic_cylinder  == Approx(4.30892059));

    CHECK(calculateSingleActing({1.5, 6, 140, 90}).volume_air_intake_piston           == Approx(0.55223308));
    CHECK(calculateSingleActing({1.5, 6, 140, 90}).compression_ratio                  == Approx(10.52380952));
    CHECK(calculateSingleActing({1.5, 6, 140, 90}).air_requirement_pneumatic_cylinder  == Approx(5.81159462));
}

TEST_CASE("PneumaticAirRequirement - Double-Acting Piston", "[CompressedAir][PneumaticAirRequirement][DoubleActing]") {
    // vol = (pi/4 * (2*D^2 - dr^2) * L * n) / 1728
    // r_c = (P + 14.7) / 14.7
    // free = vol * r_c

    CHECK(calculateDoubleActing({1.5, 6, 0.375, 100, 60}).volume_air_intake_piston           == Approx(0.71330107));
    CHECK(calculateDoubleActing({1.5, 6, 0.375, 100, 60}).compression_ratio                  == Approx(7.80272109));
    CHECK(calculateDoubleActing({1.5, 6, 0.375, 100, 60}).air_requirement_pneumatic_cylinder  == Approx(5.56568811));

    CHECK(calculateDoubleActing({3.5, 6, 0.375, 100, 60}).volume_air_intake_piston           == Approx(3.98579341));
    CHECK(calculateDoubleActing({3.5, 6, 0.375, 100, 60}).compression_ratio                  == Approx(7.80272109));
    CHECK(calculateDoubleActing({3.5, 6, 0.375, 100, 60}).air_requirement_pneumatic_cylinder  == Approx(31.10003421));

    CHECK(calculateDoubleActing({1.5, 9, 0.375, 100, 60}).volume_air_intake_piston           == Approx(1.06995160));
    CHECK(calculateDoubleActing({1.5, 9, 0.375, 100, 60}).compression_ratio                  == Approx(7.80272109));
    CHECK(calculateDoubleActing({1.5, 9, 0.375, 100, 60}).air_requirement_pneumatic_cylinder  == Approx(8.34853384));

    CHECK(calculateDoubleActing({1.5, 6, 0.575, 100, 60}).volume_air_intake_piston           == Approx(0.68221238906567405));
    CHECK(calculateDoubleActing({1.5, 6, 0.575, 100, 60}).compression_ratio                  == Approx(7.80272109));
    CHECK(calculateDoubleActing({1.5, 6, 0.575, 100, 60}).air_requirement_pneumatic_cylinder  == Approx(5.32311299495461387));

    CHECK(calculateDoubleActing({1.5, 6, 0.575, 140, 90}).volume_air_intake_piston           == Approx(1.02331858));
    CHECK(calculateDoubleActing({1.5, 6, 0.575, 140, 90}).compression_ratio                  == Approx(10.52380952));
    CHECK(calculateDoubleActing({1.5, 6, 0.575, 140, 90}).air_requirement_pneumatic_cylinder  == Approx(10.76921029));
}
