#include <iostream>
#include "binary_converter.h"

int failures = 0;

void expect(bool condition, const char testName[])
{
    if (condition)
    {
        std::cout << "PASS: " << testName << '\n';
    }
    else
    {
        std::cout << "FAIL: " << testName << '\n';
        ++failures;
    }
}

void testWidth(int width)
{
    long long minimum = minimumValue(width);
    long long maximum = maximumValue(width);
    unsigned long long signedMagnitude = 0;

    expect(fitsTwosComplement(0, width), "zero fits");
    expect(fitsTwosComplement(1, width), "one fits");
    expect(fitsTwosComplement(-1, width), "negative one fits");
    expect(fitsTwosComplement(minimum, width), "minimum fits");
    expect(fitsTwosComplement(maximum, width), "maximum fits");
    expect(!fitsTwosComplement(minimum - 1, width),
           "below minimum is rejected");
    expect(!fitsTwosComplement(maximum + 1, width),
           "above maximum is rejected");

    expect(toTwosComplement(0, width) == 0ULL,
           "zero two's complement");
    expect(toTwosComplement(-1, width) == powerOfTwo(width) - 1ULL,
           "negative one two's complement");
    expect(toTwosComplement(minimum, width) == powerOfTwo(width - 1),
           "minimum two's complement");

    expect(toSignedMagnitude(0, width, signedMagnitude) &&
           signedMagnitude == 0ULL,
           "zero signed magnitude");
    expect(toSignedMagnitude(-1, width, signedMagnitude) &&
           signedMagnitude == powerOfTwo(width - 1) + 1ULL,
           "negative one signed magnitude");
    expect(!toSignedMagnitude(minimum, width, signedMagnitude),
           "minimum signed magnitude is rejected");
}

int main()
{
    testWidth(8);
    testWidth(16);
    testWidth(32);

    if (failures == 0)
    {
        std::cout << "\nAll tests passed.\n";
        return 0;
    }

    std::cout << "\n" << failures << " test(s) failed.\n";
    return 1;
}
