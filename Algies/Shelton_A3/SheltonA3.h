#ifndef SHELTONA3PROXY
#define SHELTONA3PROXY

#include <iostream>//io stream
#include <fstream> //for opening ifstream and ofstream
#include <stdio.h> // printf(0, easy scientific notation
#include <string.h>//string type
#include <stdlib.h>//
#include <algorithm> //sort
#include <cmath>//sqrt()
#include <time.h>// clock_t, clock(), Clocks_Per_Sec
#include <limits.h>//for ticks per second
#include <iomanip>//setw(int n)
using namespace std;

/*
Andrew Shelton
    10/10/13

Description: DEM reader and basic analyzer
*creates a class Called DEMDataHolder that stores data from an file in an array
*can either sort or qsort the array
*it will then preform basic analysis to get
    *Lowest Elevation
    *Highest Elevation
    *Mean
    *Median
    *RMSE between btwn two DEM Files that have been properly read in
        *Dem1.findRMSE(Dem2) a method belonging to a Dem obj taking another Dem obj
        *Doesn't check if it's the same file
    *INPUT: two valid DEM in the ESRI ASCII Grid format

    *OUTPUT: a table displaying, low and high elevation, mean, and median, and the RMSE between them
*///End Description


//Function Declaration
class DEMDataHolder
{
public:
    DEMDataHolder();
    DEMDataHolder(string FileName);
    ~DEMDataHolder();
    void readDataFile ();//reads in file to array
    void sortData();//sort(beginning, end)
    void qsortData();//qsort({array}, numb of elts, sizeof(Type), comparison function)
    void performMath();//gets the low elev and high elev
    void findRMSE(const DEMDataHolder&);
    void printTable(const DEMDataHolder&);

protected:
    string FileName;//File name
    float* Data;//future Data Arrau
    long lengthOfArray;//length of Array
    bool sorted;//until True
    float lowEle;//lowest elevation
    float highEle;// highest elevation
    float mean;//mean
    float median;//median

};




#endif // SHELTONA3PROXY






