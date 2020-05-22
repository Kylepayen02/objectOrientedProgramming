/*
warrior.cpp
Kyle Payen
Cyclic Association and Seperate Compilation 
*/

#include "warrior.h"
#include "noble.h"

using namespace std;

namespace WarriorCraft{

    ostream &operator<<(ostream &os, const Warrior &aWarrior)
    {
        os << aWarrior.warriorName << " : " << aWarrior.warriorStrength;
        return os;
    }

    Warrior::Warrior(const string &name, int strength) : warriorName(name), warriorStrength(strength), alive(true), hired(false), employer(nullptr){};

    int Warrior::getStrength() const { return warriorStrength; }
    string Warrior::getName() const { return warriorName; }

    void Warrior::changeStrength(double ratio)
    {
        warriorStrength -= (warriorStrength * ratio);
    }

    bool Warrior::getHire(Noble *noblePtr)
    {
        if (employer != nullptr)
        {
            return false;
        }
        employer = noblePtr;
        return true;
    }

    void Warrior::fired() { hired = false; }

    void Warrior::killed()
    {
        alive = false;
        warriorStrength = 0;
    }

    void Warrior::runaway()
    {
        cout << warriorName << " flees in terror, abandoning his lord " << employer->getName() << endl;
        employer->releaseWarrior(*this);
        employer = nullptr;
    }
}