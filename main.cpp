#include <iostream>

void print32Bits(unsigned long long value)
{
    for (int bit = 31; bit >= 0; --bit)
    {
        std::cout << ((value >> bit) & 1ULL);

        if (bit > 0 && bit % 8 == 0)
            std::cout << ' ';
    }
}

int main()
{
    char choice = '1';

    while (choice != '2')
    {
        std::cout << "\n1. Convert an integer\n";
        std::cout << "2. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (!std::cin)
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid menu input.\n";
            continue;
        }

        if (choice == '1')
        {
            long long number;

            std::cout << "Enter an integer from -2147483648 to 2147483647: ";
            std::cin >> number;

            if (!std::cin)
            {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Invalid integer input.\n";
                continue;
            }

            if (number < -2147483648LL || number > 2147483647LL)
            {
                std::cout << "The integer is outside the 32-bit range.\n";
                continue;
            }

            unsigned long long magnitude;

            if (number < 0)
                magnitude = static_cast<unsigned long long>(-number);
            else
                magnitude = static_cast<unsigned long long>(number);

            std::cout << "\nSigned magnitude: ";

            if (number == -2147483648LL)
            {
                std::cout << "not representable in 32-bit signed magnitude";
            }
            else
            {
                unsigned long long signedMagnitude = magnitude;

                if (number < 0)
                    signedMagnitude |= (1ULL << 31);

                print32Bits(signedMagnitude);
            }

            unsigned long long twosComplement;

            if (number < 0)
                twosComplement = (1ULL << 32) - magnitude;
            else
                twosComplement = magnitude;

            std::cout << "\nTwo's complement: ";
            print32Bits(twosComplement);
            std::cout << '\n';
        }
        else if (choice == '2')
        {
            std::cout << "Program ended.\n";
        }
        else
        {
            std::cout << "Invalid choice. Please enter 1 or 2.\n";
        }
    }

    return 0;
}
