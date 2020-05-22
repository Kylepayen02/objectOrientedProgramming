/*
hw04.cpp
Kyle Payen
Association: Noble - Warrior
Code for hw04
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// This is the class for the Warrior object
class Warrior{
    friend ostream& operator<<(ostream& os, const Warrior& aWarrior){
        os << aWarrior.warriorName << " : " << aWarrior.warriorStrength;
        return  os;
    }

public:
    Warrior(const string& name, int strength): warriorName(name), warriorStrength(strength), hired(false), alive(true) {};

    // getters
    int getStrength() const {return warriorStrength;}
    string getName() const {return warriorName;}

    void changeStrength(double ratio){
        warriorStrength -= (warriorStrength * ratio);
    };

    bool getHire(){
        if (hired == true){
            return false;
        }
        else{
            hired = true;
            return true;
        }
    }

    void fired(){
        hired = false;
    };

    void killed(){
        alive = false;
        warriorStrength = 0;
    }

private:
    string warriorName;
    int warriorStrength;
    bool alive, hired;
};

class Noble{
    friend ostream& operator<<(ostream& os, const Noble& aNoble){
        os << aNoble.nobleName << " has an army of " << aNoble.warriorArmy.size() << endl;
        for  (size_t i = 0; i < aNoble.warriorArmy.size(); ++i){
            os << "     " << *aNoble.warriorArmy[i] << endl;
        }

        return os;
    }

public:
    Noble(const string& name) : nobleName(name), strength(0), alive(true){};

    // getters
    string getName() const {return nobleName;}
    int getStrength() const {return strength;}

    void changeStrength(double ratio){ // this function will change the strength of each warrior
        strength = 0;
        for (size_t i = 0; i < warriorArmy.size(); ++i){
            warriorArmy[i]->changeStrength(ratio);
            strength += warriorArmy[i]->getStrength();
        }

    }

    bool hire(Warrior& aWarrior){
        // if warrior is not already hired and the noble is not dead, hire a warrior

        if (alive && aWarrior.getHire()){
            warriorArmy.push_back(&aWarrior);
            strength += aWarrior.getStrength();
            return true;
        }
        //cannot hire a warrior if a noble is dead or a warrior is already hired
        return false;
    }

    bool fire(Warrior& firedWarrior){
        // noble is dead, cannot fire warriors
        if (!alive){return false;}
        // else, fire the warrior
        firedWarrior.fired();
        strength -= firedWarrior.getStrength();
        bool moveWarriors = false;
        for(size_t j = 0; j < warriorArmy.size(); ++j){ // iterate through the vector of warrior pointers
            // if we found the warrior to remove, set bool to true
            // move the rest of the vector over one and delete
            // if (warriorArmy[j] == &firedWarrior){
            //     moveWarriors = true;
            // }

            // if (j == (warriorArmy.size()-1)){
            //     warriorArmy.pop_back();
            //     break;
            // }

            // else if (moveWarriors == true){
            //     warriorArmy[j] = warriorArmy[j+1];
            // }
            if (warriorArmy[j] == &firedWarrior){ // if the warrior pointer address is the same address as the firedWarrior
                Warrior* lastWarrior = warriorArmy[warriorArmy.size() - 1]; 
                warriorArmy[warriorArmy.size() - 1] = warriorArmy[j];
                warriorArmy[j] = lastWarrior;   // swap the pointer in the back of the vector with the current pointer
                warriorArmy.pop_back();  // remove the fired warrior pointer from the vector 
                cout << "You don't work for me anymore ";
                cout << firedWarrior.getName() << "! -- " << nobleName << endl;
                return true;
            }
        }
        return false; // else the fired warrior was not in the warrior army, fail silently
        
    }

    void killed(){
        // kill noble and all the warriors
        alive = false;
        strength = 0;
        for (size_t i = 0; i < warriorArmy.size(); ++i){
            warriorArmy[i]->killed();
        }
    }

    bool isAlive(){return alive;}

    void battle(Noble& opponent){
        cout << nobleName << " battles " << opponent.getName() << endl;

        // if one or both opponents is dead
        if (!opponent.isAlive()){
            if (!alive){
                cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
            }
            else{ cout << "He's dead, " << nobleName << endl;}
        }

            // if both opponents have the same stength
        else if(opponent.getStrength() == strength){
            killed();
            opponent.killed();
            cout << "Mutual Annihalation: " << nobleName << " and ";
            cout << opponent.getName() << "die at each other's hands" << endl;
        }

            // opponent defeats Noble
        else if (opponent.getStrength() > strength){
            double ratio = (double(strength) / double(opponent.getStrength() ) );
            opponent.changeStrength(ratio);
            killed();
            cout << opponent.getName() << " defeats " << nobleName << endl;
        }


            // Noble defeats opponent
        else if (opponent.getStrength() < strength){
            double ratio = (double(opponent.getStrength()) / double(strength));
            changeStrength(ratio);
            opponent.killed();
            cout << nobleName<< " defeats " << opponent.getName() << endl;
        }
    }

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

    cout << "==========\n"
         << "Status before all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";

    art.fire(cheetah);
    cout << art << endl;

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "==========\n"
         << "Status after all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";
}
