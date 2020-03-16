
/*
  rec05.cpp
  Kyle Payen
  Recitation 06
  CS2124
  Focus: Dynamic arrays and copy control
 */

#include <string>
#include <iostream>
using namespace std;

class Position {
    friend ostream& operator<<(ostream& os, const Position& rhs) {
        os << '[' << rhs.title << ',' << rhs.salary << ']';
        return os;
    }
public:
    Position(const string& aTitle, double aSalary)
            : title(aTitle), salary(aSalary) {}
    const string& getTitle() const { return title; }
    double getSalary() const { return salary; }
    void changeSalaryTo(double d) { salary = d; }
private:
    string title;
    double salary;
}; // class Position

class Entry {
    friend ostream& operator<<(ostream& os, const Entry& rhs) {
        os << rhs.name << ' ' << rhs.room
           << ' ' << rhs.phone << ", " << *rhs.pos;
        return os;
    }
public:
    Entry(const string& name, unsigned room, unsigned phone, Position& position)
            : name(name), room(room), phone(phone), pos(&position) {
    }
    const string& getName() const { return name; }
    unsigned getPhone() const { return phone; }
private:
    string name;
    unsigned room;
    unsigned phone;
    Position* pos;
}; // class Entry

class Directory {
    // Overload output operator
    friend ostream& operator<<(ostream& os, const Directory& aDirectory){
        os << "Directory size is: " << aDirectory.size << endl;
        for (size_t i=0; i<aDirectory.size; ++i){
            cout << "    " << *((aDirectory.entries)[i]) << endl;
        }

        return os;
    }



public:
    // Of course the first function you need to write for this (or
    // any) class is...
    // ???
    // ...
    //Default Contructor
    Directory() : capacity(1), size(0), entries(new Entry*[1]){
        cout << endl;
        cout << "THIS IS THE DEFAULT CONSTRUCTOR" << endl;
        cout << endl;
    };

    // Copy Constructor

    Directory(const Directory& aDirectory) : capacity(aDirectory.capacity), size(aDirectory.size), entries(new Entry*[aDirectory.capacity]) {
        cout << endl;
        cout << "THIS IS THE COPY CONSTRUCTOR" << endl;
        cout << endl;
        for (size_t i = 0; i < aDirectory.size; ++i){
            entries[i] = new Entry(*aDirectory.entries[i]);
        }
    };

    // Destructor

    ~Directory() {
        cout << endl;
        cout << "THIS IS THE DESTRUCTOR" << endl;
        cout << endl;
        for (size_t i = 0; i < size; ++i){
            delete entries[i];
        }
        delete [] entries;
    }

    // Assignment operator

    Directory& operator=(const Directory& aDirectory){
        cout << endl;
        cout << "THIS IS THE ASSIGNMENT OPERATOR" << endl;
        cout << endl;
        if (this == &aDirectory){
            return *this;
        }
        else{
            for (size_t i = 0; i < size; ++i){
                delete entries[i];
            }
            delete [] entries;

            size = aDirectory.size;
            capacity = aDirectory.size;
            entries = new Entry*[capacity];
            for (size_t j = 0; j < size; j++){
                entries[j] = new Entry(*aDirectory.entries[j]);
            }
            return *this;
        }
    }

    // We'll get you started with the add method, but obviously you
    // have a lot of work to do here.
    void add(const string& name, unsigned room, unsigned ph, Position& pos) {
        if (size == capacity)	{
            // something is missing!!!  Add it!

            cout << endl;
            cout << "THE ARRAY IS BEING RESIZED" << endl;
            cout << endl;

            capacity *= 2;
            Entry** newEntries = new Entry*[capacity];
            for (size_t i = 0; i < size; i++){
                newEntries[i] = entries[i];
            }
            delete [] entries;
            entries = newEntries;

        } // if
        entries[size] = new Entry(name, room, ph, pos);
        ++size;
    } // add

    //overload [] operator

    const unsigned operator[](const string& name) const{
        for (size_t i=0; i<size; ++i){
            if((*entries[i]).getName() == name){
                return (entries[i])->getPhone();
            }
        }
        return 9999;
    }

private:
    Entry** entries;
    size_t size;
    size_t capacity;
}; // class Directory

void doNothing(Directory dir) { cout << dir << endl; }

int main() {

    // Note that the Postion objects are NOT on the heap.
    Position boss("Boss", 3141.59);
    Position pointyHair("Pointy Hair", 271.83);
    Position techie("Techie", 14142.13);
    Position peon("Peonissimo", 34.79);

    // Create a Directory
    Directory d;
    d.add("Marilyn", 123, 4567, boss);
    cout << d << endl;

    Directory d2 = d;	// What function is being used??
    d2.add("Gallagher", 111, 2222, techie);
    d2.add("Carmack", 314, 1592, techie);
    cout << d << endl;

    cout << "Calling doNothing\n";
    doNothing(d2);
    cout << "Back from doNothing\n";

    Directory d3;
    d3 = d2;

    // Should display 1592
    cout << d2["Carmack"] << endl;

} // main
