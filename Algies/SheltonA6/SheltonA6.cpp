//SheltonA6.cpp

//*******************************************************************

// Developer: Andrew Shelton
//
// Purpose:Implementation of a hash table using quadratic probing to find an open space
//  in the table.

// Description: User inputs:
//                  Table Size
//                  A constant
//                  Desired number to be diplayed
//                  text file
//  Program keeps track of number of collisions and the number of times
//        a certain key is input into the table. It gives organize out of
//        this information
//*******************************************************************
#include <iostream>//input output
#include <stdio.h>//
#include <string>//string functionality
#include <stdlib.h>//exit(-1)
#include <iomanip>//setw()
#include <fstream>//readin



using namespace std;

//HASH ITEM CLASS
class hashItem{
	public:
		hashItem();//CTOR
		~hashItem();//DTOR
		hashItem(string);//CTOR

		void updateCount();//update number of times the item has been seen
		void updateCollision();//updates number of times a item has been collided with given index

		//getters
		string getString(){return key;};//getter of word in the item
		int getCount(){return count;};// getter of the word's count
		int getCollision(){return collision;};// getter of the word's collision count
		//end getters

	private:
		string key;//word
		int count;//number of times word has occured in the text
		int collision;// number of times another item has tried to index into the spot in the array
};
//END HASH ITEM CLASS
////////////////////////////////////////////////////////////////////////////////////////////

//Hash Table CLass
////////////////////////////////////////////////////////////////////////////////////////////
class hashTable{
public:
	hashTable(int, int, float);//CTOR
	~hashTable();//DTOR

	void intializeTable();//INITIALIZES full hash table with blank inputs

	int hash(string);//returns an index value where the item should be placed
	int totalCollision();//adds up the total number of collision and returns it
	float hashing(string);//used by hash to get the ASCii value of the word * A constant returned to hash function
	void insert(hashItem&, int);//insert an item into the Hash Table / quadracting solves collisions
	bool full();// checks to see if the Hash table is full
	void display();//organized display of hashtable
private:

	//variables
	hashItem *hashtable;//pointer to a hash table
	float A;//A constant used for hashing
	int numberToDisplay;//number of items displayed
	int sizeOfTable;//size of the Table
	//end Variables



};
//END HASH TABLE CLASS
////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////
//hashItem methods

hashItem::hashItem(){
    //PRE: Takes no Arguements
    //POST: Contructed a DEFAULT item of the ghost fill of the Hash table
	key   = "DEFAULT";
	count = 0;
	collision = 0;
}
hashItem::~hashItem(){
	//destructed
}

hashItem::hashItem(string newKey){
    //PRE: Takes a string
    //POST: constructs an item to be placed in the hash table
	key = newKey;
	count = 1;
	collision = 0;
}


void hashItem::updateCount(){
    //PRE: Takes no Arguements
    //POST: incremented count
	count+=1;
}

void hashItem::updateCollision(){
	//PRE: Takes no Arguements
	//POST: incremented collision
	collision+=1;
}

//END hashItem methods
////////////////////////////////////////////////////////////////////////////////////////////


hashTable::hashTable(int TableSize, int ntd, float a){
    //PRE: takes 2 ints and a float
    //POST: initialized a ghost table with the desired table size, number to display at the end, and A Constant
    sizeOfTable=TableSize;
    numberToDisplay = ntd;
    A = a;
	if(numberToDisplay>sizeOfTable){
		numberToDisplay = sizeOfTable;
	}//end if error check
	hashtable = new hashItem[sizeOfTable];

	intializeTable();

}

hashTable::~hashTable(){
	//destructed
}

int hashTable::hash(string key){
    //PRE: Takes a string
    //POST: returns an index for placement in the table
    float hash_value = 0;
    hash_value = hashing(key);
	hash_value = hash_value-(int)hash_value;
	hash_value = sizeOfTable*hash_value;
	return hash_value;
}//this works

float hashTable::hashing(string key){
    //PRE: takes a string
    //POST: returns partial hashed index
    float hashing = 0;
    char newKey;
    for(unsigned int i=0; i<key.length(); i++){
        newKey = key[i];
        hashing+=newKey;
    }

    hashing = hashing*A;
    return hashing;//this works
}

