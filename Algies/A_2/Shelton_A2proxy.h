#ifndef _MYNUMBERH
#define _MYNUMBERH

#include <iostream>
#include <string>

/*Andrew Shelton
 *Shelton_A2proxy.cpp
 *9/22/13
  *
  *Description: Base Conversion
  *initializing a class establishes only the base waiting for the
  *cin to get the value and decimal value.
  *Takes user input (cin) creates an object of designated number type
  *such as binary, decimal,  and hexidecimal.(using strtol)
  *currently operator= is only overloaded to handle  obj = obj set up.
  * obj = "string" will not work.
  * obj1 = obj2 will convert the value obj2 to base of obj1 and overwrite any previous value
  *there is no error checking for strings without numbers

  *INPUT: Any length string of numbers

  *OUTPUT: Strings of values that belong to the class being called
*/
using namespace std;


//=============Number======================================================

class number
{
public:
	number();//default CTOR
	~ number();//number destructor
	string convert(int);//universal converter used to convert values from one base to another
	friend istream& operator>> (istream& , number&);//cin input overide takes a string
	friend ostream& operator<< (ostream& , number&);//cout overide allows display of string values
    int get_decimalValue()const{return this->decimalValue;};//getter allows inheireted classed to access but not change the decimalValue
    //string get_value()const{return this->value;};//getter used in debugging had problems with read out

protected:
	string value;//string value from cin
	int base;//used by inheireted classes
	int decimalValue;//used by number and inheireted to store strtol for later convert method


};
//=============endNum======================================================


//+++++++++++++BINARY++++++++++++++++++++++++++++++++++++++++++++++++++++++
class binary : public number
{
public:
	binary();//Null CTOR
	binary(const number&);//Copy CTOR
	~binary();//Destructor

    number& operator= (number&);// essentially using number::convert to convert then store other number class inheireted objects
};
//+++++++++++++endBina+++++++++++++++++++++++++++++++++++++++++++++++++++++

//---------------DECIMAL---------------------------------------------------
class decimal : public number
{
public:
	decimal();//NULL CTOR
	decimal(const number&);//COPY CTOR
	~decimal();//DESTRUCTOR

	number& operator= (number&);// essentially using number::convert to convert then store other number class inheireted objects


};
//---------------endDeci---------------------------------------------------

//**********************HEXIDECIMAL****************************************
class hexadecimal : public number
{
public:
	hexadecimal();//NULL CTOR
	hexadecimal(const number&);//COPY CTOR
	~hexadecimal();//DESTRUCTOR

	number& operator= (number&);// essentially using number::convert to convert then store other number class inheireted objects

};
//*****************endHexi*************************************************

#endif
