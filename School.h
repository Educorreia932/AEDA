#ifndef SUP_SCHOOL_SCHOOL_H
#define SUP_SCHOOL_SCHOOL_H

#include "Activity.h"
#include "Client.h"
#include "Material.h"
#include "Staff.h"

#include <vector>

class School {
    private:
        vector<Client> Clients;
    public:
        School();
};

#endif //SUP_SCHOOL_SCHOOL_H
