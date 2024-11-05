#include "Register.h"
using namespace std;

    Register::Register() { reg.fill("00"); }

    optional<string> Register::getCell(int address) const
    {
        if (address >= 0 && address < reg.size())
        {
            return reg[address];
        }
        cerr << "Error: Invalid register address\n";
        return nullopt;
    }

    void Register::setCell(int address, const string &value)
    {
        if (address >= 0 && address < reg.size())
        {
            reg[address] = value;
        }
        else
        {
            cerr << "Error: Invalid register address\n";
        }
    }

    void Register::print() const
    {
        cout << "**Register Contents:\n";
        for (int i = 0; i < reg.size(); ++i)
        {
            cout << "   Register[" << i << "] = " << reg[i] << endl;
        }
    }
