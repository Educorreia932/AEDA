#ifndef SUP_SCHOOL_ACTIVITY_H
#define SUP_SCHOOL_ACTIVITY_H

#include "Time.h"
#include <vector>

class Activity {
    protected:
        string name;
        /*! @brief This activity's ID !*/
        unsigned int id;
        /*! @brief Highest ID for any activity currently !*/
        static unsigned int last_id;
        /*! @brief When the activity begins (DD/MM/YY HH:MM) !*/
        Time startTime;
        /*! @brief When the activity ends (DD/MM/YY HH:MM) !*/
        Time endTime;
    public:
        /*! @name Constructors */
        ///@{
        Activity();
        Activity(Time startTime,Time endTime,string name);
        ///@}

        /*! @name Getters */
        ///@{
        Time getStartTime();
        Time getEndTime();
        string getName() const;
        unsigned int getId() const;
        static unsigned int getLastID();
        /*! @returns The type of activity, either Ride (R) or Lesson (L). */
        virtual string getType() const = 0;
        ///@}

        /*! @name Setters */
        ///@{
        void setName(string name);
        void setStartTime(string time);
        void setEndTime(string time);
        void setStartTime(Time time);
        void setEndTime(Time time);
        ///@}

        virtual unsigned int CalcCost() const = 0;
        virtual void print(ostream& out) const = 0;


        friend ostream& operator<<(ostream& out, const Activity& A);
};

ostream& operator<<(ostream& out, const Activity& A);

class Ride : public Activity {
    protected:
        unsigned int cost;
    public:
        /*! @name Constructors */
        ///@{
        /*! Used when adding a new ride.!*/
        Ride(); //DO NOT USE WHEN READING
        /*! Used when reading an activity from a file.!*/
        /*! @param id the ride as stated in the file it's read from.!*/
        Ride(unsigned int id); //For use when reading
    ///@}

        /*! @name Setters */
        ///@{
        void setCost(unsigned int cost);
        ///@}

        /*! @name Getters */
        ///@{
        /*! @returns The total cost of the ride. */
        unsigned int CalcCost() const;
        /*! @returns The type of activity, either Ride (R) or Lesson (L). */
        string getType() const;
        ///@}

        /*! @name Others */
        ///@{
        /*! Used to call operator<< for ride.!*/
        /*! Wihtout it, ostream calls would have a different syntax (Ex: ride << cout instead of cout << ride).!*/
        void print(ostream& out) const;
        /*!Necessary for sorting purposes when saving the activity file.!*/
        bool operator>(Ride b);
        ///@}
};

ostream& operator<<(ostream& out, const Ride& R);

class Lesson : public Activity {
    protected:
    public:
    /*! @name Constructors */
    ///@{
    /*! Used when adding a new lesson.!*/
    Lesson();
    /*! Used when reading an activity from a file.!*/
    /*! @param id the ride as stated in the file it's read from.!*/
    Lesson(unsigned int id);
    Lesson(Time startTime, Time endTime, string name) :  Activity(startTime, endTime, name){};
    ///@}
    /*! @name Getters */
    ///@{
    /*! @returns The total cost of the ride. */
    unsigned int CalcCost() const;
    /*! @returns The type of activity, either Ride (R) or Lesson (L). */
    string getType() const;
    ///@}
    /*! @name Others */
    ///@{
    /*! Used to call operator<< for ride.!*/
    /*! Wihtout it, ostream calls would have a different syntax (Ex: lesson << cout instead of cout << lesson).!*/
    void print(ostream& out) const;
    ///@}
};

class Fixing : public Activity {
protected:
    unsigned int fixid;
    static unsigned int last_fixid;
public:
    Fixing();
    Fixing(unsigned int fixid);
    //Fixing(Time startTime, Time endTime, string name) : Activity(startTime, endTime, name){};
    Fixing(Time startTime, Time endTime, string name);
    unsigned int CalcCost() const;
    string getType() const;
    void print(ostream & out) const;
};

ostream& operator<<(ostream& out, const Lesson& L);

vector<Activity*> eraseAndReturnVectorActivity(vector<Activity*> vec,unsigned int i);

/** @ingroup group_exceptions */

class activityNonExistent : exception {
public:
    unsigned int id;
    activityNonExistent(unsigned int id){id = id;};
};

ostream & operator <<(ostream &out, const activityNonExistent &activity);

#endif //SUP_SCHOOL_ACTIVITY_H
