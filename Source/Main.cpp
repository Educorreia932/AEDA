#include "../Headers/Menu.h"

using namespace std;

int main() {
    auto* PortoSUPSchool = new School("../Data/School.txt");
    Menu SUPMenu(PortoSUPSchool);
    int selected;

    while (true) {
        if((selected = Menu::showMainMenu()))
            SUPMenu.mainMenuSelection(selected);

        else {
            PortoSUPSchool->saveClients();
            break;
        }
    }

    return 0;
}