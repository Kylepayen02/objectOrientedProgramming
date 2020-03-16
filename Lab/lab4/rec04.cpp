//Kyle Payen
//02/21/20
//Lab04

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Complex { // Part of Task 16
    double real;
    double img;
};

// Part of Task 17
class PlainOldClass {
public:
    PlainOldClass() : x(-72) {}
    int getX() const { return x; }
    void setX( int val )  { x = val; }
private:
    int x;
};
 //Task 18
class PlainOldClassV2 {
public:
    PlainOldClassV2() : x(-72) {}
    int getX() const { return x; }
    //void setX( int x )  { x = x; }  HMMMM???
    void setX( int x )  { this->x = x; } // No confusion!
private:
    int x;
};

//Task 28
class Colour {
public:
    Colour(const string& name, unsigned r, unsigned g, unsigned b)
            : name(name), r(r), g(g), b(b) {}
    void display() const {
        cout << name << " (RBG: " << r << "," << g<< "," << b << ")";
    }
private:
    string name;      // what we call this colour
    unsigned r, g, b; // red/green/blue values for displaying
};

class SpeakerSystem {
public:
    void vibrateSpeakerCones(unsigned signal) const {

        cout << "Playing: " << signal << "Hz sound..." << endl;
        cout << "Buzz, buzzy, buzzer, bzap!!!\n";
    }
};

class Amplifier {
public:
    void attachSpeakers(const SpeakerSystem& spkrs)
    {
        if(attachedSpeakers)
            cout << "already have speakers attached!\n";
        else
            attachedSpeakers = &spkrs;
    }

    void detachSpeakers() { // should there be an "error" message if not attached?
        attachedSpeakers = nullptr;
    }

    void playMusic( ) const {
        if (attachedSpeakers)
            attachedSpeakers -> vibrateSpeakerCones(440);
        else
            cout << "No speakers attached\n";
    }
private:
   const SpeakerSystem* attachedSpeakers = nullptr;
};

// Task 2: Create main and add code to it.

