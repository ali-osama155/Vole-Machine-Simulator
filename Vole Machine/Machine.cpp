#include "Machine.h"
#include "Memory.h"
#include "CPU.h"
using namespace std;




    Machine::Machine() : memory(MEMORY_SIZE), processor(memory) {}
    
    void Machine::loadProgramFile(const string &filename)
    {
        ifstream file(filename);
        if (!file)
        {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        cout << "Enter the starting address of Memory (0 to 255): ";
        int startAddress;
        cin >> startAddress;
        if (startAddress < 0 || startAddress >= MEMORY_SIZE)
        {
            cout << "Invalid starting address.\n";
            return;
        }

        string instruction;
        int address = startAddress;
        while (file >> instruction && address < MEMORY_SIZE - 1)
        {
            if (instruction.size() == 4)
            {
                memory.setCell(address, instruction.substr(0, 2));
                memory.setCell(address + 1, instruction.substr(2, 2));
                address += 2;
            }
            else
            {
                cout << "Invalid instruction format: " << instruction << endl;
            }
        }
        file.close();
    }

    void Machine::stepExecution()
    {
        cout << "Stepping execution..." << endl; // Debug statement
        processor.fetch();
        processor.execute();
        outputState();
    }

    void Machine::outputState()
    {
        cout << "Program Counter (PC)(in Decimal): " << processor.getProgramCounter() << endl;
        cout << "Instruction Register (IR): " << processor.getInstructionRegister() << endl;
        processor.printRegisters();
        memory.print();
    }

    bool Machine::isHalted() const { return processor.isHalted(); }
