#include "RedBlackTree.h"
using namespace std;

int main(int argc, const char* argv[]) {

	RedBlackTree<int, int> test;
	test.insert(12, 5);
	test.insert(14, 5);
	test.insert(13, 6);
	test.insert(15, 5);
	test.insert(16, 5);
	test.insert(17, 5);
	test.insert(18, 5);
	test.insert(19, 5);
	test.insert(20, 5);

	cout << endl; 
	cout << endl;
	cout << endl;
	cout << endl;

	test.remove(17);
	test.remove(16);

	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;

	RedBlackTree<int, int> test2(test);

	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;

	RedBlackTree<int, int> test3;
	test3 = test2;
    cout << test3.remove(1) << " - 1" << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;

    //One int element
    RedBlackTree<int, int> test5;
    test5.insert(1, 5);
    cout << test5.size() << " - 1" << endl;
    cout << test5.remove(1) << " - 1" << endl;
    cout << test5.size() << " - 0" << endl;

    //One string element 
    RedBlackTree<string, string> test6;
    test6.insert("hey", "hello");
    cout << test6.size() << " - 1" << endl;
    cout << test6.remove("hey") << " - 1" << endl;
    cout << test6.size() << " - 0" << endl;

    //Multiple int elements
    RedBlackTree<int, int> test7;
    test7.insert(1, 5);
    test7.insert(3, 4);
    test7.insert(6, 3);
    test7.insert(4, 7);
    test7.insert(5, 6);
    cout << test7.size() << " - 5" << endl;
    cout << test7.remove(3) << " - 1" << endl;
    cout << test7.size() << " - 4" << endl;
    cout << test7.remove(3) << " - 0" << endl;
    cout << test7.size() << " - 4" << endl;
    cout << " " << endl;
    cout << test7.search(1) << " - 1" << endl;
    cout << test7.search(2) << " - 0" << endl;
    cout << " " << endl;
    vector<int> abc = test7.search(1, 6);
    for (int i = 0; i < abc.size(); i++) {
        cout << " " <<abc[i] << endl;
    }
    for (int i = 0; i < test7.values().size(); i++) {
        cout << test7.values()[i] << endl;
    }
    cout << " " << endl;
    for (int i = 0; i < test7.keys().size(); i++) {
        cout << test7.keys()[i] << endl;
    }
    cout << " " << endl;
    cout<<test7.getRoot()->value<<endl;
    cout << " " << endl;
    RedBlackTree<int, int> test10;
    test10 = test7;
    for (int i = 0; i < test10.values().size(); i++) {
        cout << test10.values()[i] << endl;
    }
    for (int i = 0; i < test10.keys().size(); i++) {
        cout << test10.keys()[i] << endl;
    }
    cout << " " << endl;
    RedBlackTree<int, int> test11(test7);
    for (int i = 0; i < test11.values().size(); i++) {
        cout << test11.values()[i] << endl;
    }
    for (int i = 0; i < test11.keys().size(); i++) {
        cout << test11.keys()[i] << endl;
    }
    cout << " " << endl;
    test7.~RedBlackTree();
    cout << test7.size() << " - 0" << endl;
    cout << " " << endl;


    //Multiple string elements
    RedBlackTree<string, string> test8;
    test8.insert("hi", "hello");
    test8.insert("ok", "okay");
    test8.insert("hey", "there");
    test8.insert("apple", "banana");
    test8.insert("peach", "carrot");
    cout << test8.size() << " - 5" << endl;
    cout << test8.remove("ok") << " - 1" << endl;
    cout << test8.size() << " - 4" << endl;
    cout << test8.remove("ok") << " - 0" << endl;
    cout << test8.size() << " - 4" << endl;

    //Multiple int and string elements
    RedBlackTree<int, string> test9;
    test9.insert(1, "one");
    test9.insert(5, "five");
    test9.insert(3, "three");
    test9.insert(6, "six");
    test9.insert(8, "eight");
    cout << test9.size() << " - 5" << endl;
    cout << test9.remove(5) << " - 1" << endl;
    cout << test9.size() << " - 4" << endl;
    cout << test9.remove(1) << " - 1" << endl;
    cout << test9.size() << " - 3" << endl;


  
    RedBlackTree<int, int> test20;
    test20.insert(10,20);
    test20.insert(11, 21);
    test20.insert(12, 22);
    test20.insert(13, 23);
    test20.insert(14, 24);
    test20.insert(15, 25);
    test20.insert(16, 26);
    test20.insert(17, 27);
    test20.insert(18, 28);
    test20.insert(19, 29);
    test20.insert(20, 30);
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

RedBlackTree<int, char> rb3 = rb2;
if (rb3.remove(2)) cout << "removed 2" << endl;
if (rb3.search(6)) cout << "found 6" << endl;

RedBlackTree<int, char> test22;
test22.insert(1, 'c');
test22.insert(2, 'd');
test22.insert(3, 'e');
test22.insert(4, 'f');
test22.insert(5, 'g');
for (int i = 0; i < test22.search(1, 3).size(); i++) {
    cout << test22.search(3, 1)[i] << endl;
}

RedBlackTree<int, string> test23;
test23.insert(1, "one");
test23.insert(2, "two");
test23.insert(3, "three");
test23.insert(4, "four");
test23.insert(5, "five");
for (int i = 0; i < test23.search(1, 3).size(); i++) {
    cout << test23.search(3, 1)[i] << endl;
}

return 0;
}