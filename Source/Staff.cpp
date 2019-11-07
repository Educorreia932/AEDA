#include "../Headers/Staff.h"

unsigned int Staff::last_id = 0;

Staff::Staff() {
}

Staff::Staff(string name){
    this->id = last_id+1;
    this->name = name;
    last_id++;
}

Teacher::Teacher() : Staff() {
    Activities = {};
}

Teacher::Teacher(string name) : Staff(name) {
    Activities = {};

}

ostream &operator<<(ostream &out, const Teacher &T) {
    cout << "Type: Teacher" << endl;
    cout << "ID: " << T.id << endl;
    cout << "Name: " << T.name << endl;

    if(T.Activities.size() == 0)
        cout << "No activities associated" << endl;
    else {
        cout << "Associated activities:" << endl;
        cout << "----------------------" << endl;
        for(const auto &ac: T.Activities){

            cout << ac;
            cout << "----------------------" << endl;
        }
    }

    return out;
}

