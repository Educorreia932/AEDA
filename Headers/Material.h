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
    string getObjectType() const;
    void addActivity(Activity* activity);

    //Setter functions
    void setID(int ID);
    void setType(string type);
    static void setLastID(const unsigned int id);
    static void setCapacity(unsigned int capacity);
    void setActivities(vector<Activity *> activities);

    //Getter functions
    unsigned int getID() const;
    string getType() const;
    static unsigned int getLastID();
    vector<Activity*> getActivities() const;
    string getActivitiesID() const;
    unsigned int getCapacity();
    map<Client* ,vector<Time>>* getClients();
    ///@}
private:
    string type;  //The type of material
    vector<Activity*> Activities;
    map<Client* ,vector<Time>> Clients;
    unsigned int ID;
    unsigned int capacity;
    static unsigned int last_id;

    friend ostream &operator<<(ostream &out, Material material);
};

class Boat : public Material {
public:
    static unsigned int maxCapacity;
};

class Suits : public Material {
public:
    static unsigned int maxCapacity;
};

class Board : public Material {
public:
    static unsigned int maxCapacity;
};

/** @ingroup group_exceptions */

class alreadyInUse : exception {
public:
    unsigned int materialId;
    Time startTime;
    Time endTime;
    alreadyInUse(unsigned materialId, Time startTime, Time endTime){this->materialId = materialId; this->startTime = startTime;this->endTime = endTime;};
};

ostream & operator <<(ostream &out, const alreadyInUse &info);

class materialAlreadyHasActivity : std::exception {
public:
    unsigned materialId;
    unsigned int activityId;
    materialAlreadyHasActivity(unsigned int materialId,unsigned int activityId){this->materialId = materialId;this->activityId = activityId;};
};

ostream & operator <<(ostream &out, const materialAlreadyHasActivity &ids);

#endif //SUP_SCHOOL_MATERIAL_H
