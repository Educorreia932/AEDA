#ifndef SUP_SCHOOL_MATERIAL_H
#define SUP_SCHOOL_MATERIAL_H
#include "Activity.h"
#include <string>
#include <vector>

class Material {
public:
    //Miscellaneous
    bool beingUsed(Time startTime, Time endTime);
    string getObjectType() const;

    //Setter functions
    void setID(int ID);
    void setType(string type);
    static void setLastID(const unsigned int id);
    static void setCapacity(unsigned int capac);


    //Getter functions
    unsigned int getID() const;
    string getType() const;
    static unsigned int getLastID();
    vector<Activity*> getActivities() const;
    static unsigned int getCapacity();
private:
    string type;  //The type of material
    vector<Activity*> activities;
    unsigned int ID;
    static unsigned int last_id;

    static unsigned int capacity;

    friend ostream &operator<<(ostream out, Material material);
};

class Boat : public Material {
};

class Suits : public Material {
};

class Board : public Material {
};

class ImpossibleTimeDifference: std::exception{
    Time startTime;
    Time endTime;
public:
    ImpossibleTimeDifference(Time startTime, Time endTime){
        this->startTime = startTime;
        this->endTime = endTime;
    }
    Time getStartTime() const{
        return startTime;
    }
    Time getEndTime() const{
        return endTime;
    }
};

#endif //SUP_SCHOOL_MATERIAL_H
