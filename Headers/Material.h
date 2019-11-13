#ifndef SUP_SCHOOL_MATERIAL_H
#define SUP_SCHOOL_MATERIAL_H
#include "Activity.h"
#include "Client.h"
#include <string>
#include <vector>
#include "map"

class Material {
    friend class School;

public:

    Material();
    //Miscellaneous
    bool beingUsed(Time startTime, Time endTime);
    string getObjectType() const;

    //Setter functions
    void setID(int ID);
    void setType(string type);
    static void setLastID(const unsigned int id);
    static void setCapacity(unsigned int capacity);

    //Getter functions
    unsigned int getID() const;
    string getType() const;
    static unsigned int getLastID();
    vector<Activity*> getActivities() const;
    unsigned int getCapacity();
    map<Client* ,vector<Time>>* getClients();

private:
    string type;  //The type of material
    vector<Activity*> Activities;
    map<Client* ,vector<Time>> Clients;
    unsigned int ID;
    unsigned int capacity;
    static unsigned int last_id;

    friend ostream &operator<<(ostream out, Material material);
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

class alreadyInUse : std::exception {
public:
    unsigned int materialId;
    Time startTime;
    Time endTime;
    alreadyInUse(unsigned materialId, Time startTime, Time endTime){this->materialId = materialId; this->startTime = startTime;this->endTime = endTime;};
};

std::ostream & operator <<(std::ostream &out,const alreadyInUse &info);


/*! \endcond */

#endif //SUP_SCHOOL_MATERIAL_H
