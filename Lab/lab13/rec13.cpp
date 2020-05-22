/*
Kyle Payen 
rec13.cpp
Lab 13: STL 
*/

#include <iostream>
#include <fstream>
#include <vector>      // task 1
#include <list>        // task 2
#include <algorithm>   // task 3
#include <string>      // task 21
#include <set>         // task 22
#include <map>         // task 23
using namespace std;

// Task 9:
void printList(const list<int>& intList){
    for (list<int>::const_iterator  i = intList.begin(); i != intList.end(); ++i){
        cout << *i << " ";
    }
    cout << endl;
}

// task 10:
void printList2(const list<int>& intList){
    for (int i : intList){
        cout << i << " ";
    }
    cout << endl;
}

// Task 11:
void printAlternate(const list<int>& intList){
    int counter = 0;
    for (auto i = intList.begin(); i != intList.end(); ++i){
        if (counter % 2 == 0){
            cout << *i << " ";
        }
        counter += 1;
    }
    cout << endl;
}

//task 12:
//list<int>::const_iterator findItem(const list<int>& intList, int item){
//    for (list<int>::const_iterator i = intList.begin(); i != intList.end(); ++i){
auto findItem(const list<int> intList, int item){ // Task 13
    for (auto i = intList.begin(); i != intList.end(); ++i){
        if (*i == item){
            return i;
        }
    }
    return intList.end();
}

//task 15:
bool isEven(int value){
    return value % 2 == 0;
}

//task 16:
class Kyle{
public:
    bool operator() (int val){
        return val % 2 == 0;
    }
};
 //task 19:
list<int>::const_iterator ourFind(list<int>::const_iterator beginIter, list<int>::const_iterator endIter, int val){
    cout << "This is our implementation of the find function" << endl;
    for (list<int>::const_iterator  i = beginIter; i != endIter; ++i){
        if (*i == val){
            return i;
        }
    }
    return endIter;
}

