#include <iostream>
#include <string>
#include <vector>
using namespace std;

template<class T1, class T2>
class NodeT {
public:
	//Constructor
	NodeT(T1 k, T2 v) {
		key = k;
		value = v;
		left = nullptr;
		right = nullptr;
		parent = nullptr;
		isBlack = false;
	}
	bool operator<(const NodeT& nd) { return key < nd.key; }
	bool operator==(const NodeT& nd) { return key == nd.key; }

	// Attributes
	T1 key;
	T2 value;
	NodeT* left;
	NodeT* right;
	NodeT* parent;
	bool isBlack;
};

template<class T1, class T2>
class RedBlackTree {
public:
	//default constructor
	RedBlackTree();

	//copy constructor
	RedBlackTree(const RedBlackTree<T1, T2>& rbt);

	//Assignment operator
	RedBlackTree<T1, T2>& operator=(const RedBlackTree<T1, T2>& rb);

	//destructor
	~RedBlackTree();

	//insert
	bool insert(T1 k, T2 v);

	//remove
	bool remove(T1 k);

	//search: The first one (return ture or false)
	bool search(T1 k);

	//search: The second one (return a vector) 
	vector<T2> search(T1 k1, T1 k2);

	//values
	vector<T2> values() const;

	// keys
	vector<T1> keys() const;

	//size 每 returns the number of items stored in the tree.
	int size() const;

	//getRoot 每 returns a pointer to the tree's root node.
	NodeT<T1, T2>* getRoot();

private:
	//Attribute
	NodeT<T1, T2>* root;
	int treeSize;

	//Below are Helper Functions.

	// Copy constructor and assignment operator helper function
	NodeT<T1, T2>* copyTree(const NodeT<T1, T2>* stroot);

	//Helper Function for the second search(The return vector one) method.
	void searchHelper(vector<T2>& vec, NodeT<T1, T2>* rt, T1 k1, T1 k2);

	// Helper function for values method.
	void valuesHelper(vector<T2>& vec, const NodeT<T1, T2>* rt) const;

	// Helper function for keys method.
	void keysHelper(vector<T1>& v, const NodeT<T1, T2>* rt_pt) const;

	// Left rotate
	void left_rotate(NodeT<T1, T2>* x);

	// right rotate
	void right_rotate(NodeT<T1, T2>* x);

	// isleftChild: check if the node is a left child, return true if it is; false if it is not.
	bool isLeftChild(NodeT<T1, T2>* nd);

	// getSib: Get the sibling of the parameter node 
	NodeT<T1, T2>* getSib(NodeT<T1, T2>* nd);

	// insert helper function
	void fixUp(NodeT<T1, T2>* x);

	// search: Helper function for search the node to be removed in the remove method.
	NodeT<T1, T2>* search(T1 k, NodeT<T1, T2>*& pa);

	// predecessor: get the predecessor when removing.
	NodeT<T1, T2>* predecessor(NodeT<T1, T2>* z);

	//isblack: checking if the node is black.
	bool isblack(NodeT<T1, T2>* nd);

	// Remove helper function
	void rbFix(NodeT<T1, T2>* x, NodeT<T1, T2>* pa);

	// Helper function for Remove.
	void rbRemove(NodeT<T1, T2>* z);
};

//default constructor 每 creates an empty tree whose root is a null pointer,
template<class T1, class T2>
RedBlackTree<T1, T2>::RedBlackTree() { root = nullptr; treeSize = 0; }

//copy constructor 每 a constructor that creates a deep copy of its RedBlackTree reference parameter. 
template<class T1, class T2>
RedBlackTree<T1, T2>::RedBlackTree(const RedBlackTree<T1, T2>& rbt) {
	root = copyTree(rbt.root);
	treeSize = rbt.treeSize;
}

