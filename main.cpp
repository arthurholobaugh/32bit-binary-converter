#include <iostream>
#include "binary_converter.h"

void printBits(unsigned long long value, int width)
{
    for (int bit = width - 1; bit >= 0; --bit)
    {
        std::cout << ((value >> bit) & 1ULL);

        if (bit > 0 && bit % 8 == 0)
        {
            std::cout << ' ';
        }
    }
}

void printHex(unsigned long long value, int width)
{
    const char digits[] = "0123456789ABCDEF";

    for (int shift = width - 4; shift >= 0; shift -= 4)
    {
        int digit = static_cast<int>((value >> shift) & 0xFULL);
        std::cout << digits[digit];
    }
}

bool parseInteger(const char text[], long long& number)
{
    int index = 0;
    bool negative = false;

    if (text[index] == '+' || text[index] == '-')
    {
        negative = text[index] == '-';
        ++index;
    }

    if (text[index] == '\0')
    {
        return false;
    }

    unsigned long long value = 0;

    while (text[index] != '\0')
    {
        if (text[index] < '0' || text[index] > '9')
        {
            return false;
        }

        value = value * 10ULL +
                static_cast<unsigned long long>(text[index] - '0');

        // No supported mode accepts a magnitude greater than 2^31.
        if (value > 2147483648ULL)
        {
            return false;
        }

        ++index;
    }

    if (negative)
    {
        number = -static_cast<long long>(value);
    }
    else
    {
        number = static_cast<long long>(value);
    }

    return true;
}

int readWidth()
{
    int width = 0;

    while (!isSupportedWidth(width))
    {
        std::cout << "Choose a bit width (8, 16, or 32): ";
        std::cin >> width;

        if (!std::cin)
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            width = 0;
        }
        else
        {
            std::cin.ignore(10000, '\n');
        }

        if (!isSupportedWidth(width))
        {
            std::cout << "Please enter 8, 16, or 32.\n";
        }
    }

    return width;
}

int main()
{
    std::cout << "Signed-Magnitude and Two's-Complement Converter\n";
    std::cout << "Only integers that fit the selected width are accepted.\n\n";

    int width = readWidth();
    char input[64];

    while (true)
    {
        std::cout << "\nEnter an integer";
        std::cout << " (" << minimumValue(width)
                  << " to " << maximumValue(width) << ")";
        std::cout << ", w to change width, or q to quit: ";
        std::cin.getline(input, 64);

        if (!std::cin)
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Input is too long. Please try again.\n";
            continue;
        }

        if ((input[0] == 'q' || input[0] == 'Q') && input[1] == '\0')
        {
            break;
        }

        if ((input[0] == 'w' || input[0] == 'W') && input[1] == '\0')
        {
            width = readWidth();
            continue;
        }

        long long number;

        if (!parseInteger(input, number))
        {
            std::cout << "Invalid input. Enter a whole number, w, or q.\n";
            continue;
        }

        if (!fitsTwosComplement(number, width))
        {
            std::cout << number << " does not fit in a signed "
                      << width << "-bit value.\n";
            continue;
        }

        unsigned long long twosComplement =
            toTwosComplement(number, width);
        unsigned long long signedMagnitude = 0;
        bool signedMagnitudeExists =
            toSignedMagnitude(number, width, signedMagnitude);

        std::cout << "\nDecimal:          " << number << '\n';

        std::cout << "Signed magnitude: ";
        if (signedMagnitudeExists)
        {
            printBits(signedMagnitude, width);
            std::cout << "  (0x";
            printHex(signedMagnitude, width);
            std::cout << ")\n";
        }
        else
        {
            std::cout << "not representable in " << width << " bits\n";
        }

        std::cout << "Two's complement: ";
        printBits(twosComplement, width);
        std::cout << "  (0x";
        printHex(twosComplement, width);
        std::cout << ")\n";
    }

    std::cout << "Program ended.\n";
    return 0;
}
