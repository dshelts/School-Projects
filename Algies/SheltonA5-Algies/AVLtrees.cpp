/* AVLtrees.cpp
 *
 * Program implements a binary tree base class and a binary search tree
 * derived class.
 *
 *
 */
#include "AVLtreess.h"

//binary search tree: method definitions

void binarySearchTree :: insert(elemType key, nodeType*& currentNode){
//PRE: takes a value and a node struct
//POST: Places a new value in the correct place in the Tree
    if(currentNode)//if not null
    {
        if(key < currentNode->data)
        {//value less than  the node data
            insert(key, currentNode->left);//recurse
        }
        else if(key > currentNode->data)
        {//value greater than the current node data
            insert(key, currentNode->right);//recurse
        }
        else
        {//if value in tree
            cout<<key<<", In tree already"<<endl;
        }
    }
    else
    {//hit if there is no node there
        currentNode = new nodeType;
        currentNode->data = key;
        currentNode->left = NULL;
        currentNode->right = NULL;
    }

}
///////////////////////////////////////////////////////////////////////


// Search for given key in BST.  Returns true if found, false otherwise.
bool binarySearchTree :: search (const elemType key, nodeType *p) const{
//PRE: Takes and value and a node
//POST: returns a bool on whether or not the value is in the tree
   bool leftside, rightside;

   if (p) {
      if (p->data == key)
         return true;
      else {
    leftside = search (key, p->left);
    rightside = search (key, p->right);
    return (leftside || rightside);
      }
   } else
      return false;
}


//binary tree: method definitions

// Returns the number of nodes in binary tree.
int binaryTree :: nodecount (nodeType *p) const{
//PRE: Takes a node
//POST: recursively returns the number of nodes in the tree
   if (p) {
      return 1 + nodecount (p->left) + nodecount (p->right);
   } else
      return 0;
}


//Returns the height of the Tree
int binaryTree :: height (nodeType *p) const{
//PRE: Takes a node
//POST: Recursively finds the height of the tree: 
    //height = the number of transitions to the lowest point in the tree

    if(p){
        return 1+max(height(p->left), height(p->right));
    }
    else{return -1;}
}

//Display tree
void binaryTree :: display(nodeType * p) const{
    //PRE: takes a node
    //POST: displays a formatted output of the Tree
    if (p == NULL){//Empty tree
        cout<<"Empty"<<endl;
        return;
    }
   
    int totalHeight = height(p);//height of tree #number of layers
    int howDeep = 0;//counter for what level being displayed
    int widthOfDiplay = pow( 2, height(root)+1);//2^the number of layers
    //essentially the max about of characters that will be displayed on the base level
    
    int offSet = widthOfDiplay/2;//offset to get the middle of the display

    nodeType** currentLayer = NULL;
    nodeType** tempLayer = NULL;
    int widthOfLayer = 1;

    //1st Layer intializer and printer
    currentLayer = new nodeType*[widthOfLayer];
    currentLayer[0] = p;
    cout<<setw(offSet)<<currentLayer[0]->data << endl;//points to head

    //while not at the bottom of tree
    while(howDeep < totalHeight){
        if(tempLayer){//memory Leak Prevention
            delete[] tempLayer;
        }

        //nextLayer
        widthOfLayer = pow(2, howDeep+1);
        tempLayer = new nodeType*[widthOfLayer];

        for(int i = 0; i < widthOfLayer; i +=2){//creating an array of pointers to the nodes
            if(currentLayer[i/2]!= NULL){//in pairs of children
                tempLayer[i] = currentLayer[i/2]->left;
                tempLayer[i+1] = currentLayer[i/2]->right;
            }
            else{//no children to the parent node in the array
                tempLayer[i] = NULL;
                tempLayer[i+1] = NULL;
            }
        }

        delete[] currentLayer; //Free Memory
        currentLayer = new nodeType*[widthOfLayer];
        for(int i=0; i< widthOfLayer; i++){
            currentLayer[i] = tempLayer[i];//making the current layer the children
        }
        widthOfDiplay/=2;
        offSet/=2;

        cout << setw(widthOfDiplay - offSet);
        for(int i=0; i<widthOfLayer; i++){
            if (currentLayer[i] != NULL){//diplaying the data in the current
                cout<<currentLayer[i]->data<< setw(widthOfDiplay);
            }
            else{
                cout<<" "<<setw(widthOfDiplay);
            }
        }
        cout<<endl;
        howDeep++;//cycle
    }
}
//////////////////////////////////////////////////////////////////////


