/*
 * Kyle Payen
 * Rec 14: Recursion
 * 05/08/2020
 */
#include <iostream>
#include <exception>
#include <typeindex>
using namespace std;

struct Node {
    Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
    int data;
    Node* next;
};

struct TNode {
    TNode(int data = 0, TNode *left = nullptr, TNode *right = nullptr)
            : data(data), left(left), right(right) {}
    int data;
    TNode *left, *right;
};

bool evenOnes(int num){
    if (num == 1){
        return false;
    }
    return ((num%2 == 0) == evenOnes(num/2));
}

Node* sumList(const Node* list1, const Node* list2){
    if ((list1 == nullptr) && (list2 == nullptr)){
        return nullptr;
    }
    if (list1 == nullptr){
        return new Node(list2->data, sumList(list1, list2->next));
    }
    else if (list2 == nullptr){
        return new Node(list1->data, sumList(list1->next, list2));
    }
    return new Node(list1->data + list2->data, sumList(list1->next, list2->next));
}

void clearList(Node*& aNode){
    while (aNode != nullptr){
        Node* removedNode = aNode;
        aNode = aNode->next;
        delete removedNode;
    }
}

bool palindrome(char* arrayChar, int arrSize){
    if (arrSize <= 1){
        return true;
    }
    if (arrayChar[0] == arrayChar[arrSize-1]) return true;

    return palindrome(arrayChar+1, arrSize-2);

}

int towers(int num, char start, char spare, char target){
    if (num == 0){
        return 0;
    }
    return towers(num-1, start, spare, target) + towers(num-1, spare, target, start) + 1;
}


int main() {

// Q1
    bool yes = evenOnes(36);
    cout << yes << endl;

// Q2
    Node* list1 = new Node(1, new Node(2, new Node(3)));
    Node* list2 = new Node(1, new Node(2, new Node(3, new Node(99))));
    Node* sumOfList = sumList(list1, list2);
    while (sumOfList != nullptr){
        cout << sumOfList->data << " ";
        sumOfList = sumOfList->next;
    }
    clearList(list1);
    clearList(list2);
    clearList(sumOfList);

    cout << endl;


// Q4
    char s[] = "racecar";
    if (palindrome(s, 7)) { cout << "Yes!\n"; }

//Q5
    cout << towers(1, 'a', 'b', 'c') << endl;
    cout << towers(2, 'a', 'b', 'c') << endl;
    cout << towers(3, 'a', 'b', 'c') << endl;
    cout << towers(4, 'a', 'b', 'c') << endl;
    cout << towers(5, 'a', 'b', 'c') << endl;
    cout << towers(6, 'a', 'b', 'c') << endl;
    cout << towers(7, 'a', 'b', 'c') << endl;
    cout << towers(8, 'a', 'b', 'c') << endl;
    cout << towers(9, 'a', 'b', 'c') << endl;
    cout << towers(10, 'a', 'b', 'c') << endl;


}

