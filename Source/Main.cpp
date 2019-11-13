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
            PortoSUPSchool->saveActivities();
            PortoSUPSchool->saveClients();
            PortoSUPSchool->saveTeachers();
            PortoSUPSchool->saveMaterials();
            break;
        }
    }

    return 0;
}