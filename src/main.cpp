#include <iostream>

#include "gradebook.h"

int main()
{
	//User i/o loop should be performed here
	Gradebook g;
	g.createStudent("newStudent");
	g.addEntry(Gradebook::EntryType::lab, "lab1", 10, 15);
	g.modifyEntry(Gradebook::EntryType::lab, "lab1", 12, 15);
	g.deleteEntry(Gradebook::EntryType::lab, "lab1");
	
	return 0;
}