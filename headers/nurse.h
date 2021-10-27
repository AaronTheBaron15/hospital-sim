//nurse.h, child class of caregiver
//Aaron Borjas, Trenten Nogle, Cassie Esvelt
//12/8/2019
//Rev. Doc. Prof. Bell
//CS273-1 Final project
#ifndef NURSE_H
#define NURSE_H
#include "caregiver.h"
#include <iostream>

class Nurse : public CareGiver{
    public:
        Nurse(){
            isAvailable = true; //sets isAvailable to true
        }

        //MTB changed the prototype to deal with the const problem
        //void treatPatient(const Patient p, int clockTime){
        void treatPatient(Patient* &p, int clockTime) {
            std::cout << "A nurse is treating " << p->getName() << std::endl; //says who the doctor is treating
            isAvailable = false; //sets availability to false
            treatTime = (rand()%10) + 1; //sets treatTime to a random number between 1 and 20
            int visitTime = clockTime - p->getEnterTime() + treatTime; //set the visit time to  the clock time minus the time the patient entered the hospital, plus the treatTime
            
            //Added to see if we can now change the patient
            p->setVisitTime(visitTime); //sets the patients visit time
        }

         void decrementTime(){
            treatTime--; //decrement treat time of the patient
        }

        int getTreatTime(){
            return treatTime; //return the time to treat the patient
        }

        void done(){
            std::cout << "Nurse is done with a patient." << std::endl; //says that the nurse is done with a patient
            isAvailable = true; //sets the availability of the nurse to true
        }

        int checkType() const{
            return 1; //returns the "nurse" type
        }
};



#endif