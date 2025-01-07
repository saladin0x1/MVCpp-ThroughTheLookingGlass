#include "../include/Model.h"

// Add a new student to the list
void Model::addStudent(const std::string& name, const std::string& familyName, int matriculationID) {
    Student newStudent = {name, familyName, matriculationID};
    students.push_back(newStudent);
}

// Get the list of students
std::vector<Model::Student> Model::getStudents() const {
    return students;
}