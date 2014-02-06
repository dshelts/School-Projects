/* AVLtrees.h
 Programmer: Andrew Shelton
  Worked with: Bryan Jensen
 * Program defines a binary tree base class and a binary search tree
  derived class as well as a balanced BST derived class. 

 */


#include<iostream>//input output
#include<assert.h>
#include<algorithm>
#include<iomanip>//setw() 
#include<cmath>//pow(x, y)=x^y

using namespace std;

typedef char elemType;		// "placeholder" for data type

// binary tree node
struct nodeType {
   elemType data;		// store data
   nodeType * left;		// link to left subtree
   nodeType * right;// link to right subtree
   int balanceFactor;//balance factor for weighting tree
};

// binary tree class
class binaryTree {
protected:
   nodeType * root;//base node for tree

   int nodecount (nodeType *) const;//number of nodes in the tree
   int height (nodeType *) const;//tree height

   void display (nodeType *) const;//formatted read out of tree

   void inorder (nodeType *) const;//inorder readout
   void preorder (nodeType *) const;//preorder readout 
   void postorder (nodeType *) const;//postorder readout


public:
   // constructor
   binaryTree () {root = NULL;};

   // some tree information methods
   int treeNodeCount () const {return nodecount (root);};
   int treeHeight    () const {return height    (root);};

   void treeDisplay  () const {cout<<endl; display(root);};//main accessable tree display
   // tree traversals
   void postorderTraversal () const {postorder (root);};
   void inorderTraversal () const {inorder (root);};
   void preorderTraversal () const {preorder (root);};
};


// binary search tree class
class binarySearchTree : public binaryTree {
private:
   bool search (const elemType, nodeType *) const;
   void insert (elemType, nodeType * &);
public:
   bool searchItem (const elemType key) {return search (key, root);};
   void insertItem (const elemType key){insert(key, root);};
};



//Balance Binary Search Tree
class balancedBST : public binarySearchTree{
protected:
    void rightRotation(nodeType*&);//right rotation
    void leftRotation (nodeType*&);//left leftRotation
    void rotateSubTree (nodeType*&);//decides what kind of rotation is necessary

    void bFactors(nodeType*) const;//readout balance factors
    int calculateBF(nodeType*) const;//calculates the balance factors for a given node
    void insert(elemType, nodeType*&);//inserts in a balancedTree
public:
    balancedBST() {};//default CTOR

    void insertItem(const elemType key){insert(key,root);};
    void balanceFactors() const {bFactors(root);};
};
