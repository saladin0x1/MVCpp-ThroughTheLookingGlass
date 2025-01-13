// Model.h
#ifndef MODEL_H
#define MODEL_H

#include <soci/soci.h>
#include <soci/sqlite3/soci-sqlite3.h>
#include <string>
#include <vector>
#include <juce_core/juce_core.h>  // For juce::MD5

class Model {
public:
    // Constructor to initialize the database connection
    Model(const std::string& dbConnection);

    // Method to check if the username and password hash match the records in the database
    bool checkLoginCredentials(const std::string& username, const std::string& password);
    void loadStudentData(int userId, std::string& name, std::string& lastName, std::string& id, std::string& className);

private:
    soci::session sql;  // SOCI session object for database interaction
};

#endif // MODEL_H
