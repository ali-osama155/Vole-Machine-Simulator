#include "Machine.h"
using namespace std;


void displayMenu()
{
    cout << "1. Load Program from File\n";
    cout << "2. Step Execution\n";
    cout << "3. Display Complete State (PC, IR, Registers, Memory)\n";
    cout << "4. Exit\n";
}
// main v2
int main()
{
    Machine machine;
    int choice;

    while (true)
    {
        displayMenu();
        cout << "Please, Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string filename;
            cout << "Enter the program file name: ";
            cin >> filename;
            machine.loadProgramFile(filename);
        }
        break;
        case 2:
        {
            cout << "Executing program step-by-step until halt...\n";
            while (!machine.isHalted())
            {
                machine.stepExecution();
            }
            cout << "Program execution complete.\n";
        }
        break;
        case 3:
            machine.outputState();
            break;
        case 4:
            cout << "Exiting program.\n";
            return 0;
        default:
            cout << "Invalid choice.\n";
            main();
        }
    }
}