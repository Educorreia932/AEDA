#ifndef SUP_SCHOOL_STAFF_H
#define SUP_SCHOOL_STAFF_H

#include "Activity.h"

#include <vector>

class Staff {
    public:
        Staff();
    private:
        string name;
        static unsigned int id;
};

class Teacher : public Staff {
    public:
        Teacher();
    private:
        vector<Lesson *> Lessons;
};

class Employees : public Staff {

};

#endif //SUP_SCHOOL_STAFF_H
