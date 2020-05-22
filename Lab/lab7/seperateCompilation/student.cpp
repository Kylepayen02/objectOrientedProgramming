// student.cpp

#include "student.h"
#include "course.h"

using namespace std;

namespace BrooklynPoly{
    ostream& operator<<(ostream& os, const Student& rhs){
        os << rhs.getName() << ": ";
        if (rhs.courses.size() == 0){
            os << "No courses";
        }
        else{
            for (const Course* course : rhs.courses){
            os << course->getName() << " ";
            }
        }
        return os;
    }

    Student::Student (const string& name): name(name) {};

    const string& Student::getName() const {return name;}

    bool Student::addCourse(Course* aCourse){
        for (size_t i = 0; i < courses.size(); i++){
            if (courses[i] == aCourse){
                return false;
            }
        }
        courses.push_back(aCourse);
        return true;
    }

    void Student::removedFromCourse(Course* aCourse){
        for (size_t i = 0; i < courses.size(); i++){
            if (courses[i] == aCourse){
                courses[i] = courses.back();
                courses.pop_back();
            }
        }
    }
}