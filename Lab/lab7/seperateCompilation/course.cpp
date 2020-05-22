/*
course.cpp
*/
#include "course.h"
#include "student.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace BrooklynPoly
{
ostream &operator<<(ostream &os, const Course &rhs)
{
    os << rhs.getName() << ": ";
    if (rhs.students.size() == 0)
    {
        os << "No students";
    }
    else
    {
        for (const Student *student : rhs.students)
        {
            os << student->getName() << " ";
        }
    }
    return os;
}

Course::Course(const string &courseName) : name(courseName){};

const string &Course::getName() const { return name; }

bool Course::addStudent(Student *aStudent)
{
    for (size_t i = 0; i < students.size(); i++)
    {
        if (students[i] == aStudent)
        {
            return false;
        }
    }
    students.push_back(aStudent);
    return true;
}

void Course::removeStudentsFromCourse()
{
    for (size_t i = 0; i < students.size(); i++)
    {
        students[i]->removedFromCourse(this);
    }
    students.clear();
}

} // namespace BrooklynPoly