#include "../Headers/Menu.h"

#include "../Headers/Schedule.h"

using namespace std;

//Implement as class with exception for out of range/invalid or implement function to check
int selection = 1;

int main() {
    School PortoSUPSchool("../Data/School.txt");
    Menu SUPMenu(PortoSUPSchool);

    while (selection) {
        Menu::clearScreen();
        SUPMenu.mainMenu();
    }
    /*
    Schedule test;
    Time t;
    test.view(t, 20);
    Menu::pause();
    */
    return 0;
}