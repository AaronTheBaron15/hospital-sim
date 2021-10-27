//hospitalSim.h, outline for everything together and running the simulation
//Aaron Borjas, Trenten Nogle, Cassie Esvelt
//12/8/2019
//Rev. Doc. Prof. Bell
//CS273-1 Final project
#ifndef HOSPITALSIM_H
#define HOSPITALSIM_H
#include <vector>
#include "patient.h"
#include <iostream>
#include <queue>

class HospitalSim{
    private:
        int numDoctors; //the number of doctors at the hospital
        int numNurses; //the number of nurses at the hospital
        int patientRate; //the average patient arrival rate per hour
        int minutesOfHour; //Keeps track of how far into each hour simulation is
        std::vector<Patient> residents; //a vector of possible patients ***HAVE NOT ENTERED HOSPITAL YET***
        std::priority_queue<Patient*> waitingRoom; //a priority queue of patient pointers of patients in the waiting room of the ER
    public:
        //fillVec, fills the residents vector
        //inputs - none
        //outputs - fills the residents vector based on the residents.txt file
        void fillVec(); 

        //runSim, runs the simulation
        //inputs - none
        //outputs - runs the simulation for 7 days, 24 hours per day, and 60 minutes per hour
        void runSim();

        //checkArrival, adds a new patient to the waiting room if the current clock tick is evenly divisable by the patientRate
        //inputs - an int to represent the current clock tick in the simulation
        //output - adds a patient to the waiting room and sets the patient's enter time
        void checkArrival(int clockTick);

        //addPatient, adds a patient pointer to the waiting room
        void addPatient(Patient* pat);

        //Prints information about patients that visited the hospital
        void patientMenu();
};


#endif