/*operator= 每 overloads the assignment operator for RedBlackTree objects 每 (deep) copies its RedBlackTree reference parameter into the calling object and
returns a reference to the calling object after de-allocating any dynamic memory associated with the original contents of the calling object;
if the calling object is the same as the parameter the operator should not copy it*/
template<class T1, class T2>
RedBlackTree<T1, T2>& RedBlackTree<T1, T2>::operator=(const RedBlackTree<T1, T2>& rb) {
	// if the parameter is the same as the object, just return the object.
	if (this == &rb) { return *this; }
	else {
		//first remove the current nodes.
		while (treeSize != 0) {
			rbRemove(this->root);
		}
		// use helper function to copy it.
		this->root = copyTree(rb.root);
		treeSize = rb.treeSize;
	}
	return *this;
}

//destructor
template<class T1, class T2>
RedBlackTree<T1, T2>::~RedBlackTree() {
	// remove all the nodes
	while (root != nullptr && treeSize > 0) {
		remove(root->key);
	}
}

//insert 每 if the tree does not contain the method's first parameter which represents the key, inserts the key and value (the second parameter) and returns true; 
// otherwise returns false without insertion; i.e. the tree will never contain duplicate keys; note that both key and value are template parameters and may be different types 
template<class T1, class T2>
bool RedBlackTree<T1, T2>::insert(T1 k, T2 v) {
	NodeT<T1, T2>* te = new NodeT<T1, T2>(k, v);
	//if no nodes contained, set the new node as the root.
	if (treeSize == 0) {
		root = te;
		treeSize++;
		te->isBlack = true;

	}
	else {
		NodeT<T1, T2>* pa = nullptr;
		// search if the key already exists.
		NodeT<T1, T2>* sres = search(k, pa);
		if (sres != nullptr) {
			return false;
		}
		// if the key does not exist, then insert the new node.
		else {
			NodeT<T1, T2>* tk = new NodeT<T1, T2>(k, v);
			tk->parent = pa;
			if (*tk < *pa) { pa->left = tk; }
			else { pa->right = tk; }
			treeSize++;
			// helper function: Fix up the tree to retain the property of RedBlack Tree.
			fixUp(tk);
		}
	}
	return true;
}

/* remove 每 removes the keyand associated value from the tree where the key matches the method's parameter and returns true;
   if the tree does not contain the a key matching the parameter returns false. */
template<class T1, class T2>
bool RedBlackTree<T1, T2>::remove(T1 k) {
	// If it is empty return false
	if (treeSize == 0) {
		return false;
	}
	NodeT<T1, T2>* pa = nullptr;
	// search if the node with the key is in the tree.
	NodeT<T1, T2>* sres = search(k, pa);
	// if it is not in the tree return false.
	if (sres == nullptr) {
		return false;
	}
	else {
		//use helper function to remove the node
		rbRemove(sres);
		treeSize--;
		return true;
	}
}

//search 每 searches the tree for the key that matches the method's single template parameter and returns true if it is found and false otherwise
template<class T1, class T2>
bool RedBlackTree<T1, T2>::search(T1 k) {
	NodeT<T1, T2>* forhelp = root;
	// if the tree is empty, return false.
	if (treeSize <= 0) { return false; }
	else {
		while (forhelp != nullptr) {
			if (k == forhelp->key) {
				//if it is found, return true.
				return true;
			}
			else if (k < forhelp->key) {
				forhelp = forhelp->left;

			}
			else {
				forhelp = forhelp->right;
			}
		}
	}
	// not found, return false 
	return false;
}

/*search 每 returns a vector that contains all of the values whose keys are between the method's first and second parameters (including both parameter keys if they are in the tree);
 the contents of the returned vector are in ascending order of the keys, not the values;
 if there are no keys within the range of the two parameters the returned vector should be empty. */
template<class T1, class T2>
vector<T2> RedBlackTree<T1, T2>::search(T1 k1, T1 k2) {
	vector<T2> forvalue;
	// helper function
	searchHelper(forvalue, root, k1, k2);
	return forvalue;
}

