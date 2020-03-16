#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// The Molecules object will hold a vector for the names of the formulas, an two integers for the number of carbon and hydrogen atoms
struct Molecules{
    vector<string> formulas;
    int carbonNumber;
    int hydrogenNumber;
};

//This function opens the file
void openFile(ifstream& ifs){ //this function will open the ifstream object
    string fileName;
    cout << "Please enter a valid filename";
    cin >> fileName;
    ifs.open(fileName);
    while (!ifs){
        cout << "Please input a valid filename";
        cin >> fileName;
        ifs.clear();
        ifs.open(fileName);
    }

}

//This function create Molecules objects and returns them
Molecules createMolecules(const string& name, int& cNumber, int& hNumber){
    Molecules molecule;
    molecule.formulas.push_back(name);
    molecule.carbonNumber = cNumber;
    molecule.hydrogenNumber = hNumber;
    return molecule;
}

// This function will check in one formula has less carbons and hydrogens than another formula. It will return a boolean.
bool isSmaller(const Molecules& molecule1, const Molecules& molecule2){
    bool smallerMolecule = false;
    if ((molecule1.carbonNumber < molecule2.carbonNumber) && (molecule1.hydrogenNumber < molecule2.hydrogenNumber)){
        smallerMolecule = true;
    }
    else if((molecule1.carbonNumber == molecule2.carbonNumber) && (molecule1.hydrogenNumber < molecule2.hydrogenNumber)){
        smallerMolecule = true;
    }

    return smallerMolecule;
}

// Checks if the formula has already been added to the vector
bool formulaAdded(vector<Molecules>& allFormulas, const string& name, int cNumber, int hNumber){

    bool hasBeenAdded = false;
    for (Molecules& molecule : allFormulas){
        if (molecule.carbonNumber == cNumber && molecule.hydrogenNumber == hNumber) {
            molecule.formulas.push_back(name);
            hasBeenAdded= true;
            break;
        }
    }

    return hasBeenAdded;
}

// Fills the vector with Molecule objects
void fillVector(vector<Molecules>& myVec, ifstream& ifs){
    string name;
    char elementLetter;
    int cNumber;
    int hNumber;

    while(ifs >> name >> elementLetter >> cNumber >> elementLetter >> hNumber){
       bool hasBeenAdded = formulaAdded(myVec, name, cNumber, hNumber);
       if (!hasBeenAdded){
           Molecules molecule = createMolecules(name, cNumber, hNumber);
           myVec.push_back(molecule);
       }
    }
}

// This function uses selection sort to sort the vector
void sortVector(vector<Molecules>& myVec) {

    size_t index;
    for (size_t i = 0; i < myVec.size(); ++i) {
        index = i;
        for (size_t j =i +1; j < myVec.size(); ++j) {
            if (isSmaller(myVec[j], myVec[index])) {
                index = j;
            }
        }
        Molecules molecule;
        molecule = myVec[i];
        myVec[i] = myVec[index];
        myVec[index] = molecule;
    }

}

// Displays the molecule in the compact, sorted order
void display(const vector<Molecules>& myVec){
    for (const Molecules molecule: myVec){
        cout << "C" << molecule.carbonNumber << "H" << molecule.hydrogenNumber;
        for (const string& name : molecule.formulas) {
            cout << " " << name;
        }
        cout << endl;
    }
}

int main() {
    ifstream chemFile; // created an ifstream object
    vector<Molecules> allFormulas; // vector to hold formulas
    openFile(chemFile);
    fillVector(allFormulas, chemFile);
    sortVector(allFormulas);
    display(allFormulas);
    return 0;
}
