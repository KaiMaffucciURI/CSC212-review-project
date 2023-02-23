#include <iostream>

#include "gradebook.h"

/*
To Do:
Add error throwing for add, modify, delete entry
Implement save and load
Add user I/O
*/

/*
Notes:
User I/O should be formatted to all lowercase (to prevent conflicts with names)
*/

int main()
{
	//User i/o loop should be performed here
	Gradebook g;
	g.loadStudent("teststudent");
	g.addEntry(Gradebook::EntryType::lab, "lab2", 17, 20);
	g.saveStudent();

	return 0;
}