/*
warrior.h
Kyle Payen
Cyclic Association and Seperate Compilation 
*/

#include <iostream>
#include <vector>
#include <string>


namespace WarriorCraft{
        
    class Noble;

    // This is the class for the Warrior object
    class Warrior
    {
        friend std::ostream &operator<<(std::ostream &os, const Warrior &aWarrior);

    public:
        Warrior(const std::string &name, int strength);

        // getters
        int getStrength() const;
        std::string getName() const;

        void changeStrength(double ratio);

        bool getHire(Noble *);

        void fired();

        void killed();

        void runaway();

    private:
        std::string warriorName;
        int warriorStrength;
        bool alive, hired;
        Noble *employer;
    };
}