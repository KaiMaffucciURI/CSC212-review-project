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

    ofs << "exam { final " << exam.first << ' ' << exam.second << " }";

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

bool Gradebook::printSingle(EntryType type, const std::string& name)
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

    uint16_t grade = (*it).second.first;
    uint16_t max = (*it).second.second;
    std::cout << (*it).first << " grade: " << grade << " / " << max << " " << (uint16_t)(((double)grade / (double)max) * 100.0) << "%" << std::endl << std::endl;

    return true;
}

bool Gradebook::printCategory(EntryType type, uint8_t flags)
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

    if (flags > 1)
    {
        throw std::invalid_argument("Recieved invalid flag");
        return false;
    }

    uint16_t catGrade = 0;
    uint16_t catMax = 0;

    for (const auto& entry : *map)
    {
        uint16_t grade = entry.second.first;
        uint16_t max = entry.second.second;

        catGrade += grade;
        catMax += max;

        if (flags == 0)
        {
            std::cout << entry.first << " grade: " << grade << " / " << max << " " << (uint16_t)(((double)grade / (double)max) * 100.0) << "%" << std::endl;
        }
    }

    if (flags == 0)
    {
        std::cout << "==================================" << std::endl;
    }

    std::cout << entryToString(type) << " grade: " << catGrade << " / " << catMax << " " << (uint16_t)(((double)catGrade / (double)catMax) * 100.0) << "%" << std::endl << std::endl;

    return true;
}

void Gradebook::printCourse(uint8_t flags)
{
    if (flags > 2)
    {
        throw std::invalid_argument("Recieved invalid flag");
        return;
    }

    uint16_t courseGrade = 0;
    uint16_t courseMax = 0;

    uint16_t catGrade = 0;
    uint16_t catMax = 0;

    for (const auto& entry : labs)
    {
        uint16_t grade = entry.second.first;
        uint16_t max = entry.second.second;

        catGrade += grade;
        catMax += max;

        if (flags == 0)
        {
            std::cout << entry.first << " grade: " << grade << " / " << max << " " << (uint16_t)(((double)grade / (double)max) * 100.0) << "%" << std::endl;
        }
    }

    if (flags == 0)
    {
        std::cout << "==================================" << std::endl;
    }

    if (flags != 2)
    {
        std::cout << entryToString(EntryType::lab) << " grade: " << catGrade << " / " << catMax << " " << (uint16_t)(((double)catGrade / (double)catMax) * 100.0) << "%" << std::endl << std::endl;
    }

    courseGrade += catGrade;
    courseMax += catMax;
    catGrade = 0;
    catMax = 0;

    for (const auto& entry : assignments)
    {
        uint16_t grade = entry.second.first;
        uint16_t max = entry.second.second;

        catGrade += grade;
        catMax += max;

        if (flags == 0)
        {
            std::cout << entry.first << " grade: " << grade << " / " << max << " " << (uint16_t)(((double)grade / (double)max) * 100.0) << "%" << std::endl;
        }
    }

    if (flags == 0)
    {
        std::cout << "==================================" << std::endl;
    }

    if (flags != 2)
    {
        std::cout << entryToString(EntryType::assignment) << " grade: " << catGrade << " / " << catMax << " " << (uint16_t)(((double)catGrade / (double)catMax) * 100.0) << "%" << std::endl << std::endl;
    }

    courseGrade += catGrade;
    courseMax += catMax;
    catGrade = 0;
    catMax = 0;

    for (const auto& entry : projects)
    {
        uint16_t grade = entry.second.first;
        uint16_t max = entry.second.second;

        catGrade += grade;
        catMax += max;

        if (flags == 0)
        {
            std::cout << entry.first << " grade: " << grade << " / " << max << " " << (uint16_t)(((double)grade / (double)max) * 100.0) << "%" << std::endl;
        }
    }

    if (flags == 0)
    {
        std::cout << "==================================" << std::endl;
    }

    if (flags != 2)
    {
        std::cout << entryToString(EntryType::project) << " grade: " << catGrade << " / " << catMax << " " << (uint16_t)(((double)catGrade / (double)catMax) * 100.0) << "%" << std::endl << std::endl;
    }

    courseGrade += catGrade;
    courseMax += catMax;
    catGrade = 0;
    catMax = 0;

    courseGrade += exam.first;
    courseMax += exam.second;

    if (flags != 2)
    {
        std::cout << entryToString(EntryType::exam) << " grade: " << exam.first << " / " << exam.second << " " <<  (uint16_t)(((double)exam.first / (double)exam.second) * 100.0) << "%" << std::endl;
    }

    if (flags != 2)
    {
        std::cout << "==================================" << std::endl;
    }

    std::cout << "Course total: " << courseGrade << " / " << courseMax << " " << (uint16_t)(((double)courseGrade / (double)courseMax) * 100.0) << "%" << std::endl << std::endl;

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

std::string Gradebook::entryToString(EntryType t)
{
    if (t == EntryType::lab)
    {
        return "Labs";
    }

    if (t == EntryType::assignment)
    {
        return "Assignments";
    }

    if (t == EntryType::project)
    {
        return "Projects";
    }

    if (t == EntryType::exam)
    {
        return "Exam";
    }

    if (t == EntryType::error)
    {
        return "Error";
    }

    return "";
}
