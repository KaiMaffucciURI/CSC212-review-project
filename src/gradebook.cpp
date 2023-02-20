#include "gradebook.h"

#include <fstream>
#include <sstream>
#include <iostream>

bool Gradebook::createStudent(const std::string& name)
{
	std::ifstream test(name + ".grades");
	if (test.good())
	{
		test.close();
		return false;
	}
	test.close();

	//Student does not already exist
	//Prepare the gradebook for this student
	clearData();
	currentStudent = name;

	saved = false;

	return true;
}

bool Gradebook::loadStudent(const std::string& name)
{
	return true;
}

void Gradebook::saveStudent(const std::string& name)
{
	return;
}

bool Gradebook::addEntry(EntryType type, const std::string& name, uint16_t grade, uint16_t maxGrade)
{
	gradeMap* map = nullptr;

	switch (type)
	{
	case EntryType::lab:
		map = &labs;
		break;
	case EntryType::assignment:
		map = &assignments;
		break;
	case EntryType::project:
		map = &projects;
		break;
	case EntryType::exam:
		if (exam != gradePair(0, 0))
		{
			return false;
		}
		exam.first = grade;
		exam.second = maxGrade;
		saved = false;
		return true;
	default:
		//Will throw error instead
		return false;
	}

	//Check if entry already exists
	if (map->find(name) != map->end())
	{
		return false;
	}

	map->insert(std::pair<std::string, gradePair>(name, gradePair(grade, maxGrade)));
	saved = false;
	
	return true;
}

bool Gradebook::modifyEntry(EntryType type, const std::string& name, uint16_t grade, uint16_t maxGrade)
{
	gradeMap* map;

	switch (type)
	{
	case EntryType::lab:
		map = &labs;
		break;
	case EntryType::assignment:
		map = &assignments;
		break;
	case EntryType::project:
		map = &projects;
		break;
	case EntryType::exam:
		exam.first = grade;
		exam.second = maxGrade;
		return true;
	default:
		//Will throw error instead
		return false;
	}

	gradeMap::iterator it = map->find(name);
	if (it == map->end())
	{
		return false;
	}

	(*it).second = gradePair(grade, maxGrade);
	saved = false;

	return true;
}

bool Gradebook::deleteEntry(EntryType type, const std::string& name)
{
	gradeMap* map;

	switch (type)
	{
	case EntryType::lab:
		map = &labs;
		break;
	case EntryType::assignment:
		map = &assignments;
		break;
	case EntryType::project:
		map = &projects;
		break;
	case EntryType::exam:
		exam.first = 0;
		exam.second = 0;
		return true;
	default:
		//Will throw error instead
		return false;
	}

	gradeMap::iterator it = map->find(name);
	if (it == map->end())
	{
		return false;
	}

	map->erase(it);
	saved = false;

	return true;
}

void Gradebook::printSingle(EntryType type, const std::string& name)
{
	return;
}

void Gradebook::printCategory(EntryType type)
{
	return;
}

void Gradebook::printCourse(uint8_t flags)
{
	return;
}

void Gradebook::clearData()
{
	currentStudent.clear();
	labs.clear();
	assignments.clear();
	projects.clear();
	exam = gradePair(0, 0);

	return;
}
