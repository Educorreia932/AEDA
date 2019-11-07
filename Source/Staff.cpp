#include "../Headers/Staff.h"

Staff::Staff() {
    this->id = Staff::id++;
}

Staff::Staff(string name){
    this->id = Staff::id++;
    this->name = name;

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

