#include "gradebook.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <stdexcept>

bool Gradebook::createStudent(const std::string& name)
{
	std::ifstream test("data\\" + name + ".grades");
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
	std::ifstream ifs("data\\" + name + ".grades");
	if (!ifs.good())
	{
		ifs.close();
		return false;
	}

	std::stringstream ss;
	ss << ifs.rdbuf();
	ifs.close();

	std::string buffer = ss.str();
	ss.clear();

	//Boy I do love lambda expressions

	std::string formattedBuffer;
	//Remove duplicate whitespaces from buffer and insert into formattedBuffer
	std::unique_copy(buffer.begin(), buffer.end(), std::back_insert_iterator<std::string>(formattedBuffer),
		[](char a, char b) { return std::isspace(a) && std::isspace(b); });

	//Replace whitespace characters with a regular space
	std::replace_if(formattedBuffer.begin(), formattedBuffer.end(),
		[](char a) { return std::isspace(a); }, ' ');

	//Make the whole string lowercase
	std::transform(formattedBuffer.begin(), formattedBuffer.end(), formattedBuffer.begin(),
		[](char a) { return std::tolower(a); });

	ss.str(formattedBuffer);
	std::vector<std::string> tokens;
	std::string token;

	while (ss >> token)
	{
		tokens.push_back(token);
	}

	if (tokens.size() == 0)
	{
		return false;
	}

	clearData();

	std::vector<std::string>::iterator labStart = std::find(tokens.begin(), tokens.end(), std::string("labs"));
	std::vector<std::string>::iterator assignmentStart = std::find(tokens.begin(), tokens.end(), std::string("assignments"));
	std::vector<std::string>::iterator projectStart = std::find(tokens.begin(), tokens.end(), std::string("projects"));
	std::vector<std::string>::iterator examStart = std::find(tokens.begin(), tokens.end(), std::string("exam"));

	std::vector<std::string>::iterator openSection, closeSection;

	if (labStart != tokens.end())
	{
		openSection = std::find(labStart, assignmentStart, std::string("{"));
		closeSection = std::find(labStart, assignmentStart, std::string("}"));

		if (openSection == assignmentStart || closeSection == assignmentStart)
		{
			return false;
		}

		//Number of increments from opening { to closing }, should be some multiple of 3 (name, grade, max)
		if ((std::distance(openSection, closeSection) - 1) % 3)
		{
			return false;
		}

		for (auto it = openSection + 1; it != closeSection; it += 3)
		{
			uint16_t grade = std::stoi(*(it + 1));
			uint16_t maxGrade = std::stoi(*(it + 2));
			labs.insert(std::pair<std::string, gradePair>(*it, gradePair(grade, maxGrade)));
		}
	}

	if (assignmentStart != tokens.end())
	{
		openSection = std::find(assignmentStart, projectStart, std::string("{"));
		closeSection = std::find(assignmentStart, projectStart, std::string("}"));

		if (openSection == projectStart || closeSection == projectStart)
		{
			return false;
		}

		//Number of increments from opening { to closing }, should be some multiple of 3 (name, grade, max)
		if ((std::distance(openSection, closeSection) - 1) % 3)
		{
			return false;
		}

		for (auto it = openSection + 1; it != closeSection; it += 3)
		{
			uint16_t grade = std::stoi(*(it + 1));
			uint16_t maxGrade = std::stoi(*(it + 2));
			assignments.insert(std::pair<std::string, gradePair>(*it, gradePair(grade, maxGrade)));
		}
	}

	if (projectStart != tokens.end())
	{
		openSection = std::find(projectStart, examStart, std::string("{"));
		closeSection = std::find(projectStart, examStart, std::string("}"));

		if (openSection == examStart || closeSection == examStart)
		{
			return false;
		}

		//Number of increments from opening { to closing }, should be some multiple of 3 (name, grade, max)
		if ((std::distance(openSection, closeSection) - 1) % 3)
		{
			return false;
		}

		for (auto it = openSection + 1; it != closeSection; it += 3)
		{
			uint16_t grade = std::stoi(*(it + 1));
			uint16_t maxGrade = std::stoi(*(it + 2));
			projects.insert(std::pair<std::string, gradePair>(*it, gradePair(grade, maxGrade)));
		}
	}

	if (examStart != tokens.end())
	{
		openSection = std::find(examStart, tokens.end(), std::string("{"));
		closeSection = std::find(examStart, tokens.end(), std::string("}"));

		if (openSection == tokens.end() || closeSection == tokens.end())
		{
			return false;
		}

		//Number of increments from opening { to closing }, should be some multiple of 3 (name, grade, max)
		if ((std::distance(openSection, closeSection) - 1) % 3)
		{
			return false;
		}

		uint16_t grade = std::stoi(*(openSection + 2));
		uint16_t maxGrade = std::stoi(*(openSection + 3));
		exam = gradePair(grade, maxGrade);
	}

	currentStudent = name;

	return true;
}

bool Gradebook::saveStudent()
{
	std::ofstream ofs("data\\" + currentStudent + ".grades", std::ofstream::trunc);
	if (!ofs.good())
	{
		ofs.close();
		return false;
	}

	ofs << "labs { ";
	for (auto it = labs.begin(); it != labs.end(); it++)
	{
		ofs << (*it).first << ' ' << (*it).second.first << ' ' << (*it).second.second << ' ';
	}
	ofs << "} ";

	ofs << "assignments { ";
	for (auto it = assignments.begin(); it != assignments.end(); it++)
	{
		ofs << (*it).first << ' ' << (*it).second.first << ' ' << (*it).second.second << ' ';
	}
	ofs << "} ";

	ofs << "projects { ";
	for (auto it = projects.begin(); it != projects.end(); it++)
	{
		ofs << (*it).first << ' ' << (*it).second.first << ' ' << (*it).second.second << ' ';
	}
	ofs << "} ";

	ofs << "exam { " << exam.first << ' ' << exam.second << " }";

	ofs.close();

	saved = true;
	return true;
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
		throw std::invalid_argument("Recieved invalid category");
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
		saved = false;
		return true;
	default:
		throw std::invalid_argument("Recieved invalid category");
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
		saved = false;
		return true;
	default:
		throw std::invalid_argument("Recieved invalid category");
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

void Gradebook::printCategory(EntryType type, uint8_t flags)
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
