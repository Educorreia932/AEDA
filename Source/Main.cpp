#include "../Headers/Menu.h"
#include "../Headers/Schedule.h"

using namespace std;

int main() {
    School PortoSUPSchool("../Data/School.txt");
    Menu SUPMenu(PortoSUPSchool);
    int selected;

    while (true) {
        if(selected = SUPMenu.showMainMenu())
            SUPMenu.mainMenuSelection(selected);

        else
            break;
    }

/*    Schedule test;
    Time t(23, 5, 2015);
    test.view(t, 30);
    Menu::pause();*/

    return 0;
}