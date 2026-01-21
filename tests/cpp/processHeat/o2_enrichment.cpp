#include "processHeat/o2_enrichment.h"

#include "catch.hpp"

using namespace Catch;
using namespace o2_enrichment;

TEST_CASE("Calculate o2 enrichment", "[Process Heat][O2Enrichment]") {
    auto o2Enrichment = calculateO2Enrichment(21, 100, 1800, 1900, 5, 1, 900, 80, 10);
    CHECK(o2Enrichment.available_heat == Approx(61.97));
    CHECK(o2Enrichment.available_heat_enriched == Approx(74.2210855231));
    CHECK(o2Enrichment.fuel_savings_enriched == Approx(16.5058213035));
    CHECK(o2Enrichment.fuel_consumption_enriched == Approx(8.3494178697));
}

TEST_CASE("Calculate o2 enrichment 2", "[Process Heat][O2Enrichment]") {
    auto o2Enrichment = calculateO2Enrichment(21, 100, 2200, 2300, 5, 1, 900, 80, 10);
    CHECK(o2Enrichment.available_heat == Approx(49.7183629149));
    CHECK(o2Enrichment.available_heat_enriched == Approx(69.9474376972));
    CHECK(o2Enrichment.fuel_savings_enriched == Approx(28.9203942964));
    CHECK(o2Enrichment.fuel_consumption_enriched == Approx(7.1079605704));
}

TEST_CASE("Calculate o2 enrichment 3", "[Process Heat][O2Enrichment]") {
    auto o2Enrichment = calculateO2Enrichment(21, 100, 2200, 2300, 8, 3, 1100, 110, 10);
    CHECK(o2Enrichment.available_heat == Approx(49.1204784776));
    CHECK(o2Enrichment.available_heat_enriched == Approx(66.3723712295));
    CHECK(o2Enrichment.fuel_savings_enriched == Approx(25.9925816002));
    CHECK(o2Enrichment.fuel_consumption_enriched == Approx(7.40074184));
}
