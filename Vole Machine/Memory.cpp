#include "memory.h"
using namespace std;

    Memory::Memory(int size) : memory(size, "00") {}

    optional<string> Memory::getCell(int address) const
    {
        if (address >= 0 && address < memory.size())
        {
            return memory[address];
        }
        cerr << "Error: Invalid memory address\n";
        return nullopt;
    }

    void Memory::setCell(int address, const string &value)
    {
        if (address >= 0 && address < memory.size())
        {
            memory[address] = value;
        }
        else
        {
            cerr << "Error: Invalid memory address\n";
        }
    }

    void Memory::print() const
    {
        cout << "**Memory Contents (16x16):\n";
        for (int i = 0; i < MEMORY_SIZE; i += 16)
        {
            for (int j = 0; j < 16; ++j)
            {
                if (i + j < MEMORY_SIZE) // Check bounds
                    cout << setw(3) << memory[i + j] << " ";
            }
            cout << endl; // New line after each row
        }
    }

