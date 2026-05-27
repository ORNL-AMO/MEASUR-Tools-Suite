#include "catch.hpp"

#include "compressedAir/pneumatic_valve.h"

using namespace Catch;
using namespace pneumatic_valve;

TEST_CASE("PneumaticValve - Flow Rate (Cv = 1)", "[CompressedAir][PneumaticValve][FlowRate]") {
    CHECK(calculateFlowRate({100, 70}).flow_rate == Approx(49.097320446));
    CHECK(calculateFlowRate({120, 70}).flow_rate == Approx(67.00921112));
    CHECK(calculateFlowRate({120, 90}).flow_rate == Approx(54.56862079));
}

TEST_CASE("PneumaticValve - Flow Coefficient (Cv)", "[CompressedAir][PneumaticValve][Cv]") {
    CHECK(calculateCv({80, 75, 55}).flow_coefficient == Approx(2.873684832));
    CHECK(calculateCv({90, 75, 55}).flow_coefficient == Approx(1.608060504));
    CHECK(calculateCv({90, 85, 55}).flow_coefficient == Approx(2.7044936151));
    CHECK(calculateCv({90, 85, 95}).flow_coefficient == Approx(4.671398062));
}
