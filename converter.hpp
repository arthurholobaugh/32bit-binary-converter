#ifndef CONVERTER_HPP
#define CONVERTER_HPP

bool is32BitSignedInteger(long long number);
bool hasSignedMagnitudeRepresentation(long long number);
unsigned long long toTwosComplement(long long number);
unsigned long long toSignedMagnitude(long long number);
void print32Bits(unsigned long long value);

#endif
