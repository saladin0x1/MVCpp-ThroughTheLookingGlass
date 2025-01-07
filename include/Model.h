#pragma once
#include <string>
#include <vector>

class Model {  // Model class declaration comes first
public:
    struct Student { // Student struct is a private nested type.  
        std::string name;
        std::string familyName;
        int matriculationID;
    };

    std::vector<Student> students;

public:

    void addStudent(const std::string& name, const std::string& familyName, int matriculationID);
    std::vector<Student> getStudents() const;

  
};