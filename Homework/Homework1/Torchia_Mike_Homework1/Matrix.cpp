#include "matrix.h"
#include <iostream>
#include <fstream>
#include <list>
using namespace std;

/*Constructor takes in the matrix size of the specific matrix its
associated with.*/
MatrixOps::MatrixOps(int size)
{
	this->matrixSize = size;
}


/*Sets all of the values of the matrix to zero.
So when we later fill in values the cells not worked on
will already be filled with zeros*/
void MatrixOps::initMatrix(int** matrix)
{	
	for (int i = 0; i < matrixSize; i++)
	{
		for (int j = 0; j < matrixSize; j++)
		{
			matrix[i][j] = 0;
		}
	}
}


//Simply prints matrix to the screen
void MatrixOps::printMatrix(int** matrix)
{
	for (int i = 0; i < matrixSize; i++)
	{
		for (int j = 0; j < matrixSize; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}


/*Takes in the dictionary we define in the main, alone with the filename
and the matrix to be worked on. Then it reads each character in file(edgelist.txt)
for then based on the int value it was mapped with in our dictionary it is
assigned to i or j. Because we know the format of the edgelist. This function
knows that there are only two characters per line, first being the i value of the matrix
and second being the j value. Based off that a 1 is placed in the correct cell in the matrix*/
void MatrixOps::populate(map<int, char> dict, string filename, int** matrix)
{
	ifstream input(filename);
	while (!input.eof())
	{
		int first = 0;
		int second = 0;
		char ch;
		input.get(ch);
		for (auto elem : dict)
		{
			if (elem.second == ch)
			{
				first = elem.first;
			}
		}
		input.ignore();
		input.get(ch);
		for (auto elem : dict)
		{
			if (elem.second == ch)
			{
				second = elem.first;
			}
		}
		matrix[first][second] = 1;
		input.ignore();
	}
}


/*Takes in the dictionary that is defined in the main, the populated matrix, and the list
that will be worked on. A temporary pointer varible of type Node is created. The function then
knows the from each i value (0-matrixSize) there is a letter associated with it based on the dictionary.
That first value will be the head of that node in the list. Once that is realized head is set to true
because we now have a head for that node. Then the function will go through that current row to see where
there are 1s (j++) whereever we find 1s we find what character is associated with that j value. From that
we can figure out the next character in that node. Once the whole row is read, that node is then pushed onto
the list that is passed, the i value is incremented (next row) and the process starts over untill all the rows
have been scanned and pushed onto the list. The function then returns the list.*/

//The explaination should make more once the program runs and you see the output
list<Node*> MatrixOps::matrixToList(map<int, char> dict, int** matrix, list<Node*> V)
{
	Node *temp=NULL;
	for (int i = 0; i < matrixSize; i++)
	{
		bool head = false;
		char value = ' ';
		for (int j = 0; j < matrixSize; j++)
		{
			for (auto elem : dict)
			{
				if (elem.first == i && head==false)
				{
					value = elem.second;
					temp = new Node(value);
					head = true;
				}
			}
			if (matrix[i][j] == 1 && head == true)
			{
				for (auto elem : dict)
				{
					if (elem.first == j)
					{
						value = elem.second;
						temp->addNode(value);
					}
				}
			}
		}
		V.push_front(temp);
		temp = NULL;
	}
	return V;
}


/*Takes the dictonary that is defined in main, the ajacency list, and the matrix to be worked on.
The matrix is first passed into the initMatrix function to set all of its values to 0. Two temp variables
are created. A char list to hold all the characters of the current node and a Node pointer varible to keep
track of the current node being examined. The int iSize and int jSize values of there because the lists continue
to change sizes so this is so the for loop is given a const number. The temp Node pointer is then assigned the
back value of the list thats passed. The back value is then popped from the list. The temp Node pointer then runs
a fucntion that gathers the values of that Node and then retuns them as a list which is assigned to the tempC list.
Then the function takes the first char value in the tempC list (which is the row) and finds the int value associated with
it based on the dictionary thats passed. Assigns it to iValue and then pops off the character from tempC. It then sets start
to true because we know we have the start of the row we are working on. From there the rest of the values from tempC are scanned
and the int values for each of them are found and assigned to jValue. So now that the program knows the iValue(current row) and it
gets a jValue(column) for each other char in tempC it can then go through and assign a 1 to each cell of the matrix that is needed 
to represent the ajacency list. You can think of it like this, the first value in each Node is the row that is to be worked on, and
the following values are the column. The row stays constant until all of the column have been acconted for then the program goes to
the next row.*/
int ** MatrixOps::listToMatrix(map<int, char>dict, list<Node*> V, int** matrix)
{
	initMatrix(matrix);
	list<char>tempC;
	Node *temp = NULL;
	int iSize = V.size();
	for (int i = 0; i < iSize; i++)
	{
		bool start = false;
		char value = ' ';
		int iValue;
		int jValue;
		temp = V.back();
		V.pop_back();
		tempC = temp->getNodeValues();
		int jSize = tempC.size();
		for (int j = 0; j < jSize; j++)
		{
			if (start == false)
			{
				value = tempC.back();
				tempC.pop_back();
				start = true;
				for (auto elem : dict)
				{
					if (elem.second == value )
					{
						iValue = elem.first;
					}
				}
			}
			else if (start == true)
			{
				value = tempC.back();
				tempC.pop_back();
				for (auto elem : dict)
				{
					if (elem.second == value)
					{
						jValue = elem.first;
					}
				}
				matrix[iValue][jValue] = 1;
			}
		}	
	}
	return matrix;
}

void MatrixOps::homework(int **matrix,int size)
{
	for (int i = 0; i < size - 2; i++)
	{
		for (int j = 1 + 1; j < size - 1; j++)
		{
			matrix[i][j] = 5;
			matrix[j][i] = 5;
		}
	}
}