#ifndef INTEGER_H
#define INTEGER_H 

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Integer
{
public:
	vector<char> num;  //store the number
public:
	//constructor
	//Integer();
	Integer(string number);	//default constructor
	bool neg = 0;
	bool an = 0;
	//operation overload 
	Integer operator +(const Integer& b);
	Integer operator -(const Integer& b);

	//output overload
	friend ostream& operator << (ostream& out, const Integer& i);
};
#endif