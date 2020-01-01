#include "../Headers/Menu.h"

#include <set>

using namespace std;

set<School*> loadSchools() {
    set<School*> result;
    School* aux;

    for (int i = 1; i < 5; i++) {
        aux = new School("../Data/" + to_string(i) + "/School.txt");
        result.insert(aux);
    }

    return result;
}

void printSchools(set<School*> &Schools) {
    for (auto s : Schools) {
        cout << s->getName() << endl
             << "\tNumber of Clients: " << s->getClients().size() << endl
             << "\tLocality: " << s->getLocality() << endl;
    }
}

int main() {
    set<School*> Schools = loadSchools();

    auto* SelectedSchool = chooseSchool(Schools);
    Menu SUPMenu(SelectedSchool);
    int selected;

    //printSchools(Schools);
    Menu::pause();
    while (true) {
        if((selected = Menu::showMainMenu()))
            SUPMenu.mainMenuSelection(selected);

        else {
            SelectedSchool->saveActivities();
            SelectedSchool->saveClients();
            SelectedSchool->saveTeachers();
            SelectedSchool->saveMaterials();
            SelectedSchool->saveActivities();
            break;
        }
    }

    return 0;
}