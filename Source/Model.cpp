#include "Model.h"
#include <iostream>
#include <soci/soci.h>
#include <soci/sqlite3/soci-sqlite3.h>
#include <juce_core/juce_core.h>  // For juce::MD5
#include <juce_cryptography/juce_cryptography.h>

Model::Model(const std::string& dbConnection) : sql(soci::sqlite3, dbConnection) {}

// Function to hash the password using JUCE's MD5
std::string hashPassword(const std::string& password) {
    // Convert std::string to juce::String
    juce::String jucePassword(password.c_str());  // Convert c-string to juce::String

    // Create an MD5 object and initialize it with the juce::String
    juce::MD5 md5(jucePassword.toUTF8());  // Use toUTF8() for proper encoding

    // Get the MD5 hash as a 32-character hexadecimal string
    return md5.toHexString().toStdString();
}

// Method to check login credentials in the database
bool Model::checkLoginCredentials(const std::string& username, const std::string& password) {
    try {
        std::string storedHash;
        // Fetch the stored hash for the username from the database
        sql << "SELECT password_hash FROM login_cred WHERE username = :username", soci::use(username), soci::into(storedHash);

        // Hash the provided password and compare it with the stored hash
        return (storedHash == hashPassword(password));
    } catch (const soci::soci_error& e) {
        std::cerr << "Error checking login credentials: " << e.what() << std::endl;
        return false;
    }
}

// Method to load student data from the database
void Model::loadStudentData(int userId, std::string& name, std::string& lastName, std::string& id, std::string& className) {
    try {
        // Query the database for the student information
        sql << "SELECT name, lastName, userId, class FROM users WHERE userId = :userId",
            soci::use(userId), soci::into(name), soci::into(lastName), soci::into(id), soci::into(className);
    } catch (const soci::soci_error& e) {
        std::cerr << "Error loading student data: " << e.what() << std::endl;
        throw std::runtime_error("Failed to load student data.");
    }
}
