#include "../Headers/Menu.h"

extern int selection;

Menu::Menu(School SUPSchool) {
    this->SUPSchool = SUPSchool;
}

void Menu::mainMenu() {
    cout << "What do you want to do? Insert the corresponding key." << endl
         << endl
         << "1) Rent material." << endl
         << "2) Manage clients." << endl
         << "3) Manage teachers." << endl
         << "4) Manage activities" << endl
         << "5) Consult schedules." << endl
         << "6) Consult school's information." << endl
         << "0) Exit" << endl //And save to files
         << endl;

    selection = readOption(0, 6);

    switch (selection) {
        case 1:
            //Call function
            return;
        case 2:
            manageClientsMenu();
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

void Menu::manageClientsMenu() {
    clearScreen();

    cout << "What do you want to do? Insert the corresponding key." << endl
         << endl
         << "1) Enrole a client in an activity." << endl
         << "0) Go back" << endl;

    switch(readOption(0, 1)) {
        case 1:
            int client;
            cout << "Which client?" << endl;
            cout << SUPSchool.Clients[0]->getName();

            try {
                SUPSchool.Clients[0]->enroll(1, SUPSchool.Activities);
            }

            catch (exception &e) {
                cerr << e.what();
            }

            pause();
            return;
        case 0:
            return;
    }
}

void Menu::clearScreen() {
    #ifdef __unix__
        system("clear");
    #endif

    #ifdef _WIN32
        system("cls");
    #endif

    //cout << string( 100, '\n' );
}

void Menu::pause() {
    cout << "Press any key to continue ...";
    cin.get();
}

