#include "../include/View.h"
#include <iostream>

void View::setListener(ViewListener* listener) {
    this->listener = listener;
}

void View::printStudents(const std::vector<Model::Student>& students) {
    for (const auto& student : students) {
        std::cout << "Name: " << student.name << ", Family Name: " << student.familyName << ", Matriculation ID: " << student.matriculationID << std::endl;
    }
}

void View::run() {
    // Example implementation of run method
    std::string name, familyName;
    int matriculationID;

    std::cout << "Enter student name: ";
    std::cin >> name;
    std::cout << "Enter student family name: ";
    std::cin >> familyName;
    std::cout << "Enter student matriculation ID: ";
    std::cin >> matriculationID;

    if (listener) {
        listener->userEnterAddStudent(name, familyName, matriculationID);
    }

    if (listener) {
        listener->userEnterShowStudents();
    }
}