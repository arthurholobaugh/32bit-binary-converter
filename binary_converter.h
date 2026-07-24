#ifndef BINARY_CONVERTER_H
#define BINARY_CONVERTER_H

inline unsigned long long powerOfTwo(int exponent)
{
    return 1ULL << exponent;
}

inline long long minimumValue(int width)
{
    return -static_cast<long long>(powerOfTwo(width - 1));
}

inline long long maximumValue(int width)
{
    return static_cast<long long>(powerOfTwo(width - 1) - 1ULL);
}

inline bool isSupportedWidth(int width)
{
    return width == 8 || width == 16 || width == 32;
}

inline bool fitsTwosComplement(long long number, int width)
{
    return isSupportedWidth(width) &&
           number >= minimumValue(width) &&
           number <= maximumValue(width);
}

inline unsigned long long magnitudeOf(long long number)
{
    if (number < 0)
    {
        return static_cast<unsigned long long>(-number);
    }

    return static_cast<unsigned long long>(number);
}

inline unsigned long long toTwosComplement(long long number, int width)
{
    if (number < 0)
    {
        return powerOfTwo(width) - magnitudeOf(number);
    }

    return static_cast<unsigned long long>(number);
}

inline bool toSignedMagnitude(long long number, int width,
                              unsigned long long& result)
{
    if (!fitsTwosComplement(number, width) ||
        number == minimumValue(width))
    {
        return false;
    }

    result = magnitudeOf(number);

    if (number < 0)
    {
        result |= powerOfTwo(width - 1);
    }

    return true;
}

#endif
