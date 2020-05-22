/*
polynomical.h
Kyle Payen
Hw08: Linked Lists
*/
#include <vector>
#include <string>
#include <iostream>
#include <cmath> 


struct Node{
    Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
    int data;
    Node* next;
};

class Polynomial{
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& rhs); 

    friend bool operator==(const Polynomial& lhs, const Polynomial& rhs); 
public:
    Polynomial();

    Polynomial(std::vector<int> coefficientList);

    Polynomial(const Polynomial& rhs);

    Polynomial& operator=(const Polynomial& rhs);

    ~Polynomial();

    Polynomial& operator+=(const Polynomial& rhs);

    int evaluate(int val); 


private:
    int degree;
    Node* headPtr;
};