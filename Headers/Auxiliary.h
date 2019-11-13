#ifndef SUP_SCHOOL_AUXILIARY_H
#define SUP_SCHOOL_AUXILIARY_H

#include "Activity.h"

#include <vector>

using namespace std;

int readOption(int min, unsigned int max);
double readOption(double min, double max);
bool stob(const string &s);
string btos(const bool &b);
string centerString(int width, const string& s);

//template <class T>
//vector<T*> eraseAndReturnVector(vector<T*> vec,unsigned int i); //Calls std::erase for vector, but returns the vector without the element instead of just the element

#endif //SUP_SCHOOL_AUXILIARY_H
