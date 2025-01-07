#include <mysqlx/xdevapi.h> 
#include <iostream>
#include "../include/Controller.h"

// Function to test database connection
bool isDatabaseAvailable() {
    try {
        mysqlx::Session session("localhost", 33060, "root", "password");
        return true; // Connection successful
    } catch (const mysqlx::Error& err) {
        return false; // Connection failed
    } catch (...) {
        return false; // Connection failed
    }
}


void Controller::userEnterAddStudent(const std::string& name, const std::string& familyName, int matriculationID) {
    if (!isDatabaseAvailable()) {
        std::cerr << "Error: Database is not available. Exiting.\n";
        exit(1); // Or handle the error differently, like returning an error code.
    }

    model->addStudent(name, familyName, matriculationID);
    updateDatabaseForStudents();
    std::cout << "Student added.\n";
}

void Controller::userEnterShowStudents() {
    if (!isDatabaseAvailable()) {
        std::cerr << "Error: Database is not available. Exiting.\n";
        exit(1); // Or handle as needed
    }

    auto students = model->getStudents();
    view->printStudents(students);
}


void Controller::updateDatabaseForStudents() {
    try {
        mysqlx::Session session("localhost", 33060, "root", "password");
        mysqlx::Schema schema = session.getSchema("mvc-cpp");
        mysqlx::Table studentsTable = schema.getTable("students");

        auto latestStudent = model->getStudents().back();

        studentsTable.insert("name", "familyName", "matriculationID")
            .values(latestStudent.name, latestStudent.familyName, latestStudent.matriculationID)
            .execute();

        std::cout << "Database updated successfully with student data.\n";

    } catch (const mysqlx::Error& err) {
        std::cerr << "MySQL X DevAPI Error: " << err.what() << std::endl;
        // Consider what to do here.  Perhaps rollback any model changes.
        exit(1); // Or handle differently.

    } catch (std::exception& ex) {
        std::cerr << "Standard Exception: " << ex.what() << std::endl;
        exit(1);

    } catch (...) {
        std::cerr << "Unknown error occurred.\n";
        exit(1); 
    }
}