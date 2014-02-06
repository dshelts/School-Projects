#include "Hash.h"
////////////////////////////////////////////////////////////////////////////////////////////
//hashItem methods

hashItem::hashItem(){
	key   = "DEFAULT";
	count = 0;
	collision = 0;
}
hashItem::~hashItem(){
	//destructed
}

hashItem::hashItem(string newKey){
	key = newKey;
	count = 1;
	collision = 0;
}


void hashItem::updateCount(){
	count+=1;
}

void hashItem::updateCollision(){
	collision+=1;
}

//END hashItem methods
////////////////////////////////////////////////////////////////////////////////////////////


hashTable::hashTable(int TableSize, int ntd, float a){

    sizeOfTable=TableSize;
    numberToDisplay = ntd;
    A = a;
	if(numberToDisplay>sizeOfTable){
		numberToDisplay = sizeOfTable;
	}//end if error check
	hashtable = new hashItem[sizeOfTable];

	intializeTable();

    cout<<"size of table: "<<sizeOfTable<<" numberToDisplay: "<<numberToDisplay<<" A: "<<A<<endl;
}

hashTable::~hashTable(){
	//destructed
}

int hashTable::hash(string key){
    float hash_value = 0;
    hash_value = hashing(key);
	hash_value = hash_value-(int)hash_value;
	hash_value = sizeOfTable*hash_value;
	return hash_value;
}//this works

float hashTable::hashing(string key){
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

    }
}

bool hashTable::full(){
    for(int i=0; i<sizeOfTable; i++){
        if(hashtable[i].getString()=="DEFAULT"){
            return false;
        }//end if
    }//end for
    return true;
}

void hashTable::display(){
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
    int totalCollisions = 0;
    for(int i=0; i<sizeOfTable; i++){
        totalCollisions += hashtable[i].getCollision();
    }//end for
    return totalCollisions;

}
void hashTable::intializeTable(){
	//intializes a hash table Full of "DEFAULT" hash items
	cout<<sizeOfTable<<endl;
	hashItem item;
	for(int i=0; i<sizeOfTable; i++){
		hashtable[i]=item;
	}//end For

}
//End hashTable Methods
////////////////////////////////////////////////////////////////////////////////////////////

