//SheltonA6.cpp

//*******************************************************************

// Developer: Andrew Shelton

// Purpose:Implementation of a hash table using Knuth's hash function



//*******************************************************************
#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <iomanip>
#include <fstream>



using namespace std;

//HASH ITEM CLASS
class hashItem{
	public:
		hashItem();//CTOR
		~hashItem();//DTOR
		hashItem(string);//CTOR

		void updateCount();
		void updateCollision();

		//getters
		string getString(){return key;};
		int getCount(){return count;};
		int getCollision(){return collision;};
		//end getters

	private:
		string key;
		int count;
		int collision;
};
//END HASH ITEM CLASS
////////////////////////////////////////////////////////////////////////////////////////////

//Hash Table CLass
////////////////////////////////////////////////////////////////////////////////////////////
class hashTable{
public:
	hashTable(int, int, float);
	~hashTable();

	void intializeTable();

	int hash(string);
	int totalCollision();
	float hashing(string);
	void insert(hashItem&, int);
	bool full();
	void display();
private:

	//variables
	hashItem *hashtable;
	int collisions;
	float A;
	int numberToDisplay;
	int sizeOfTable;
	//end Variables



};
//END HASH TABLE CLASS
////////////////////////////////////////////////////////////////////////////////////////////

