#ifndef SUP_SCHOOL_ACTIVITY_H
#define SUP_SCHOOL_ACTIVITY_H

class Activity {
};

class Ride : protected Activity {
};

class Lesson : protected Activity {
};

class StandUpPaddle : protected Lesson {
};

class Surf : protected Lesson {
};

class Windsurf : protected Lesson {
};

#endif //SUP_SCHOOL_ACTIVITY_H
