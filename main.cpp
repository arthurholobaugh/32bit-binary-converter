#include <iostream>
using namespace std;

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

int main()
{
    long long number;

    cout << "Enter an integer: ";
    cin >> number;

    if (!cin || number < -2147483648LL || number > 2147483647LL)
    {
        cout << "The input must be a 32-bit signed integer.\n";
        return 1;
    }

    unsigned long long twosComplement;

    if (number < 0)
    {
        twosComplement = (1ULL << 32)
                       - static_cast<unsigned long long>(-number);
    }
    else
    {
        twosComplement = static_cast<unsigned long long>(number);
    }

    cout << "Two's complement: ";
    print32Bits(twosComplement);
    cout << '\n';

    if (number == -2147483648LL)
    {
        cout << "Signed magnitude: not representable in 32 bits\n";
        return 0;
    }

    unsigned long long signedMagnitude;

    if (number < 0)
    {
        signedMagnitude = static_cast<unsigned long long>(-number);
        signedMagnitude |= (1ULL << 31);
    }
    else
    {
        signedMagnitude = static_cast<unsigned long long>(number);
    }

    cout << "Signed magnitude: ";
    print32Bits(signedMagnitude);
    cout << '\n';

    return 0;
}
