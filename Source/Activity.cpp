
#include "../Headers/Activity.h"

using namespace std;

Activity::Activity(Time startTime, Time endTime) {
    this->startTime = startTime;
    this->endTime = endTime;
}

Time Activity::getStartTime() {
    return startTime;
}

Time Activity::getEndTime() {
    return endTime;
}