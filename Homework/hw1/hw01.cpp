// Created by Kyle Payen
// 2/3/20
// Homework 01
// Ceaser Cypher

#include <vector>
#include <string>
#include <iostream>
#include <fstream>


using namespace std;

//decrypt each character of the file and return it
char decryptChar(char& character, const int& num){  //parameters: encrypted character and the number of spaces to shift the number

    if (character >= 'a' && character <= 'z'){ //check if the char is from a-z

        string lowercaseLetters = "abcdefghijklmnopqrstuvwxyz";

        int charIndex = lowercaseLetters.find_first_of(character);

        if (num > 0){ // check if the number to shift is positive
            if (charIndex - num < 0){
                character = lowercaseLetters[charIndex + (26 - num)];
            }
            else{
                character = lowercaseLetters[charIndex - num];
            }

        }
        else{ // check to see if number to shift is negative
            if (charIndex - num > 26){
                character = lowercaseLetters[charIndex - (26 + num)];
            }
            else{
                character = lowercaseLetters[charIndex - num];
            }
        }
    }
    return character;
}

// this function will fix each line in the file and return the line
string fixLine(string& line , const int& num){ // parameters: each line of the doc and number to shift the characters

    for (char& character : line){  //  This for loop will loop through each character in the word
        char newCharacter = decryptChar(character, num);
        character = newCharacter;
    }
    return line;

}

// this function will open the file and get the needed variables to pass into decryptChar and fixLine
// it will get all the line in the right order in the vector and print the lines in the correct order
void decryptFile(){

    ifstream decryptedFile("encrypted.txt"); // create a filestream object and open it

    if (!decryptedFile) { // check to see if the file opened
        cout << "The file could not be opened" << endl;
        exit(1);
    }

    int shiftNumber;
    decryptedFile >> shiftNumber; // get the number to shift the char
    string word;

    string fileLine;
    vector<string> sentences; // vector to hold the lines in the correct order

//  This while loop get each line in the file , decrypt them, then place lines in correct order in vector
    while (getline(decryptedFile, fileLine)){
        string sentence = fixLine(fileLine, shiftNumber);
        sentences.insert(sentences.begin(), sentence);
    }


    for (string sentence : sentences){ // this loop prints the sentences in the correct order
        cout << sentence << endl;
    }
}

int main(){
    decryptFile();
}

