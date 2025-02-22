#include "catch.hpp"
#include "processHeat/losses/LeakageLosses.h"

TEST_CASE( "Calculate Heat Loss for gas leakage", "[Heat Loss]" ) {

    REQUIRE( LeakageLosses(0.1, 3.0, 1600.0, 80.0, 0.8052, 1.02, 1.0).getExfiltratedGasesHeatContent() == Approx( 2850767.0 ) );

}