/* values 每 returns a vector that contains all of the values in the tree; the contents of the vector are in ascending key - not value - order;
   if the tree is empty the returned vector should also be empty. */
template<class T1, class T2>
vector<T2> RedBlackTree<T1, T2>::values() const {
	vector<T2> containV;
	// helper function
	valuesHelper(containV, root);
	return containV;
}

/* keys 每 returns a vector that contains all of the keys in the tree;
   the contents of the vector are in ascending order; if the tree is empty the returned vector should also be empty. */
template<class T1, class T2>
vector<T1> RedBlackTree<T1, T2>::keys() const {
	vector<T1> containK;
	// helper function
	keysHelper(containK, root);
	return containK;
}

//size 每 returns the number of items stored in the tree
template<class T1, class T2>
int RedBlackTree<T1, T2>::size() const {
	return treeSize;
}


//getRoot 每 returns a pointer to the tree's root node
template<class T1, class T2>
NodeT<T1, T2>* RedBlackTree<T1, T2>::getRoot() {
	NodeT<T1, T2>* theR = root;
	return theR;
}

//private Helper Method

// Copy constructor and assignment operator helper function
template<class T1, class T2>
NodeT<T1, T2>* RedBlackTree<T1, T2>::copyTree(const NodeT<T1, T2>* stroot) {
	if (stroot == nullptr) { return nullptr; }
	else {
		// recursively call
		NodeT<T1, T2>* leftst = copyTree(stroot->left);
		NodeT<T1, T2>* rightst = copyTree(stroot->right);
		NodeT<T1, T2>* cnode = new NodeT<T1, T2>(stroot->key, stroot->value);
		//deep copy the key, value and pointers of the node.
		cnode->isBlack = stroot->isBlack;
		cnode->left = leftst;
		if (leftst != nullptr)
			leftst->parent = cnode;
		cnode->right = rightst;
		if (rightst != nullptr)
			rightst->parent = cnode;
		return cnode;
	}
}

//Helper Function for the second search method.
template<class T1, class T2>
void RedBlackTree<T1, T2>::searchHelper(vector<T2>& vec, NodeT<T1, T2>* rt, T1 k1, T1 k2) {
	// if root is not equal to nullptr
	if (rt != nullptr) {
		searchHelper(vec, rt->left, k1, k2);
		//compare the key with parameters.
		if ((rt->key >= k1 && rt->key <= k2) || (rt->key >= k2 && rt->key <= k1)) {
			vec.push_back(rt->value);
		}
		searchHelper(vec, rt->right, k1, k2);
	}
}

// Helper function for values method.
// just inserting all the values from the root of the second parameter in the tree to the first parameter vector.
template<class T1, class T2>
void RedBlackTree<T1, T2>::valuesHelper(vector<T2>& vec, const NodeT<T1, T2>* rt) const {
	if (rt != nullptr) {
		valuesHelper(vec, rt->left);
		// insert the values into the vector.
		vec.push_back(rt->value);
		valuesHelper(vec, rt->right);
	}
}

// Helper function for keys method.
// just inserting all the kays from the root of the second parameter in the tree to the first parameter vector.
template<class T1, class T2>
void RedBlackTree<T1, T2>::keysHelper(vector<T1>& v, const NodeT<T1, T2>* rt_pt) const {
	if (rt_pt != nullptr) {
		keysHelper(v, rt_pt->left);
		v.push_back(rt_pt->key);
		keysHelper(v, rt_pt->right);
	}
}

//left rotation:
template<class T1, class T2>
void RedBlackTree<T1, T2>::left_rotate(NodeT<T1, T2>* x) {// x is the node to be rotated

	NodeT<T1, T2>* y = x->right;
	x->right = y->left;
	// Set nodes＊ parent references
	// checking y＊s left child
	if (y->left != nullptr)
		y->left->parent = x;
	// y
	y->parent = x->parent;
	// Set child reference of x＊s parent
	if (x->parent == nullptr) //x was root, then
	{
		root = y;
		y->isBlack = true;
	}
	else if (x == x->parent->left) //left child 
		x->parent->left = y;
	else
		x->parent->right = y;
	// Make x y＊s left child
	y->left = x;
	x->parent = y;
}

