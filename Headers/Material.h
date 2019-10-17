#ifndef SUP_SCHOOL_MATERIAL_H
#define SUP_SCHOOL_MATERIAL_H
#include "Activity.h"
class Material {
    public:
        bool beingUsed(Time startTime, Time endTime);
    private:
        Activity* activity;
};

class Boat : public Material {
};

class Suits : protected Material {
};

class Board : protected Material {
};

#endif //SUP_SCHOOL_MATERIAL_H
