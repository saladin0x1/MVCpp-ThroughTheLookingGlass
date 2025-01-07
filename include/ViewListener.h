// include/ViewListener.h
#pragma once
#include <string> // Include for string parameters

class ViewListener {
public:
    virtual void userEnterAddStudent(const std::string& name, const std::string& familyName, int matriculationID) = 0;
    virtual void userEnterShowStudents() = 0;

};