#include "../Headers/Menu.h"

#include <set>

using namespace std;

int main() {
    auto* PortoSUPSchool = new School("../Data/1/School.txt");
    Menu SUPMenu(PortoSUPSchool);
    int selected;

    set<School> Schools;

    while (true) {
        if((selected = Menu::showMainMenu()))
            SUPMenu.mainMenuSelection(selected);

        else {
            PortoSUPSchool->saveActivities();
            PortoSUPSchool->saveClients();
            PortoSUPSchool->saveTeachers();
            PortoSUPSchool->saveMaterials();
            PortoSUPSchool->saveActivities();
            break;
        }
    }

    return 0;
}