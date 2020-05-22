/*
noble.cpp
Kyle Payen
Cyclic Association and Seperate Compilation 
*/

#include "warrior.h"
#include "noble.h"

using namespace std;

namespace WarriorCraft{
    
    ostream &operator<<(ostream &os, const Noble &aNoble)
    {
        os << aNoble.nobleName << " has an army of " << aNoble.warriorArmy.size() << endl;
        for (size_t i = 0; i < aNoble.warriorArmy.size(); ++i)
        {
            os << "     " << *aNoble.warriorArmy[i] << endl;
        }
        return os;
    }

    Noble::Noble(const string &name) : nobleName(name), strength(0), alive(true){};

    string Noble::getName() const { return nobleName; }

    int Noble::getStrength() const { return strength; }

    void Noble::changeStrength(double ratio)
    { // this function will change the strength of each warrior
        strength = 0;
        for (size_t i = 0; i < warriorArmy.size(); ++i)
        {
            warriorArmy[i]->changeStrength(ratio);
            strength += warriorArmy[i]->getStrength();
        }
    }

    bool Noble::hire(Warrior &aWarrior)
    {
        // if warrior is not already hired and the noble is not dead, hire a warrior
        if (alive && aWarrior.getHire(this))
        {
            warriorArmy.push_back(&aWarrior);
            strength += aWarrior.getStrength();
            return true;
        }
        //cannot hire a warrior if a noble is dead or a warrior is already hired
        return false;
    }

    bool Noble::fire(Warrior &firedWarrior)
    {
        // noble is dead, cannot fire warriors
        if (!alive)
        {
            return false;
        }
        // else, fire the warrior
        firedWarrior.fired();
        strength -= firedWarrior.getStrength();
        for (size_t j = 0; j < warriorArmy.size(); ++j)
        {
            if (warriorArmy[j] == &firedWarrior)
            { // if the warrior pointer address is the same address as the firedWarrior
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

    void Noble::killed()
    {
        // kill noble and all the warriors
        alive = false;
        strength = 0;
        for (size_t i = 0; i < warriorArmy.size(); ++i)
        {
            warriorArmy[i]->killed();
        }
    }

    bool Noble::isAlive() { return alive; }

    void Noble::battle(Noble &opponent)
    {
        cout << nobleName << " battles " << opponent.getName() << endl;

        // if one or both opponents is dead
        if (!opponent.isAlive())
        {
            if (!alive)
            {
                cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
            }
            else
            {
                cout << "He's dead, " << nobleName << endl;
            }
        }

        // if both opponents have the same stength
        else if (opponent.getStrength() == strength)
        {
            killed();
            opponent.killed();
            cout << "Mutual Annihalation: " << nobleName << " and ";
            cout << opponent.getName() << "die at each other's hands" << endl;
        }

        // opponent defeats Noble
        else if (opponent.getStrength() > strength)
        {
            double ratio = (double(strength) / double(opponent.getStrength()));
            opponent.changeStrength(ratio);
            killed();
            cout << opponent.getName() << " defeats " << nobleName << endl;
        }

        // Noble defeats opponent
        else if (opponent.getStrength() < strength)
        {
            double ratio = (double(opponent.getStrength()) / double(strength));
            changeStrength(ratio);
            opponent.killed();
            cout << nobleName << " defeats " << opponent.getName() << endl;
        }
    }

    void Noble::releaseWarrior(Warrior &aWarrior)
    {
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
}