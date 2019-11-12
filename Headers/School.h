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
        //Constructors
        School();
        School(const string& filename);

        void addClient(Client* client);
        int clientIndex(unsigned int id);
        void removeClient(unsigned int id);

        void addActivity(Activity* activity);

        //Getters
        vector<Activity*> getActivities() const;
        vector<Teacher *> getTeachers() const;
        //Read-Functions
        void readClients();
        void readActivities();
        void readTeachers();
        void enroll(const unsigned int clientId, const unsigned int activityId);
        void readClientsActivities(stringstream* planned_activities, Client* c);
        void readTeachersActivities(stringstream* planned_activities, Teacher* t);
        void assign(const unsigned int teacherId, const unsigned int activityId);
        void saveClients();
        void saveActivities();
        void saveTeachers();

        void addTeacher(Teacher* teacher);
        int teacherIndex(unsigned int id);

    private:
        // View Functions ← Display detailed information
        void viewClients(bool detailed = true);
        void viewActivities();
        void viewMaterial();
        void viewTeachers(bool detailed = true);
        vector<Time> getDatesFromActivicties(vector <Activity*> Activities);
        void viewDates(vector <Time> Dates);

        friend ostream& operator<<(ostream& out, const School& S);
    private:
        string name;
        unsigned int id;
        Time currentTime;
        map<string, string> Files;
        vector<Client*> Clients;
        vector<Material*> Materials;
        vector<Teacher*> Teachers;
        vector<Activity*> Activities;
        vector<Activity*> PastActivities;
        vector<Activity*> ScheduledActivities;
};

//Exceptions

class NonExistantClient : std::exception {
    public:
        unsigned int id;
        NonExistantClient(unsigned int id){this->id = id;};
};

std::ostream & operator <<(std::ostream &out,const NonExistantClient &client);

class NonExistantTeacher : std::exception {
public:
    unsigned int id;
    NonExistantTeacher(unsigned int id){this->id = id;};
};

std::ostream & operator <<(std::ostream &out,const NonExistantTeacher &teacher);

class ClientAlreadyExists : std::exception {
public:
    unsigned int id;
    ClientAlreadyExists(unsigned int id){this->id = id;};
};

std::ostream & operator <<(std::ostream &out, const ClientAlreadyExists &client);

class TeacherAlreadyExists : std::exception {
public:
    unsigned int id;
    TeacherAlreadyExists(unsigned int id){this->id = id;};
};

std::ostream & operator <<(std::ostream &out, const TeacherAlreadyExists &client);



#endif //SUP_SCHOOL_SCHOOL_H
