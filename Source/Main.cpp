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

School* chooseSchool(set<School*> &Schools) {
    cout << "Choose the school:" << endl;
    vector<School*> aux;
    int selected, counter = 0;

    for (auto s : Schools) {
        cout << counter << ") " << s->getName() << endl;
        aux.push_back(s);
        counter++;
    }

    selected = readOption(0, Schools.size() - 1);

    return aux[selected];
}

int main() {
    set<School*> Schools = loadSchools();

    auto* SelectedSchool = chooseSchool(Schools);
    Menu SUPMenu(SelectedSchool);
    int selected;

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