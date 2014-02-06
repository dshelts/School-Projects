
#include "Hash.h"

////////////////////////////////////////////////////////////////////////////////////////////
//READIN
void readDataFile(string FileName, hashTable& table){
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
	int counter = 0;
    while(fin){
    	fin >> word;
    	counter++;
    	hashItem item(word);
    	index =  table.hash(item.getString());
        //cout<<"Key: "<<item.getString()<<" index: "<<index<<endl;
        table.insert(item, index);
    }//end while
    cout<<"Word Count: "<<counter<<endl;


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
    //cout<<"INPUT TABLE SIZE"<<endl;
	//cin>>TableSize;
	//cout<<"INPUT A VALUE"<<endl;
	//cin>>A;
	//cout<<"INPUT FILE NAME"<<endl;
	//cin>>file;
	//cout<<"INPUT NUMBER OF ITEMS YOU WANT TO DISPLAY FROM TABLE"<<endl;
	//cin>>ntd;
	//end user input
    A = .618;
    TableSize = 1001;
    ntd =0;
    file = "Test.txt";
    hashTable dataTable(TableSize, ntd, A);

    readDataFile(file, dataTable);
	dataTable.display();

	cout<<"---------------------DONE----------------------"<<endl;
    return 0;
}
