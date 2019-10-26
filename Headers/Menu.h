#ifndef SUP_SCHOOL_MENU_H
#define SUP_SCHOOL_MENU_H

#include "Auxiliary.h"
#include "School.h"

class Menu {
    public:
        //Constructors
        Menu(School SUPSchool);

        int showMainMenu();
        void mainMenuSelection(int selected);

        void manageClientsMenu();

        //Utils
        static void clearScreen();
        static void pause();
    private:
        School SUPSchool;

        //Schedules

};

#endif //SUP_SCHOOL_MENU_H
