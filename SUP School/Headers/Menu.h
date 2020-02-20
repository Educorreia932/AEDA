#ifndef SUP_SCHOOL_MENU_H
#define SUP_SCHOOL_MENU_H

#include "Schedule.h"
#include "School.h"

#include <set>

/** @defgroup group_menu Menu */

/** @ingroup group_menu */

class Menu {
    public:
        /** @name Constructors */
        ///@{
        Menu();
        Menu(School* SUPSchool);
        ///@}

        static int showMainMenu();
        void mainMenuSelection(int selected);

        /** @name Auxiliary */
        ///@{
        static void clearScreen();
        static void pause();
        ///@}

        static School* chooseSchool(set<School*> &Schools); //static
private:
        School* SUPSchool;

        /** @name Client related */
        ///@{
        static int showManageClients();
        void manageClientsSelection(int selected);
        void createClient();
        void changeClient(int client_id);
        void monthlyReport(Client* C);
        ///@}

        /** @name Activity related */
        ///@{
        static int showManageActivities();
        void manageActivitiesSelection(int selected);
        void createActivity();
        void removeActivity();
        void changeActivity();
        ///@}

        //Fixes section
        static int showManageFixes();
        void manageFixesSelection(int selected);
        void createFixing();
        void removeFixing();

        // Teacher related
        static int showManageTeachers();
        void manageTeachersSelection(int selected);
        void createTeacher();
        void changeTeachers(int teacherId);

        //Material relateed
        void createMaterial();
        int showManageMaterials();
        void manageMaterialsSelection(int selected);
        void rentMaterial();

        // Schedule related
        static int showConsultSchedule();
        void consultScheduleSelection(int selected);
};

/** @defgroup group_exceptions Exceptions */

/** @ingroup group_exceptions */

class ImproperString : exception{
        string msg;
    public:
        ImproperString(std::string msg){this->msg = msg;}
        string getMsg() const{return msg;}
};

class IdAlreadyExists : exception{
    public:
        IdAlreadyExists(){};
};

class InvalidActivity{
    private:
        string msg;
    public:
        InvalidActivity(string msg){
            this->msg = msg;
        }
        string getMsg() const{return msg;}
};


#endif //SUP_SCHOOL_MENU_H
