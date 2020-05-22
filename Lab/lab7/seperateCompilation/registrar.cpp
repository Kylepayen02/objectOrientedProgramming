// registrar.cpp 

#include "course.h"
#include "student.h"
#include "registrar.h"

using namespace std;

namespace BrooklynPoly{
    ostream& operator<<(ostream& os, const Registrar& rhs){
        os << "Registrar's Report" << endl;
        os << "Courses: " << endl;
        for (const Course* curr_course: rhs.courses){
            os << *curr_course << endl;
        }
        os << "Students:" << endl;
        for (const Student* curr_student: rhs.students){
            os << *curr_student << endl;
        }
        return os;
    }

    Registrar::Registrar() : courses(), students() {}

    bool Registrar::addCourse(const string& courseName){
        if (findCourse(courseName) == -1){
            courses.push_back(new Course(courseName));
            return true;
        }
        return false;
    }

    bool Registrar::addStudent(const string& studentName){
        if (findStudent(studentName) == -1){
            students.push_back(new Student(studentName)); 
            return true;
        }
        return false;
    }

    bool Registrar::enrollStudentInCourse(const string& studentName, const string& courseName){
        if (findStudent(studentName) == -1 || findCourse(courseName) == -1){
            return false;
        }
        students[findStudent(studentName)]->addCourse(courses[findCourse(courseName)]);
        courses[findCourse(courseName)]->addStudent(students[findStudent(studentName)]);
        return true;
    }

    bool Registrar::cancelCourse(const string& courseName){
        if (findCourse(courseName) == -1){
            return false;
        }
        
        size_t i = findCourse(courseName);
        courses[i]->removeStudentsFromCourse();
        delete courses[i];
        courses[i] = courses.back(); 
        courses.pop_back();
        return true;
    }

    void Registrar::purge(){
        for (size_t i = 0; i < courses.size(); i++){
            cancelCourse(courses[i]->getName());
        }
        for (size_t i = 0; i < students.size(); i++){
            delete students[i];
        }
        courses.clear();
        students.clear();
    }

    size_t Registrar::findCourse(const string& courseName) const {
        for (size_t i = 0; i < courses.size(); i++){
            if (courses[i]->getName() == courseName){
                return i;
            }
        }
        return -1;
    }

    size_t Registrar::findStudent(const string& studentName) const {
        for (size_t i = 0; i < students.size(); i++){
            if (students[i]->getName() == studentName){
                return i;
            }
        }
        return -1;
    }
}