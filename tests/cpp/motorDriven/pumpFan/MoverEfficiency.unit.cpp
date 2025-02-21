#include "catch.hpp"
#include "motorDriven/pumpFan/MoverEfficiency.h"
#include <unordered_map>
#include <array>

TEST_CASE( "Pump efficiency", "[Pump][pump efficiency]" ) {
	CHECK(MoverEfficiency(0.5, 1000, 125, 125).calculate() == Approx(0.126218641));
	CHECK(MoverEfficiency(1.5, 1000, 125, 125).calculate() == Approx(0.3786559229));
	CHECK(MoverEfficiency(3.5, 1000, 125, 125).calculate() == Approx(0.8835304869));
	CHECK(MoverEfficiency(9.5, 1000, 125, 125).calculate() == Approx(2.3981541786));
	CHECK(MoverEfficiency(20.5, 1000, 125, 125).calculate() == Approx(5.1749642801));
	CHECK(MoverEfficiency(50.5, 1000, 125, 125).calculate() == Approx(12.7480827388));

	CHECK(MoverEfficiency(1.5, 500, 125, 125).calculate() == Approx(0.1893279615));
	CHECK(MoverEfficiency(1.5, 700, 125, 125).calculate() == Approx(0.2650591461));
	CHECK(MoverEfficiency(1.5, 1100, 125, 125).calculate() == Approx(0.4165215152));
	CHECK(MoverEfficiency(1.5, 1800, 125, 125).calculate() == Approx(0.6815806613));
	CHECK(MoverEfficiency(1.5, 2800, 125, 125).calculate() == Approx(1.0602365842));

	CHECK(MoverEfficiency(1.5, 1000, 25, 125).calculate() == Approx(0.0757311846));
	CHECK(MoverEfficiency(1.5, 1000, 75, 125).calculate() == Approx(0.2271935538));
	CHECK(MoverEfficiency(1.5, 1000, 125, 125).calculate() == Approx(0.3786559229));
	CHECK(MoverEfficiency(1.5, 1000, 195, 125).calculate() == Approx(0.5907032398));
	CHECK(MoverEfficiency(1.5, 1000, 225, 125).calculate() == Approx(0.6815806613));
	CHECK(MoverEfficiency(1.5, 1000, 325, 125).calculate() == Approx(0.9845053996));

	CHECK(MoverEfficiency(1.5, 1000, 125, 25).calculate() == Approx(1.8932796147));
	CHECK(MoverEfficiency(1.5, 1000, 125, 75).calculate() == Approx(0.6310932049));
	CHECK(MoverEfficiency(1.5, 1000, 125, 155).calculate() == Approx(0.3053676798));
	CHECK(MoverEfficiency(1.5, 1000, 125, 255).calculate() == Approx(0.1856156485));
	CHECK(MoverEfficiency(1.5, 1000, 125, 425).calculate() == Approx(0.1113693891));
}

TEST_CASE( "Pump Motor efficiency", "[Pump][pump efficiency]" ) {
	CHECK(MoverEfficiency(0.5, 1000, 125, 125).calculate() == Approx(0.126218641));
	CHECK(MoverEfficiency(1.5, 1000, 125, 125).calculate() == Approx(0.3786559229));
	CHECK(MoverEfficiency(3.5, 1000, 125, 125).calculate() == Approx(0.8835304869));
	CHECK(MoverEfficiency(9.5, 1000, 125, 125).calculate() == Approx(2.3981541786));
	CHECK(MoverEfficiency(20.5, 1000, 125, 125).calculate() == Approx(5.1749642801));
	CHECK(MoverEfficiency(50.5, 1000, 125, 125).calculate() == Approx(12.7480827388));

	CHECK(MoverEfficiency(1.5, 500, 125, 125).calculate() == Approx(0.1893279615));
	CHECK(MoverEfficiency(1.5, 700, 125, 125).calculate() == Approx(0.2650591461));
	CHECK(MoverEfficiency(1.5, 1100, 125, 125).calculate() == Approx(0.4165215152));
	CHECK(MoverEfficiency(1.5, 1800, 125, 125).calculate() == Approx(0.6815806613));
	CHECK(MoverEfficiency(1.5, 2800, 125, 125).calculate() == Approx(1.0602365842));

	CHECK(MoverEfficiency(1.5, 1000, 25, 125).calculate() == Approx(0.0757311846));
	CHECK(MoverEfficiency(1.5, 1000, 75, 125).calculate() == Approx(0.2271935538));
	CHECK(MoverEfficiency(1.5, 1000, 125, 125).calculate() == Approx(0.3786559229));
	CHECK(MoverEfficiency(1.5, 1000, 195, 125).calculate() == Approx(0.5907032398));
	CHECK(MoverEfficiency(1.5, 1000, 225, 125).calculate() == Approx(0.6815806613));
	CHECK(MoverEfficiency(1.5, 1000, 325, 125).calculate() == Approx(0.9845053996));

	CHECK(MoverEfficiency(1.5, 1000, 125, 25).calculate() == Approx(1.8932796147));
	CHECK(MoverEfficiency(1.5, 1000, 125, 75).calculate() == Approx(0.6310932049));
	CHECK(MoverEfficiency(1.5, 1000, 125, 155).calculate() == Approx(0.3053676798));
	CHECK(MoverEfficiency(1.5, 1000, 125, 255).calculate() == Approx(0.1856156485));
	CHECK(MoverEfficiency(1.5, 1000, 125, 425).calculate() == Approx(0.1113693891));
}
