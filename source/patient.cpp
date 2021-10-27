//patient.cpp, implements the patient class
//Aaron Borjas, Trenten Nogle, Cassie Esvelt
//12/8/2019
//Rev. Doc. Prof. Bell
//CS273-1 Final project
#include "../headers/patient.h"

int Patient::getCurSeverity() const {
    return severityVec.back(); //return the last item in the severityVec (the most recent/current severity)
}

bool Patient::operator<(const Patient & p) const {
    return (this->getCurSeverity() < p.getCurSeverity());//return true if the severity of *this* is less than the severity of p
}

std::string Patient::getName() const{
    return name; //return the name of the patient
}

void Patient::addVisit(int severity){
    severityVec.push_back(severity); //add a new severity to the severityVec, indicating a new visit.
}

