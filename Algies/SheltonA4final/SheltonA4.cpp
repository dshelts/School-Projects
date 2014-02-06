#include <iostream>
#include <fstream>//open files
#include <string.h>//string type
#include <stdlib.h>//exit(-1)
#include <vector>//hull vector

using namespace std;
/*
Andrew Shelton
    11/5/13
Description: Finds the convex Hull of a set of points using the brute force algorithm that has O(n^3).
    This program unfortunately seems to be limited to only finding a Hull from a file
     consisting of less than 1000 points.
     //I don't know why it's doing this....


*/
class coordinatePair
{
public:
    coordinatePair();//Null CTOR
    coordinatePair(int, int);//CTOR
    //~coordinatePair();//destructor
    int getX()const{return this->x;};//allows access to the value at x without the capability of manipulating it
    int getY()const{return this->y;};//allows access to the value at y without the capability of manipulating it

private:
    int x;//x value
    int y;//y value

};

class datapointcontainer
{
public:
    datapointcontainer();//NULL CTOR
    datapointcontainer(string File);//CTOR Reads the file into the array of appropriate length
    ~datapointcontainer();//DTOR
    void readDataFile();//Read in File
    void display();//displays the point pairs in the array
    void findConvexHull();// Uses brute force algorithm to find the Convex hull of a set of points
    void displayVector();//displays the vector of points that is the convex hull
    void addToVector(const coordinatePair&);//adds points to the vector if they belong to the HULL

private:
    int sizeOfArray;//size of the array/number of points
    coordinatePair* paircontainer;// an array
    vector<coordinatePair> Hull;//vector to store the points in the Hull
    string Filename;// The origin filename that the points were taken from
};
//COORDINATE PAIR INFORMATION//
coordinatePair::coordinatePair()
{
    //NULL CONSTRUCTOR
}
coordinatePair::coordinatePair(int x, int y)
{
    //Pre: takes in two ints that are stored to x and y
    //Post: a Node group that has both an x and y values. acts as a point pair
    this->x = x;
    this->y = y;
}
//END COORDINATE PAIR INFORMATION//

//DATA POINT CONTAINER//
datapointcontainer::datapointcontainer()
{
    //Null CTOR
    this->Filename = "No File name";
}

datapointcontainer::datapointcontainer(string File)
{
    //PRE: Takes a string to be opened and read into the obj
    //POST: an array full of Coordinate Pairs read in from the file
    this->Filename = File;
    readDataFile();
}

datapointcontainer::~datapointcontainer()
{
    //Destructor
}

void datapointcontainer::readDataFile()
{
    //PRE: Takes no arguments. There needs to be a valid file named stored in the class already
    //POST: Read the file of x,y pairs into nodes and put the nodes into the array
    int numOfpairs;
    int x;
    int y;
    ifstream fin;//read in
    string filename;
    filename = this->Filename;

    fin.open(filename.c_str());
    if(fin.fail())
    {//error check
        cout<<"ERROR: file called "<<filename<<" did NOT Open."<<endl;
        exit(-1);
    }//end if

    cout<< "Reading "<<filename<<endl;
    fin >> numOfpairs;
    this->sizeOfArray = numOfpairs;//size of array from file
    this->paircontainer = new coordinatePair[numOfpairs];// new array with appropriate size


    for(int i=0; i<sizeOfArray; i++)
    {//read in the pairs to new nodes and then adds nodes to array
        fin >> x;
        fin >> y;

        coordinatePair newPair(x,y);
        paircontainer[i] = newPair;

    }//end for
   fin.close();//close file pipe
    cout<<"Done Reading Files from "<<filename<<endl;
}

void datapointcontainer::display()
{
    for(int i = 0; i < sizeOfArray; i++)
    {//reads out every pair in the array
        cout<<"("<<paircontainer[i].getX()<<", "<<paircontainer[i].getY()<<") "<<endl;

    }//END FOR
}


