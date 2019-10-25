#include "../Headers/Menu.h"

#include "../Headers/Schedule.h"

using namespace std;

//Implement as class with exception for out of range/invalid or implement function to check
int selection = 1;

School PortoSUPSchool("../Data/School.txt");

int main() {

    Menu SUPMenu(PortoSUPSchool);

    /*
    while (selection) {
        Menu::clearScreen();
        SUPMenu.mainMenu();
    }
    */

    Schedule test;
    Time t(20, 10, 2019);
    test.view(t);

    return 0;
}