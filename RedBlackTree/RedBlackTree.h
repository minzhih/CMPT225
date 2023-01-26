#include<iostream>
#include<vector>
#include<string>
using namespace std;

template<class T1,class T2>
class NodeT{
public:
    NodeT(T1 k,T2 v);
    T1 key;
    T2 value;
    NodeT* left;
    NodeT* right;
    NodeT* parent;
    bool isBlack;
};


template<class T1,class T2>
class RedBlackTree{
public:
    //default constructor
    RedBlackTree();
    //copy constructor
    RedBlackTree(const RedBlackTree<T1,T2> & rbt);
    //operator=
    RedBlackTree<T1,T2> & operator=(const RedBlackTree<T1,T2> & rbt);
    //destructor
    ~RedBlackTree();
    //insert function
    bool insert(T1 k,T2 v);
    //remove function
    bool remove(T1 k);
    //search function which return true/false
    bool search(T1 k);
    //search function which return a vector
    vector<T2> search(T1 k1,T1 k2);
    //values function
    vector<T2> values();
    //keys function
    vector<T1> keys ();
    //size function
    int size();
    //getRoot function
    NodeT<T1,T2>* getRoot();
    //in order print
    void inOrderPrint(NodeT<T1,T2>* nd);

private:
    NodeT<T1,T2>* root;
    int sizee;
	NodeT<T1,T2>* search_helper(T1 k);
    NodeT<T1,T2>* search_pa_helper(T1 k);
    void copy_helper(NodeT<T1, T2> * &copy_to, NodeT<T1, T2>* newParent, const NodeT<T1, T2> * copy_from);
    void values_help(vector<T2>& ve,NodeT<T1,T2>* troot);
    void Keys_help(vector<T1>& ve,NodeT<T1,T2>* troot);
    void rbtRemove(NodeT<T1,T2>* z);
    void rbtFix(NodeT<T1,T2>* x,NodeT<T1,T2>* pa);
    NodeT<T1,T2>* predecessor(NodeT<T1,T2>* z);
	void rbtInsertFix(NodeT<T1,T2>* x);
    void right_rotate(NodeT<T1,T2>* x);
    void left_rotate(NodeT<T1,T2>* x);
};

//All Helper/Additional/Private Functions
template<class T1,class T2>
void RedBlackTree<T1,T2>::copy_helper(NodeT<T1, T2>* &copy_to, NodeT<T1, T2>* newParent, const NodeT<T1, T2> * copy_from)
{
    if (copy_from == nullptr){
            copy_to = nullptr;
    }
        else {
            copy_to = new NodeT<T1,T2>(copy_from->key,copy_from->value);
            copy_to->isBlack = copy_from->isBlack;
            copy_to->parent = newParent;
            copy_helper(copy_to->left, copy_to, copy_from->left);
            copy_helper(copy_to->right, copy_to, copy_from->right);
            sizee++;
        }
}

template<class T1,class T2>
void RedBlackTree<T1,T2>::values_help(vector<T2>& ve, NodeT<T1,T2>* troot)
{
    if(troot!=nullptr){
        values_help(ve,troot->left);
        ve.push_back(troot->value);
        values_help(ve,troot->right);
    }
}

template<class T1,class T2>
void RedBlackTree<T1,T2>::Keys_help(vector<T1>& ve, NodeT<T1,T2>* troot)
{
    if(troot!=nullptr){
        Keys_help(ve,troot->left);
        ve.push_back(troot->key);
        Keys_help(ve,troot->right);
    }
}

template<class T1,class T2>
NodeT<T1,T2>* RedBlackTree<T1,T2>::predecessor(NodeT<T1,T2>* z){
    NodeT<T1,T2>* res=z->left;
    while (res->right!=nullptr)
    {
        res=res->right;
    }
    return res;
}

template<class T1,class T2>
void RedBlackTree<T1,T2>::rbtRemove(NodeT<T1,T2>* z){
    NodeT<T1,T2>* y=nullptr;
    NodeT<T1,T2>* x=nullptr;
    if (z->left == nullptr || z->right == nullptr){
        y = z;
    }
    else{
        y = predecessor(z); //or successor
    }
    if (y->left != nullptr){
        x = y->left;
    }
    else{
        x = y->right;
    }
    if(x != nullptr){
        x->parent = y->parent;
    }
    
    if (y->parent == nullptr) {
        root = x;
        root->isBlack=true;
    }
    else{
        if (y == y->parent->left){
            y->parent->left = x;
        }
        else{
            y->parent->right = x;
        }
    }
    if (y != z){
        z->key = y->key;
        z->value = y->value;
    }
    if (y->isBlack){
        rbtFix(x,y->parent);
    }
    delete y;
}

template<class T1, class T2>
NodeT<T1,T2>* RedBlackTree<T1,T2>::search_helper(T1 k)
{
    NodeT<T1,T2>* curr = root;
    while (curr!= nullptr)
    {
        if (curr->key == k) {
                break;
        }
        else if (k<curr->key)
        {
                curr = curr->left;
        }
        else
        {
          curr = curr->right;
        }
    }
    return curr;
}

