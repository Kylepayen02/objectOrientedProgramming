/*
noble.h
Kyle Payen
Cyclic Association and Seperate Compilation 
*/

#include <iostream>
#include <vector>
#include <string>

namespace WarriorCraft
{
    class Warrior;

    class Noble
    {
        friend std::ostream &operator<<(std::ostream &os, const Noble &aNoble);

    public:
        Noble(const std::string &name);

        // getters
        std::string getName() const;
        int getStrength() const;

        void changeStrength(double ratio);

        bool hire(Warrior &aWarrior);

        bool fire(Warrior &firedWarrior);

        void killed();

        bool isAlive();

        void battle(Noble &opponent);

        void releaseWarrior(Warrior &aWarrior);

    private:
        std::string nobleName;
        int strength;
        bool alive;
        std::vector<Warrior *> warriorArmy;
    };
}