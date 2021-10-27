//caregiver.h, parent class for doctor and nurse
//Aaron Borjas, Trenten Nogle, Cassie Esvelt
//12/8/2019
//Rev. Doc. Prof. Bell
//CS273-1 Final project
#ifndef CAREGIVER_H
#define CAREGIVER_H
#include "patient.h"
#include <cstdlib>
#include <ctime>


class CareGiver{
    protected:
        bool isAvailable; //if the caregiver is currently treated a patient or not
        int treatTime; //the time it takes the caregiver to treat the patient
    public:
        //MTB changed the prototype to get around the const problem
        //virtual void treatPatient(const Patient p, int clockTime) = 0;
        //treatPatient, a function that treats the patient
        //inputs - a pointer to a patient and an int for the time that the patient begun treatment
        //outputs - sets the amount of time it takes for the caregiver to treat the patient, makes the caregiver unavailable
        virtual void treatPatient(Patient* &p, int clockTime) = 0;

        //done, a function to run once the patient is done being treated
        //inputs - none
        //output - says that the patient is done being treated, makes the caregiver available
        virtual void done() = 0;

        //checkAvailablity, checks if the caregiver is currently treating a patient
        //no inputs
        //outputs - returns true or false based on if the caregiver is available
        bool checkAvailability(){
            return isAvailable;
        }
        //decrementTime, decrements the total time taken to treat the patient
        //inputs - none
        //output - none, but decrements the time taken to treat the patient
        virtual void decrementTime() = 0;
        
        //getTreatTime, gets the total time to treat the patient
        //input - none
        //output - returns the time to treat the patient
        virtual int getTreatTime() = 0;

        //checkType, checks what type of caregiver the caregiver is
        //inputs - none
        //output - returns an int based on what type of caregiver the object is (doctor or nurse)  
        virtual int checkType() const = 0;
};

#endif