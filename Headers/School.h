#ifndef SUP_SCHOOL_SCHOOL_H
#define SUP_SCHOOL_SCHOOL_H

#include "Client.h"
#include "Material.h"
#include "Teacher.h"
#include "Time.h"

#include <algorithm>
#include <map>

/** @defgroup group_school School */

/** @ingroup group_school */

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

        void addActivity(Activity* activity, bool past);
        int activityIndex(unsigned int id, bool past);

        int materialIndex(unsigned int id);
        void removeMaterial(unsigned int id);

        /*! @name Getters */
        ///@{
        Activity* getActivity(unsigned int id) const;
        vector<Client *> getClients() const;
        vector<Material *> getMaterials() const;
        ///@}

        /** @name Read Functions
         * This functions read from the data files to internal data structures of the program.
         */
        ///@{
        void readClients();
        void readActivities();
        void readTeachers();
        void readMaterials();
        ///@}

        /** @brief Enrolls a client with clientId on an activity with activityId. */
        /** @throws NonExistentClient The client does not exist in the School.*/
        /** @throws clientAlreadHasActivity The client already is enrolled in that activity */
        void enroll(const unsigned int clientId, const unsigned int activityId);
        void readClientsActivities(stringstream* activities, Client* c);
        void readTeachersActivities(stringstream* planned_activities, Teacher* t);
        void readMaterialActivities(stringstream* activities, Material* m);
        /** @brief Assigns a designated activity to a teacher. */
        void assign(const unsigned int teacherId, const unsigned int activityId);
        void rent(const unsigned int materialId,const unsigned int clientId, Time startTime, Time endTime);

        /** @name Save Functions
         * This functions save the alterations made to the respective data files.
         */
        ///@{
        void saveClients();
        void saveActivities();
        void saveTeachers();
        void saveMaterials();
        ///@}

        void addTeacher(Teacher* teacher);
        int teacherIndex(unsigned int id);
        void removeTeacher(unsigned id);

    private:
        /** @name View Functions
         * This functions display information about the School elements.
         */
        ///@{
        /**
        * @param detailed States whether the output includes all of the information about the activities or only the strictly necessary to distinguish them (mainly used
        * in selection menus).
        */
        void viewActivities(bool detailed = true);
        /**
         * @param detailed States whether the output includes all of the information about the clients or only the strictly necessary to distinguish them (mainly used
         * in selection menus).
         */
        void viewClients(bool detailed = true);
        /**
         * @param detailed States whether the output includes all of the information about the material or only the strictly necessary to distinguish them (mainly used
         * in selection menus).
         */
        void viewMaterial(bool detailed = true);
        /**
         * @param detailed States whether the output includes all of the information about the teachers or only the strictly necessary to distinguish them (mainly used
         * in selection menus).
         */
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

/** @ingroup group_exceptions */

class NonExistentClient : exception {
    public:
        unsigned int id;
        NonExistentClient(unsigned int id){this->id = id;};
};

std::ostream & operator <<(ostream &out,const NonExistentClient &client);

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

class NonExistentMaterial : exception {
public:
    unsigned int id;
    NonExistentMaterial(unsigned int id){this->id = id;};
};

ostream & operator <<(ostream &out,const NonExistentMaterial &material);

#endif //SUP_SCHOOL_SCHOOL_H
