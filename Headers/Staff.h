#ifndef SUP_SCHOOL_STAFF_H
#define SUP_SCHOOL_STAFF_H

#include "Activity.h"

#include <vector>

class Staff {
    public:
        Staff();
        Staff(string name);

    protected:
        string name;
        unsigned int id;
        static unsigned int last_id;
};

class Teacher : public Staff {
    public:
        Teacher();
        Teacher(string name);

        friend ostream& operator<<(ostream& out, const Teacher& C);
    private:
        vector<Activity *> Activities;


};

class Employees : public Staff {

};

#endif //SUP_SCHOOL_STAFF_H
