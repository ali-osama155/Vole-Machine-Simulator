#include "ALU.h"
using namespace std;



     int ALU::hexToDecimal(const string &value)
    {
        return stoi(value, nullptr, 16);
    }

     string ALU::decimalToHex(int decimal)
    {
        stringstream ss;
        ss << hex << uppercase << (decimal & 0xFF); // Limit to 8-bit
        return ss.str();
    }

     float ALU::addFloatingPoint(const string &valS, const string &valT, bool implicitOne)
    {
        float floatS = hexToFloat(valS);
        float floatT = hexToFloat(valT);
        return floatS + floatT;
    }

     float ALU::hexToFloat(const string &value)
    {
        int hexValue = stoi(value, nullptr, 16);
        int sign = (hexValue & 0x80) ? -1 : 1;
        int exponent = (hexValue >> 4) & 0x07;
        int mantissa = hexValue & 0x0F;

        float decimalMantissa = 1.0 + (mantissa / 16.0);
        int biasedExponent = exponent - 3;
        float result = sign * decimalMantissa * pow(2, biasedExponent);

        return result;
    }

     string ALU::floatToHex(float value)
    {
        int sign = (value < 0) ? 1 : 0;
        value = abs(value);

        int exponent = 0;
        float mantissa = frexp(value, &exponent);
        exponent += 3;

        int mantissaInt = static_cast<int>((mantissa - 1.0) * 16);
        int hexValue = (sign << 7) | ((exponent & 0x07) << 4) | (mantissaInt & 0x0F);

        stringstream ss;
        ss << hex << uppercase << hexValue;
        return ss.str();
    }

     int ALU::rotateRight(int value, int steps)
    {
        return (value >> steps) | (value << (8 - steps)) & 0xFF;
    }

     int ALU::twosComplement(int value)
    {
        return value < 128 ? value : value - 256;
    }

