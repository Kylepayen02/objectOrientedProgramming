// hw07.cpp 
// Inheritance: Nobles and Warriors 

#include <string>
#include <vector>
#include <iostream> 
using namespace std; 

class Protector; 

class Noble{
public:
    Noble(const string& name);

    const string& getName() const;

    bool isAlive() const;

    virtual void killed();

    virtual int getStrength() const = 0;

    virtual void changeStrength(double ratio) = 0;

    void battle(Noble& aNoble);

    virtual void fightingSound() const = 0;

private: 
    string name;
    bool alive;
};

class Lord : public Noble{
public:
    Lord(const string& name);

    int getStrength() const;

    bool hires(Protector& aProtector);

    void fires(Protector& aProtector);

    void killed();

    void changeStrength(double ratio);

    void letQuit(Protector* aProtector);

    void fightingSound() const;

private:
    vector<Protector*> army;
    int strength; 
};

class PersonWithStrengthToFight : public Noble{
public:
    PersonWithStrengthToFight(const string& name, int strength);

    int getStrength() const;

    void fightingSound() const;

    void killed();

    void changeStrength(double ratio);

private:
    int strength;
};


class Protector{
public:
    Protector(const string& name, int strength);

    Noble* getBoss() const;

    const string& getName() const;

    bool hire(Lord& aLord);

    int getStrength() const;

    void fired();

    void killed();

    void changeStrength(double ratio);

    void quit();

    virtual void battleCry() const = 0;


private: 
    string name; 
    int strength;
    bool alive; 
    Lord* boss;
};

class Wizard : public Protector{
public: 
    Wizard (const string& name, int strength);
    void battleCry() const;
};

class Archer : public Protector{
public: 
    Archer(const string& name, int strength);
    void battleCry() const;
};

class Swordsman : public Protector{
public: 
    Swordsman(const string& name, int strength);
    void battleCry() const;
};


int main() {
    Lord sam("Sam");
    Archer samantha("Samantha", 200);
    sam.hires(samantha);
    Lord joe("Joe");
    PersonWithStrengthToFight randy("Randolf the Elder", 250); 	
    joe.battle(randy);	
    joe.battle(sam);	
    Lord janet("Janet");	
    Swordsman hardy("TuckTuckTheHardy", 100);
    Swordsman stout("TuckTuckTheStout", 80);
    janet.hires(hardy);	
    janet.hires(stout);	
    PersonWithStrengthToFight barclay("Barclay the Bold", 300);	
    janet.battle(barclay);	
    janet.hires(samantha);	
    Archer pethora("Pethora", 50);	
    Archer thora("Thorapleth", 60);
    Wizard merlin("Merlin", 150);
    janet.hires(pethora);
    janet.hires(thora);
    sam.hires(merlin);
    janet.battle(barclay);	
    sam.battle(barclay);	
    joe.battle(barclay);
}

Noble::Noble(const string& name) : name(name), alive(true){}

const string& Noble::getName() const { return name; }

bool Noble::isAlive() const { return alive; }

void Noble::killed() { alive = false; }


void Noble::battle(Noble& aNoble){
    cout << name << " battles " << aNoble.name << endl;

    // if one or both opponents is dead
    if ((!aNoble.alive) && (!alive)){
        cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
        return;
    }
    else if (!aNoble.alive){
        fightingSound();
        cout << "He's dead, " << name << endl;
        return;
    }
    else if (!alive){
        aNoble.fightingSound();
        cout << "He's dead, " << aNoble.name << endl;
        return;
    }

    // if both opponents have the same stength
    else if (aNoble.getStrength() == getStrength()){
        killed();
        aNoble.killed();
        cout << "Mutual Annihalation: " << name << " and ";
        cout << aNoble.name << "die at each other's hands" << endl;
    }

        // opponent defeats Noble
    else if (aNoble.getStrength() > getStrength()){
        fightingSound();
        aNoble.fightingSound();
        double ratio = double(getStrength()) / double(aNoble.getStrength());
        aNoble.changeStrength(ratio);
        killed();
        cout << aNoble.name << " defeats " << name << endl;
    }


        // Noble defeats opponent
    else if (aNoble.getStrength() < getStrength()){
        fightingSound();
        aNoble.fightingSound();
        double ratio = (double(aNoble.getStrength()) / double(getStrength()));
        changeStrength(ratio);
        aNoble.killed();
        cout << name<< " defeats " << aNoble.name << endl;
    }
}

