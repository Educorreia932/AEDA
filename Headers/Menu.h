#ifndef SUP_SCHOOL_MENU_H
#define SUP_SCHOOL_MENU_H

#include "Auxiliary.h"
#include "School.h"

class Menu {
    public:
        Menu(School SUPSchool);
        void mainMenu();
        static void clearScreen();
    private:
        School SUPSchool;
};

#endif //SUP_SCHOOL_MENU_H