void datapointcontainer::findConvexHull()
{   int x1, x2, y1, y2, checkX, checkY, temp;//variables for use in the for loop
    int a, b, c, result;//line results
    bool firstRun, pointsAreGood;// bools for third for loop

    for(int i=0; i<sizeOfArray; i++)
    {//gets each pair of x,y points
        x1 = paircontainer[i].getX();
        y1 = paircontainer[i].getY();
        for(int j=0; j<sizeOfArray; j++)
        {//gets each pair of x,y points
            x2 = paircontainer[j].getX();
            y2 = paircontainer[j].getY();
            pointsAreGood= false;//false to start assuming they are the same
            if (!(x1 == x2 && y1 == y2))// if the comparing points aren't the same
            {
                //drawline
                a = y2- y1;
                b = x1- x2;
                c = x1*y2 - y1*x2;
                //end drawline
                pointsAreGood = true;//assuming the points are in the Hull
                firstRun = true;//first time through the third for loop
                for (int k = 0; k<sizeOfArray; k++)
                {
                    checkX = paircontainer[k].getX();
                    checkY = paircontainer[k].getY();
                    if ((checkX == x1 && checkY == y1) or (checkX == x2 && checkY == y2))
                    {//if we are comparing the same points ignore the loop until we aren't
                        continue;
                    }//end if

                    result = ((a*checkX) + (b*checkY) - c);// checking the side of the line
                    if(firstRun)
                    {//only happens on the first proper run through
                        temp = result;// temp should never be changed;
                        firstRun = false;
                    }//end if
                    else
                    {//no points are the same enter the check to see if they stay on the same side of the line
                        if(result==0 and temp==0)//stays on the line
                        {                        }
                        else if(result>0 and temp>0)//stays on the same side of the line
                        {                        }
                        else if (result<0 and temp<0)//stays on the same side of the line
                        {                        }
                        else
                        {//not on the same side thus not in hull, break the loop
                            pointsAreGood=false;// points shouldn't be added
                            break;
                        }//end else
                    }//checking the side of the line END ELSE

                }//END COMPARISON FOR LOOP 3RD ONE
                if(pointsAreGood)
                {// if the points aren't the same and if they pass the line test
                    //entered into vector
                    addToVector(paircontainer[i]);
                    addToVector(paircontainer[j]);
                }//end if
            }//END IF THEY AREN'T THE SAME POINTS
        }//end second for
    }//end first for
}//end function

//VECTOR STUFF//
void datapointcontainer::addToVector(const coordinatePair& pointPair)
{
    //PRE: Takes a pointer to a coordinate pair
    //POST: inserted the pair into the Hull vector
    for (unsigned int i=0; i < Hull.size(); i++)
    {
        if(Hull[i].getX() == pointPair.getX() and Hull[i].getY()==pointPair.getY())
        {//check to see if in the hull
            return;
        }//end if
    }//end for
    Hull.push_back(pointPair);//add point to HULL
}

void datapointcontainer::displayVector()
{
    //PRE: takes no arguement
    //POST: displays the coordinate pairs in the vector(note: not in clockwise order)
    for (unsigned int i=0; i < Hull.size(); i++)
    {
        cout<<Hull[i].getX()<<", "<<Hull[i].getY()<<endl;
    }//end for
}
//END VECTOR STUFF//
//END DATA POINT CONTAINER//
int main()
{
    string readInFile;
    cout<<"Please input a File: "<<endl;
    cin>>readInFile;
    datapointcontainer PointContainer(readInFile);
    cout<<"===============POINTS==============="<<endl;
   // PointContainer.display();
    cout<<"=============END POINTS============="<<endl;
    PointContainer.findConvexHull();
    cout<<"===============HULL================="<<endl;
    PointContainer.displayVector();
    cout<<"=========== END HULL ==============="<<endl;

    cout<<endl<<"---------DONE----------"<<endl;
    return 0;
}









