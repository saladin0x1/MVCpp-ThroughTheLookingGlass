#include "../include/View.h"
#include "../include/Controller.h"
#include "../include/Model.h"

int main() {
	View v;
	Model m;
	Controller c(&v, &m);
	v.setListener(&c);
	v.run();
}