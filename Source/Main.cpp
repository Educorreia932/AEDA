#include "../Headers/Menu.h"

using namespace std;

//Implement as class with exception for out of range/invalid or implement function to check
int selection = 1;

int main() {
    School PortoSUPSchool("School.txt");
    Menu SUPMenu(PortoSUPSchool);

    while (selection) {
        Menu::clearScreen();
        SUPMenu.mainMenu();
    }

    return 0;
}