#include "../Headers/Menu.h"
#include "../Headers/Schedule.h"

using namespace std;

int main() {

    Time startTime = Time(25, 4, 2012, 0, 0);
    Time endTime = Time(24, 4, 2013, 0, 1);
    Time deltaTime = endTime - startTime;
    cout << "The difference of time (D/M/Y HH::MM) is: " << deltaTime.getDay() << "/" << deltaTime.getMonth() << "/" << deltaTime.getYear() << " " << setw(2) << setfill('0') << deltaTime.getHours() << ":" << setw(2) << setfill('0') << deltaTime.getMinutes() << endl;
    /*
    School PortoSUPSchool("../Data/School.txt");
    Menu SUPMenu(PortoSUPSchool);
    int selected;



    while (true) {
        if(selected = SUPMenu.showMainMenu())
            SUPMenu.mainMenuSelection(selected);

        else
            break;
    }
/*
/*    Schedule test;
    Time t(23, 5, 2015);
    test.view(t, 30);
    Menu::pause();*/

    return 0;
}