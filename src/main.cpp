#include "../include/View.h"
#include "../include/Controller.h"
#include "../include/Model.h"

int main() {
    View View;
    Model Model;
    Controller Controller(&View, &Model);
    View.setListener(&Controller);
    View.run();
}