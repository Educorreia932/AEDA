#include "../Headers/Menu.h"

using namespace std;

//Implement as class with exception for out of range/invalid or implement function to check
int selection = 1;

int main() {
    vector<Client> Clients; //Read from file
    vector<Material> Materials; //Read from file

    School PortoSUPSchool(Clients, Materials);
    Menu SUPMenu(PortoSUPSchool);

    while (selection) {
        Menu::clearScreen();
        SUPMenu.mainMenu();
    }

    return 0;
}