//right rotation:
template<class T1, class T2>
void RedBlackTree<T1, T2>::right_rotate(NodeT<T1, T2>* x) {// x is the node to be rotated
	NodeT<T1, T2>* y = x->left;
	if (y != nullptr) {
		x->left = y->right;
	}
	// Set nodes＊ parent references
	// checking y＊s left child
	if (y != nullptr && y->right != nullptr)
		y->right->parent = x;
	// y
	if (y != nullptr) {
		y->parent = x->parent;
	}
	// Set child reference of x＊s parent
	if (x->parent == nullptr) //x was root
	{
		if (y != nullptr) {
			y->isBlack = true;
		}
		root = y;
	}
	else if (x == x->parent->right) //left child 
		x->parent->right = y;
	else
		x->parent->left = y;
	// Make x y＊s left child
	if (y != nullptr) {
		y->right = x;
	}
	x->parent = y;
}

// isleftChild: check if the node is a left child, return true if it is; false if it is not.
template<class T1, class T2>
bool RedBlackTree<T1, T2>::isLeftChild(NodeT<T1, T2>* nd) {
	return nd == nd->parent->left;
}

// getSib: Get the sibling of the parameter node 
template<class T1, class T2>
NodeT<T1, T2>* RedBlackTree<T1, T2>::getSib(NodeT<T1, T2>* nd) {
	// if nd is the left child
	if (isLeftChild(nd)) {
		return nd->parent->right;
	}
	else { return nd->parent->left; }
}

// insert helper function
template<class T1, class T2>
void RedBlackTree<T1, T2>::fixUp(NodeT<T1, T2>* x) {
	while (x != root and (!x->parent->isBlack)) {
		if (x->parent == x->parent->parent->left) {
			NodeT<T1, T2>* y = x->parent->parent->right; //x＊s ※uncle§
			if (y != nullptr && !y->isBlack) { //like x.p
				//setting the color
				x->parent->isBlack = true;
				y->isBlack = true;
				x->parent->parent->isBlack = false;
				x = x->parent->parent;
			}
			else {//y.colour == black
				if (x == x->parent->right) {
					x = x->parent;
					left_rotate(x);
				}
				//setting the color
				x->parent->isBlack = true;
				x->parent->parent->isBlack = false;
				right_rotate(x->parent->parent);
			}
		}
		else {
			NodeT<T1, T2>* y = x->parent->parent->left; //x＊s ※uncle§
			if (y != nullptr && y->isBlack == false) { //like x.p
				//setting the color
				x->parent->isBlack = true;
				y->isBlack = true;
				x->parent->parent->isBlack = false;
				x = x->parent->parent;
			}
			else {//y.colour == black
				if (x == x->parent->left) {
					x = x->parent;
					right_rotate(x);
				}
				//setting the color
				x->parent->isBlack = true;
				x->parent->parent->isBlack = false;
				left_rotate(x->parent->parent);
			}
		}
	}
	root->isBlack = true;
}

// search: Helper function for search the node to be removed in the remove method.
template<class T1, class T2>
NodeT<T1, T2>* RedBlackTree<T1, T2>::search(T1 k, NodeT<T1, T2>*& pa) {
	NodeT<T1, T2>* te = root;
	while (te != nullptr) {
		if (k == te->key) {
			// if the key is found, return this pointer
			return te;
		}
		else if (k < te->key) {
			pa = te;
			te = te->left;

		}
		else {
			pa = te; te = te->right;
		}
	}
	// not found return nullptr.
	return nullptr;

}

