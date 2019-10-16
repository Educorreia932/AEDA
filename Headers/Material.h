#ifndef SUP_SCHOOL_MATERIAL_H
#define SUP_SCHOOL_MATERIAL_H
#include "Activity.h"
class Material {
    public:
        bool BeingUsed(Time startTime, Time endTime);
    private:
        Activity* activity;
};

class Boat : protected Material {
};

class Suits : protected Material {
};

class Board : protected Material {
};

#endif //SUP_SCHOOL_MATERIAL_H
