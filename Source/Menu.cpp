#include "../Headers/Menu.h"

extern int selection;

Menu::Menu(School SUPSchool) {
    this->SUPSchool = SUPSchool;
}

void Menu::mainMenu() {
    cout << "1) Manage clients." << endl
         << "2) *Consultar conta cliente" << endl
         << "3) *Marcar aulas" << endl
         << "4) *Horário de aulas, horário de professores" << endl
         << "5) *Consultar aluguer material*" << endl
         << "6) Consult school's information." << endl
         << "0) Sair" << endl
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

