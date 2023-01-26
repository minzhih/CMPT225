#include <iostream>
#include <vector>
#include "RedBlackTree.h"
using namespace std;

int main(int argc, const char* argv[]) {
        // Int Tree Tests
        RedBlackTree<int, char> rb1;
        if (rb1.insert(6, 'f')) cout << "inserted 42" << endl;
        rb1.insert(10, 'j');
        rb1.insert(2, 'b');
        RedBlackTree<int, char> rb2(rb1);
     
        if (rb1.remove(2)) cout << "removed 2" << endl;
        if (rb1.search(6)) cout << "found 6" << endl;
     
        vector<char> v1 = rb1.search(8, 21); //should contain j
        vector<char> v2 = rb1.values(); //should contain {f, j}
        vector<int> v3 = rb1.keys(); //should contain {6, 10}
     
        cout << "size = " << rb1.size() << endl; //should be 2
        NodeT<int, char>* pRoot = rb1.getRoot(); //BAD design - for our testing only
    }
