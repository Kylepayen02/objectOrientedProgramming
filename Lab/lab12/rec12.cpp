// Doubly linked list
//  Test code

#include <cstdlib>
#include <iostream>
#include <vector> 
#include <string> 

using namespace std;

struct Node{
        Node(int data = 0, Node* next = nullptr, Node* prior = nullptr) : data(data), prior(prior), next(next) {}; 
        int data; 
        Node* next; 
        Node* prior; 
    };


class List {
    friend ostream& operator <<(ostream& os, const List& rhs){
        if (rhs.theSize > 0){
            Node* curr = rhs.header->next; 
            while (curr != rhs.trailer){
                os << curr->data << " "; 
                curr = curr->next;
            }
        }
        return os;
    }

public:

    class iterator{

        friend List;

        friend bool operator!=(const List::iterator& lhs, const List:: iterator& rhs){
            return lhs.position != rhs.position;
        }

        friend bool operator==(const List::iterator& lhs, const List:: iterator& rhs){
            return lhs.position == rhs.position;
        }

    public: 
        iterator(Node* position): position(position){}; 

        void operator++(){
            position = position->next; 
        }

        void operator--(){
            position = position->prior; 
        }

        int& operator*() {
            return position->data;
        }

    private:
        Node* position; 
    };
    
    List() : theSize(0) {
        header = new Node();
        trailer = new Node(0, nullptr, header);
        header->next = trailer; 
    }

    void push_back(int data){
        Node* newNode = new Node(data, trailer, trailer->prior);
        newNode->prior->next = newNode; 
        trailer->prior = newNode;
        theSize += 1;  
    }

    void pop_back(){
        if (theSize == 0){
            return;
        }
        Node* removedNode = trailer->prior;
        trailer->prior = removedNode->prior;
        trailer->prior->next = trailer; 
        delete removedNode; 
        theSize -= 1;
    }

    // const version of front()
    int front() const{
        return header->next->data;
    }

    // non-constant version of front()
    int& front(){
        return header->next->data;
    }

    // const version of front()
    int back() const{
        return trailer->prior->data;
    }

    // non-constant version of front()
    int& back(){
        return trailer->prior->data;
    }

    int size() const{
        return theSize;
    }

    void push_front(int data){
        Node* newNode = new Node(data, header->next, header); 
        header->next = newNode;
        newNode->next->prior = newNode;
        theSize += 1;
    }

    void pop_front(){
        if (theSize == 0){
            return;
        }
        Node* removedNode = header->next;
        header->next = removedNode->next;
        removedNode->next->prior = header; 
        delete removedNode; 
        theSize -= 1;
    }

    void clear(){
        Node* curr = header->next; 
        while (curr != trailer){
            Node* removedNode = curr;
            curr = curr->next; 
            delete removedNode;
            theSize -= 1;
        }
        header->next = trailer;
        trailer->prior = header;
    }

    int operator[](size_t index) const{
        Node* curr = header->next; 
        while (index>0){
            curr = curr->next;
            index -= 1;
        }
        return curr->data; 

    }

    int& operator[](size_t index){
        Node* curr = header->next; 
        while (index>0){
            curr = curr->next;
            index -= 1;
        }
        return curr->data; 

    }

    iterator begin(){
        return iterator(header->next); 
    }

    iterator end(){
        return iterator(trailer);
    }

    iterator insert(const iterator& iter, int data){
        theSize += 1;
        Node* nodeAfter = iter.position;
        Node* nodeBefore = iter.position->prior;
        nodeBefore->next = new Node(data, nodeAfter, nodeBefore);
        nodeAfter->prior = nodeBefore->next;
        iterator nextIterator(nodeBefore->next); 
        return nextIterator; 
    }

    iterator erase(const iterator& iter){
        theSize -= 1;
        Node* nodeAfter = iter.position->next; 
        Node* nodeBefore = iter.position->prior; 
        nodeAfter->prior = nodeBefore;
        nodeBefore->next = nodeAfter;  
        delete iter.position; 
        iterator nextIterator(nodeAfter);
        return nextIterator;
    }

private:
    int theSize;
    Node* header; 
    Node* trailer; 
};

