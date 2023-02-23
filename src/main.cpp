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
	g.loadStudent("C:\\Projects\\Spring2023\\project-1\\data\\teststudent");

	return 0;
}