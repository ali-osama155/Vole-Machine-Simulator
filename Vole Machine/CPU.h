#ifndef CPU_H
#define CPU_H

#include <cstdint>
#include <string>
#include "Register.h"
#include "ALU.h"
#include "Memory.h"



class CPU
{
private:
    int programCounter = 0; // Program Counter
    std::string instructionRegister; // Holds the current instruction
    Register reg; // Register file for the CPU
    ALU alu; // Arithmetic and Logic Unit
    Memory &mem; // Reference to the memory
    bool halt = false; // Flag to check if CPU is halted
    int noop = 0; // No-operation counter
    int maxnoop = 15; // Maximum number of no-ops before halting

public:
    // Constructor that initializes memory reference
    CPU(Memory &memory);

    // Gets the current value of the program counter
    int getProgramCounter() const;

    // Gets the current instruction in the instruction register
    std::string getInstructionRegister() const;

    // Increments the program counter with boundary checks
    void incrementProgramCounter();

    // Fetches the instruction from memory at the current program counter
    void fetch();

    // Decodes and executes the fetched instruction
    void execute();

    // Checks if the CPU has been halted
    bool isHalted() const;

    // Prints the contents of the CPU's registers
    void printRegisters() const;
};

#endif // CPU_H