template<class T1, class T2>
NodeT<T1,T2>* RedBlackTree<T1,T2>::search_pa_helper(T1 k)
{
    NodeT<T1,T2>* curr = root;
    while (curr!= nullptr)
    {
        if (k<curr->key)
        {
        if (curr->left==nullptr){
            return curr;
        }
                curr = curr->left;
        }
        else
        {
        if (curr->right==nullptr){
            return curr;
        }
              curr = curr->right;
        }
    }
    return curr;
}

template<class T1, class T2>
void RedBlackTree<T1,T2>::left_rotate(NodeT<T1,T2>* x) {
        NodeT<T1,T2>* y = x->right;
        x->right = y->left;
        if (y->left != nullptr){
            y->left->parent = x;
            y->parent = x->parent;
        }
        if (x->parent == nullptr)
        {    root = y;
            y->isBlack=true;
        }
        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else{
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

template<class T1, class T2>
void RedBlackTree<T1,T2>::right_rotate(NodeT<T1,T2>* x) {
        NodeT<T1,T2>* y = x->left;
        x->left = y->right;
        if (y->right != nullptr)
        {
        y->right->parent = x;
        y->parent = x->parent;
        }
        if (x->parent == nullptr)
        {   y->isBlack=true;
            root = y;
        }
        else if (x == x->parent->right)
        {
            x->parent->right = y;
        }
        else
        {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

template<class T1, class T2>
void RedBlackTree<T1,T2>::rbtFix(NodeT<T1,T2>* x,NodeT<T1,T2>* pa){
        while (x != root && (x==nullptr ||x->isBlack )){
            if (x == pa->left){
                NodeT<T1,T2>* y = pa->right;
                if (!y->isBlack){
                    y->isBlack = true;
                    pa->isBlack = false;
                    left_rotate(pa);
                    y = pa->right;
                }
                if ((y->left==nullptr || y->left->isBlack)  && (y->right==nullptr || y->right->isBlack))
                {
                    y->isBlack = false;
                    x = pa;
                    pa=pa->parent;
                }
                else{
                    if (y->right->isBlack == true){
                        y->left->isBlack = true;
                        y->isBlack = false;
                        right_rotate(y);
                        y = pa->right;
                    }
                    y->isBlack = pa->isBlack;
                    pa->isBlack = true;
                    y->right->isBlack = true;
                    left_rotate(pa);
                    break;
                }
            }
            else{
                NodeT<T1,T2>* y=pa->left;
                if (y->isBlack == false){
                    y->isBlack = true;
                    pa->isBlack = false;
                    right_rotate(pa);
                    y = pa->left;
                }
                if ((y->left==nullptr || y->left->isBlack) && (y->right==nullptr || y->right->isBlack)){
                    y->isBlack = false;
                    x = pa;
                    pa=pa->parent;
                }
                else{
                    if (y->left->isBlack == true){
                        y->right->isBlack = true;
                        y->isBlack = false;
                        left_rotate(y);
                        y = pa->left;
                    }
                    y->isBlack = pa->isBlack;
                    pa->isBlack = true;
                    y->left->isBlack = true;
                    right_rotate(pa);
                    break;
                }
            }
        }
        root->isBlack = true;
}

template<class T1, class T2>
void RedBlackTree<T1,T2>::rbtInsertFix(NodeT<T1,T2>* x){
        while (x != root and (!x->parent->isBlack)){
            if (x->parent == x->parent->parent->left){
                NodeT<T1,T2>* y = x->parent->parent->right;
                if (y!=nullptr && !y->isBlack){
                    x->parent->isBlack = true;
                    y->isBlack=true;
                    x->parent->parent->isBlack=false;
                    x = x->parent->parent;
                }
                else {
                    if (x == x->parent->right){
                        x = x->parent;
                        left_rotate(x);
                    }
                     x->parent->isBlack=true;
                    x->parent->parent->isBlack = false;
                    right_rotate(x->parent->parent);
                }
            }
            else{
                NodeT<T1,T2>* y = x->parent->parent->left;
                if (y!=nullptr && y->isBlack == false){
                    x->parent->isBlack = true;
                    y->isBlack = true;
                    x->parent->parent->isBlack = false;
                    x = x->parent->parent;
                }
                else {
                    if (x == x->parent->left){
                        x = x->parent;
                        right_rotate(x) ;
                    }
                    x->parent->isBlack = true;
                    x->parent->parent->isBlack = false;
                    left_rotate(x->parent->parent);
                }
            }
        }
        root->isBlack = true;
}

//Constructor - sets the key and value to its two template type parameters, pointers to null, and isBlack to false
template<class T1,class T2>
NodeT<T1,T2>::NodeT(T1 k,T2 v)
{
    key=k;
    value=v;
    left=nullptr;
    right=nullptr;
    parent=nullptr;
    isBlack=false;
}


//Default constructor – creates an empty tree whose root is a null pointer
template<class T1,class T2>
RedBlackTree<T1,T2>::RedBlackTree()
{
    root=nullptr;
    sizee=0;
}

//copy constructor – a constructor that creates a deep copy of its RedBlackTree reference parameter
template<class T1,class T2>
RedBlackTree<T1,T2>::RedBlackTree(const RedBlackTree<T1,T2> & rbt)
{
    copy_helper(this->root, nullptr, rbt.root);
}
/*operator= – overloads the assignment operator for RedBlackTree objects – (deep) copies its RedBlackTree reference parameter into the calling object and returns a reference to the calling object after de-allocating any dynamic memory associated with the original contents of the calling object; if the calling object is the same as the parameter the operator should not copy it*/
template<class T1,class T2>
RedBlackTree<T1,T2> & RedBlackTree<T1,T2>::operator=(const RedBlackTree<T1,T2> & rbt)
{
    if (this!= & rbt)
            {
                if (root != nullptr)
                {
                  while(this->sizee>0)
                  {
                  remove(this->key);
                  }
                }
                if (rbt.root == nullptr)
                {
                    root = NULL;
                }
                else
                {
                copy_helper(this->root, nullptr, rbt.root);
                }
            }
     return *this;
}


//destructor – deletes dynamic memory allocated by the tree
//Need to revise
template<class T1,class T2>
RedBlackTree<T1,T2>::~RedBlackTree()
{
    while(sizee>0){
        remove(root->key);
    }
    root = nullptr;
    sizee=0;
}

/*insert – if the tree does not contain the method's first parameter which represents the key, inserts the key and value (the second parameter) and returns true; otherwise returns false without insertion; i.e. the tree will never contain duplicate keys; note that both key and value are template parameters and may be different types*/
template<class T1, class T2>
bool RedBlackTree<T1,T2>::insert( T1 k,T2 v){
        NodeT<T1,T2>* nnode=new NodeT<T1,T2>(k,v);
        if(sizee==0){
            root=nnode;
            nnode->isBlack=true;
            sizee++;
        }
        else{
            cout<<v<<endl;
            NodeT<T1,T2>* pa=search_pa_helper(k);
            NodeT<T1,T2>* tk=new NodeT<T1,T2>(k,v);
            tk->parent=pa;
            cout<<v<<endl;
            if(k<pa->key){pa->left=tk;}
            else{pa->right=tk;}
            sizee++;
            rbtInsertFix(tk);
            cout<<v<<endl;
        }
        return true;
    }

/*remove – removes the key and associated value from the tree where the key matches the method's parameter and returns true; if the tree does not contain the a key matching the parameter returns false*/
template<class T1, class T2>
bool RedBlackTree<T1,T2>::remove(T1 k){
        if(sizee==0){
            return false;
        }
        NodeT<T1,T2>* sres= search_helper(k);
        if(sres==nullptr){
            return false;
        }
        else{
            rbtRemove(sres);
            sizee--;
            return true;
        }
    }

//searches the tree for the key that matches the method's single template parameter and returns true if it is found and false otherwise
template<class T1, class T2>
bool RedBlackTree<T1,T2>::search(T1 k){
	return search_helper(k)!=nullptr;
}

/*returns a vector that contains all of the values whose keys are between the method's first and second parameters (including both parameter keys if they are in the tree); the contents of the returned vector are in ascending order of the keys, not the values; if there are no keys within the range of the two parameters the returned vector should be empty*/
template<class T1,class T2>
vector<T2> RedBlackTree<T1,T2>::search(T1 k1,T1 k2){
    vector<T1> keysVec=keys() ;
    vector<T2> valuesVec=values() ;
    vector<T2> res; // empty vector
       for(int i=0;i<keysVec.size();i++){
        if(k1<keysVec[i] && keysVec[i]<k2){
            res.push_back(valuesVec[i]);
        }
    }
    return res;
}

/*returns a vector that contains all of the values in the tree; the contents of the vector are in ascending key - not value - order; if the tree is empty the returned vector should also be empty*/
template<class T1, class T2>
vector<T2> RedBlackTree<T1,T2>::values()
{
    vector<T2> k;
    values_help(k,root);
    return k;
}

/*returns a vector that contains all of the keys in the tree; the contents of the vector are in ascending order; if the tree is empty the returned vector should also be empty*/
template<class T1, class T2>
vector<T1> RedBlackTree<T1,T2>::keys() 
{
    vector<T1> k;
    Keys_help(k,root);
    return k;
}

//size – returns the number of items stored in the tree
template<class T1, class T2>
int RedBlackTree<T1,T2>::size() 
{
    return this->sizee;
}

//Returns a pointer to the tree's root node
template<class T1, class T2>
NodeT<T1,T2>* RedBlackTree<T1,T2>::getRoot()
{
    return this->root;
}

template<class T1, class T2>
void RedBlackTree<T1,T2>::inOrderPrint(NodeT<T1,T2>* nd){
    inOrderPrint(nd->left);
    cout<<nd->key<<endl;
    inOrderPrint(nd->right);
    
}
