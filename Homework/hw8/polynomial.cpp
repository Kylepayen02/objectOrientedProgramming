/*
polynomial.cpp
Kyle Payen
Hw08: Linked Lists
*/
#include "polynomial.h"

using namespace std;

Polynomial::Polynomial() : degree(0), headPtr(new Node()) {}

Polynomial::Polynomial(vector<int> coefficientList){
        degree = 0;
        headPtr = new Node(coefficientList[0]); 
        for (size_t i = 1; i < coefficientList.size() ; ++i){
            headPtr = new Node(coefficientList[i], headPtr);
            degree += 1;
        }
    }

Polynomial::Polynomial(const Polynomial& rhs) : degree(rhs.degree), headPtr(new Node(rhs.headPtr->data)){
    Node* currNode = headPtr; 
    Node* copyNode = rhs.headPtr->next; 
    while (copyNode){
        currNode->next = new Node(copyNode->data);
        copyNode = copyNode->next;
        currNode = currNode->next;
    }
}

Polynomial& Polynomial::operator=(const Polynomial& rhs){
    degree = rhs.degree;
    Node* oldHeadPtr = headPtr;
    while (oldHeadPtr->next){
        Node* deletedNode = oldHeadPtr;
        oldHeadPtr = oldHeadPtr->next;
        delete deletedNode;
    }
    delete oldHeadPtr; 
    headPtr = new Node(rhs.headPtr->data);
    Node* rhsPosition = rhs.headPtr->next;
    Node* currPosition = headPtr;
    while (rhsPosition){
        currPosition->next = new Node(rhsPosition->data);
        currPosition = currPosition->next;
        rhsPosition = rhsPosition->next;
    }
    return *this;
}

Polynomial::~Polynomial(){
    while (headPtr->next){
        Node* deletedNode = headPtr;
        headPtr = headPtr->next;
        delete deletedNode;
    }
    delete headPtr;
}


Polynomial& Polynomial::operator+=(const Polynomial& rhs){
    int difference;
    Node* smallerPoly = nullptr;
    Node* biggerPoly = nullptr;
    if (rhs.degree > degree){
        difference = rhs.degree - degree;
        smallerPoly = headPtr; 
        while (smallerPoly->next){
            smallerPoly = smallerPoly->next; 
        }
        while (difference > 0){
            smallerPoly->next = new Node(0);
            smallerPoly = smallerPoly->next;
            degree += 1;
            difference -= 1;
        }
    }
    smallerPoly = rhs.headPtr;
    biggerPoly = headPtr;
    while (smallerPoly){
        biggerPoly->data += smallerPoly->data;
        biggerPoly = biggerPoly->next;
        smallerPoly = smallerPoly->next;
    }
    return *this;
    
}

Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs){
    Polynomial result; 
    result += lhs; 
    result += rhs; 
    return result;
}

bool operator==(const Polynomial& lhs, const Polynomial& rhs){
    if (lhs.degree != rhs.degree){
        return false; 
    }
    Node* lhsHeadPtr = lhs.headPtr;
    Node* rhsHeadPtr = rhs.headPtr;
    while (lhsHeadPtr){
        if (lhsHeadPtr->data != rhsHeadPtr->data){
            return false;
        }
        lhsHeadPtr = lhsHeadPtr->next;
        rhsHeadPtr = rhsHeadPtr->next;
    }
    return true;

}

bool operator!=(const Polynomial& lhs, const Polynomial& rhs){
    return !(lhs == rhs);
}

ostream& operator<<(ostream& os, const Polynomial& rhs){
    string output = "";
    Node* p = rhs.headPtr;
    int degree = 0; 
    while(p){

        if (rhs.degree == 0){
            os << p->data;
            return os;
        }
        if (degree == 0){
            output = to_string(p->data) + output;
        }
        else if ((degree == 1) && (p->data != 0)){
            output = "x + " + output;
        }
        else if ((degree > 0) && (p->data != 0)){
            output = "x^" + to_string(degree) + " + " + output;
        }
        if (((p->data > 1) || (p->data < 0)) & (degree > 0)){
            output = to_string(p->data) + output;
        }
        degree += 1;
        p = p->next;
    }
    os << output;
    return os;
}

int Polynomial::evaluate(int val){
    int result = 0; 
    int exponent = 0;
    Node* p = headPtr; 
    while (p){
        result += (p->data * pow(val, exponent));
        p = p->next;
        exponent += 1;
    }
    return result;
}

