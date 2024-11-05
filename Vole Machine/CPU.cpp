#include "CPU.h"
using namespace std;


    CPU::CPU(Memory &memory) : mem(memory) {}

    int CPU::getProgramCounter() const { return programCounter; }
    string CPU::getInstructionRegister() const { return instructionRegister; }

    void CPU::incrementProgramCounter()
    {
        if (programCounter + 2 < MEMORY_SIZE)
        {
            programCounter += 2;
            if(instructionRegister[0] == 'C')programCounter -= 2;
        }
        else
        {
            cerr << "Error: Program Counter out of bounds.\n";
        }
    }

    void CPU::fetch()
    {
        auto instr1 = mem.getCell(programCounter);
        auto instr2 = mem.getCell(programCounter + 1);
        if (instr1 && instr2)
        {
            instructionRegister = *instr1 + *instr2;
            incrementProgramCounter();
        }
    }

    void CPU::execute()
    {
        char opcode = instructionRegister[0];
        int r = std::stoi(string(1, instructionRegister[1]), nullptr, 16);  // Convert hex character to integer
        int x = std::stoi(string(1, instructionRegister[2]), nullptr, 16);  // Convert hex character to integer
        int y = std::stoi(string(1, instructionRegister[3]), nullptr, 16);  // Convert hex character to integer
        int address = ALU::hexToDecimal(instructionRegister.substr(2, 2));
        int s = x; // Interpret x as register S for certain instructions
        int t = y; // Interpret y as register T for certain instructions

        switch (opcode)
        {
        case '0': // Skip empty memroy cells and exit code if there is more than 10 lines with no opcode (possible infinite loop) 
            noop++;
            if(noop > maxnoop){
                cout<< "Error no opcode for 10 lines, possible infinite loop,\nExiting program.... "<<endl;
                exit(-1);
            } 
            return;    
        case '1': // LOAD from memory
            if (auto value = mem.getCell(address))
            {
                reg.setCell(r, *value);
            }
            break;
        case '2': // LOAD immediate
            reg.setCell(r, ALU::decimalToHex(address));
            break;
        case '3': // STORE to memory
            if (address == 0)
            {
                if (auto value = reg.getCell(r))
                {
                    cout << "Screen Output: " << *value << endl; // Special screen output for address 00
                }
            }
            else if (auto value = reg.getCell(r))
            {
                mem.setCell(address, *value);
            }
            break;
        case '4': // MOVE
            if (auto srcValue = reg.getCell(x))
            {
                reg.setCell(y, *srcValue);
            }
            break;
        case '5': // ADD (2's Complement)  V1
            if (auto valX = reg.getCell(x), valY = reg.getCell(y); valX && valY)
            {
                int sum = ALU::hexToDecimal(*valX) + ALU::hexToDecimal(*valY);
                reg.setCell(r, ALU::decimalToHex(sum & 0xFF)); // Limit to 8-bit
            }
            break;
       case '6': // Floating-point ADD
            if (auto valX = reg.getCell(x), valY = reg.getCell(y); valX && valY)
            {
                // Convert hex strings to 32-bit integer representation
                uint32_t intX = std::stoul(*valX, nullptr, 16);
                uint32_t intY = std::stoul(*valY, nullptr, 16);

                // Reinterpret these integers as floats
                union {
                    uint32_t i;
                    float f;
                } floatX, floatY, floatResult;

                floatX.i = intX;
                floatY.i = intY;

                // Perform floating-point addition
                floatResult.f = floatX.f + floatY.f;

                // Store the result in hexadecimal format
                reg.setCell(r, ALU::floatToHex(floatResult.i)); //converting result to hex
            }
            break;


        case '7': // OR R = S | T
            if (auto valS = reg.getCell(s), valT = reg.getCell(t); valS && valT)
            {
                int result = ALU::hexToDecimal(*valS) | ALU::hexToDecimal(*valT);
                reg.setCell(r, ALU::decimalToHex(result));
            }
            break;
        case '8': // AND R = S & T
            if (auto valS = reg.getCell(s), valT = reg.getCell(t); valS && valT)
            {
                int result = ALU::hexToDecimal(*valS) & ALU::hexToDecimal(*valT);
                reg.setCell(r, ALU::decimalToHex(result));
            }
            break;
        case '9': // XOR R = S ^ T
            if (auto valS = reg.getCell(s), valT = reg.getCell(t); valS && valT)
            {
                int result = ALU::hexToDecimal(*valS) ^ ALU::hexToDecimal(*valT);
                cout<< result << ALU::decimalToHex(result)<<endl;
                reg.setCell(r, ALU::decimalToHex(result));
            }
            break;
        case 'A': // ROTATE right R by X steps
            if (auto valR = reg.getCell(r); valR)
            {
                int rotatedValue = ALU::rotateRight(ALU::hexToDecimal(*valR), x);
                reg.setCell(r, ALU::decimalToHex(rotatedValue));
            }
            break;

        case 'B': // JUMP if Register[R] == Register[0]
        {
            auto regValR = reg.getCell(r);
            auto regVal0 = reg.getCell(0); // Get the value of Register[0]
            if (regValR && regVal0 && *regValR == *regVal0)
            {
                programCounter = address; // Jump to address if R == 0
            }
        }
        break;

        case 'C': // HALT
            halt = true;
            break;

        case 'D': // JUMP to XY if Register[R] > Register[0] (Two's Complement)
        {
            auto regValR = reg.getCell(r);
            auto regVal0 = reg.getCell(0); // Get the value of Register[0]
            if (regValR && regVal0 && ALU::hexToDecimal(*regValR) > ALU::hexToDecimal(*regVal0))
            {
                programCounter = address; // Jump to address if R > 0
            }
        }
        break;

        default:
            cout << "Invalid instruction" << endl;
            cout << " " << opcode << " with r: " << r << ", x: " << x << ", y: " << y << ", address: " << address << endl;
        }
    }

    bool CPU::isHalted() const { return halt; }

    void CPU::printRegisters() const { reg.print(); }
