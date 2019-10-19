#include "../Headers/Auxiliary.h"

int readOption(int min, int max) {
    int option;

    while (true) {
        cout << "Choose your option: ";

        if (cin >> option && option >= min && option <= max) {
            cin.ignore(1000, '\n');
            return option;
        }

        else {
            cin.clear();
            cin.ignore(1000, '\n');
            cerr << "ERROR: Invalid input. Please try again:\n"; //Throw exception
        }
    }
}

bool stob(const string& s) {
    return s == "true";
}

void viewSchedule(const vector<Activity *>& Activities) {

}