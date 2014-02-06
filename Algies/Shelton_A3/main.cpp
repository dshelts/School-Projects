
#include "SheltonA3.h"


using namespace std;

int main()
{
   string FileName1;
   string FileName2;

/*
    //User input
    cout << "Please input File 1 <name.extension>"<<endl;
    cin  >> FileName1;
    cout << "Please input File 2 <name.extension>"<<endl;
    cin  >> FileName2;
    */

    FileName1 = "testFile18.grd";
    FileName2 = "testFile19.grd";

    //Read in the Files
    DEMDataHolder dem1(FileName1);
    DEMDataHolder dem2(FileName2);

   //sort files respectively to using different types of sort
   dem1.sortData();
   dem2.qsortData();
    /*
   //get analyses
   dem1.performMath();
   dem2.performMath();

   //print table
   dem1.printTable(dem2);//performMath must have been excuted on all objs involved before using this
   //print RMSE
   dem1.findRMSE(dem2);
*/


        return 0;
}
