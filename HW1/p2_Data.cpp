// DSnP HW1
// Data class member-function definitions
#include <iostream>
#include "p2_Data.h" // include Data class definition
using namespace std;

Data::Data(int numberOfCols) // constructor, define a class Data to represent the data of a row.
{
	// Since the number of columns is not known in the beginning and will be fixed after initialization, please use “int *” as its data member.
	_cols = new int[numberOfCols]; // given address for the array of rows to be initialized	
} 

const int Data::operator[] (int subscript) const // the previous const is for the return type, the latter one for the function
{
	return _cols[subscript];
} 

int& Data::operator[] (int subscript)
{
	return _cols[subscript];
} // pass by reference, not a clone

Data::~Data()
{
	// delete[] _cols;
}

