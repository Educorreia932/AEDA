#include "../Headers/Menu.h"

using namespace std;

int main() {
    School PortoSUPSchool("../Data/School.txt");
    Menu SUPMenu(PortoSUPSchool);
    int selected;

    while (true) {
        if((selected = Menu::showMainMenu()))
            SUPMenu.mainMenuSelection(selected);

        else
            break;
    }

    return 0;
}