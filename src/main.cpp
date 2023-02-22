#include <iostream>

#include "gradebook.h"

int main()
{

    Gradebook book = new Gradebook();

    // plan: loop which prompts the user with a list of options
    // which option they pick determines which

    std::string option;
    bool running = true;

    while (running) {

        // list options: we could make this into a function so it doesn't make main look messy
        // and what order do we want to print in, by alphabetical, or anything else?
        std::cout << "Options to choose from: " << std::endl;
        std::cout << "new <name>\n\tcreate new student" << std::endl;
        std::cout << "load <name>\n\tload student <name> from file into memory" << std::endl;
        std::cout << "add <type> <grade> <total>\n\tadd an assignment of type <type> with grade <grade> out of <total>" << std::endl;
        std::cout << "view <type>\n\tdisplays all assignments of type <type>; if no <type> given, displays all assignments" << std::endl;
        std::cout << "modify <index> <grade> <total>\n\tmodify grade at <index> with <grade> and <total>" << std::endl;
        std::cout << "modify all\n\tlists all grades, then prompts user for an index, grade, and total the grade is out of" << std::endl;
        std::cout << "delete <type> <name>\n\tdeletes all entries of type <type> under name <name>"
        std::cout << "exit\n\tclose the program" << std::endl;

        // get user's choice and parse it
        std::cout << "Which option would you like to choose? " << std::endl;
        std::cin >> line; // put user input into line
        std::vector<std::string> command_args; // vector of strings, will be the components of the user's input

        std::stringstream string_stream(line);
        std::string part;
        while (getline(string_stream, part, ' ')) {
            command_args.push_back(part);
        }

        // long if-else chain of different options
        if (command_args[0] == "new") {

            // create new student
            book.createStudent(command_args[1]);

        } else if (command_args[0] == "load") {

            // load student into memory from file as current working student
            book.loadStudent(command_args[1]);

        } else if (command_args[0] == "add") {

            // add new assignment
            if (command_args[1] == "labs") {
                book.addEntry(labs, std::atoi(command_args[2]), std::atoi(command_args[3]));
            } else if (command_args[1] = "assignments") {
                book.addEntry(assignments, std::atoi(command_args[2]), std::atoi(command_args[3]));
            } else if (command_args[1] = "projects") {
                book.addEntry(projects, std::atoi(command_args[2]), std::atoi(command_args[3]));
            } else if (command_args[1] = "exams") {
                book.addEntry(exams, std::atoi(command_args[2]), std::atoi(command_args[3]));
            } else {
                // bad argument(s)
                std::cout << "you suck" << std::endl; // we can put something else here
            }

        } else if (command_args[0] == "view") {

            // view all assignments of type command_args[1]
            // might be nice to make a helper function which converts string to type somehow,
            // so we don't have to go through this each time, if that's possible
            if (command_args[1] == "labs") {
                book.printCategory(labs);
            } else if (command_args[1] = "assignments") {
                book.printCategory(assignments);
            } else if (command_args[1] = "projects") {
                book.printCategory(projects);
            } else if (command_args[1] = "exams") {
                book.printCategory(exams);
            } else {
                // bad argument(s)
                std::cout << "you suck" << std::endl; // we can put something else here
            }

        } else if (command_args[0] == "modify") {

            // modify existing assignments
            // two different branches for each possible args given to modify
            if (command_args[1] == "all") {

                // print out all stuff and prompt for which one they'd like to modify
                book.printCourse(0);
                std::string user_in;
                std::cin >> line;

                // parse user input
                command_args.clear();
                std::stringstream string_stream(line);
                std::string part;
                while (getline(string_stream, part, ' ')) {
                    command_args.push_back(part);
                }

                // call modifyEntry based on parsed user input
                // there's no modifyEntry call that calls based on an index like in the example diagram:
                // what do you prefer me to do here?

            } else if (command_args[0] == "delete") {

                // delete entry
                if (command_args[1] == "labs") {
                    book.deleteEntry(labs, command_args[2]);
                } else if (command_args[1] = "assignments") {
                    book.deleteEntry(assignments, command_args[2]);
                } else if (command_args[1] = "projects") {
                    book.deleteEntry(projects, command_args[2]);
                } else if (command_args[1] = "exams") {
                    book.deleteEntry(exams, command_args[2]);
                } else {
                    // bad argument(s)
                    std::cout << "you suck" << std::endl; // we can put something else here

            } else {

                // just call modify normally, depending on type
                if (command_args[1] == "labs") {
                    book.modifyEntry(labs, std::atoi(command_args[2]), std::atoi(command_args[3]));
                } else if (command_args[1] = "assignments") {
                    book.modifyEntry(assignments, std::atoi(command_args[2]), std::atoi(command_args[3]));
                } else if (command_args[1] = "projects") {
                    book.modifyEntry(projects, std::atoi(command_args[2]), std::atoi(command_args[3]));
                } else if (command_args[1] = "exams") {
                    book.modifyEntry(exams, std::atoi(command_args[2]), std::atoi(command_args[3]));
                } else {
                    // bad argument(s)
                    std::cout << "you suck" << std::endl; // we can put something else here
                }
            }

        } else if (option == "exit" || option == "quit") {

            std::cout << "Exiting the program..."
            // we can put a cin/are you sure prompt right here if we want it to wait for the user before actually closing
            running = false;

        } else {

            // if the user gave bad input
            std::cout << "Invalid option: please choose a valid option." << std::endl;

        }

        command_args.clear();
    }

	return 0;
}