void hashTable::insert(hashItem& item,  int index){
    //PRE: takes an item and its index
    //POST: inserts the item into the index or the quadradically adjusted index
    if(this->full()){
        cout<<" Hash Table Full Exiting Program "<<endl;
        exit(-1);
    }
    bool IFed = false;

    if(hashtable[index].getString() == "DEFAULT"){
    //index empty
        hashtable[index] = item;//placed in table
        IFed=true;
    }//end if

    else if(hashtable[index].getString() == item.getString()){
        //index the same value
        hashtable[index].updateCount();//placed in table
        IFed=true;
    }//else if
    else{
        int quadProb = 0;
        while((hashtable[index].getString() != "DEFAULT") || (hashtable[index].getString() == item.getString())){
            hashtable[index].updateCollision();
            //cout<<"Key: "<< hashtable[index].getString()<<" Number of collisions: "<<hashtable[index].getCollision()<<endl;
            quadProb+=1;
            index = index +(quadProb*quadProb);
            index = index%sizeOfTable;
        }//end while


        if(hashtable[index].getString() == "DEFAULT" && IFed==false){
        //index empty
            hashtable[index] = item;//placed in table
        }//end if

        else if(hashtable[index].getString() == item.getString()&& IFed==false){
            //index the same value
            hashtable[index].updateCount();//placed in table
        }//else if

    }//end while
}

bool hashTable::full(){
    //PRE: Takes no Arguements
    //POST: determines if table is full returns true if full
    for(int i=0; i<sizeOfTable; i++){
        if(hashtable[i].getString()=="DEFAULT"){
            return false;
        }//end if
    }//end for
    return true;
}

void hashTable::display(){
    //PRE: Takes no Arguements
    //POST: displays an organized table of information from the hash table
	cout<<"table size: "<<sizeOfTable<<endl;
	cout<<"value for A: "<<A<<endl;
	cout<<"Number of items displayed: "<<numberToDisplay<<endl;
	cout<<endl<<"display table here"<<endl;
	int i=0;
    int j=0;//howManyDisplayed
	cout<<"Index"<<setw(15)<<"Word"<<setw(10)<<"Count"<<setw(15)<<"Collisions"<<endl;
	cout<<"-----------------------------------------------"<<endl;

	while(j<numberToDisplay&&i<sizeOfTable){
        if(hashtable[i].getString()=="DEFAULT"){
            //Do nothing
        }//if
        else{
        cout<<setw(5)<<i<<setw(15)<<hashtable[i].getString()<<setw(10)<<hashtable[i].getCount()<<setw(10)<<hashtable[i].getCollision()<<endl;
        j++;
        }//else
        i++;
	}
	cout<<"Total number of Collisions: "<<this->totalCollision()<<endl;
}

int hashTable::totalCollision(){
    //PRE: Takes no Arguements
    //POST: returns the full number of collisions across the whole hash table
    int totalCollisions = 0;
    for(int i=0; i<sizeOfTable; i++){
        totalCollisions += hashtable[i].getCollision();
    }//end for
    return totalCollisions;

}
void hashTable::intializeTable(){
    //PRE: Takes no Arguements
    //POST: Filled the Hash table with empty items

	//intializes a hash table Full of "DEFAULT" hash items
	cout<<sizeOfTable<<endl;
	hashItem item;
	for(int i=0; i<sizeOfTable; i++){
		hashtable[i]=item;
	}//end For

}
//End hashTable Methods
////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////
//READIN
void readDataFile(string FileName, hashTable& table){
    //PRE: Takes a file name
    //POST: returns nothing, but has placed the words from the text file from in the hashTable
    //Declaration of variables
    string word;

    ifstream fin;//allows to write to file
    string filename;
    filename = FileName;//for convience

    fin.open(filename.c_str());
    if(fin.fail()){
        cout<<"ERROR: file called " << filename << " did NOT open."<< endl;
        exit(-1);// default exit
    }



	int index;
    while(fin){
    	fin >> word;
    	hashItem item(word);
    	index =  table.hash(item.getString());
        //cout<<"Key: "<<item.getString()<<" index: "<<index<<endl;
        table.insert(item, index);
    }//end while


    fin.close();
}
//END READIN
////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    float A;
    int TableSize, ntd;
    string file;
   //User input
    cout<<"INPUT TABLE SIZE"<<endl;
	cin>>TableSize;
	cout<<"INPUT A VALUE"<<endl;
	cin>>A;
	cout<<"INPUT FILE NAME"<<endl;
	cin>>file;
	cout<<"INPUT NUMBER OF ITEMS YOU WANT TO DISPLAY FROM TABLE"<<endl;
	cin>>ntd;
	//end user input
	//HARD CODE
   /* A = .618;
    TableSize = 201;
    ntd =201;
    file = "Test.txt";*/
    hashTable dataTable(TableSize, ntd, A);

    readDataFile(file, dataTable);
	dataTable.display();

	cout<<"---------------------DONE----------------------"<<endl;
    return 0;
}