Lord::Lord(const string& name) : Noble(name), strength(0) {}

int Lord::getStrength() const{ return strength; }

bool Lord::hires(Protector& aProtector){
    if ((isAlive()) && aProtector.hire(*this)){
        army.push_back(&aProtector);
        strength += aProtector.getStrength();
        return true;
    }
    return false;
}

void Lord::fires(Protector& aProtector){
    for (size_t i = 0; i < army.size(); ++i){
        if (army[i] == &aProtector){
            Protector* temp = army[army.size()-1];
            army[army.size()-1] = army[i]; 
            army[i] = temp;
            army.pop_back(); 
        }
    }
    strength -= aProtector.getStrength();
    aProtector.fired();

}

void Lord::killed(){
    for (size_t i = 0; i < army.size(); ++i){
        army[i]->killed();
    }
    Noble::killed();
}

void Lord::changeStrength(double ratio){
    strength = 0;
    for (size_t i = 0; i < army.size(); ++i){
        army[i]->changeStrength(ratio);
        strength += army[i]->getStrength(); 
    }
}

void Lord::letQuit(Protector* aProtector){
    strength -= aProtector->getStrength();
    for (size_t i = 0; i < army.size(); ++i){
        if (army[i] == aProtector){
            Protector* temp = army[army.size()-1];
            army[army.size()-1] = army[i]; 
            army[i] = temp;
            army.pop_back(); 
        }
    }
}

void Lord::fightingSound() const{
    for(size_t i = 0; i < army.size(); ++i){
        army[i]->battleCry();
    }
}

PersonWithStrengthToFight::PersonWithStrengthToFight(const string& name, int strength) : Noble(name), strength(strength) {}

int PersonWithStrengthToFight::getStrength() const { return strength; }

void PersonWithStrengthToFight::fightingSound() const{
    cout << "Ugh!" << endl;
}

void PersonWithStrengthToFight::killed(){
    strength = 0;
    Noble::killed();
}

void PersonWithStrengthToFight::changeStrength(double ratio){
    strength *= (1-ratio);
}

Protector::Protector(const string& name, int strength) : name(name), strength(strength), alive(true), boss(nullptr){}

Noble* Protector::getBoss() const { return boss;}

const string& Protector::getName() const{ return name; }

bool Protector::hire(Lord& aLord){
    if ((boss == nullptr) && alive){
        boss = &aLord;
        return true;
    }
    return false;
}

int Protector::getStrength() const { return strength; }

void Protector::fired(){
    boss = nullptr;
}

void Protector::killed(){
    strength = 0; 
    alive = false; 
}

void Protector::changeStrength(double ratio){
    strength *= (1-ratio);
}

void Protector::quit(){
    cout << name << " quits, abandoning his lord " << boss->getName() << endl;
    boss->letQuit(this);
    boss = nullptr;
}

Wizard::Wizard (const string& name, int strength) : Protector(name, strength) {}

void Wizard::battleCry() const{
    cout << "POOF!" << endl;
}

Archer::Archer(const string& name, int strength) : Protector(name, strength) {}

void Archer::battleCry() const{
    cout << "TWANG! " << getName() << " says: Take that in the name of my lord, " << getBoss()->getName()<< endl;
}

Swordsman::Swordsman(const string& name, int strength) : Protector(name, strength) {}

void Swordsman::battleCry() const{
    cout << "CLANG! " << getName() << " says: Take that in the name of my lord, " << getBoss()->getName()<< endl;
}