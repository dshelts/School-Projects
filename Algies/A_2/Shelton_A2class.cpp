#include <iostream>
#include <string>
#include <stdlib.h>
#include "Shelton_A2proxy.h"

using namespace std;

//===========Number=========================================================
number::number()
{//PRE: TAKES NOTHING, WHENEVER IT OR ITS CHILDREN ARE CALLED TO CREATE AND OBJ
 //POST:SETS A DECIMALVALUE
	this->decimalValue = 0;//SETS A NULL DECIMALVALUE
}

number::~number(){}//INLINE DESTRUCTOR

string number::convert(int newbase)
{//PRE: TAKES THE BASE OF THE DESIRED NEW VALUE; E.G for binary it would take 2
 //POST: RETURNS A STRING WITH THE CONVERTED VALUE OF THE OLD OBJ
    int DV = this->decimalValue;// always converts from the stored decimal value
    string converted;//the string that will be returned
    int n = 1;//counter i
    int b = newbase;// the base to be converted into
    int m = DV;// m for the mutatable decimalValue
    int p;//is the variable to index into the choices list
    string choices = "0123456789abcdefghijklmonpqrstuvwxyz";// used to create new value

    //Top down build find the upper limit essential a/b while b<a
    while(DV/(b) != 0 )
    {n++;//increase how long the value will be> for loop
     b = b * newbase;//Ex: 2, 4, 8, 16
    }
    b = b/newbase;// reeling in the out of bounds base 64->32

    for(int i = n; i>0; i--)// for loop to construct string
    {
        p = m/(b);// divides decival to  by the base to get the floored value 3/2 = 1
        converted = converted + choices[p]; //keys into the choices to construct string
        m = m%(b);// get the remainder for the next time through the for loop
        b = b/newbase;// decrements the base
    }
    return converted;
}



istream& operator>> (istream& ci, number& n)
{	ci>>n.value;//stores inputed string in the value
    n.decimalValue = strtol(n.value.c_str(), NULL, n.base);// strtol to convert the string to a long
	return ci;
}

ostream& operator<< (ostream& co, number& n)
{
    co<< n.value;//output value
    return co;
}

///////////////////////////////////////////////////////////////////////////


//+++++++++++++BINARY++++++++++++++++++++++++++++++++++++++++++++++++++++++
binary::binary()
{
	this->base = 2;//NULL constructor sets base
}

binary::binary(const number& n)
{
	this->decimalValue = n.get_decimalValue();//using getter to assign decimal value

}

binary::~binary(){}//INLINE DESTRUCTOR

number& binary::operator= (number& n)
{//PRE: TAKES IN ANY NUMBER OR CHILD
 //POST: overwrites the old obj with the new obj's converted value into binary
    string s = n.convert(this->base);//calls convert to change obj into the base 2
    this->value = s;//overwrites old value with the returned value
    this->decimalValue = n.get_decimalValue();//gets the new decimal value and overrides the old
    return (*this);
}
///////////////////////////////////////////////////////////////////////////

//---------------DECIMAL---------------------------------------------------
decimal::decimal()
{
    this->base         = 10;//NULL constructor sets base

}

decimal::decimal(const number& n)
{
	this->decimalValue = n.get_decimalValue();// using getter to assign decimal value
}
decimal::~decimal(){}//Inline destructor

number& decimal::operator= (number& n)
{//PRE: takes in any number or child obj
 //post: overwrites the old obj with the new obj's converted value into decimal
    string s = n.convert(this->base);//calls convert to change an obj to base 10
    this->value = s;//stores new value
    this->decimalValue = n.get_decimalValue();//overwrites old decival with the new one
    return (*this);//return everything
}
//**********************HEXIDECIMAL****************************************

hexadecimal::hexadecimal()
{
	this->base  = 16;//NULL constructor sets base

}

hexadecimal::hexadecimal(const number& n)
{
	this->decimalValue = n.get_decimalValue();//using getter to assign decimal value

}

hexadecimal::~hexadecimal(){}//inline destructor

number& hexadecimal::operator= (number& n)
{//PRE: takes in any number or child obj
 //post: overwrites the old obj with the new obj's converted value into hexidecimal
    string s = n.convert(this->base);//calls conver to change an obj to base 16
    this->value = s;
    this->decimalValue = n.get_decimalValue();
    return (*this);
}

