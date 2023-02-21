#include <iostream>

#include "gradebook.h"

int main()
{

    Gradebook grades = new Gradebook();

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
        // we can change what the user input has to be to select different options if we want
        // (eg. creating a student they could type "create student" instead
        if (command_args[0] == "new") {

            // create new student

        } else if (command_args[0] == "load") {

            // load student into memory from file as current working student

        } else if (command_args[0] == "add") {

            // add new assignment

        } else if (command_args[0] == "view") {

            // view assignments

        } else if (command_args[0] == "modify") {

            // modify existing assignments
            // two different branches for each possible args given to modify

        } else if (option == "exit" || option == "quit") {

            std::cout << "Exiting the program..."
            // we can put a cin/are you sure prompt right here if we want it to wait for the user before actually closing
            running = false;

        } else {

            // if the user gave bad input
            std::cout << "Invalid option: please choose a valid option." << std::endl;

        }
    }

	return 0;
}