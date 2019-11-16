#ifndef SUP_SCHOOL_MATERIAL_H
#define SUP_SCHOOL_MATERIAL_H

#include "Activity.h"
#include "Client.h"
#include <string>
#include <vector>
#include "map"

/*! @brief School's aquatic material, such as Suits, Boats and Boards. Available for the clients to rent or to be used in the school's activities */

class Material {
    friend class School;
public:
    Material();
    //Miscellaneous
    bool beingUsed(Time startTime, Time endTime);
    void addActivity(Activity* activity);


    /*! @name Getters */
    ///@{
    unsigned int getID() const;
    string getType() const;
    static unsigned int getLastID();
    vector<Activity*> getActivities() const;
    string getActivitiesID() const;
    map<Client*,vector<Time>>* getClients();
    ///@}

    /*! @name Setters */
    ///@{
    void setID(int ID);
    void setType(string type);
    static void setLastID(const unsigned int id);
    void setActivities(vector <Activity*> activities);
    void setClients(map<Client*,vector<Time>> clients);
    ///@}
private:
    string type;  //The type of material
    vector<Activity*> Activities;
    map<Client* ,vector<Time>> Clients;
    unsigned int ID;
    static unsigned int last_id;

    friend ostream &operator<<(ostream &out, Material material);
};

class Boat : public Material {
public:
    static double cost;
};

class Suits : public Material {
public:
    static double cost;
};

class Board : public Material {
public:
    static double cost;
};

/*! \cond */

class alreadyInUse : std::exception {
public:
    unsigned int materialId;
    Time startTime;
    Time endTime;
    alreadyInUse(unsigned materialId, Time startTime, Time endTime){this->materialId = materialId; this->startTime = startTime;this->endTime = endTime;};
};

std::ostream & operator <<(std::ostream &out,const alreadyInUse &info);

class materialAlreadyHasActivity : std::exception {
public:
    unsigned materialId;
    unsigned int activityId;
    materialAlreadyHasActivity(unsigned int materialId,unsigned int activityId){this->materialId = materialId;this->activityId = activityId;};
};

ostream & operator <<(std::ostream &out,const materialAlreadyHasActivity &ids);

/*! \endcond */

#endif //SUP_SCHOOL_MATERIAL_H
