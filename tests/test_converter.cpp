#include <catch2/catch_test_macros.hpp>
#include "converter.hpp"

TEST_CASE("32-bit signed range is validated")
{
    REQUIRE(is32BitSignedInteger(-2147483648LL));
    REQUIRE(is32BitSignedInteger(2147483647LL));
    REQUIRE_FALSE(is32BitSignedInteger(-2147483649LL));
    REQUIRE_FALSE(is32BitSignedInteger(2147483648LL));
}

TEST_CASE("two's complement conversion handles representative values")
{
    REQUIRE(toTwosComplement(0) == 0x00000000ULL);
    REQUIRE(toTwosComplement(5) == 0x00000005ULL);
    REQUIRE(toTwosComplement(-1) == 0xFFFFFFFFULL);
    REQUIRE(toTwosComplement(-5) == 0xFFFFFFFBULL);
    REQUIRE(toTwosComplement(2147483647LL) == 0x7FFFFFFFULL);
    REQUIRE(toTwosComplement(-2147483648LL) == 0x80000000ULL);
}

TEST_CASE("signed magnitude conversion handles representative values")
{
    REQUIRE(toSignedMagnitude(0) == 0x00000000ULL);
    REQUIRE(toSignedMagnitude(5) == 0x00000005ULL);
    REQUIRE(toSignedMagnitude(-5) == 0x80000005ULL);
    REQUIRE(toSignedMagnitude(2147483647LL) == 0x7FFFFFFFULL);
    REQUIRE(toSignedMagnitude(-2147483647LL) == 0xFFFFFFFFULL);
}

TEST_CASE("minimum two's complement integer has no signed magnitude form")
{
    REQUIRE(hasSignedMagnitudeRepresentation(-2147483647LL));
    REQUIRE_FALSE(hasSignedMagnitudeRepresentation(-2147483648LL));
}
