//DSnP HW1
#include <iostream> // for cout and cin
#include <fstream> // for reading files
#include <string> // for saving text into strings
#include <sstream> // for cutting strings
#include "p2_Data.cpp" // for making the rows of a table
#include <vector> // for making a table formed of "Data(rows)"
#include <iomanip> // to use setw() and right
#include <algorithm> // to use sort()
using namespace std;

// function template sort definition
// template <class RandomAccessIterator, class StrictWeakOrdering> 
// void sort(RandomAccessIterator first, RandomAccessIterator last, StrictWeakOrdering comp);

// struct definition for SortData
struct SortData 
{
	bool operator() (const Data&, const Data&); 
	void pushOrder(int);
	vector<int> _sortOrder;
};

bool SortData::operator() (const Data& d1, const Data& d2)
{
	for(int count = 0; count < _sortOrder.size(); count++) 
	{
		// if empty, the value would be 1000, which is much larger than anything else
		// i.e. no need for exception handling
		if (d1[_sortOrder[count]] < d2[_sortOrder[count]])
		{
			return 1; // TRUE
		}
		else if (d1[_sortOrder[count]] > d2[_sortOrder[count]])
		{
			return 0; // FALSE
		}
	}	
	return 0; // which means all cells are the same
}

void SortData::pushOrder(int colNum)
{
	_sortOrder.push_back(colNum);
}

int main()
{
	// In the beginning, your program should prompt the message to ask for the content of the .csv file.
	int rows, cols;
	string fileName, fileContent;

	cout << "Please enter the file name: ";
	cin >> fileName;
	cout << "Please enter the number of rows and columns: ";
	cin >> rows >> cols;

	// Read a file into memory, no need to write in any files.	
	// Build a table with class Data and <vector>
	ifstream fin;
	fin.open(fileName); 

	vector<Data> table; // initialize table as a vector of Data (rows)	 
	
	// Putting fileContent into the table
	for(int rowsCount = 0; rowsCount < rows; rowsCount++) 
	{		
		// separating fileContent into "rows(#)" of strings	by '\n' or '\r'
		string rowsString;
		getline(fin, rowsString, '\r');
		Data tempRow(cols); // initialize a temporary row with "cols(#)" of columns
		stringstream cutIntoCells(rowsString); 
		for(int colsCount = 0; colsCount < cols; colsCount++) 
		{
			// separating rowsString into "cols(#)" of integer cells		 
			string cell;
			getline(cutIntoCells, cell, ',');
			if (cell.length() == 0) // if empty
			{
				tempRow[colsCount] = 1000; // set a value out of scope, i.e. empty
			}	
			else 
			{
				tempRow[colsCount] = stoi(cell); // convert string to integer
			}					 
		}
		table.push_back(tempRow); // vector usage
	}

	// Once the .csv file is properly read in, print the message (change the filename accordingly)
	fin.close();
	cout << "File \"" << fileName << "\" was read in successfully." << endl;

	// Reading inputs and identifying commands
	string command; 

	while(cin >> command)
	{				
		// cout << "The current command is:" << command << endl;
		// The command “PRINT” prints the entire table content in a tabular format.
		// Please use “setw(4)” and “right” for “cout” to control the output format.
		if (command == "PRINT")
		{
			for (int i = 0; i < rows; i++)
			{
				cout << right;
				for (int j = 0; j < cols; j++)
				{					
					if (table[i][j] == 1000) // set a value out of scope, i.e. empty
					{
						cout << setw(4) << " ";
					}
					else
					{
						cout << setw(4) << table[i][j];
					}					
				}
				cout << endl;
			}
		}

		// The command “ADD” adds a new row to the end of the table. 
		// The added data are provided as arguments to this command and are separated by space. 
		// For the column with intended null data, put a ‘-‘ symbol to represent it. 
		// Therefore, there must be exactly #columns arguments for this command.
		// Nothing will be printed for this command. Use “PRINT” command to check the result.
		else if (command == "ADD")
		{			
			string input;
			Data newRow(cols);
			for (int k = 0; k < cols; k++)
			{
				cin >> input;
				if (input == "-")
				{
					newRow[k] = 1000; // set a value out of scope, i.e. empty
					//cout << "newRow[k]: empty" << newRow[k] << endl;
				}
				else
				{
					newRow[k] = stoi(input); // convert string to integer
					//cout << "newRow[k]: integer" << newRow[k] << endl;
				}
			}
			table.push_back(newRow);
			rows++;
		}

		// The commands “SUM”, “AVE”, “MAX”, “MIN” and “COUNT” compute the summation, average, maximum, minimum, and distinct count of data in the specified column. 
		// Clearly, there will be only one argument (i.e. the column index) for these commands. 
		// Null cells are ignored (not treated as ‘0’) here.
		else if (command == "SUM")
		{
			int number;
			int sum = 0;
			cin >> number;

			for (int m = 0; m < rows; m++)
			{
				if (table[m][number] != 1000)
				{
					sum = sum + table[m][number];
				}					
			}

			cout << "The summation of data in column #" << number << " is " << sum << "." << endl;
		}

		else if (command == "AVE")
		{
			int number;
			int sum = 0;
			int average;
			cin >> number;

			for (int m = 0; m < rows; m++)
			{
				if (table[m][number] != 1000)
				{
					sum = sum + table[m][number];
				}				
			}

			average = sum / rows;

			cout << "The average of data in column #" << number << " is " << average << "." << endl;
		}

		else if (command == "MAX")
		{
			int number;
			int max = -100;
			cin >> number;

			for (int m = 0; m < rows; m++)
			{
				if (table[m][number] == 1000)
				{
					max = max;
				}
				else if (table[m][number] > max)
				{
					max = table[m][number];
				} 
			}

			cout << "The maximum of data in column #" << number << " is " << max << "." << endl;			
		}

		else if (command == "MIN")
		{
			int number;
			int min = 101;
			cin >> number;

			for (int m = 0; m < rows; m++)
			{
				if (table[m][number] < min)
				{
					min = table[m][number];
				} 
			}

			cout << "The minimum of data in column #" << number << " is " << min << "." << endl;	
		}

		else if (command == "COUNT")
		{
			int number;
			int count = 1;
			int tempCount = 1;
			cin >> number;

			for (int m = 0; m < rows; m++) // select one cell
			{
				for (int c = 0; c < m; c++) // compare the integer in the cell with all cells numbered smaller
				{
					if (table[c][number] != table[m][number]) // mark if the integer in the cells are different
					{
						tempCount++;
						//cout << tempCount << endl;
					}
				}

				// if every cell numbered smaller than the selected cell doesn't contain the same integer as the selected cell,
				// the selected cell is distinct
				if (tempCount == m ) 
				{
					count++;
				}
			}
			//cout << count << endl;

			cout << "The distinct count of data in column #" << number << " is " << count << "." << endl;		
		}

		// The command “SORT” sorts the data in ascending order with respected to the specified series of column indices 
		// (note: column #0 is the first column). 
		// Null cells are assumed to be greater than any number in this column.
		// In your program you should first create a functional object of struct SortData, 
		// and then push the sorting column indices to this object by the member function SortData::pushOrder(), 
		// according to the arguments in the “SORT” command. 
		// Finally, pass this functional object to the sort() algorithm and the data in the table will be sorted automatically.
		else if (command == "SORT")
		{
			int number;
			SortData temp;
			string content;
			getline(cin, content, '\n');
			stringstream cutSort;
			while (cutSort >> number)
			{
				temp.pushOrder(number);
			}
			sort(table.begin(), table.end(), temp);
		}
	}
	return 0;
}