// Displays data in postorder; note that << operator must be overloaded
// if elemType is a user-defined type.
void binaryTree :: postorder (nodeType *p) const{
//PRE: takes a node
//POST: displays post order inline
   if (p) {
      postorder (p->left);
      postorder (p->right);
      cout << p->data << " ";
   }
}


//////////////////////////////////////////////////////////////////////


// Displays data in inorder; note that << operator must be overloaded
// if elemType is a user-defined type.
void binaryTree :: inorder (nodeType * p) const{
//PRE: takes a node
//POST: inline display inorder
   if (p) {
      inorder (p->left);
      cout << p->data << " ";
      inorder (p->right);
   }
}


///////////////////////////////////////////////////////////////////////


// Displays data in preorder; note that << operator must be overloaded
// if elemType is a user-defined type.
void binaryTree :: preorder(nodeType *p) const{
//PRE: takes a node
//POST: inline display preorder
   if (p) {
      cout << p->data << " ";
      preorder (p->left);
      preorder (p->right);
   }
}


///////////////////////////////////////////////////////////////////////
bool imbalanced(nodeType* p){
//PRE: takes a node
//POST: returns a bool on whether or not the node is balanced
    return(p->balanceFactor<-1|| p->balanceFactor>1);
}


void balancedBST :: insert(elemType key, nodeType*& p){
//PRE: takes a key and a node
//POST: creates a balanced Binary Search Tree 
    if(p){//Same as Binary Search Tree insert
        if(key < p->data){
            insert(key, p->left);
        }
        else if(key > p->data){
            insert(key, p->right);
        }
        else{
            cout<<key<<", In tree already"<<endl;
        }
    }
    else{
        p = new nodeType;
        p->data = key;
        p->left = NULL;
        p->right = NULL;
    }
    p->balanceFactor = calculateBF(p);//assigns a balance factor to the node 
    if (p){
        if(imbalanced(p)){//if the node is not balanced
            rotateSubTree(p);//call the rotation decider

        }
        p->balanceFactor = calculateBF(p);//recalculate the Balance factor for the node.
    }
}//end insert

//read out balance factors to the console in pre-Order fashion
void balancedBST:: bFactors(nodeType* p)const{
//PRE: Takes a node
//POST: displays the balance factors for each node in preorder fashion
    if(p){
        cout<<p->balanceFactor<<" ";
        bFactors(p->left);
        bFactors(p->right);
    }
}//end balance factors read out

int balancedBST::calculateBF(nodeType* p)const{
//PRE: takes a node
//POST: returns an int value for the Balance factor
    if (p){
        return (height(p->left)-height(p->right));
    }
    else{return 0;}
}

void balancedBST::rightRotation(nodeType*& p){
//PRE:Takes a node
//POST: Rotates an inbalance to the right

    //   D   :rotation     C
    //  C               B      D
    // B  subtree           subtree(left of D)
    //

    //renaming for clarity
    nodeType*& node1 = p;//D
    nodeType*& node2 = p->left;//C


    //subtree
    nodeType* subtree = node2->right;//the subtree to the right of C

    node2->right= node1;//D to right of C
    node1 = node2;//Reseting head node to the new head node
    node1->right->left = subtree;//moves subTree to the left of D
    node1->right->balanceFactor = calculateBF(node1->right);//recalculates the balance factors
}

void balancedBST::leftRotation(nodeType*& p ){
//PRE:Takes a node
//POST: Rotates an inbalance to the left
       //   D   :rotation           E
    //          E               D       F
    //    subtree  F             subtree(right of D) 
    //
    //node manipulation and clarity
    nodeType*& node1 = p;//D
    nodeType*& node2 = p->right;//C                          

    nodeType* subtree = node2->left;//subtree

    node2->left = node1;//Moves D down to left of E
    node1 = node2;//Reset Head
    node1->left->right = subtree;//subtree to right of D
    node1->left->balanceFactor = calculateBF(node1->left);//Recalculate Balance Factor
}

void balancedBST::rotateSubTree(nodeType*& p){
//PRE: Takes a node
//POST: decides the type of rotation that needs to be done then calls the functions needed
    if(p->balanceFactor>1){//Left side too Heavy
        if(p->left->balanceFactor <0){//heavy left->right
            leftRotation(p->left);//possible dbl rotation
        }
        rightRotation(p);
    }
    else{
        if(p->right->balanceFactor>0){//heavy right->left
            rightRotation(p->right);//possible dbl rotation
        }
        leftRotation(p);
    }
}
