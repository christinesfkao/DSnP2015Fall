// DSnP HW1
// Data class definition
// Member functions defined in p2_Data.cpp
#ifndef DATA_H
#define DATA_H

class Data 
{
public:
	Data(int); // constructor for a row, given the number of columns
	~Data(); // destructor
	// operator overloading of [], which used to be indicate how many shifts after the assigned address
	// give two versions of the function by whether it is const or not
	const int operator[] (int) const; // the previous const is for the return type, the latter one for the function
	int& operator[] (int); // pass by reference, not a clone

private:
	int *_cols; // do not use move to public or use friend to bypass data encapsulation
};

#endif