//task 20:
template<typename iter, typename targetType>
iter ourFind(const iter& beginning, const iter& end, targetType target){
    cout << "This is the template version" << endl;
    for (iter i = beginning; i != end; ++i){
        if (*i == target){
            return i;
        }
    }
    return end;
}
int main() {
    // 1. Create a vector with some values and display using ranged for
    cout << "Task 1:\n";
    cout << "vector: " ;
    vector<int> v({2,52,64,35,90,14});
    for (int value : v){
        cout << value << " ";
    } 
    cout << "\n=======\n";

    // 2. Initalize a list as a copy of values from the vector
    cout << "Task 2:\n";
    cout << "list: ";
    list<int> aList(v.begin(), v.end());
    for (int i : aList){
        cout << i << " "; 
    }
    cout << "\n=======\n";

    // 3. Sort the original vector.  Display both the vector and the list
    cout << "Task 3:\n";
    sort(v.begin(), v.end());
    cout << "Sorted Vector: "; 
    for (int value : v){
        cout << value << " "; 
    }
    cout << endl;
    cout << "List: ";
    for (int i: aList){
        cout << i << " ";
    }
    cout << "\n=======\n";

    // 4. print every other element of the vector.
    cout << "Task 4:\n";
    for (size_t i = 0; i < v.size(); i+=2){
        cout << v[i] << " ";
    }
    cout << "\n=======\n";

    // 5. Attempt to print every other element of the list using the
    //    same technique.
    cout << "Task 5:\n";
    // does not compile
//    for (size_t i = 0; i < aList.size(); i+=2){
////        cout << aList[i] << " ";
////    }
    cout << "\n=======\n";

    //
    // Iterators
    //

    // 6. Repeat task 4 using iterators.  Do not use auto;
    cout << "Task 6:\n";
    for (vector<int>::iterator i = v.begin(); i != v.end(); i+=2){
        cout << *i << " ";
    }
    cout << "\n=======\n";

    // 7. Repeat the previous task using the list.  Again, do not use auto.
    //    Note that you cannot use the same simple mechanism to bump
    //    the iterator as in task 6.
    cout << "Task 7:\n";
    int counter = 0;
    for (list<int>::iterator i = aList.begin(); i != aList.end(); ++i){
        if (counter % 2 == 0){
            cout << *i << ' ';
        }
        counter += 1;
    }

    cout << "\n=======\n";

    // 8. Sorting a list
    cout << "Task 8:\n";
    aList.sort();
    for (int value: aList){
        cout << value << " ";
    }
    cout << "\n=======\n";

    // 9. Calling the function to print the list
    cout << "Task 9:\n";
    printList(aList);
    cout << "=======\n";

    // 10. Calling the function that prints the list, using ranged-for
    cout << "Task 10:\n";
    printList2(aList);
    cout << "=======\n";

    //
    // Auto
    //

    // 11. Calling the function that, using auto, prints alterate
    // items in the list
    cout << "Task 11:\n";
    printAlternate(aList);
    cout << "=======\n";

    
    // 12.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 12:\n";
    list<int>::const_iterator foundItem  =  findItem(aList, 52);
    cout << *foundItem << endl;
    list<int>::const_iterator notFound = findItem(aList, 3);
    cout << *notFound << endl;
    cout << "=======\n";

    // 13.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 13:\n";
    foundItem  =  findItem(aList, 52);
    cout << *foundItem << endl;
    cout << "=======\n";

    //
    // Generic Algorithms
    //

    // 14. Generic algorithms: find
    cout << "Task 14:\n";
    foundItem = find(aList.begin(), aList.end(), 52);
    cout  << *foundItem << endl;
    cout << "=======\n";

    // 15. Generic algorithms: find_if
    cout << "Task 15:\n";
    auto val = find_if(aList.begin(), aList.end(), isEven);
    cout << *val << endl;
    cout << "=======\n";

    // 16. Functor
    cout << "Task 16:\n";
    val = find_if(aList.begin(), aList.end(), Kyle());
    cout << *val << endl;
    cout << "=======\n";
    
    // 17. Lambda
    cout << "Task 17:\n";
    val = find_if(aList.begin(), aList.end(), [] (int value) {return value % 2 == 0;});
    cout << *val << endl;
    cout << "=======\n";

    // 18. Generic algorithms: copy to an array
    cout << "Task 18:\n";
    int* dynArray = new int[6];
    copy(aList.begin(), aList.end(), dynArray);
    for (size_t i = 0; i < 6; ++i){
        cout << dynArray[i] << " ";
    }
    cout << endl;
    auto res = find_if(dynArray, dynArray+6, isEven);
    cout << *res << endl;
    delete [] dynArray;
    dynArray = nullptr;
    cout << "=======\n";

    //
    // Templated Functions
    //

    // 19. Implement find as a function for lists
    cout << "Task 19:\n";
    list<int>::const_iterator result = ourFind(aList.begin(), aList.end(), 52);
    cout << *result << endl;
    cout << "=======\n";
    
    // 20. Implement find as a templated function
    cout << "Task 20:\n";
    auto vecResult = ourFind(v.begin(), v.end(), 52);
    cout << *vecResult << endl;
    cout << "=======\n";

    //
    // Associative collections
    //

    // 21. Using a vector of strings, print a line showing the number
    //     of distinct words and the words themselves.
    cout << "Task 21:\n";
    string word;
    vector<string> wordList;
    ifstream ifs("pooh-nopunc.txt");
    if (!ifs){
        cerr << "Couldn't open file" << endl;
        exit(1);
    }
    while (ifs >> word){
        if (find(wordList.begin(), wordList.end(), word) == wordList.end()){
            wordList.push_back(word);
        }
    }
    ifs.close();
    cout << "Size: " << wordList.size() << endl;
    cout << "Words: " << endl;
    for (string item : wordList){
        cout << item << " ";
    }
    cout << "\n=======\n";

    // 22. Repeating previous step, but using the set
    cout << "Task 22:\n";
    set<string> wordList2;
    string wordSet;
    ifs.open("pooh-nopunc.txt");
    if (!ifs){
        cerr << "Couldn't open file" << endl;
        exit(1);
    }
    while (ifs >> wordSet){
        wordList2.insert(wordSet);
    }
    ifs.close();
    cout << "Size: " << wordList2.size() << endl;
    cout << "Words: " << endl;
    for (string item : wordList2){
        cout << item << " ";
    }
    cout << "=======\n";

    // 23. Word co-occurence using map
    cout << "Task 23:\n";
    map<string, vector<int>> wordMap;
    string mapWord;
    int pos = 0;
    ifs.open("pooh-nopunc.txt");
    if (!ifs){
        cerr << "Couldn't open file" << endl;
        exit(1);
    }
    while (ifs >> mapWord){
        wordMap[mapWord].push_back(pos);
        ++pos;
    }
    ifs.close();
    for (const auto& pair : wordMap){
        cout << "Word: " << pair.first << endl;
        cout  << "At Positions: ";
        for (int i : pair.second){
            cout << i << " ";
        }
        cout << endl;
    }
    cout << endl;
    cout << "=======\n";
}
