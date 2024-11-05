#ifndef ALU_H
#define ALU_H

#include <string>
#include <sstream>
#include <cmath>
#include <iomanip>

class ALU
{
public:
    // Converts a hexadecimal string to a decimal integer
    static int hexToDecimal(const std::string &value);

    // Converts a decimal integer to a hexadecimal string (8-bit limit)
    static std::string decimalToHex(int decimal);

    // Adds two floating-point values represented as hexadecimal strings
    static float addFloatingPoint(const std::string &valS, const std::string &valT, bool implicitOne);

    // Converts a hexadecimal string to a floating-point number
    static float hexToFloat(const std::string &value);

    // Converts a floating-point number to a hexadecimal string
    static std::string floatToHex(float value);

    // Performs a right rotation on an 8-bit integer value
    static int rotateRight(int value, int steps);

    // Returns the two's complement of an 8-bit integer value
    static int twosComplement(int value);
};

#endif // ALU_H