// Task 1
void printListInfo(const List& myList) {
        cout << "size: " << myList.size()
             << ", front: " << myList.front()
             << ", back(): " << myList.back()
             << ", list: " << myList << endl;
}

// The following should not compile. Check that it does not.
// void changeFrontAndBackConst(const List& theList){
//     theList.front() = 17;
//     theList.back() = 42;
// }

void changeFrontAndBack(List& theList){
    theList.front() = 17;
    theList.back() = 42;
}

// Task 4
void printListSlow(const List& myList) {
    for (size_t i = 0; i < myList.size(); ++i) {
        cout << myList[i] << ' ';
    }
    cout << endl;
}

// Task 8
void doNothing(List aList) {
    cout << "In doNothing\n";
    printListInfo(aList);
    cout << endl;
    cout << "Leaving doNothing\n";
}    

int main() {

    // Task 1
    cout << "\n------Task One------\n";
    List myList;
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList.push_back(" << i*i << ");\n";
        myList.push_back(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    
    cout << "Modify the first and last items, and display the results\n";
    changeFrontAndBack(myList);
    printListInfo(myList);
    cout << "===================\n";

    cout << "Remove the items with pop_back\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_back();
    }
    cout << "===================\n";

    // Task 2
    cout << "\n------Task Two------\n";
    cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList2.push_front(" << i*i << ");\n";
        myList.push_front(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_front\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_front();
    }
    cout << "===================\n";

    // Task 3
    cout << "\n------Task Three------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        myList.push_back(i*i);
    }
    printListInfo(myList);
    cout << "Now clear\n";
    myList.clear();
    cout << "Size: " << myList.size() << ", list: " << myList << endl;
    cout << "===================\n";

    // Task 4
    cout << "\n------Task Four------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    cout << "Display elements with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Add one to each element with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
    cout << "And print it out again with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Now calling a function, printListSlow, to do the same thing\n";
    printListSlow(myList);
    cout << "Finally, for this task, using the index operator to modify\n"
         << "the data in the third item in the list\n"
         << "and then using printListSlow to display it again\n";
    myList[2] = 42;
    printListSlow(myList);
    

    // Task 5
    cout << "\n------Task Five------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    printListInfo(myList);
    cout << "Now display the elements in a ranged for\n";
    for (int x : myList) cout << x << ' ';
    cout << endl;
    cout << "And again using the iterator type directly:\n";
    // Note you can choose to nest the iterator class or not, your choice.
    //for (iterator iter = myList.begin(); iter != myList.end(); ++iter) {
    for (List::iterator iter = myList.begin(); iter != myList.end(); ++iter) {
        cout << *iter << ' ';
    }
    cout << endl;
    cout << "WOW!!! (I thought it was cool.)\n";
    
    // Task 6
    cout << "\n------Task Six------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Filling an empty list with insert at begin(): "
         << "i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i*i);
    printListInfo(myList);
    // ***Need test for insert other than begin/end***
    cout << "===================\n";

    // Task 7
    cout << "\n------Task Seven------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    cout << "Erasing the elements in the list, starting from the beginning\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.erase(myList.begin());
    }
    // ***Need test for erase other than begin/end***
    cout << "===================\n";

    // // Task 8
    // cout << "\n------Task Eight------\n";
    // cout << "Copy control\n";
    // cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    // myList.clear();
    // for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    // printListInfo(myList);
    // cout << "Calling doNothing(myList)\n";
    // doNothing(myList);
    // cout << "Back from doNothing(myList)\n";
    // printListInfo(myList);

    // cout << "Filling listTwo with insert at begin: i*i for i from 0 to 9\n";
    // List listTwo;
    // for (int i = 0; i < 10; ++i) listTwo.insert(listTwo.begin(), i*i);
    // printListInfo(listTwo);
    // cout << "listTwo = myList\n";
    // listTwo = myList;
    // cout << "myList: ";
    // printListInfo(myList);
    // cout << "listTwo: ";
    // printListInfo(listTwo);
    // cout << "===================\n";
}
