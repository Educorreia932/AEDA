#ifndef SUP_SCHOOL_MENU_H
#define SUP_SCHOOL_MENU_H

#include "Schedule.h"
#include "School.h"

class Menu {
    public:
        //Constructors
        Menu(School SUPSchool);

        static int showMainMenu();
        void mainMenuSelection(int selected);

        //Utils
        static void clearScreen();
        static void pause();
    private:
        School SUPSchool;

        static int showManageClients();
        void manageClientsSelection(int selected);

        static int showConsultSchedule();
        void consultScheduleSelection(int selected);
};

#endif //SUP_SCHOOL_MENU_H
