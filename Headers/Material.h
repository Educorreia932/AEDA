#ifndef SUP_SCHOOL_MATERIAL_H
#define SUP_SCHOOL_MATERIAL_H
#include "Activity.h"
#include "Client.h"
#include <string>
#include <vector>
#include "map"

class Material {
public:
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
private:
    string type;  //The type of material
    vector<Activity*> Activities;
    vector<Client*> Clients;
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


/*! \endcond */

#endif //SUP_SCHOOL_MATERIAL_H
