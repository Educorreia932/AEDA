#ifndef SUP_SCHOOL_SCHOOL_H
#define SUP_SCHOOL_SCHOOL_H

#include "Client.h"
#include "Material.h"
#include "Teacher.h"
#include "Time.h"

#include <map>

class School {
    friend class Menu;

    public:
        static double goldCardPrice;

        /*! @name Constructors */
        ///@{
        School();
        School(const string& filename);
        ///@}

        void addClient(Client* client);
        int clientIndex(unsigned int id);
        void removeClient(unsigned int id);

        void addActivity(Activity* activity);
        bool isPastActivity(unsigned int id);
        int activityIndex(unsigned int id);

        /*! @name Getters */
        ///@{
        Time getCurrentTime() const;
        vector<Activity*> getPastActivities() const;
        vector<Activity*> getScheduledActivities() const;
        vector<int> getPastActivitiesID() const;
        vector<int> getSheduledActivitiesID() const;
        vector<Teacher *> getTeachers() const;
        vector<Client *> getClients() const;
        ///@}

        /** @name Read Functions
         * This functions from the data files to internal data structures of the program.
         */
        ///@{
        void readClients();
        void readActivities();
        void readTeachers();
        ///@}

        void enroll(const unsigned int clientId, const unsigned int activityId);
        void readClientsActivities(stringstream* activities, Client* c);
        void readTeachersActivities(stringstream* planned_activities, Teacher* t);
        void assign(const unsigned int teacherId, const unsigned int activityId);
        void rent(const unsigned int materialId,const unsigned int clientId, Time startTime, Time endTime);

        /** @name Save Functions
         * This functions save the alterations made to the respective data files.
         */
        ///@{
        void saveClients();
        void saveActivities();
        void saveTeachers();
        ///@}

        void addTeacher(Teacher* teacher);
        int teacherIndex(unsigned int id);
        void removeTeacher(unsigned id);

    private:
        /** @name View Functions
         * This functions display information about the School elements.
         */
        ///@{
        void viewClients(bool detailed = true);
        void viewActivities(bool detailed = true);
        void viewMaterial();
        void viewTeachers(bool detailed = true);
        void viewDates(vector <Time> Dates);
        ///@}

        vector<Time> getDatesFromActivicties(vector <Activity*> Activities);

        friend ostream& operator<<(ostream& out, const School& S);
    private:
        string name;
        unsigned int id;
        Time currentTime;
        map<string, string> Files;
        vector<Client*> Clients;
        vector<Material*> Materials;
        vector<Teacher*> Teachers;
        vector<Activity*> PastActivities;
        vector<Activity*> ScheduledActivities;
};

/*! \cond */

class NonExistentClient : std::exception {
    public:
        unsigned int id;
        NonExistentClient(unsigned int id){this->id = id;};
};

std::ostream & operator <<(std::ostream &out,const NonExistentClient &client);

class NonExistentTeacher : exception {
public:
    unsigned int id;
    NonExistentTeacher(unsigned int id){this->id = id;};
};

ostream & operator <<(std::ostream &out,const NonExistentTeacher &teacher);

class ClientAlreadyExists : exception {
public:
    unsigned int id;
    ClientAlreadyExists(unsigned int id){this->id = id;};
};

ostream & operator <<(std::ostream &out, const ClientAlreadyExists &client);

class TeacherAlreadyExists : exception {
        public:
            unsigned int id;
            TeacherAlreadyExists(unsigned int id){this->id = id;};
};

ostream & operator <<(std::ostream &out, const TeacherAlreadyExists &client);

class NonExistentMaterial : std::exception {
public:
    unsigned int id;
    NonExistentMaterial(unsigned int id){this->id = id;};
};

std::ostream & operator <<(std::ostream &out,const NonExistentMaterial &material);


/*! \endcond */

#endif //SUP_SCHOOL_SCHOOL_H
