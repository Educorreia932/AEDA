#include "../Headers/Menu.h"

extern int selection;

Menu::Menu(School SUPSchool) {
    this->SUPSchool = SUPSchool;
}

void Menu::mainMenu() {
    cout << "1) Rent material." << endl
         << "2) Manage clients." << endl
         << "3) Manage teachers." << endl
         << "4) Manage activities" << endl
         << "5) Consult schedules."
         << "6) Consult school's information." << endl
         << "0) Exit" << endl //And save to files
         << endl;

    selection = readOption(0, 6);

    switch (selection) {
        case 1:
            //Call function
            return;
        case 6:
            cout << SUPSchool.currentTime << endl;
            system("pause"); //Implement in function
            return;
        case 0:
            return;
        default:
            //Error not valid
            return;
    }
}

void Menu::clearScreen() {
    /*
    #ifdef __unix__
        system("clear");
    #endif

    #ifdef _WIN32
        system("cls");
    #endif
     */

    cout << string( 100, '\n' );
}

