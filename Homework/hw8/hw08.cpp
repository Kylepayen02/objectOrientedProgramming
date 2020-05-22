#include <vector>
#include <string>
#include <iostream> 

using namespace std; 

struct Node{
    Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
    int data;
    Node* next;
};

class Polynomial{
    friend ostream& operator<<(ostream& os, const Polynomial& rhs); 

    friend bool operator==(const Polynomial& lhs, const Polynomial& rhs); 
public:
    Polynomial();

    Polynomial(vector<int> coefficientList);

    Polynomial(const Polynomial& rhs);

    Polynomial& operator=(const Polynomial& rhs);

    ~Polynomial();

    Polynomial& operator+=(const Polynomial& rhs);


private:
    int degree;
    Node* headPtr;
};

Polynomial::Polynomial() : degree(0), headPtr(new Node()) {}

Polynomial::Polynomial(vector<int> coefficientList){
        degree = 0;
        headPtr = new Node(coefficientList[0]); 
        for (size_t i = coefficientList.size()-1; i > -1; --i){
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
    headPtr = rhs.headPtr; 
    while (oldHeadPtr->next){
        Node* deletedNode = oldHeadPtr;
        oldHeadPtr = oldHeadPtr->next;
        delete deletedNode;
    }
    delete oldHeadPtr; 
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
    Node* myHeadPtr = headPtr;
    Node* otherHeadPtr = rhs.headPtr;
    if (degree < rhs.degree){
        int difference = rhs.degree - degree;  
        while(myHeadPtr->next){
            myHeadPtr = myHeadPtr->next;
        }
        for (int i = difference; i > -1; --i){
            myHeadPtr->next = new Node(); 
            myHeadPtr = headPtr->next;
        }
        myHeadPtr = headPtr;
    }
    while (otherHeadPtr){
        myHeadPtr->next += otherHeadPtr->data;
        myHeadPtr = myHeadPtr->next;
        otherHeadPtr = otherHeadPtr->next; 
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
    }
    return true;

}

bool operator!=(const Polynomial& lhs, const Polynomial& rhs){
    return !(lhs == rhs);
}

ostream& operator<<(ostream& os, const Polynomial& rhs){
    string output = "";
    Node* p = rhs.headPtr;
    int degree = rhs.degree; 
    while(p){
        if (rhs.degree == 0){
            os << p->data;
            return os;
        }
        if (p->data != 0){
            output = to_string(p->data) + "x^" + to_string(degree) + " " + output;
            degree -= 1; 
        }
        else{
            degree -= 1; 
        }
        os << output; 
        return os; 
    }
}

