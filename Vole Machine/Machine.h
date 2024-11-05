#ifndef MACHINE_H
#define MACHINE_H

#include <fstream>
#include <string>
#include "Memory.h"
#include "CPU.h"

class Machine
{
private:
    Memory memory;
    CPU processor;

public:
    // Constructor initializing memory and processor with MEMORY_SIZE
    Machine();

    // Loads program instructions from a file into memory starting from a user-specified address
    void loadProgramFile(const std::string &filename);

    // Executes the next instruction in the program
    void stepExecution();

    // Outputs the current state of the program counter, instruction register, registers, and memory
    void outputState();

    // Checks if the processor has halted
    bool isHalted() const;
};

#endif // MACHINE_H
