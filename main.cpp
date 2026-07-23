#include <iostream>
#include "converter.hpp"

using namespace std;

int main()
{
    long long number;

    cout << "Enter an integer: ";
    cin >> number;

    if (!cin || !is32BitSignedInteger(number))
    {
        cout << "The input must be a 32-bit signed integer.\n";
        return 1;
    }

    cout << "Two's complement: ";
    print32Bits(toTwosComplement(number));
    cout << '\n';

    if (!hasSignedMagnitudeRepresentation(number))
    {
        cout << "Signed magnitude: not representable in 32 bits\n";
        return 0;
    }

    cout << "Signed magnitude: ";
    print32Bits(toSignedMagnitude(number));
    cout << '\n';

    return 0;
}