// predecessor: get the predecessor when removing.
template<class T1, class T2>
NodeT<T1, T2>* RedBlackTree<T1, T2>::predecessor(NodeT<T1, T2>* z) {
	NodeT<T1, T2>* res = z->left;
	while (res->right != nullptr)
		res = res->right;
	return res;
}

//isblack: checking if the node is black.
template<class T1, class T2>
bool RedBlackTree<T1, T2>::isblack(NodeT<T1, T2>* nd) {
	return nd == nullptr || nd->isBlack;
}

// Remove helper function: Fix the R&B order to remain the tree property.
template<class T1, class T2>
void RedBlackTree<T1, T2>::rbFix(NodeT<T1, T2>* x, NodeT<T1, T2>* pa) {

	while (x != root && (x == nullptr || x->isBlack)) {

		if (x == pa->left) { //x is left child

			NodeT<T1, T2>* y = pa->right; //x＊s sibling

			if (y->isBlack == false) {
				//change the color
				y->isBlack = true;
				pa->isBlack = false; //x＊s parent must have been black since y is red
				left_rotate(pa);
				y = pa->right;
			}
			if (isblack(y->left) && isblack(y->right)) {
				y->isBlack = false;
				x = pa;
				pa = pa->parent;
			}
			else {
				if (y->right->isBlack == true) {
					//change the color
					y->left->isBlack = true;
					y->isBlack = false;
					right_rotate(y);
					y = pa->right;
				}
				y->isBlack = pa->isBlack;
				//change the color
				pa->isBlack = true;
				y->right->isBlack = true;
				left_rotate(pa);

				//x = root;
				break;
			}
		}
		else {
			NodeT<T1, T2>* y = pa->left; //x＊s sibling
			if (y->isBlack == false) {
				//change the color
				y->isBlack = true;
				pa->isBlack = false; //x＊s parent must have been black since y is red
				right_rotate(pa);
				y = pa->left;
			}

			if (isblack(y->left) && isblack(y->right)) {
				y->isBlack = false;
				x = pa;
				pa = pa->parent;
			}
			else {
				if (y->left->isBlack == true) {
					//change the color
					y->right->isBlack = true;
					y->isBlack = false;
					left_rotate(y);
					y = pa->left;
				}
				y->isBlack = pa->isBlack;
				//change the color
				pa->isBlack = true;
				y->left->isBlack = true;
				right_rotate(pa);
				//x = root;
				break;
			}
		}
	}
	if (root != nullptr) {
		root->isBlack = true;
	}
}

//Helper function for remove: remove the parameter node and still retain the R&B tree property.
template<class T1, class T2>
void RedBlackTree<T1, T2>::rbRemove(NodeT<T1, T2>* z) {
	NodeT<T1, T2>* y = nullptr;
	NodeT<T1, T2>* x = nullptr;
	//it is not an empty tree.
	if (root != nullptr) {
		if (z->left == nullptr || z->right == nullptr) {
			y = z; //node to be removed
		}
		else {
			y = predecessor(z); //get the predecessor.
		}
		if (y->left != nullptr) {
			x = y->left;
		}
		else {
			x = y->right;
		}
		if (x != nullptr) {
			//if x is not nullptr, detach x from y
			x->parent = y->parent;
		}
		if (y->parent == nullptr) {//if y is the root
			root = x;
			if (root != nullptr) {
				root->isBlack = true;
			}
		}
		else {
			// Attach x to y＊s parent
			if (y == y->parent->left) { //get left child
				y->parent->left = x;
			}
			else {
				y->parent->right = x;
			}
		}

		if (y != z) { //i.e. y has, conceptually, been moved up
			z->key = y->key;
			z->value = y->value; //replace z with y
		}
		if (y->isBlack) {
			if (x != nullptr && x->isBlack == false) {
				x->isBlack = true;
			}
			else {
				rbFix(x, y->parent);
			}
		}
		delete y;
	}
	else {
		return;
	}
}
