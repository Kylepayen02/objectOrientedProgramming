/*
rec05.cpp
Kyle Payen (kcp341)
More pointers
Modeling a  part of the School of Engineering CS lab administration.
*/

#include <iostream>
#include <vector>
#include <string>



using namespace std;

class Section{
    friend ostream& operator << (ostream& os, const Section& aSection){
        os << "Section: " << aSection.sectionName << ", " << aSection.sectionTime << ", Students: " << endl;
        if (aSection.students.size() == 0){
            os << "None";
        }
        else{
            for (const StudentRecord* currStudent: aSection.students){
                os << *currStudent;
            }
        }
        return os;
    }

private:
    class TimeSlot{
        // Output operator
        // format: Time slot: [Day: theDay, Start time: theTime am/pm]
        friend ostream& operator << (ostream& os, const TimeSlot& theTimeSlot){
            os << "TimeSlot: [Day: " << theTimeSlot.day << ", Start time: " ;
            if (theTimeSlot.time <= 11){ // Before 12 pm
                os << theTimeSlot.time << "am";
            }
            else if (theTimeSlot.time == 12){ // At 12pm
                os << theTimeSlot.time << "pm";
            }
            else{
                os << (theTimeSlot.time -12) << "pm"; // After 12pm
            }

            os << "]";
            return os;

        }

    public:
        // Constructor for TimeSlot
        TimeSlot(const string& labDay, int labTime): day(labDay), time(labTime) {};

    private:
        string day;
        int time;

    };

    class StudentRecord{
        // Output Operator
        // format: Name: John, Grades: [vector of grades]
        friend ostream& operator<<(ostream& os, const StudentRecord& student){
            os << "Name: " << student.studentName << ", Grades: ";
            for (size_t i = 0; i <= 14; ++i){
                os << student.grades[i] << ", ";
            }
            os << endl;
            return os;
        }

    public:
        // When the StudentRecord class is first initialized, all of the student grades must be -1
        StudentRecord(const string& name): studentName(name) {
            grades = vector<int>(14, -1);
        };

        // getters
        string getName(){return studentName;}

        void addGrade(int grade, int week){
            grades[week-1] = grade;
        }

    private:
        string studentName;
        vector<int> grades;


    };
    string sectionName;
    TimeSlot sectionTime;
    vector<StudentRecord*> students;

public:
    // constructor for Section
    Section(const string& name, const string& day, int time): sectionName(name), sectionTime(TimeSlot(day, time)) {};

    // Copy Construtor
    Section(const Section& aSection) : sectionName(aSection.sectionName), sectionTime(aSection.sectionTime) {
        vector<StudentRecord*> studentRecords;
        for(size_t i = 0; i < aSection.students.size(); i++){
            studentRecords.emplace_back(new StudentRecord(*aSection.students[i]));
        }
        students = studentRecords;
    };

    //Destructor
    ~Section(){
        cout << "Section " << sectionName << " is being deleted" << endl;
        for(size_t i = 0; i < students.size(); i++){
            cout << "Deleting " << students[i]->getName() << endl;
            delete students[i];
            students[i] = nullptr;
        }
        students.clear();
    };

    // getters
    string getName(){return sectionName;}
    TimeSlot getSectionTime(){return sectionTime;}
    vector<StudentRecord*> getStudents(){return students;}

    //Adds grade to a students grades
    void addGrade(const string& name, int grade, int week){
        for (size_t i = 0; i < students.size(); i++){
            if (students[i]->getName() == name){
                students[i]->addGrade(grade, week);
            }
        }
    }

    void addStudent(const string& name){
        students.emplace_back(new StudentRecord(name));
    }

};

// The labWorker Class: It needs to know what section it is teaching, but the section can exist prior to the lab worker.
class LabWorker{
    friend ostream& operator<<(ostream& os, const LabWorker& aLabWorker){

        os << aLabWorker.workerName;
        if (aLabWorker.labSection == nullptr){
            os << " does not have a section.";
        }
        else{
            os << " has " << *aLabWorker.labSection;
        }
        return os;
    }

public:
    LabWorker(const string& name): workerName(name), labSection(nullptr) {}; // by default, the labSection will be a null pointer since it is not assigned to a section


    void addSection(Section& asection){
        labSection = &asection;
    }

    void addGrade(const string& name, int grade, int week){
        labSection->addGrade(name, grade, week);

    }


private:
    string workerName;
    Section* labSection;

};


// Test code
void doNothing(Section sec) { cout << sec << endl; }

int main() {

    cout << "Test 1: Defining a section\n";
     Section secA2("A2", "Tuesday", 16);
     cout << secA2 << endl;

    cout << "\nTest 2: Adding students to a section\n";
    secA2.addStudent("John");
    secA2.addStudent("George");
    secA2.addStudent("Paul");
    secA2.addStudent("Ringo");
    cout << secA2 << endl;

    cout << "\nTest 3: Defining a lab worker.\n";
    LabWorker moe( "Moe" );
    cout << moe << endl;

    cout << "\nTest 4: Adding a section to a lab worker.\n";
    moe.addSection( secA2 );
    cout << moe << endl;

    cout << "\nTest 5: Adding a second section and lab worker.\n";
     LabWorker jane( "Jane" );
     Section secB3( "B3", "Thursday", 11 );
     secB3.addStudent("Thorin");
     secB3.addStudent("Dwalin");
     secB3.addStudent("Balin");
     secB3.addStudent("Kili");
     secB3.addStudent("Fili");
     secB3.addStudent("Dori");
     secB3.addStudent("Nori");
     secB3.addStudent("Ori");
     secB3.addStudent("Oin");
     secB3.addStudent("Gloin");
     secB3.addStudent("Bifur");
     secB3.addStudent("Bofur");
     secB3.addStudent("Bombur");
     jane.addSection( secB3 );
     cout << jane << endl;

    cout << "\nTest 6: Adding some grades for week one\n";
     moe.addGrade("John", 17, 1);
     moe.addGrade("Paul", 19, 1);
     moe.addGrade("George", 16, 1);
     moe.addGrade("Ringo", 7, 1);
     cout << moe << endl;

    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
     moe.addGrade("John", 15, 3);
     moe.addGrade("Paul", 20, 3);
     moe.addGrade("Ringo", 0, 3);
     moe.addGrade("George", 16, 3);
     cout << moe << endl;

    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
         << "those students (or rather their records?)\n";

    cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, "
         << "then make sure the following call works:\n";
     doNothing(secA2);
     cout << "Back from doNothing\n\n";

} // main

