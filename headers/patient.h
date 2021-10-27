//patient.h, the outline of a patient in the ER from entrance time to the time they leave
//Aaron Borjas, Trenten Nogle, Cassie Esvelt
//12/8/2019
//Rev. Doc. Prof. Bell
//CS273-1 Final project
#ifndef PATIENT_H
#define PATIENT_H
#include <string>
#include <iostream>
#include <vector>


class Patient{
    private:
        std::string name; //the name of the patient
        std::vector<int> severityVec; //a vector different severities of the patient (per visit)
        int enterTime; //the time the patient entered the hospital
        int visitTime; //the total visit time of the patient
        bool treated = false;
    public:
        //default constructor for patient
        Patient();

        //constructor for patient
        //inputs - takes in a string for the patient's name
        //outputs - sets the patients name to the input name
        Patient(std::string n){name = n;}

        //getName, returns the name of the patient
        //inputs - none
        //outputs - returns the patient's name
        std::string getName() const;

        //addVisit, adds a visit with a set severity to the severityVector
        //input - an int for the severity of the new visit
        //output - adds the new severity to the severityVec
        void addVisit(int severity);

        int getVisitTime() {
            return visitTime;
        }

        //operator overload for the < operator, compares two patients based on their severity
        //input - another const patient reference
        //output - a bool value for if *this* patient is less than the input patient or not
        bool operator<(const Patient & p) const;

        //getCurSeverity, gets the current severity of the patient (the most recent severity)
        //input - none
        //output - returns an int for the current or most recent severity of a patient
        int getCurSeverity() const;

        //setEnterTime, sets a new enter time of the ER for the patient 
        //input - an int for the enter time, should be a simulated clock tick
        //output - sets the enter time of the patient
        void setEnterTime(int enter){
            enterTime = enter; //sets the enter time of the patient to the input enter time
        }

        //getEnterTime, gets the time the patient entered the ER
        //input - none
        //output - returns the time the patient entered the ER
        int getEnterTime() const{
            return enterTime; //returns the enter time of the patient
        }

        //setVisitTime, sets the total time the patient was in the hospital, from wait time to the time they left
        //input - an int for the total time IN MINUTES the patient spent in the hospital
        //output - changes the visit time of the patient
        void setVisitTime(int vt){
            visitTime = vt; //sets the visitTime of the patient to vt
        }

        //Get method for treated
        bool isTreated() {
            return treated;
        }

        //Sets treated to true
        void setTreated() {
            treated = true;
        }

        //Get method for number of visits
        int getNumVisits(){
            return severityVec.size();
        }

        //Prints severity of visits for patient
        void printVisits(){
            for(int i = 0; i < severityVec.size(); i++){
                if(i == severityVec.size()-1) { //Doesn't put a comma after last severity
                    std::cout << severityVec[i] << std::endl;
                }
                else {
                    std::cout << severityVec[i] << ", ";
                }
            }
        }
};

#endif