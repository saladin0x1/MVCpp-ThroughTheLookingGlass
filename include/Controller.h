    #pragma once
    #include "Model.h"
    #include "View.h"
    #include "ViewListener.h"
    #include <mysqlx/xdevapi.h> // Include for MySQL X DevAPI

    class Controller : public ViewListener {
    public:
        Controller(View* view, Model* model) : view(view), model(model) {}

        virtual void userEnterAddStudent(const std::string& name, const std::string& familyName, int matriculationID) override;
        virtual void userEnterShowStudents() override;

    private:
        void updateDatabaseForStudents();

        View* view;
        Model* model;
    };
