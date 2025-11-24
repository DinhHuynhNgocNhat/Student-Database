// Standard (system) header files
#include <iostream>
#include <cstdlib>
// Add more standard header files as required
// #include <string>
#include <Poco/Data/Date.h>
#include "SimpleUI.h"
#include "StudentDb.h"
using namespace std;

// Add your project's header files here
// #include "CFraction.h"

// Main program
int main ()
{
    // TODO: Add your program code here
	cout << "Lab3_StudentDB started." << endl << endl;

	StudentDb studentDb;
	SimpleUI ui(studentDb);

	ui.run();

	return 0;
}
