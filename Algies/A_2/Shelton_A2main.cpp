#include <iostream>
#include <string>
#include "Shelton_A2proxy.h"

using namespace std;
//==========================================================================


int main()
{
	binary bnum, bnum2, bnum3;
	decimal dnum, dnum2, dnum3;
	hexadecimal hnum, hnum2, hnum3;

	cout << "Enter binary 1: ";
    cin >> bnum;
	cout << "Enter binary 2: ";
	cin >> bnum2;
	cout<< "Enter binary : ";
	cin>> bnum3;
    cout << "binary 1, 2, 3: " << bnum << " , "<< bnum2 <<" , " << bnum3 << endl;


	cout << "Enter Hex1: ";
	cin >> hnum;
	cout << "2";
	cin >> hnum2;
	cout << "3";
	cin >> hnum3;

	cout << "Hex number is 1,2,3: " << hnum<< " "<< hnum2<<" " <<hnum3 << endl;

	cout << "Enter dec1: ";
	cin >> dnum;
	cout << "2";
	cin >> dnum2;
	cout << "3";
	cin >> dnum3;
    cout << "dec number is 1,2,3: " << hnum<< " "<< hnum2<<" " <<hnum3 << endl;

    //////////////dnum =
    dnum = bnum2;
    cout<<"dnum = bnum2: "<<dnum<<" bnum2 "<< bnum2<<endl;
    dnum = hnum2;
    cout<<"dnum = hnum2: "<<dnum<<" hnum2 "<< hnum2<<endl;


    /////////////////////bnum =
    bnum = dnum;
    cout<<"bnum = dnum: "<<bnum<<" dnum "<< dnum<<endl;
    bnum = hnum;
    cout<<"bnum = hnum: "<<bnum<<" hnum "<< hnum<<endl;

    /////////// hum =
    hnum = dnum3;
    cout<<"hnum = dnum3: "<<hnum<<" dnum3 "<< dnum3<<endl;
    hnum = bnum3;
    cout<<"hnum = bnum3: "<<hnum<<" bnum 3 "<< bnum3<<endl;
	return 0;
}
