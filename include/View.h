#pragma once
#include "ViewListener.h"
#include "Model.h"
#include <vector>

class View {
public:
    void setListener(ViewListener* listener);
    void printStudents(const std::vector<Model::Student>& students);
    void run();

private:
    ViewListener* listener = nullptr;
};