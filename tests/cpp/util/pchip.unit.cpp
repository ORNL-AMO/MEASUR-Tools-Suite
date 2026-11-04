#include "util/pchip.h"

#include <algorithm>
#include <cmath>
#include <limits>
#include <stdexcept>

#include "catch.hpp"
#include "../../fixtures/pump_efficiency_hi_2020_reference.h"

namespace {
template <std::size_t N, std::size_t M>
void checkReference(const double (&x)[N], const double (&y)[N], const double (&samples)[M][2]) {
    const pchip::Interpolator curve(x, y);
    for (const auto& sample : samples) {
        CAPTURE(sample[0], sample[1]);
        CHECK(curve.evaluate(sample[0]) == Catch::Approx(sample[1]).epsilon(1e-13).margin(1e-13));
    }
    for (std::size_t i = 0; i < N; ++i) {
        CHECK(curve.evaluate(x[i]) == y[i]);
    }
    for (std::size_t i = 0; i + 1 < N; ++i) {
        for (int j = 0; j <= 100; ++j) {
            const double value = curve.evaluate(x[i] + (x[i + 1] - x[i]) * j / 100.0);
            CHECK(value >= std::min(y[i], y[i + 1]) - 1e-12);
            CHECK(value <= std::max(y[i], y[i + 1]) + 1e-12);
        }
    }
    CHECK(std::isnan(curve.evaluate(std::nextafter(x[0], -INFINITY))));
    CHECK(std::isnan(curve.evaluate(std::nextafter(x[N - 1], INFINITY))));
    CHECK(std::isnan(curve.evaluate(INFINITY)));
    CHECK(std::isnan(curve.evaluate(-INFINITY)));
    CHECK(std::isnan(curve.evaluate(NAN)));
}
} // namespace

TEST_CASE("PCHIP matches independent SciPy goldens and preserves interval shape", "[pchip]") {
    using namespace hi2020_reference;
    checkReference(utility0_x, utility0_y, utility0_samples);
    checkReference(utility1_x, utility1_y, utility1_samples);
    checkReference(utility2_x, utility2_y, utility2_samples);
    checkReference(utility3_x, utility3_y, utility3_samples);
    checkReference(utility4_x, utility4_y, utility4_samples);
}

TEST_CASE("PCHIP rejects malformed reference data and owns its coordinates", "[pchip]") {
    const double x[] = {0, 1, 3};
    const double y[] = {0, 2, 4};
    const double duplicate[] = {0, 1, 1};
    const double descending[] = {0, 3, 1};
    const double nonfinite[] = {0, NAN, 3};
    const double overflow[] = {-std::numeric_limits<double>::max(), 0, std::numeric_limits<double>::max()};
    CHECK_THROWS_AS(pchip::Interpolator({}, {}), std::invalid_argument);
    CHECK_THROWS_AS(pchip::Interpolator(std::span(x, 1), std::span(y, 1)), std::invalid_argument);
    CHECK_THROWS_AS(pchip::Interpolator(std::span(x, 2), y), std::invalid_argument);
    CHECK_THROWS_AS(pchip::Interpolator(duplicate, y), std::invalid_argument);
    CHECK_THROWS_AS(pchip::Interpolator(descending, y), std::invalid_argument);
    CHECK_THROWS_AS(pchip::Interpolator(nonfinite, y), std::invalid_argument);
    CHECK_THROWS_AS(pchip::Interpolator(x, nonfinite), std::invalid_argument);
    CHECK_THROWS_AS(pchip::Interpolator(x, overflow), std::invalid_argument);
    double mutable_y[] = {0, 2, 4};
    const pchip::Interpolator owned(x, mutable_y);
    mutable_y[1] = 100;
    CHECK(owned.evaluate(1) == 2);
}
