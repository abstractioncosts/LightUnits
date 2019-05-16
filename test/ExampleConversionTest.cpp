#include <catch.hpp>
#include <IntegralUnits/Conversions.hpp>

std::ostream& operator << ( std::ostream& os, Ampere const& value ) {
	os << value.To<Prefix::Micro>() << " uA";
	return os;
}

std::ostream& operator << ( std::ostream& os, Volt const& value ) {
    os << value.To<Prefix::Milli>() << " mV";
    return os;
}

std::ostream& operator << ( std::ostream& os, Ohm const& value ) {
    os << value.To<Prefix::Milli>() << " mOhm";
    return os;
}


TEST_CASE("Division_Explore")
{
    // Volt BasePrefix Milli
    // Ohm  BasePrefix Milli
    REQUIRE(1_mV/2_Ohm == 500_uA);
}

TEST_CASE("Division_Regression")
{
    REQUIRE(4_V / 2_Ohm == 2_A);
    REQUIRE(4_mV / 2_mOhm == 2_A);
    REQUIRE(4_mV / 2_Ohm == 2_mA);
    REQUIRE(4_V / 200_Ohm == 20_mA);
}

TEST_CASE("Multiplication_Regression")
{
    REQUIRE(1_V == 1_A*1_Ohm);
    REQUIRE(2_V == 2_A*1_Ohm);
    REQUIRE(2_V == 1_A*2_Ohm);

    REQUIRE(1_mV == 1_mA * 1_Ohm);
    REQUIRE(1_mV == 1_A * 1_mOhm);
    REQUIRE(10_mV == 1_uA * 10_kOhm);
}
