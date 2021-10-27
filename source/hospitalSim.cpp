//hospitalSim.cpp, the implementation of the hospital simulation
//Aaron Borjas, Trenten Nogle, Cassie Esvelt
//12/8/2019
//Rev. Doc. Prof. Bell
//CS273-1 Final project
#include "../headers/hospitalSim.h"
#include "../headers/caregiver.h"
#include "../headers/doctor.h"
#include "../headers/nurse.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <set>


void HospitalSim::fillVec(){
    std::ifstream file; //create an ifstream variable called file
    file.open("C:/Users/aborjas22/Desktop/FinalProject/data/residents.txt"); //open the file at this filepath
    
    std::string name; //creates a new string called name, for holding the current line's name
   
    while(!file.eof()){ //while the file is not over
    
        getline(file,name); //get the current line of the file and set name to be equal to it
        Patient * p = new Patient(name); //create a new patient pointer on the heap of a patient with the name at the current line
        residents.push_back(*p); //push the new patient to the back of the residents vector
    }
    file.close(); //close the file
}

void HospitalSim::addPatient(Patient* pat){
    
    int determineSeverity = (rand() % 10) + 1; //helps determine severity of the patient
    int severity; //the actual severity of the patient
    if(determineSeverity <= 7){ //if determine severity is lessthan or equal to 7
        severity = (rand() % 10) + 1; //set severity to a random number from 1-10
    }
    if(determineSeverity == 8 || determineSeverity == 9){ //if determine severity is 8 or 9
        severity = (rand() % 5) + 11; //set severity to a random number between 11 and 15
    }
    if(determineSeverity == 10){ //if determineSeverity is equal to 10
        severity = (rand() % 5) + 15; //set severity to a random number from 16-20
    }
    
    pat->addVisit(severity); //add a new visit (severity) to the patient pointer
    
    waitingRoom.push(pat); //push the patient pointer to the waiting room
    //say the patient has entered the hospital with a certain severity
    std::cout << pat->getName() << " has entered the Hospital. Severity: " << pat->getCurSeverity() << std::endl;

    pat->setTreated();//set treated bool to true, the patient visited the hospital

}

void HospitalSim::checkArrival(int clockTick){
    Patient* pat = &residents[rand() % 2000]; //create a patient pointer based on a random resident
        if(clockTick % 60 == 0){ //New hour starts
            minutesOfHour = 0;
        }
        else{
            minutesOfHour++;
        }
        if(minutesOfHour < patientRate){//add a new pateint every minute while it is less than the pateint Rate
            addPatient(pat); //add the patient pat to the waitingRoom
            (pat)->setEnterTime(clockTick); //record the clockTick the patient enterd at
        }
    
        
}

void HospitalSim::patientMenu() {//End of Simulation Report Menu
    std::vector<Patient> treated;//vector of the patients that were treated
    for(int i = 0; i < residents.size(); i++) {
        if(residents[i].isTreated()) {//fills the treated vector with patients that were treated. calls patient's isTreated() method
            std::cout << residents[i].getName() << std::endl;
            treated.push_back(residents[i]);
        }
    }

    long double total = 0;//the total visit time for all patients
    for(int i = 0; i < treated.size(); i++) {
        total+=treated[i].getVisitTime();//each treated patient's visit time is added to total
    }
    std::cout << "total visit times for all " << treated.size() << " patients: " << total << std::endl;
    long double average = total/treated.size();

    std::cout << "The average visit time all patients was: " << average << " minutes" << std::endl;//prints average visit time for all patients
    
    std::string name;

    while(name != "exit"){//if name equals exit, close program
        std::cout << "Enter a patient you'd like to retrieve the record of: (Enter \"exit\" to exit): ";
        std::cin >> name;

        for(int i = 0; i < treated.size(); i++){//gets the record of the patient who's name was entered
            if(name == treated[i].getName()){
                std::cout << name << "'s record: " << std::endl;
                std::cout << "Number of visits: " << treated[i].getNumVisits() << std::endl;
                std::cout << "Severity of illness on each visit: ";
                treated[i].printVisits();
                std::cout << "Visit time: " << treated[i].getVisitTime() << std::endl;
                
            }
        }
    }
}

void HospitalSim::runSim(){

    std::cout << "Input Patient Arrival Rate:\n"; //tells user what to input
    std::cin >> patientRate; //gets user input for hourly patient rate
    std::cout << "\nInput number of Doctors:\n"; //tells user what to input
    std::cin >> numDoctors; //gets user input for number of doctors
    std::cout << "\nInput number of Nurses:\n"; //tells user what to input
    std::cin >> numNurses; //gets user input for number of doctors

    std::set<CareGiver*> staff; //creates a set of CareGiver pointers called staff
    for(int i = 0; i < numNurses; i++) { //create a certian number of new nurses based on user input
        CareGiver* nurse = new Nurse();//create a caregiver pointer called doc and point it to a new nurse object
        staff.insert(nurse);//insert the new nurse to the staff set
    }

    for(int i = 0; i < numDoctors; i++) { //creates a certain number of new doctors based on user input
        CareGiver* doc = new Doctor(); //create a caregiver pointer called doc and point it to a new Doctor object
        staff.insert(doc); //insert the new doctor to the staff set
    }
    std::cout << "staff size: " << staff.size() << std::endl;

    //**THE SIMULATION**
    for(int clock = 1; clock <= 10080; clock++){ //CHANGE 60 To 10080 or whatever 7*24*60 is
        checkArrival(clock); //call check arrival based on the current clock tick (can add new patient)
        std::set<CareGiver*>::iterator it = staff.begin(); //create an iterator for the staff set, set it equal to staff.begin()

        while(it != staff.end()) { //while it is not equal to staff.end()

            if((*it)->checkAvailability()) { //checks the current staff's availability

                if(!waitingRoom.empty()) {
                    Patient* temp = waitingRoom.top(); //creates a temp patient pointer to waitingRoom.top()

                    if( ((*it)->checkType() == 1) && (temp->getCurSeverity()) <= 10) { //if the current staff is a nurse and the severity is <= 10
                                              
                        (*it)->treatPatient(temp, clock); //treat the top patient
                        waitingRoom.pop(); //pop the top patient
                        
                    }
                    else if((*it)->checkType() == 2) { //if the current staff is a doctor
                        
                        (*it)->treatPatient(temp, clock); //treat the top patient
                        waitingRoom.pop(); //pop the top patient
                        
                    }
                }
            }
            ++it; //increment the iterator to find another available caregiver
        }

        //CHANGING AVAILABILITY AND TIME TO TREAT THE PATIENTS BY DOCTORS/NURSES
        it = staff.begin(); //set it back to staff.begin
        while(it != staff.end()){ //while it is not equal to staff.end()
            
            if(!(*it)->checkAvailability()){ //if the doc/nurse at it is not available
            
                (*it)->decrementTime(); //decrement the doctor/nurses time to treat
            
                if((*it)->getTreatTime() == 0){ //if the doc/nurses time to treat is 0
                    
                    (*it)->done(); //the doc/nurse is done treating the patient
                    
                }
            }
            
            ++it; //increment it
        }
        
    }

    //calculate average visit time

    patientMenu();
}