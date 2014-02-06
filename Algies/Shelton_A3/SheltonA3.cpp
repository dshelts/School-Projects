#include "SheltonA3.h"


DEMDataHolder::DEMDataHolder()
{//NULL DATA CTOR
    //PRE: can contstruct obj of DEMDATA CLASS with no arg
    this->FileName = "NO FILE NAME";
}

DEMDataHolder::DEMDataHolder(string Filename)
{//CTOR
    //PRE: takes a string "File"
    //POST: File name in obj as well as the array of evelations
    this->FileName = Filename;
    readDataFile();//reads the data file into the array
    this->sorted = false;//Sets a sorted bool
}

DEMDataHolder::~DEMDataHolder(){}//inline destructor


void DEMDataHolder::readDataFile()
{
    //PRE: takes no arguements but if there is no real file it will close the program
    //POST: read in the data to an array and sets the number of elts in the array(lengthOfArray)

    //Declaration of variables
    string junk; //for toss away variables
    long ncols;   //length of col
    long nrows;  //length of rows
    float datapoint;//grabs the data
    ifstream fin;//allows to write to file
    string filename;
    filename= this->FileName;//for convience

    fin.open(filename.c_str());
    if(fin.fail())
    {
        cout<<"ERROR: file called " << filename << " did NOT open."<< endl;
        exit(-1);// default exit
    }

    cout<< "Reading "<< filename << " into Data array." <<endl;
    //Grabbing important pieces
    fin >> junk;//"ncols"
    fin >> ncols;// the actual number
    fin >> junk;//"nrows"
    fin >> nrows;//actual numbers

    for(int i = 0; i < 6; i++)
        //Removing yll, xll, cellsize and their respective numbers
        {fin>>junk;}//end for

    this->lengthOfArray = ncols * nrows;//number of in elets in array
    this->Data = new float[lengthOfArray];//constructs an array with number of elets

    fin >> datapoint;// grabs first data point
    long counter = 0; //place in array
    while(fin && counter < lengthOfArray)
    //constructing array
    {
        this->Data[counter] = datapoint;
        counter++;

        fin >> datapoint;
    }//end while

    fin.close();
    cout<<"DONE Reading Files from: " <<this->FileName<<endl<<endl;
}

void DEMDataHolder::sortData()
{
    //PRE: sort needs a pointer to the front and end of the array
    //POST: a sorted array
    double t;// time
    clock_t start, stop;
    start = clock();
    sort(this->Data, (this->Data + this->lengthOfArray));//(front pointer of array, end of array pointer)
    stop = clock();
    t = (double)(stop-start)/CLOCKS_PER_SEC;
    cout<<"sort timer: "<< t<<endl;
    cout<<this->lengthOfArray<<endl;
    this->sorted = true;
}
//FUNCTION NOT IN CLASS USED FOR QSORT
int compare(const void * a, const void * b)
{//does not belong to File::
    //PRE: two void pointers to access and compare the numbers in the array
    //POST: returns an int to the qsort() when it is asked to
    if ( *(float*)a < *(float*)b )
    {
        return -1 ;
    }
    else
    {
        return 1;
    }
    //returns a positive or negative value to qsort
}//ENDFUNCTION

void DEMDataHolder::qsortData()
{//PRE: qsort() needs the start of the array, the number of elts, sizeof(variable type in array), comparison()
    //POST: qsorts an array in place
    double t;
    clock_t start, stop;
    start = clock();
    qsort(this->Data, lengthOfArray, sizeof(float), compare);//qsort
    stop = clock();
    t = (double)(stop-start)/CLOCKS_PER_SEC;
    cout<<"qsort timer: "<< t<<endl;
    this->sorted = true;
cout<<this->lengthOfArray<<endl;
}

void DEMDataHolder::performMath()
{//PRE: needs the array sorted checks for whether or not it's sorted
    //POST: The array is sorted, you have access to the low and high elevation
        //the mean and the median

    while (this->sorted == false)
    {//if sorted
        cout<< "File NOT SORTED defaulting to sort()"<<endl;
        this->sortData();
    }//end while

    //high low
    this->lowEle= this->Data[0];
    this->highEle= this->Data[this->lengthOfArray-1];
    //end high low

    //mean
    float total = 0;
    for(int i = 0; i<this->lengthOfArray; i++){total += this->Data[i];}
    this->mean = total/lengthOfArray;
    //mean end

    //median
    if(lengthOfArray%2 == 0)
    {
        int key = (lengthOfArray/2);
        float numer = (this->Data[key])+(this->Data[key+1]);
        float denom = 2.0;
        float m = numer/denom;
        this->median = (m);//-1 to account for 0 index
    }

    else
    {
        this->median = this->Data[lengthOfArray/2];
    }
    //end median
//end analysis
}

void DEMDataHolder::findRMSE(const DEMDataHolder& otherData)
{//PRE: need an array and another DEMDataHolder array
        //assumes the arrays are the same length
    //POST: Yeilds the Root mean square error of the two files
        // not stored any where just cout<< at end of function
    long N = this->lengthOfArray;
    float RMSE= 0;
    float sum = 0;
    float tempValue;
    float divSum;

    for(int i = 0; i<N; i++)
    {
        tempValue =((this->Data[i])-(otherData.Data[i]));
        sum += (tempValue*tempValue);
    }
    divSum = sum/N;
    RMSE = sqrt(divSum);

    cout<<"RMSE of "<<this->FileName<<" and "<<otherData.FileName<<": "<<RMSE<<endl;
    cout<<"------------------------------------------------------------------------"<<endl;


}

void DEMDataHolder::printTable(const DEMDataHolder& other)
{   //PRE: preform math needs to have been carried out
        //takes another DEMDataHolder thus only capable of printing a table for only one set of data
    //POST: cout a table to console of analysis of files


   cout<<" File Name   | Lowest Elevation | Highest Elevation | Mean | Median "<<endl;
   cout<<"------------------------------------------------------------------------"<<endl;
   cout<< this->FileName<<setw(10)<<this->lowEle<<setw(15)<<this->highEle<<setw(15)<<this->mean<<setw(10)<<this->median<<endl<<endl;
   cout<< other.FileName<<setw(10)<<other.lowEle<<setw(15)<<other.highEle<<setw(15)<<other.mean<<setw(10)<<other.median<<endl<<endl;

}


