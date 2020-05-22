/*
hw06.cpp
Kyle Payen
Cyclic Association and Seperate Compilation 
*/

// #include "Noble.h"
// #include "Warrior.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;
// using namespace WarriorCraft;

class Noble;

// This is the class for the Warrior object
class Warrior{
    friend ostream& operator<<(ostream& os, const Warrior& aWarrior);

public:
    Warrior(const string& name, int strength);

    // getters
    int getStrength() const;
    string getName() const;

    void changeStrength(double ratio);

    bool getHire(Noble*);

    void fired();

    void killed();

    void runaway();

private:
    string warriorName;
    int warriorStrength;
    bool alive, hired;
    Noble* employer;
};

class Noble{
    friend ostream& operator<<(ostream& os, const Noble& aNoble);

public:
    Noble(const string& name);

    // getters
    string getName() const;
    int getStrength() const;

    void changeStrength(double ratio);

    bool hire(Warrior& aWarrior);

    bool fire(Warrior& firedWarrior);

    void killed();

    bool isAlive();

    void battle(Noble& opponent);

    void releaseWarrior(Warrior& aWarrior);

private:
    string nobleName;
    int strength;
    bool alive;
    vector<Warrior*> warriorArmy;

};


int main() {
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");
	
    Warrior cheetah("Tarzan", 10);
    Warrior wizard("Merlin", 15);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);
	
    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(wizard);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(cheetah);
	
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;

    cheetah.runaway();
    cout << art << endl;
	
    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);
}

ostream& operator<<(ostream& os, const Warrior& aWarrior){
    os << aWarrior.warriorName << " : " << aWarrior.warriorStrength;
    return  os;
}

Warrior::Warrior(const string& name, int strength): warriorName(name), warriorStrength(strength), alive(true), hired(false), employer(nullptr) {};


int Warrior::getStrength() const {return warriorStrength;}
string Warrior::getName() const {return warriorName;}

void Warrior::changeStrength(double ratio){
    warriorStrength -= (warriorStrength * ratio);
}

bool Warrior::getHire(Noble* noblePtr){
    if (employer != nullptr){
        return false;
    }
    employer = noblePtr;
    return true;
}

void Warrior::fired(){hired = false;}

void Warrior::killed(){
    alive = false;
    warriorStrength = 0;
}

void Warrior::runaway(){
    cout << warriorName << " flees in terror, abandoning his lord " << employer->getName() << endl;
    employer->releaseWarrior(*this);
    employer = nullptr; 
}

ostream &operator<<(ostream &os, const Noble &aNoble){
    os << aNoble.nobleName << " has an army of " << aNoble.warriorArmy.size() << endl;
    for (size_t i = 0; i < aNoble.warriorArmy.size(); ++i){
        os << "     " << *aNoble.warriorArmy[i] << endl;
    }
    return os;
}

Noble::Noble(const string &name) : nobleName(name), strength(0), alive(true) {};

string Noble::getName() const { return nobleName; }

int Noble::getStrength() const { return strength; }

void Noble::changeStrength(double ratio){ // this function will change the strength of each warrior
    strength = 0;
    for (size_t i = 0; i < warriorArmy.size(); ++i){
        warriorArmy[i]->changeStrength(ratio);
        strength += warriorArmy[i]->getStrength();
    }
}

bool Noble::hire(Warrior &aWarrior){
    // if warrior is not already hired and the noble is not dead, hire a warrior
    if (alive && aWarrior.getHire(this)){
        warriorArmy.push_back(&aWarrior);
        strength += aWarrior.getStrength();
        return true;
    }
    //cannot hire a warrior if a noble is dead or a warrior is already hired
    return false;
}

bool Noble::fire(Warrior &firedWarrior){
    // noble is dead, cannot fire warriors
    if (!alive){
        return false;
    }
    // else, fire the warrior
    firedWarrior.fired();
    strength -= firedWarrior.getStrength();
    for (size_t j = 0; j < warriorArmy.size(); ++j){ 
        if (warriorArmy[j] == &firedWarrior){ // if the warrior pointer address is the same address as the firedWarrior
            Warrior *lastWarrior = warriorArmy[warriorArmy.size() - 1];
            warriorArmy[warriorArmy.size() - 1] = warriorArmy[j];
            warriorArmy[j] = lastWarrior; // swap the pointer in the back of the vector with the current pointer
            warriorArmy.pop_back();       // remove the fired warrior pointer from the vector
            cout << "You don't work for me anymore ";
            cout << firedWarrior.getName() << "! -- " << nobleName << endl;
            return true;
        }
    }
    return false; // else the fired warrior was not in the warrior army, fail silently
}

void Noble::killed(){
    // kill noble and all the warriors
    alive = false;
    strength = 0;
    for (size_t i = 0; i < warriorArmy.size(); ++i){
        warriorArmy[i]->killed();
    }
}

bool Noble::isAlive() { return alive; }

void Noble::battle(Noble &opponent){
    cout << nobleName << " battles " << opponent.getName() << endl;

    // if one or both opponents is dead
    if (!opponent.isAlive()){
        if (!alive){
            cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
        }
        else{
            cout << "He's dead, " << nobleName << endl;
        }
    }

    // if both opponents have the same stength
    else if (opponent.getStrength() == strength){
        killed();
        opponent.killed();
        cout << "Mutual Annihalation: " << nobleName << " and ";
        cout << opponent.getName() << "die at each other's hands" << endl;
    }

    // opponent defeats Noble
    else if (opponent.getStrength() > strength){
        double ratio = (double(strength) / double(opponent.getStrength()));
        opponent.changeStrength(ratio);
        killed();
        cout << opponent.getName() << " defeats " << nobleName << endl;
    }

    // Noble defeats opponent
    else if (opponent.getStrength() < strength){
        double ratio = (double(opponent.getStrength()) / double(strength));
        changeStrength(ratio);
        opponent.killed();
        cout << nobleName << " defeats " << opponent.getName() << endl;
    }
}

void Noble::releaseWarrior(Warrior& aWarrior){
    aWarrior.fired();
    strength -= aWarrior.getStrength();
    for (size_t j = 0; j < warriorArmy.size(); ++j)
    {
        if (warriorArmy[j] == &aWarrior)
        { // if the warrior pointer address is the same address as the firedWarrior
            Warrior *lastWarrior = warriorArmy[warriorArmy.size() - 1];
            warriorArmy[warriorArmy.size() - 1] = warriorArmy[j];
            warriorArmy[j] = lastWarrior; // swap the pointer in the back of the vector with the current pointer
            warriorArmy.pop_back();       // remove the fired warrior pointer from the vector

        }
    }
}