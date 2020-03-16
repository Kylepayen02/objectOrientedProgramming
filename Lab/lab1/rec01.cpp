//
//  Lab1.cpp
//  LAB
//
//  Created by Kyle Payen on 1/31/20.
//  Copyright © 2020 Kyle Payen. All rights reserved.
//


//Output
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
// without using namespace
    std::cout << "Hello World!" << endl;
    
// with "using namespace std;"
    cout << "Hello World!" << endl;

//Static Typing and defining variables
// Creating an undefined variable
    int x;
    cout << "x: " << x << endl;

    
// Initializing three vaiable
    int y = 17;
    int z = 2000000017;
    double pie = 3.14159;
    cout << "The size of x is: " << sizeof(x) << endl;
    cout << "The size of y is: " << sizeof(y) << endl;
    cout << "The size of z is: " << sizeof(z) << endl;
    cout << "The size of pie is: " << sizeof(pie) << endl;
// The variable "pie" has the largest size

// Compilation error b/c and variable x is supposed to be assigned an int, not a string literal
//    x = "feilx"
    
// Conditions
// Check whether y is between 10 and 20
    if ((y >= 10) && (y <= 20)){
        cout << "y is between 10 and 20" << endl;
    }
    else{
        cout << "y is not between 10 and 20";
    }
    
// looping
//Print a line with the values from 10 to 20 inclusive
//For loop
    for (int i = 10; i <= 20; ++i) {
        cout << "i:" << i << " ";
    }
    cout << endl;
    
//While loop
    int count = 10;
    while (count <= 20){
        cout << "count:" << count << " ";
        ++count;
    }
    cout << endl;
    
//do While
    int j = 10;
    do {
        cout << "j:" << j << " ";
        ++j;
    } while (j <= 20);
    cout << endl;
    
//Repeatedly ask for file name, need while loop
    
    ifstream ifs;
    string filename;
    cout << "Please enter a valid filename";
    cin >> filename;
    ifs.open(filename);
    while (!ifs){
        cout << "Please input a valid filename";
        cin >> filename;
        ifs.open(filename);
    }
    
// Reading File word by word
    string word;
    while (ifs >> word){
        cout << word << endl;
    }

// Vectors
//Fill vector with even integers from 10 to 100
    vector<int> vectorOfInts;
    
    for (int k = 10; k <= 100; ++k){
        if (k%2==0){
            vectorOfInts.push_back(k);
        }
    }
//Looping through vector by indices
    for (size_t l = 0; l < vectorOfInts.size(); ++l) {
      cout << vectorOfInts[l] << endl;
        
    }
    
//Looping through ranged for
    for (int number : vectorOfInts){
        cout << number << endl;
    }
    
//Looping Backwards
    for (size_t i = vectorOfInts.size(); i--;) {
        cout << vectorOfInts[i] << endl;
    }
    
//Defining a vector holding the primes less than 20
    vector<int> prime{2,3,5,7,11,13,17,19};
    for (size_t i = 0; i < prime.size(); ++i) {
        cout << prime[i] << endl;
    }

}

//Functions
void Numbers(const vector<int> v){
    for (int value : v){
        cout << value << endl;
    }
}

void myFunc(){
    vector<int> myVec(5,1);
    Numbers(myVec); 
}



