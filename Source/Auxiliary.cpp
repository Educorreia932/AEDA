#include "../Headers/Auxiliary.h"

int readOption(int min, int max) {
    int option;

    do {
        cout << endl << "Choose your option:  ";

        if (cin >> option && option >= min && option <= max) {
            cin.ignore(1000, '\n');
            return option;
        }

        else {
            cin.clear();
            cin.ignore(1000, '\n');
            cerr << "\nERROR: Invalid input. Please try again:\n"; //Throw exception
        }

    } while (true);
}
