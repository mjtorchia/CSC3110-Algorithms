#include <fstream>
#include <iostream>
#include <map>
#include <list>
#include <string>
#include "matrix.h"
#include "Node.h"
using namespace std;

//Function prototypes
map<int, char>mapFile(string filename, map<int, char>dict);
int getMapSize(map<int, char> dict);
void printList(list<Node*> L);
bool boolhomework(int ** matrix,int size);


int main(int argc, char *argv[])
{
	ifstream input(argv[1]);		//File is passed from argv
	map<int, char> dict;			//Dictionary that is used to map ints to chars
	dict=mapFile(argv[1],dict);		//Function that parses the file and fills dictionary	
	int matrixSize = getMapSize(dict);	//Based on the dictionary size we can get the size of the matrix
	list<Node*> ajList;				//List later to be used to convert a matrix to a list


	/////////////////////////////////////////////
	//dynamic create 2d array based on dict size
	//found @ http://stackoverflow.com/questions/936687/how-do-i-declare-a-2d-array-in-c-using-new
	int** matrix = new int*[matrixSize];
	for (int i = 0; i < matrixSize; ++i)
		matrix[i] = new int[matrixSize];
	////////////////////////////////////////////



	MatrixOps *ajMatrix = new MatrixOps(matrixSize);		//A matrix operation object is created for based on the square matrix we get from the file
	ajMatrix->initMatrix(matrix);							//Preform the init operation on our dynamic 2d matrix
	ajMatrix->printMatrix(matrix);
	ajMatrix->populate(dict, argv[1],matrix);				//Based on the edge list and the dictionary associated, populate the matrix
	ajMatrix->printMatrix(matrix);							//Print the populated matrix
	ajList=ajMatrix->matrixToList(dict,matrix,ajList);		//Convert the matrix into a list based on the dictionary
	matrix = ajMatrix->listToMatrix(dict, ajList, matrix);	//Convert the list into a matrix based on the dictionary
	printList(ajList);										//Print the list
	ajMatrix->printMatrix(matrix);							//Use matrix operations object to print the matrix
	


	cout << endl;


	system("PAUSE");
	return 0;
}


/*Creates the dictionary based on the edge list passed. Creates a list of chars
then reads each letter from the file into the list. Sorts the list and then inserts
a pair<int, char> into the list (skipping duplicates) using the char from the sorted list
and an interator that I defined to keep try of the number of chars*/
map<int, char>mapFile(string filename, map<int, char>dict)
{
	list<char>alpha;
	char last = ' ';
	int inter = 0;
	ifstream input(filename);
	char ch;
	while (input)
	{
		input.get(ch);
		if (!isspace(ch) && ch != '\n'){
			alpha.push_back(ch);
		}
	}
	alpha.sort();
	while (!alpha.empty()){
		if (last != alpha.front()){
			last = alpha.front();
			dict.insert(std::pair<int, char>(inter, last));
			alpha.pop_front();
			inter++;
		}
		else
			alpha.pop_front();
	}
	return dict;
}


//Helper function to get the size of the dictionary
int getMapSize(map<int, char> dict)
{
	return (const int)dict.size();
}


//Used to print the ajacency list
void printList(list<Node*> L)
{
	int forSize = L.size();
	for (int i = 0; i <forSize; i++)
	{
		Node *temp = L.back();
		temp->printList();
		L.pop_back();
		cout << endl;
	}
}

bool boolhomework(int ** matrix,int size)
{
	for (int i = 0; i < size - 2; i++)
	{
		for (int j = 1 + 1; j < size - 1; j++)
		{
			if (matrix[i][j] != matrix[j][i])
			{
				cout << "fasle" << endl;
				return false;
			}
		}
	}
}