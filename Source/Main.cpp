#include "../Headers/Menu.h"

using namespace std;

int main() {
    if(1 < 5){
        cout << "I?AWEPOwqdpuaiweuOPKDoqw89udqwpuh BRUH" << endl;
    }
    auto* PortoSUPSchool = new School("../Data/School.txt");
    Menu SUPMenu(PortoSUPSchool);
    int selected;

    while (true) {
        if((selected = Menu::showMainMenu()))
            SUPMenu.mainMenuSelection(selected);

        else {
            PortoSUPSchool->saveClients();
            PortoSUPSchool->saveTeachers();
            break;
        }
    }

    return 0;
}