int main() {
    cout << "Task 2: " << endl;
    int x;
    x = 10;
    cout << "x = " << x << endl;
    // Task 3: Using the debug facilities in environment

    // Task 4: Step over in IDE

    // Task 5: Using the "Watch" tab
    cout << endl;
    cout << "Task 6: " << endl;
    cout << 0xB << endl; //Task 6: Using the "address-of" operator

    // Task 7: Finding what is stored at the address of "x" -- 10 of course

    //Task 8: pointers
    cout << endl;
    cout << "Task 8: " << endl;
    int* p;
    p = &x;
    cout << "p = " << p << endl;
    //Task 9: Error
    //p = 0x00007ffeecbfea7c;

    //Task 10: dereferencing a pointer
    cout << endl;
    cout << "Task 10: " << endl;
    cout << "p points to where " << *p << " is stored\n";
    cout << "*p contains " << *p << endl;

    //Task 11: Changing x using *p
    cout << endl;
    cout << "Task 11: " << endl;
    *p = -2763;
    cout << "p points to where " << *p << " is      stored\n";
    cout << "*p now contains " << *p << endl;
    cout << "x now contains " << x << endl;

    //Task 12: We made p point to y and changed y through *p
    cout << endl;
    cout << "Task 12: " << endl;
    int y(13);
    cout << "y contains " << y << endl;
    p = &y;
    cout << "p now points to where " << *p << " is stored\n";
    cout << "*p now contains " << *p << endl;
    *p = 980;
    cout << "p points to where " << *p << " is stored\n";
    cout << "*p now contains " << *p << endl;
    cout << "y now contains " << y << endl;

    //Task 13:
    cout << endl;
    cout << "Task 13: " << endl;
    int* q;
    q = p;
    cout << "q points to where " << *q << " is stored\n";
    cout << "*q contains " << *q << endl;

    //Task 14
    cout << endl;
    cout << "Task 14: " << endl;
    double d(33.44);
    double* pD(&d);
    *pD = *p;
    *pD = 73.2343;
    *p  = *pD;
    //*q  = *p;
    //pD  = p;
    // The error occurs in the last two lines

    // Task 15
    cout << endl;
    cout << "Task 15: " << endl;
    int joe = 24;
    const int sal = 19;
    int*  pI;
    pI = &joe;
    *pI = 234;
    //pI = &sal; not allowed
    *pI = 7623;

    const int* pcI;
    pcI = &joe;
    //*pcI = 234; not allowed
    pcI = &sal;
    //*pcI = 7623; not allowed

    //int* const cpI; not allowed
    int* const cpI(&joe);
    //int* const cpI(&sal); redefinition
    //cpI = &joe; not allowed
    *cpI = 234;
    //cpI = &sal; not allowed
    *cpI = 7623;

    //const int* const cpcI; not allowed
    const int* const cpcI(&joe);
    //const int* const cpcI(&sal); Not allowed
    //cpcI = &joe; not allowed
    //*cpcI = 234; not allowed
    //cpcI = &sal; not allowed
    //*cpcI = 7623; not allowed

    //Task 16:
    cout << endl;
    cout << "Task 16: " << endl;
    Complex c = {11.23,45.67};
    Complex* pC(&c);
    //cout << "real: " << *pC.real << "\nimaginary: " << *pC.img << endl; wrong way
    //cout << "real: " << (*pC).real << "\nimaginary: " << (*pC).img << endl; better way not clumsy
    cout << "real: " << pC->real << "\nimaginary: " << pC->img << endl; // right syntax

    // Task 17
    cout <<  endl;
    cout << "Task 17: " << endl;
    PlainOldClass poc;
    PlainOldClass* ppoc( &poc );
    cout << ppoc->getX() << endl;
    ppoc->setX( 2837 );
    cout << ppoc->getX() << endl;

    //Task 18
    cout << endl;
    cout << "Task 18: " << endl;
    int* pDyn = new int(3); // p points to an int initialized to 3 on the heap
    *pDyn = 17;
    cout << "The " << *pDyn
         << " is stored at address " << pDyn
         << " which is in the heap\n";
    cout << pDyn << endl;
    delete pDyn;
    //pDyn = nullptr; // Task 21
    cout << pDyn << endl;

    cout << "The 17 might STILL be stored at address " << pDyn<< " even though we deleted pDyn\n";
    cout << "But can we dereference pDyn?  We can try.  This might crash... " << *pDyn << ".  Still here?\n";

    //Task 21: nullptr
    cout << endl;
    cout << "Task 21: " << endl;
    double* pDouble = nullptr;

    //Task 22: dereferencing nullptr
    cout << endl;
    cout << "Task 22: " << endl;
    //cout << "Can we dereference nullptr?  " << *pDyn << endl;
    //cout << "Can we dereference nullptr?  " << *pDouble << endl;

    // Task 23

    //Task 24: deleting nullptr
    cout << endl;
    cout << "Task 24: " << endl;
    double* pTest = new double(12);
    delete pTest;
    pTest = nullptr;
    delete pTest; // safe

    //Task 25:
    cout << endl;
    cout << "Task 25: " << endl;
    short* pShrt = new short(5);
    //delete pShrt;
    //delete pShrt;
    // My system raises an error and sets a breakpoint to debug

    //Task 26:
    cout << endl;
    cout << "Task 26: " << endl;
//    long jumper = 12238743;
//    delete jumper;
//    long* ptrTolong = &jumper;
//    delete ptrTolong;
//    Complex cmplx;
//    delete cmplx;

    //Task 27:
    cout << endl;
    cout << "Task 27: " << endl;
    vector<Complex*> complV; // can hold pointers to Complex objects
    Complex* tmpPCmplx;      // space for a Complex pointer
    for (size_t ndx = 0; ndx < 3; ++ndx) {
        tmpPCmplx = new Complex; // create a new Complex object on the heap
        tmpPCmplx->real = ndx;   // set real and img to be the
        tmpPCmplx->img  = ndx;   // value of the current ndx
        complV.push_back(tmpPCmplx); // store the ADDRESS of the object in a vector or pointer to Complex
    }
// display the objects using the pointers stored in the vector
    for (size_t ndx = 0; ndx < 3; ++ndx) {
        cout << complV[ ndx ]->real << endl;
        cout << complV[ ndx ]->img  << endl;
    }
// release the heap space pointed at by the pointers in the vector
    for (size_t ndx = 0; ndx < 3; ++ndx) {
        delete complV[ndx];
    }
// clear the vector
    complV.clear();

    //Task 28:
    cout << endl;
    cout << "Task 28: " << endl;
    vector<Colour*> colours;
    string inputName;
    unsigned inputR, inputG, inputB;

// fill vector with Colours from the file
// this could be from an actual file but here we are using the keyboard instead of a file
// (so we don't have to create an actual file)
// Do you remember the keystroke combination to indicate "end of file" at the keyboard?
// somehow the while's test has to fail - from keyboard input
    while (cin >> inputName >> inputR >> inputG >> inputB) {
        colours.push_back(new Colour(inputName, inputR, inputG, inputB));
    }

// display all the Colours in the vector:
    for (size_t ndx = 0; ndx < colours.size(); ++ndx) {
        colours[ndx]->display();
        cout << endl;
    }



}



