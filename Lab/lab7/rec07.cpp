/*
  rec07
  Starter Code for required functionality
  Yes, you may add other methods.
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student;

class Course {
    friend ostream& operator<<(ostream& os, const Course& rhs);

public:
    // Course methods needed by Registrar
    Course(const string& courseName);
    const string& getName() const;
    bool addStudent(Student*);
    void removeStudentsFromCourse();

private:
    string name;
    vector<Student*> students;
};

class Student {
    friend ostream& operator<<(ostream& os, const Student& rhs);

public:
    // Student methods needed by Registrar
    Student(const string& name);
    const string& getName() const;
    bool addCourse(Course*);

    // Student method needed by Course
    void removedFromCourse(Course*);

private:
    string name;
    vector<Course*> courses;
};

class Registrar {
    friend ostream& operator<<(ostream& os, const Registrar& rhs);

public:
    Registrar();
    bool addCourse(const string&);
    bool addStudent(const string&);
    bool enrollStudentInCourse(const string& studentName, const string& courseName);
    bool cancelCourse(const string& courseName);
    void purge();

private:
    size_t findStudent(const string&) const;
    size_t findCourse(const string&) const;

    vector<Course*> courses;
    vector<Student*> students;
};

int main() {

    Registrar registrar;

    cout << "No courses or students added yet\n";
    cout << registrar << endl;

    cout << "AddCourse CS101.001\n";
    registrar.addCourse("CS101.001");
    cout << registrar << endl;

    cout << "AddStudent FritzTheCat\n";
    registrar.addStudent("FritzTheCat");
    cout << registrar << endl;

    cout << "AddCourse CS102.001\n";
    registrar.addCourse("CS102.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
    cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
    cout << "Should fail, i.e. do nothing, "
         << "since Bullwinkle is not a student.\n";
    registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
    cout << registrar << endl;

    cout << "CancelCourse CS102.001\n";
    registrar.cancelCourse("CS102.001");
    cout << registrar << endl;

    /*
    // [OPTIONAL - do later if time]
    cout << "ChangeStudentName FritzTheCat MightyMouse\n";
    registrar.changeStudentName("FritzTheCat", "MightyMouse");
    cout << registrar << endl;

    cout << "DropStudentFromCourse MightyMouse CS101.001\n";
    registrar.dropStudentFromCourse("MightyMouse", "CS101.001");
    cout << registrar << endl;

    cout << "RemoveStudent FritzTheCat\n";
    registrar.removeStudent("FritzTheCat");
    cout << registrar << endl;
    */

    cout << "Purge for start of next semester\n";
    registrar.purge();
    cout << registrar << endl;
}

ostream& operator<<(ostream& os, const Course& rhs){
    os << rhs.getName() << ": ";
    if (rhs.students.size() == 0){
        os << "No students";
    }
    else{
        for (const Student* student : rhs.students){
            os << student->getName() << " ";
        }
    }
    return os;
    
}

Course::Course (const string& courseName): name(courseName) {};

const string& Course::getName() const {return name;}

bool Course::addStudent(Student* aStudent) {
    for (size_t i = 0; i < students.size(); i++){
        if (students[i] == aStudent){
            return false;
        }
    }
    students.push_back(aStudent);
    return true;
}

void Course::removeStudentsFromCourse() {
    for (size_t i = 0; i < students.size(); i++){
        students[i]->removedFromCourse(this);
    }
    students.clear();
}

ostream& operator<<(ostream& os, const Student& rhs){
    os << rhs.getName() << ": ";
    if (rhs.courses.size() == 0){
        os << "No courses";
    }
    else{
        for (const Course* const course : rhs.courses){
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