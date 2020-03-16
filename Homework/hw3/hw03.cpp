/*
 Kyle Payen
 02/08/20
 This program will model a game of medieval times.
 The program will read a file of commands including: Warrior, Battle, and Status.
 */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// This is the class for the Warrior object
class Warrior{

private:

    class Weapon{

        friend ostream& operator<<(ostream& os, Weapon& aWeapon){
            os << ", weapon: " << aWeapon.getName() << ", " << aWeapon.getStrength();
            return  os;
        }

    private:

        string weaponName;
        int weaponStrength;

    public:

        Weapon(const string& theName, int theStrength) : weaponName(theName), weaponStrength(theStrength){ };

        string getName(){
            return weaponName;
        }

        int getStrength(){
            return weaponStrength;
        }

        void changeStrength(int newStrength){
            weaponStrength = newStrength;
        }




    };

    string name;
    string aWeaponName;
    int strength;
    Weapon weapon;



public:

    friend ostream& operator<<(ostream& os, Warrior& somebody);

    //getters
    string getName() const{
        return name;

    }
    int getStrength() {
        return strength;
    }

    Weapon getWeapon(){
        return weapon;
    }

    void weaponChangeStrength(int newStrength){
        return weapon.changeStrength(newStrength);
    }

    Warrior (const string& theName, const string& weaponName, int theStrength) :  name(theName), weapon(weaponName, theStrength){}




//    void display() const {
//        cout << "Warrior: "<< name << ", strength: "  << strength << endl;
//    }


};


ostream& operator<<(ostream& os, Warrior& somebody) {
    os << "Warrior: " << somebody.name << somebody.weapon << endl;

    return os;
    }


// This function will open the file.
ifstream openFile(const string& fileName){
    ifstream ifs(fileName);
    if(!ifs){
        cerr << "failed to open warriors" << endl;
        exit(1);
    }
    return ifs;
}

void warriorCommand(ifstream& ifs, vector<Warrior>& warriorList){ // This function will create a new warrior object and add it to the warrior list
    string theName;
    string theWeapon;
    int theStrength;
    ifs >> theName >> theWeapon >> theStrength;

    warriorList.emplace_back(theName, theWeapon, theStrength);
}

void statusCommand(vector<Warrior>& warriorList){ // This function will display each warrior in the warrior list
    cout << "There are: " << warriorList.size() << " warriors" << endl;
    for(size_t i = 0; i < warriorList.size(); i++){ // for each warrior in the warriorList vector, display the name, weapon name, and strength of the warrior
        cout << warriorList[i];
    }
}

void combatOutcomes(Warrior& warrior1, Warrior& warrior2){ // This function will execute the possible outcomes when two warriors battle
    if ((warrior1.getWeapon().getStrength() == warrior2.getWeapon().getStrength()) && (warrior1.getWeapon().getStrength() > 0 && warrior2.getWeapon().getStrength() > 0)){ // If their strengths are equal
        warrior1.weaponChangeStrength(0);
        warrior2.weaponChangeStrength(0);
        cout << "Mutual Annihilation: " << warrior1.getName() << " and " << warrior2.getName() <<  " die at each other's hands" << endl;
    }
    else if ((warrior1.getWeapon().getStrength() == 0 && warrior2.getWeapon().getStrength() > 0) || (warrior1.getWeapon().getStrength() > 0 && warrior2.getWeapon().getStrength() == 0)){ // If one of the warriors is already dead
        if (warrior1.getWeapon().getStrength() == 0){
            cout << "He's dead, " << warrior2.getName() << endl;
        }
        else{
            cout << "He's dead, " << warrior1.getName() << endl;
        }
    }
    else if ((warrior1.getWeapon().getStrength() > warrior2.getWeapon().getStrength()) || (warrior1.getWeapon().getStrength() < warrior2.getWeapon().getStrength())){ // If one warrior has more strength than another warrior. Both warriors have strengths > 0
        if (warrior1.getWeapon().getStrength() > warrior2.getWeapon().getStrength()){
            warrior1.weaponChangeStrength(warrior1.getWeapon().getStrength() - warrior2.getWeapon().getStrength());
            warrior2.weaponChangeStrength(0);
            cout << warrior1.getName() << " defeats " << warrior2.getName() << endl;

        }
        else{
            warrior2.weaponChangeStrength(warrior2.getWeapon().getStrength() -  warrior1.getStrength());
            warrior1.weaponChangeStrength(0);
            cout << warrior2.getName() << " defeats " << warrior1.getName() << endl;
        }
    }
    else{ // If they are both dead
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
    }
}

void battleCommand(vector<Warrior>& warriorList, ifstream& ifs){ // This function will execute the battle command.
    string opponent1;
    string opponent2;
    ifs >> opponent1;
    ifs >> opponent2;
    size_t warrior1Index;
    size_t warrior2Index;
    for (size_t i = 0; i < warriorList.size(); ++i){
        if (warriorList[i].getName() == opponent1){
            warrior1Index = i;
        }
        else if (warriorList[i].getName() == opponent2){
            warrior2Index = i;
        }
    }
    cout << warriorList[warrior1Index].getName() << " battles " << warriorList[warrior2Index].getName() << endl;
    combatOutcomes(warriorList[warrior1Index], warriorList[warrior2Index]);

}


// This function will read each command in the file and do the appropriate command
void checkCommands(ifstream& ifs){
    string command;
    vector<Warrior> warriorList;
    while (ifs >> command){ // read each command in the file
        if (command == "Warrior"){
            warriorCommand(ifs, warriorList);
        }
        else if (command == "Status"){
            statusCommand(warriorList);
        }
        else{
            battleCommand(warriorList, ifs);
        }
    }

}

int main() {
    ifstream warriors = openFile("warriors.txt");
    checkCommands(warriors);
    return 0;
}
