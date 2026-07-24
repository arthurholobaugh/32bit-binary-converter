# Binary Representation Converter

A console C++ program that converts signed integers to signed-magnitude and
two's-complement representations. It supports 8-, 16-, and 32-bit output and
inserts a space between every eight binary digits.

The application uses only the C++ `<iostream>` library and compiles with GCC.

## Features

- Converts integers to signed magnitude and two's complement.
- Supports 8-, 16-, and 32-bit widths.
- Displays decimal, binary, and hexadecimal values together.
- Accepts `q` to quit or `w` to change the bit width.
- Recovers from invalid, out-of-range, and excessively long input.
- Keeps conversion logic separate from user-interface code.
- Includes automated boundary tests for every supported width.

## Representation ranges

| Width | Two's-complement range | Signed-magnitude range |
| --- | ---: | ---: |
| 8 bits | -128 to 127 | -127 to 127 |
| 16 bits | -32,768 to 32,767 | -32,767 to 32,767 |
| 32 bits | -2,147,483,648 to 2,147,483,647 | -2,147,483,647 to 2,147,483,647 |

The most-negative two's-complement value at each width cannot be represented
in signed magnitude because signed magnitude reserves its highest bit for the
sign. The program reports this case instead of displaying an incorrect value.

## Files

- `main.cpp` contains the console interface and formatting functions.
- `binary_converter.h` contains reusable range and conversion functions.
- `tests.cpp` contains automated boundary tests.

## Build

```bash
g++ -std=c++11 -Wall -Wextra -pedantic main.cpp -o binary-converter
```

## Run

```bash
./binary-converter
```

Example:

```text
Choose a bit width (8, 16, or 32): 32

Enter an integer (-2147483648 to 2147483647), w to change width, or q to quit: -42

Decimal:          -42
Signed magnitude: 10000000 00000000 00000000 00101010  (0x8000002A)
Two's complement: 11111111 11111111 11111111 11010110  (0xFFFFFFD6)
```

## Test

```bash
g++ -std=c++11 -Wall -Wextra -pedantic tests.cpp -o converter-tests
./converter-tests
```

The tests cover zero, `1`, `-1`, the minimum and maximum value, values just
outside the valid range, and the signed-magnitude minimum-value limitation for
all supported widths.
