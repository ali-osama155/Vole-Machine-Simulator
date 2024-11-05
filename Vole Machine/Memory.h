#ifndef MEMORY_H
#define MEMORY_H

#include <vector>
#include <string>
#include <optional>
#include <iostream>
#include <iomanip>

constexpr int MEMORY_SIZE = 256;

class Memory
{
private:
    std::vector<std::string> memory; // Vector to store memory cells

public:
    // Constructor that initializes memory with the given size, setting each cell to "00"
    Memory(int size);

    // Returns the value at a specific memory address, or nullopt if out of bounds
    std::optional<std::string> getCell(int address) const;

    // Sets the value at a specific memory address, with bounds checking
    void setCell(int address, const std::string &value);

    // Prints the contents of memory in a 16x16 format
    void print() const;
};

#endif // MEMORY_H
