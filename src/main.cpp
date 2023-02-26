#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <algorithm>

#include "gradebook.h"

Gradebook::EntryType getType(const std::string& str)
{
    if (str == "labs")
    {
        return Gradebook::EntryType::lab;
    }

    if (str == "assignments")
    {
        return Gradebook::EntryType::assignment;
    }

    if (str == "projects")
    {
        return Gradebook::EntryType::project;
    }

    if (str == "exam")
    {
        return Gradebook::EntryType::exam;
    }

    return Gradebook::EntryType::error;
}

int main()
{

    Gradebook book;

    std::cout << "type 'help' for help" << std::endl;

    bool running = true;
    while (running)
    {
        std::cout << book.getStudent() << '>';

        std::string line;

        std::getline(std::cin, line);

        std::stringstream ss(line);

        std::vector<std::string> tokens;
        std::string token;

        while (ss >> token)
        {
            tokens.push_back(token);
        }

        if (tokens.size() == 0)
        {
            continue;
        }

        std::transform(tokens.at(0).begin(), tokens.at(0).end(), tokens.at(0).begin(),
		[](char a) { return std::tolower(a); });

        if (tokens.at(0) == "exit")
        {
            if (!book.isSaved())
            {
                std::cout << "There are unsaved changes, save now? y/n ";
                char c;
                std::cin >> c;

                if (std::tolower(c) == 'y')
                {
                    book.saveStudent();
                }
            }

            running = false;
            continue;
        }

        if (tokens.at(0) == "help")
        {
            if (tokens.size() == 1)
            {
                std::cout << "The following commands are available:" << std::endl;
                std::cout << "help - prints all commands" << std::endl;
                std::cout << "help [cmd] - prints specific information about command [cmd]" << std::endl;
                std::cout << "new [student] - creates a new student of name [student]" << std::endl;
                std::cout << "load [student] - loads a student of name [student]" << std::endl;
                std::cout << "save - save student to file of student name" << std::endl;
                std::cout << "add [cat] [name] [grade] [max] - add a new entry to [cat] grades" << std::endl;
                std::cout << "modify [cat] [name] [grade] [max] - changes existing entry [name] in [cat]" << std::endl;
                std::cout << "delete [cat] [name] - deletes entry [name] in [cat]" << std::endl;
                std::cout << "print all [flags] - prints whole course" << std::endl;
                std::cout << "print [cat] [flags] - prints a category" << std::endl;
                std::cout << "print [cat] [name] - prints a single entry [name]" << std::endl;
                std::cout << "exit - exits program" << std::endl;

                continue;
            }

            if (tokens.at(1) == "new")
            {
                std::cout << "new [student]" << std::endl;
                std::cout << "Creates a new student of name [student]" << std::endl;
                continue;
            }

            if (tokens.at(1) == "load")
            {
                std::cout << "load [student]" << std::endl;
                std::cout << "Loads a student from the file [student].grades in the data folder" << std::endl;
                continue;
            }

            if (tokens.at(1) == "save")
            {
                std::cout << "save" << std::endl;
                std::cout << "Saves a student to the file of studentname.grades in the data folder" << std::endl;
                continue;
            }

            if (tokens.at(1) == "add")
            {
                std::cout << "add [cat] [name] [grade] [max]" << std::endl;
                std::cout << "Adds an entry of name [name] to category [cat], where [grade] is the grade and [max] is the max grade for the entry" << std::endl;
                continue;
            }

            if (tokens.at(1) == "modify")
            {
                std::cout << "modify [cat] [name] [grade] [max]" << std::endl;
                std::cout << "Changes an existing entry of name [name] in category [cat], where [grade] is the new grade and [max] is the new max grade" << std::endl;
                continue;
            }

            if (tokens.at(1) == "delete")
            {
                std::cout << "delete [cat] [name]" << std::endl;
                std::cout << "Deletes an existing entry of name [name] in category [cat]" << std::endl;
                continue;
            }

            if (tokens.at(1) == "print")
            {
                std::cout << "print all [flags]" << std::endl;
                std::cout << "print [cat] [flags]" << std::endl;
                std::cout << "print [cat] [name]" << std::endl;
                std::cout << "all - prints the entire course with the following flags available :" << std::endl;
                std::cout << "-c - prints all categories but not entries" << std::endl;
                std::cout << "-o - prints overall grade but not categories or entries" << std::endl;
                std::cout << "[cat] [flags] - prints a categories with the -c flag available" << std::endl;
                std::cout << "[cat] [name] - prints a single entry" << std::endl;
                continue;
            }

            if (tokens.at(1) == "exit")
            {
                std::cout << "exit" << std::endl;
                std::cout << "Exits the program" << std::endl;
                continue;
            }

            continue;
        }

        if (tokens.at(0) == "new")
        {

            if (tokens.size() == 1)
            {
                std::cout << "Usage - new [student]" << std::endl;
                continue;
            }

            if (!book.isSaved())
            {
                std::cout << "There are unsaved changes, save now? y/n ";
                char c;
                std::cin >> c;
                std::cin.ignore();

                if (std::tolower(c) == 'y')
                {
                    book.saveStudent();
                }
            }

            if (!book.createStudent(tokens.at(1)))
            {
                std::cout << "Student '" << tokens.at(1) << "' already exists" << std::endl;
            }

            continue;
        }

        if (tokens.at(0) == "load")
        {
            if (tokens.size() == 1)
            {
                std::cout << "Usage - load [student]" << std::endl;
                continue;
            }

            if (!book.isSaved())
            {
                std::cout << "There are unsaved changes, save now? y/n ";
                char c;
                std::cin >> c;
                std::cin.ignore();

                if (std::tolower(c) == 'y')
                {
                    book.saveStudent();
                }
            }

            if (!book.loadStudent(tokens.at(1)))
            {
                std::cout << "Student '" << tokens.at(1) << "' does not exist" << std::endl;
            }

            continue;
        }

        if (tokens.at(0) == "save")
        {
            if (book.getStudent() == "")
            {
                std::cout << "No selected student" << std::endl;
                continue;
            }

            if (!book.saveStudent())
            {
                std::cout << "Failed to save student" << std::endl;
            }

            continue;
        }

        if (tokens.at(0) == "add")
        {
            if (book.getStudent() == "")
            {
                std::cout << "No selected student" << std::endl;
                continue;
            }

            if (tokens.size() != 5)
            {
                std::cout << "Usage - add [cat] [name] [grade] [max]" << std::endl;
                continue;
            }

            Gradebook::EntryType t = getType(tokens.at(1));
            if (t == Gradebook::EntryType::error)
            {
                std::cout << "Invalid category '" << tokens.at(1) << "'" << std::endl;
                continue;
            }

            uint16_t grade;
            uint16_t maxGrade;

            try
            {
                grade = std::stoi(tokens.at(3));
                maxGrade = std::stoi(tokens.at(4));
            }
            catch (std::invalid_argument e)
            {
                std::cout << "Invalid argument, usage - add [cat] [name] [grade] [max]" << std::endl;
                continue;
            }

            if (!book.addEntry(t, tokens.at(2), grade, std::stoi(tokens.at(4))))
            {
                std::cout << "Entry '" << tokens.at(2) << "' already exists" << std::endl;
            }

            continue;
        }

        if (tokens.at(0) == "modify")
        {
            if (book.getStudent() == "")
            {
                std::cout << "No selected student" << std::endl;
                continue;
            }

            if (tokens.size() != 5)
            {
                std::cout << "Usage - modify [cat] [name] [grade] [max]" << std::endl;
                continue;
            }

            Gradebook::EntryType t = getType(tokens.at(1));
            if (t == Gradebook::EntryType::error)
            {
                std::cout << "Invalid category '" << tokens.at(1) << "'" << std::endl;
                continue;
            }

            uint16_t grade;
            uint16_t maxGrade;

            try
            {
                grade = std::stoi(tokens.at(3));
                maxGrade = std::stoi(tokens.at(4));
            }
            catch (std::invalid_argument e)
            {
                std::cout << "Invalid argument, usage - modify [cat] [name] [grade] [max]" << std::endl;
                continue;
            }

            if (!book.modifyEntry(t, tokens.at(2), std::stoi(tokens.at(3)), std::stoi(tokens.at(4))))
            {
                std::cout << "Entry '" << tokens.at(2) << "' does not exist" << std::endl;
            }

            continue;
        }

        if (tokens.at(0) == "delete")
        {
            if (book.getStudent() == "")
            {
                std::cout << "No selected student" << std::endl;
                continue;
            }

            if (tokens.size() != 3)
            {
                std::cout << "Usage - delete [cat] [name]" << std::endl;
                continue;
            }

            Gradebook::EntryType t = getType(tokens.at(1));
            if (t == Gradebook::EntryType::error)
            {
                std::cout << "Invalid category '" << tokens.at(1) << "'" << std::endl;
                continue;
            }

            if (!book.deleteEntry(t, tokens.at(2)))
            {
                std::cout << "Entry '" << tokens.at(2) << "' does not exist" << std::endl;
            }

            continue;
        }

        if (tokens.at(0) == "print")
        {
            if (book.getStudent() == "")
            {
                std::cout << "No selected student" << std::endl;
                continue;
            }

            if (tokens.size() != 2 && tokens.size() != 3)
            {
                std::cout << "Usage - print all [flags], print [cat] [flags], print [cat] [name]" << std::endl;
                continue;
            }

            if (tokens.at(1) == "all")
            {
                if (tokens.size() == 2)
                {
                    book.printCourse();
                    continue;
                }

                if (tokens.at(2) == "-c")
                {
                    book.printCourse(1);
                    continue;
                }

                if (tokens.at(2) == "-o")
                {
                    book.printCourse(2);
                    continue;
                }

                continue;
            }

            Gradebook::EntryType t = getType(tokens.at(1));
            if (t == Gradebook::EntryType::error)
            {
                std::cout << "Invalid category '" << tokens.at(1) << "'" << std::endl;
                continue;
            }

            if (tokens.size() == 2)
            {
                book.printCategory(t);
                continue;
            }

            if (*(tokens.at(2).begin()) == '-')
            {
                if (tokens.at(2) == "-c")
                {
                    book.printCategory(t, 1);
                    continue;
                }

                continue;
            }

            book.printSingle(t, tokens.at(2));

            continue;
        }
    }
    
	return 0;
}
