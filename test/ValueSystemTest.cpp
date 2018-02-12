#include <LightUnits/ValueSystem.hpp>
#include <cstdint>

using namespace LightUnits;
using namespace LightUnits::detail;

using Sys0 = ValueSystem<>;
using Sys1 = ValueSystem<std::int8_t>;
using Sys2 = ValueSystem<std::int8_t, std::int16_t>;
using Sys4 = ValueSystem<std::int8_t, std::int16_t, std::int32_t, std::int64_t>;

static_assert(!HasElement<Sys0, std::int8_t>::Value, "");
static_assert(HasElement<Sys1, std::int8_t>::Value, "");
static_assert(!HasElement<Sys1, std::int16_t>::Value, "");

static_assert(HasElement<Sys2, std::int8_t>::Value, "");
static_assert(HasElement<Sys2, std::int16_t>::Value, "");
static_assert(!HasElement<Sys2, std::int32_t>::Value, "");

static_assert(PositionOf<Sys2, std::int8_t>::value == 0, "");
static_assert(PositionOf<Sys2, std::int16_t>::value == 1, "");

static_assert(std::is_same<std::int8_t, detail::Element<Sys1, 0>::type>::value, "");
static_assert(std::is_same<std::int16_t, detail::Element<Sys2, 1>::type>::value, "");
static_assert(!std::is_same<std::int16_t, detail::Element<Sys2, 0>::type>::value, "");


static_assert(
        std::is_same<std::int16_t, MultiplicationResultHelper<Sys4, std::int8_t, std::int8_t>::type>::value,
        "");
static_assert(
        std::is_same<std::int32_t, MultiplicationResultHelper<Sys4, std::int16_t, std::int8_t>::type>::value,
        "");
static_assert(
        std::is_same<std::int32_t, MultiplicationResultHelper<Sys4, std::int8_t, std::int16_t>::type>::value,
        "");
static_assert(
        std::is_same<std::int64_t, MultiplicationResultHelper<Sys4, std::int32_t, std::int16_t>::type>::value,
        "");
