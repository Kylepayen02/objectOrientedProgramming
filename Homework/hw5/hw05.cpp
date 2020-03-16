/*
hw05.cpp
Kyle Payen
Association: Noble - Warrior
Code for hw05
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
    bool ishired() const {return hired;};

    void changeStrength(double ratio){
        warriorStrength -= (warriorStrength * ratio);
    };

    bool hire(){
        if (hired == true){
            return false;
        }
        else{
            hired = true;
            return true;
        }
    }

    void fire(){
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
    // constructor
    Noble(const string& name) : nobleName(name), strength(0), alive(true){};


    // getters
    string getName() const {return nobleName;}
    int getStrength() const {return strength;}
    vector<Warrior*> getArmy() const {return warriorArmy;}

    void changeStrength(double ratio){ // this function will change the strength of each warrior
        strength = 0;
        for (size_t i = 0; i < warriorArmy.size(); ++i){
            warriorArmy[i]->changeStrength(ratio);
            strength += warriorArmy[i]->getStrength();
        }

    }

    bool hire(Warrior& aWarrior){
        // if warrior is not already hired and the noble is not dead, hire a warrior

        if (alive && aWarrior.hire()){
            warriorArmy.push_back(&aWarrior);
            strength += aWarrior.getStrength();
            return true;
        }
        //cannot hire a warrior if a noble is dead or a warrior is already hired
        cerr << "Error: noble" << getName() << " is attempting to hire warrior " << aWarrior.getName() << "who is already employed" << endl;
        return false;
    }

    bool fire(Warrior& firedWarrior){
        // noble is dead, cannot fire warriors
        if (!alive){return false;}
        // else, fire the warrior
        firedWarrior.fire();
        strength -= firedWarrior.getStrength();
        bool moveWarriors = false;
        for(size_t j = 0; j < warriorArmy.size(); ++j){
            // if we found the warrior to remove, set bool to true
            // move the rest of the vector over one and delete
            if (warriorArmy[j] == &firedWarrior){
                moveWarriors = true;
            }

            if (j == (warriorArmy.size()-1)){
                warriorArmy.pop_back();
                break;
            }

            else if (moveWarriors == true){
                warriorArmy[j] = warriorArmy[j+1];
            }
        }
        cout << "You don't work for me anymore ";
        cout << firedWarrior.getName() << "! -- " << nobleName << endl;
        return true;
    }

    void killed(){
        // kill noble and all the warriors
        alive = false;
        strength = 0;
        for (size_t i = 0; i < warriorArmy.size(); ++i){
            warriorArmy[i]->killed();
        }
    }

    bool isAlive(){return alive;};

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
            double ratio = (double(strength) /
                            double(opponent.getStrength()));
            opponent.changeStrength(ratio);
            killed();
            cout << opponent.getName() << " defeats " << nobleName << endl;
        }


            // Noble defeats opponent
        else if (opponent.getStrength() < strength){
            double ratio = (double(opponent.getStrength()) /
                            double(strength));
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

ifstream openFile(const string& fileName);
void nobleCommand(ifstream& ifs, vector<Noble*>& allNobles);
void warriorCommand(ifstream& ifs, vector<Warrior*>& allWarriors);
void status(vector<Noble*>& nobleList, vector<Warrior*>& warriorList, vector<Warrior>& unemployedWarriors);
void clearLists(vector<Noble*>& nobleList, vector<Warrior*>& warriorList);
size_t findNoble(const string& nobleName, vector<Noble*>& nobleList);
size_t findWarrior(const string& warriorName, vector<Warrior*>& warriorList);
void hire(ifstream& ifs, vector<Noble*>& nobleList, vector<Warrior*>& warriorList);
void battle(ifstream& ifs, vector<Noble*>& nobleList, vector<Warrior*>& warriorList);
void checkCommands(ifstream& ifs, vector<Noble*>& nobleList, vector<Warrior*>& warriorList, vector<Warrior>& unemployedWarriors);
void fire(ifstream& ifs, vector<Noble*>& nobleList);

int main(){
    vector<Noble*> nobleList;
    vector<Warrior*> warriorList;
    vector<Warrior> unemployedWarriors;
    ifstream nobleWarriors = openFile("nobleWarriors-20S.txt");
    checkCommands(nobleWarriors, nobleList, warriorList, unemployedWarriors);
    nobleWarriors.close();
}

ifstream openFile(const string& fileName){
    ifstream ifs(fileName);
    if(!ifs){
        cerr << "failed to open warriors" << endl;
        exit(1);
    }
    return ifs;
}

void checkCommands(ifstream& ifs, vector<Noble*>& nobleList, vector<Warrior*>& warriorList, vector<Warrior>& unemployedWarriors) {
    string command;
    while (ifs >> command) { // read each command in the file
        if (command == "Noble") {
            nobleCommand(ifs,nobleList);
        }
        else if (command == "Warrior") {
            warriorCommand(ifs, warriorList);
        }
        else if (command == "Status"){
            status(nobleList, warriorList, unemployedWarriors);
        }
        else if (command == "Clear"){
            clearLists(nobleList, warriorList);
        }
        else if (command == "Hire"){
            hire(ifs, nobleList, warriorList);
        }
        else if (command == "Battle"){
            battle(ifs, nobleList, warriorList);
        }
        else{
            fire(ifs, nobleList);
        }

    }
}

void nobleCommand(ifstream& ifs, vector<Noble*>& allNobles){
    string nobleName;
    ifs >> nobleName;
    bool exists = false;
    for (size_t i = 0; i < allNobles.size(); ++i){
        if (allNobles[i]->getName() == nobleName){
            exists = true;
            cerr << "Error: noble " << nobleName << " already exists, use a different name.";
        }
    }
    if (exists == false){
        Noble* aNoble = new Noble(nobleName);
        allNobles.push_back(aNoble);
    }
}

void warriorCommand(ifstream& ifs, vector<Warrior*>& allWarriors){
    string warriorName;
    int warriorStrength;
    bool exists = false;
    ifs >> warriorName >> warriorStrength;
    for (size_t i = 0; i < allWarriors.size(); ++i){
        if (allWarriors[i]->getName() == warriorName){
            exists = true;
            cerr << "Error: warrior " << warriorName << " already exists, use a different name.";
        }
    }
    if (exists == false){
        Warrior* aWarrior = new Warrior(warriorName, warriorStrength);
        allWarriors.push_back(aWarrior);
    }

}

void status(vector<Noble*>& nobleList, vector<Warrior*>& warriorList, vector<Warrior>& unemployedWarriors){
    cout << "Status" << endl;
    cout << "====" << endl;
    cout << "Nobles:" << endl;
    if (nobleList.size() == 0){
        cout << "NONE" << endl;
    }
    else{
        for (size_t i = 0; i < nobleList.size(); i++){ // for each noble in the list of all nobles, display their status. Then display the unemployed warriors
            cout << *nobleList[i] << endl;
        }
    }
    cout << "Unemployed Warriors:" << endl;
    for (Warrior*& aWarrior : warriorList){
        if (aWarrior->ishired() == false){
            unemployedWarriors.emplace_back(*aWarrior);
        }
    }
    if (unemployedWarriors.size() == 0) {
        cout << "NONE" << endl;
    }
    else{
        for (Warrior& aWarrior : unemployedWarriors){ // display the status of each of the unemployed Warriors
            cout << aWarrior << endl;
        }
    }
    unemployedWarriors.clear();

}

void clearLists(vector<Noble*>& nobleList, vector<Warrior*>& warriorList){
    nobleList.clear();
    warriorList.clear();
}

size_t findNoble(const string& nobleName, vector<Noble*>& nobleList){
    for (size_t i = 0; i < nobleList.size(); ++i){
        if (nobleList[i]->getName() == nobleName){
            return i;
        }
    }
    return nobleList.size();
}

size_t findWarrior(const string& warriorName, vector<Warrior*>& warriorList){
    for (size_t i = 0; i < warriorList.size(); ++i){
        if (warriorList[i]->getName() == warriorName){
            return i;
        }
    }
    return warriorList.size();
}


void hire(ifstream& ifs, vector<Noble*>& nobleList, vector<Warrior*>& warriorList){
    string nobleName;
    string warriorName;
    ifs >> nobleName >> warriorName;
    size_t indexOfNoble = findNoble(nobleName, nobleList);
    size_t indexOfWarrior = findWarrior(warriorName, warriorList);
    if ((indexOfNoble < nobleList.size() && (indexOfWarrior < warriorList.size()))){
        nobleList[indexOfNoble]->hire(*warriorList[indexOfWarrior]);
    }
    else if ((indexOfNoble < nobleList.size() && (indexOfWarrior == warriorList.size()))){
        cerr << "Error: The warrior does not exist" << endl;
    }
    else if ((indexOfNoble == nobleList.size() && (indexOfWarrior < warriorList.size()))){
        cerr << "Error: The Noble does not exist" << endl;
    }
    else{
        cerr << "Error: Both the Noble and the Warrior do not exist" << endl;
    }
}

void battle(ifstream& ifs, vector<Noble*>& nobleList, vector<Warrior*>& warriorList){
    string noble1Name;
    string noble2Name;
    ifs >> noble1Name >> noble2Name;
    size_t indexOfNoble1 = findNoble(noble1Name, nobleList);
    size_t indexOfNoble2 = findNoble(noble2Name, nobleList);
    if ((indexOfNoble1 < nobleList.size() && (indexOfNoble2 < nobleList.size()))){
        nobleList[indexOfNoble1]->battle(*nobleList[indexOfNoble2]);
    }
    else if ((indexOfNoble1 < nobleList.size() && (indexOfNoble2 == nobleList.size()))){
        cerr << "The Noble " << nobleList[indexOfNoble2]->getName() << " does not exist" << endl;
    }
    else if ((indexOfNoble1 == nobleList.size() && (indexOfNoble2 < nobleList.size()))){
        cerr << "The Noble " << nobleList[indexOfNoble1]->getName() << " does not exist" << endl;
    }
    else{
        cerr << "Both the Nobles do not exist" << endl;
    }
}

void fire(ifstream& ifs, vector<Noble*>& nobleList){
    string nobleName;
    string warriorName;
    ifs >> nobleName >> warriorName;
    size_t indexOfNoble = findNoble(nobleName, nobleList);
    if (indexOfNoble == nobleList.size()){
        cerr << "The noble does not exist" << endl;
    }
    else {
        size_t warriorIndex = nobleList[indexOfNoble]->getArmy().size();
        for (size_t i = 0; i < nobleList[indexOfNoble]->getArmy().size(); ++i){
            if (nobleList[indexOfNoble]->getArmy()[i]->getName() == warriorName){
                warriorIndex = i;
            }
        }
        if (warriorIndex < nobleList[indexOfNoble]->getArmy().size()){
            nobleList[indexOfNoble]->fire(*nobleList[indexOfNoble]->getArmy()[warriorIndex]);
        }
    }
}

