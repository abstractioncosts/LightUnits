#include <catch.hpp>
#include <LightUnits/BaseUnit.hpp>
#include <cstdint>
#include <type_traits>

using namespace LightUnits;

struct DummyType
{
    static Prefix const BasePrefix = Prefix::Milli;
    typedef std::int16_t ValueType;
};

struct Dummy_t; ///< Tag which uniquely identifies type "Dummy"
using TestUnit   = BaseUnit<Dummy_t, DummyType>;

std::ostream& operator << ( std::ostream& os, TestUnit const& value ) {
    os << value.To<TestUnit::BasePrefix>() << " (Base-Prefix)";
    return os;
}

const DummyType::ValueType a = 1;
const DummyType::ValueType b = 2;

static TestUnit Create(int16_t val)
{
    return TestUnit::From<Prefix::Milli>(val);
}

TEST_CASE("CreatedByFrom_RawMatchesArgument") {
    auto x = Create(a);
    REQUIRE(x.To<DummyType::BasePrefix>() == a);
}

TEST_CASE("SimpleAssignment_ValueIsStored") {
    auto x = Create(a);
    x = Create(b);
    REQUIRE(x.To<DummyType::BasePrefix>() == b);
}

TEST_CASE("AdditionAssignment_CompareWithStandardCompoundAssignmentBehaviour") {
    auto x = Create(a);
    x += Create(b);

    // For built-in types the expression a+=b returns (a+b).
    // Verify this behaviour for our user-defined type
    DummyType::ValueType standardX = a;
    REQUIRE(x == Create(standardX += b));
}

TEST_CASE("SubtractionAssignment_CompareWithStandardCompoundAssignmentBehaviour") {
    auto x = Create(a);
    x -= Create(b);

    // For built-in types the expression a+-b returns (a-b).
    // Verify this behaviour for our user-defined type
    DummyType::ValueType standardX = a;
    REQUIRE(x == Create(standardX -= b));
}

TEST_CASE("UnaryMinus_ValueIsInverted") {
    auto const x = Create(a);
    REQUIRE( (-x) == Create(-a));

    auto const y = Create(-a);
    REQUIRE( (-y) == Create(a));
}

TEST_CASE("Addition_ResultIsSum") {
    auto const sum = Create(a) + Create(b);
    REQUIRE(sum == Create(a+b));
}

TEST_CASE("Subtraction_ResultIsDiff") {
    auto const diff = Create(a) - Create(b);
    REQUIRE(diff == Create(a-b));
}

TEST_CASE("Modulo_ResultIsOfUnitType") {
   TestUnit x = Create(5);
   TestUnit y = Create(3);
   auto res = x % y;
   static_assert(std::is_same<decltype(x), decltype(res)>::value, "Unit modulo Unit has to be of type Unit");
   REQUIRE(res == Create(2));
}

TEST_CASE("EqualTo_AisA") {
    REQUIRE(Create(a) == Create(a));
}

TEST_CASE("NotEqualTo_AisNotB") {
    REQUIRE(Create(a) != Create(b));
}

TestUnit const small = Create(10);
TestUnit const large = Create(20);
TestUnit const epsilon = Create(1);

TEST_CASE("LessThan") {
    REQUIRE(small < large);
    REQUIRE(small < small + epsilon);
    REQUIRE(small - epsilon < small);

    REQUIRE(! (large < small));
    REQUIRE(! (small < small));
}

TEST_CASE("GreaterThan") {
    REQUIRE(large > small);
    REQUIRE(large + epsilon > large);
    REQUIRE(large > large - epsilon);

    REQUIRE(! (large > large));
    REQUIRE(! (small > large));
}

TEST_CASE("LesshanOrEqual") {
    REQUIRE( small <= small);
    REQUIRE(! (large <= small));
}

TEST_CASE("GreaterThanOrEqual") {
    REQUIRE(large >= large);
    REQUIRE(! (small >= large));
}

TEST_CASE("UnitTimesFloat") {
    REQUIRE(Create(2) * 0.5f== Create(1));
    REQUIRE(Create(100)*0.4f == Create(40));
    REQUIRE(Create(10)*4.f == Create(40));
    REQUIRE(Create(100)*-0.4f == Create(-40));
}

TEST_CASE("FloatTimesUnit") {
    REQUIRE(0.5f  * Create(2) == Create(1));
    REQUIRE(0.4f  * Create(100) == Create(40));
    REQUIRE(4.f   * Create(10) == Create(40));
    REQUIRE(-0.4f * Create(100) == Create(-40));
}

TEST_CASE("NumericLimitsTypeTraitMax_EqualsBaseTypeMin")
{
    auto base = std::numeric_limits<DummyType::ValueType>::max();
    auto unit = std::numeric_limits<TestUnit>::max();
    REQUIRE(base == unit.To<DummyType::BasePrefix>());
}

TEST_CASE("NumericLimitsTypeTraitMin_EqualsBaseTypeMax")
{
    auto base = std::numeric_limits<DummyType::ValueType>::min();
    auto unit = std::numeric_limits<TestUnit>::min();
    REQUIRE(base == unit.To<DummyType::BasePrefix>());
}
