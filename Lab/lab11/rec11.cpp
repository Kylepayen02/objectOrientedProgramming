#include <string> 
#include <vector> 
#include <iostream> 

using namespace std; 

struct Node {
	Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
	int data;
	Node* next;
};

// listAddHead: adds a data item to the beginning of a [possibly empty] list
void listAddHead(Node*& headPtr, int entry) {
	headPtr = new Node(entry, headPtr);
}

// listClear: frees up all the nodes in a list
void listClear(Node*& headPtr) {
    while (headPtr) {
        Node* next = headPtr->next;
        delete headPtr;
        headPtr = next;
    }
}

// listBuild: constructs a list from a vector of data items. Note that
// you can use a curly-braced sequence.
// This may be useful for setting up test cases. Feel free to use it
// or not as you like. 
// Example of using would be:
//    Node* myList = listBuild({1, 4, 9, 16}); // builds a list of: 1 4 9 16
Node* listBuild(const vector<int>& vals) {
    Node* result = nullptr;
    for (size_t index = vals.size(); index > 0; --index) {
        listAddHead(result, vals[index-1]);
    }
    return result;
}

void displayList(const Node* headptr){
    while (headptr){
        cout << headptr->data << " ";
        headptr = headptr->next;
    }
    cout << endl;
}

void splice(Node* newNode, Node*& oldNode){
    if (oldNode == nullptr){
        oldNode = newNode;
        return;
    }
    if (newNode == nullptr){
        return;
    }
    Node* nextNode = oldNode->next;
    oldNode->next = newNode; 
    while (newNode->next){
        newNode = newNode->next;
    }
    newNode->next = nextNode;
}

Node* isSublist(Node*& sublist, Node*& currList){
    bool matches = false;
    for (Node* p = currList; p->next != nullptr; p = p->next){
        if (sublist->data == p->data){
            Node* copySublist = sublist;
            Node* startOfList = p;
            matches = true;
            while (copySublist){
                if (startOfList->data != copySublist->data){
                    matches = false; 
                    break;
                }
                copySublist = copySublist->next;
                startOfList = startOfList->next;
            }
        }
    }
    if (matches){
        return sublist;
    }
    return nullptr;
}

int main(){

    //splice function
    vector<int> originalList{5,7,9,1};
    Node* headOriginalList = listBuild(originalList);
    vector<int> newList{6,3,2};
    Node* headNewList = listBuild(newList);
    Node* seven = headOriginalList->next;
    cout << "L1: ";
    Node* headNode = headOriginalList;
    displayList(headNode);
    cout << "L2: ";
    headNode = headNewList;
    displayList(headNode);
    splice(headNewList, seven);
    cout << "L1 after splicing L2 at 7: ";
    headNode = headOriginalList;
    displayList(headNode);
    listClear(headOriginalList);
    cout << endl;


    //sublist function
    vector<int> L1{5,7,6,3,2,9,1};
    Node* mainList = listBuild(L1);
    vector<int> L2{6,3,2,9};
    Node* sublist = listBuild(L2);
    cout << "Main List: ";
    Node* firstNode = mainList;
    displayList(firstNode);
    cout << "Sublist ";
    firstNode = sublist;
    displayList(firstNode);
    cout << "Result: ";
    Node* location = isSublist(sublist, mainList);
    displayList(location);
    listClear(mainList);
    listClear(sublist);
}