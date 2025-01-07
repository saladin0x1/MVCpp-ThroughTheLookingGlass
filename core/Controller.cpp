#include "../include/Controller.h"
#include <mysqlx/xdevapi.h> // Include for X DevAPI
#include <iostream>

Controller::Controller(View* view, Model* model)
    : view(view), model(model) // Use member initializer list for efficiency
{
}

void Controller::userEnterAdd()
{
    this->model->addByOne();
    updateDatabase();
}

void Controller::userEnterAddShow()
{
    int userNumber = this->model->getAddTimes();
    this->view->printNumber(userNumber);
}

void Controller::updateDatabase()
{
    try {
        // Connect to the MySQL server
        mysqlx::Session session("localhost", 33060, "root", "password");
        mysqlx::Schema schema = session.getSchema("mvc-cpp");

        // Get the table for updating
        mysqlx::Table table = schema.getTable("model");

        int timesAdd = this->model->getAddTimes();

        // Insert or update the value in the table
        table.insert("times_add")
             .values(timesAdd)
             .execute();
        
        // Alternative: Upsert using replace
        table.update()
             .set("times_add", timesAdd)
             .execute();

        std::cout << "Database updated successfully with times_add = " << timesAdd << std::endl;
    } 
    catch (const mysqlx::Error& err) {
        std::cerr << "MySQL X DevAPI Error: " << err.what() << std::endl;
    } 
    catch (std::exception& ex) {
        std::cerr << "Standard Exception: " << ex.what() << std::endl;
    } 
    catch (...) {
        std::cerr << "Unknown error occurred while updating the database." << std::endl;
    }
}
