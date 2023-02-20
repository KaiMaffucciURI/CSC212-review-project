#pragma once

#include <map>
#include <string>
#include <utility>

///Pair of uints where grade.first is the grade, grade.second is the max grade
typedef std::pair<uint16_t, uint16_t> gradePair;
///Map of grades for a single category accessed by a string key representing the entries name
typedef std::map<std::string, gradePair> gradeMap;

/*
Notes for Gradebook class
-Only the create, save, and load functions should perform file i/o operations
-Save should only be called when it is called by user or on exit
-All user i/o should occur in main rather than within the class
*/

class Gradebook
{
public:
	//Helper enum for modifying entries
	enum class EntryType
	{
		lab,
		assignment,
		project,
		exam
	};

	Gradebook() {}

	/// Creates a new student
	/// Returns true if successful
	/// Returns false if student name already exists
	bool createStudent(const std::string& name);
	/// Loads a student from csv files
	/// Returns true if successful
	/// Returns false if student name does not exist
	bool loadStudent(const std::string& name);
	/// Saves a student into csv files
	/// Overwrites existing csv file for this student
	void saveStudent(const std::string& name);

	//Returns true if successful, false if entry already exists
	bool addEntry(EntryType type, const std::string& name, uint16_t grade, uint16_t maxGrade);
	//Returns true if successful, false if entry does not exist
	bool modifyEntry(EntryType type, const std::string& name, uint16_t grade, uint16_t maxGrade);
	//Returns true if successful, false if entry does not exist
	bool deleteEntry(EntryType type, const std::string& name);

	/// Prints a single entry from a category
	/// Prints a simple error message if entry not found
	void printSingle(EntryType type, const std::string& name);
	/// Prints a category
	void printCategory(EntryType type);
	/// Prints the course grade
	/// flag 0 Prints all categories and assignments
	/// flag 1 Prints all categories
	/// flag 2 Prints only the course grade
	void printCourse(uint8_t flags = 0);

private:
	void clearData();

	gradeMap labs;
	gradeMap assignments;
	gradeMap projects;
	gradePair exam;

	//Current student loaded
	std::string currentStudent;
	//To determine if changes will be unsaved when exiting / changing student
	bool saved = true;
};