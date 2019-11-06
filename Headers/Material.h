#ifndef SUP_SCHOOL_MATERIAL_H
#define SUP_SCHOOL_MATERIAL_H
#include "Activity.h"
#include <string>
#include <vector>

class Material {
    public:
        bool beingUsed(Time startTime, Time endTime);
        string getObjectType() const;
        vector<Activity*> getActivities() const;
    private:
        string objectType;
        vector<Activity*> activities;

        friend ostream &operator<<(ostream out, Material material);
};

class Boat : public Material {
};

class Suits : public Material {
};

class Board : public Material {
};

#endif //SUP_SCHOOL_MATERIAL_H
