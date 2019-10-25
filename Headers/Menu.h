#ifndef SUP_SCHOOL_MENU_H
#define SUP_SCHOOL_MENU_H

#include "Auxiliary.h"
#include "School.h"

class Menu {
    public:
        //Constructors
        Menu(School SUPSchool);

        //Menus
        void mainMenu();
        void manageClientsMenu();

        //Utils
        static void clearScreen();
        static void pause();
    private:
        School SUPSchool;
};

#endif //SUP_SCHOOL_MENU_H
