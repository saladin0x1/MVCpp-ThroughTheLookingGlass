// In View.cpp

#include "../include/View.h"

void View::setListener(ViewListener* listener)
{
    this->listener = listener;
}

void View::printNumber(int n)
{
    std::cout << n << "\n";
}

void View::run()
{
    std::cout << "Enter 'add' to increment and show count, or 'show' to display the count.\n";
    while (true)
    {
        std::string enter;
        std::cin >> enter;
        if (enter == "add")
        {
            listener->userEnterAdd();      // Tell the controller to increment
            listener->userEnterAddShow();  // Immediately tell the controller to show
        }
        else if (enter == "show")
        {
            listener->userEnterAddShow();
        }
    }
}