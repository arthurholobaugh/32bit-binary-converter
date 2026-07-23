#include <iostream>
#include "converter.hpp"

using namespace std;

bool is32BitSignedInteger(long long number)
{
    return number >= -2147483648LL && number <= 2147483647LL;
}

bool hasSignedMagnitudeRepresentation(long long number)
{
    return number >= -2147483647LL && number <= 2147483647LL;
}

unsigned long long toTwosComplement(long long number)
{
    if (number < 0)
    {
        return (1ULL << 32) - static_cast<unsigned long long>(-number);
    }

    return static_cast<unsigned long long>(number);
}

unsigned long long toSignedMagnitude(long long number)
{
    if (number < 0)
    {
        return static_cast<unsigned long long>(-number) | (1ULL << 31);
    }

    return static_cast<unsigned long long>(number);
}

void print32Bits(unsigned long long value)
{
    for (int bit = 31; bit >= 0; --bit)
    {
        cout << ((value >> bit) & 1ULL);

        if (bit != 0 && bit % 8 == 0)
        {
            cout << ' ';
        }
    }
}
