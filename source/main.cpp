//main.cpp, compiles everything and runs the simulation.
//Aaron Borjas, Trenten Nogle, Cassie Esvelt
//12/8/2019
//Rev. Doc. Prof. Bell
//CS273-1 Final project
#include "../headers/hospitalSim.h"
#include <iostream>
#include <cstdlib>
#include <ctime>


int main(){
    srand(time(NULL)); //generating the seed for rand
    
    HospitalSim sim; //create a new HospitalSim object called sim
    
    sim.fillVec(); //fill a vector of residents of the town the hospital is in
    
    sim.runSim(); //run the simulation

}