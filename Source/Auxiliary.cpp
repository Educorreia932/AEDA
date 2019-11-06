#include "../Headers/Auxiliary.h"

int readOption(int min, int max) {
    int option;

    while (true) {
        cout << "Your option: ";

        if (cin >> option && option >= min && option <= max) {
            cin.ignore(1000, '\n');
            return option;
        }

        else {
            cin.clear();
            cin.ignore(1000, '\n');
            cerr << endl
                 << "Invalid input. Please try again:" << endl
                 << endl;
        }
    }
}

bool stob(const string& s) {
    return s == "true";
}

string centerString(int width, const string& s) {
    int length = s.length();
    int pos = (width - length) / 2;
    string result = string(pos, ' ') + s + string(width - pos - length, ' ');

    return result;
};