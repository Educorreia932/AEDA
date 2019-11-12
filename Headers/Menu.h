#ifndef SUP_SCHOOL_MENU_H
#define SUP_SCHOOL_MENU_H

#include "Schedule.h"
#include "School.h"

class Menu {
    public:
        //Constructors
        Menu(School* SUPSchool);

        static int showMainMenu();
        void mainMenuSelection(int selected);

        //Utils
        static void clearScreen();
        static void pause();
    private:
        School* SUPSchool;

        // Client related        
        static int showManageClients();
        void manageClientsSelection(int selected);
        void createClient();
        void changeClient(int client_id);

        //Activity related
        static int showManageActivities();
        void manageActivitiesSelection(int selected);
        void createActivity();
        void removeActivity();

        // Teacher related
        static int showManageTeachers();
        void manageTeachersSelection(int selected);
        void createTeacher();
        void changeTeachers(int teacherId);
        
        // Schedule related
        static int showConsultSchedule();
        void consultScheduleSelection(int selected);
};


//Exceptions

class ImproperString: std::exception{
    std::string msg;
public:
    ImproperString(std::string msg){this->msg = msg;}
    std::string getMsg() const{return msg;}
};

class IdAlreadyExists: std::exception{
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
