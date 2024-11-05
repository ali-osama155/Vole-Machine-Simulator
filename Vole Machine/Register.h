#ifndef REGISTER_H
#define REGISTER_H

#include <array>
#include <string>
#include <optional>
#include <iostream>

constexpr int REGISTER_SIZE = 16;

class Register
{
private:
    std::array<std::string, REGISTER_SIZE> reg; // Array to store register values

public:
    // Constructor initializes all registers to "00"
    Register();

    // Returns the value at a specific register address, or nullopt if out of bounds
    std::optional<std::string> getCell(int address) const;

    // Sets the value at a specific register address, with bounds checking
    void setCell(int address, const std::string &value);

    // Prints the contents of all registers
    void print() const;
};

#endif // REGISTER_H
