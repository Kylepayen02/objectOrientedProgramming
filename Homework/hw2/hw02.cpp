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

// This is the struct for the Warrior object
struct Warrior {
    string name;
    int strength;
    void display() const {
        cout << "Warrior: "<< name << ", strength: "  << strength << endl;
    }
};

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
   int strength;
   string name;
   ifs >> name;
   ifs >> strength;
   Warrior newWarrior;
   newWarrior.name = name;
   newWarrior.strength = strength;
   warriorList.push_back(newWarrior);
}

void statusCommand(vector<Warrior>& warriorList){ // This function will display each warrior in the warrior list
    cout << "There are: " << warriorList.size() << " warriors" << endl;
    for( Warrior fighter : warriorList){ // for each warrior in the warriorList vector, display the name and age of the warrior
        fighter.display();
    }
}

void combatOutcomes(Warrior& warrior1, Warrior& warrior2){ // This function will execute the possible outcomes when two warriors battle
    if ((warrior1.strength == warrior2.strength) && (warrior1.strength > 0 && warrior2.strength > 0)){ // If their strengths are equal
        warrior1.strength = 0;
        warrior2.strength = 0;
        cout << "Mutual Annihilation: " << warrior1.name << " and " << warrior2.name <<  " die at each other's hands" << endl;
    }
    else if ((warrior1.strength == 0 && warrior2.strength > 0) || (warrior1.strength > 0 && warrior2.strength == 0)){ // If one of the warriors is already dead
        if (warrior1.strength == 0){
            cout << "He's dead, " << warrior2.name << endl;
        }
        else{
            cout << "He's dead, " << warrior1.name << endl;
        }
    }
    else if ((warrior1.strength > warrior2.strength) || (warrior1.strength < warrior2.strength)){ // If one warrior has more strength than another warrior. Both warriors have strengths > 0
        if (warrior1.strength > warrior2.strength){
            warrior1.strength -= warrior2.strength;
            warrior2.strength = 0;
            cout << warrior1.name << " defeats " << warrior2.name << endl;

        }
        else{
            warrior2.strength -= warrior1.strength;
            warrior1.strength = 0;
            cout << warrior2.name << " defeats " << warrior1.name << endl;
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
        if (warriorList[i].name == opponent1){
            warrior1Index = i;
        }
        else if (warriorList[i].name == opponent2){
            warrior2Index = i;
        }
    }
    cout << warriorList[warrior1Index].name << " battles " << warriorList[warrior2Index].name << endl;
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
