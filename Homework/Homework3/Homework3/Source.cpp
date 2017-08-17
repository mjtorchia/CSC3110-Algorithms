#include <fstream>
#include <iostream>
#include <map>
#include <list>
#include "matrix.h"
#include "Node.h"
#include <vector>
#include <algorithm>
using namespace std;

//Global Vars
int traverse[9] = {4,2,3,0,1};
vector<int> popOrder;
vector<int>click;
int matrixSize;

//Function prototypes
map<int, int>mapFile(string filename, map<int, int>dict);
int getMapSize(map<int, int> dict);
void printList(list<Node*> L);
int *DFS(list<Node*>L);
int *DFS(list<Node*>L, int traverse[]);
void dfs(int value, list<Node*>L, list<int> X, int* order);
void printDFSorder(int* order, vector<int>popOrder);
void getClicks(int **matrix, int clicksize);
vector< vector<int> > getAllSubsets(vector<int> set);




int main(int argc, char *argv[])
{
	ifstream input(argv[1]);		//File is passed from argv
	map<int, int> dict;			//Dictionary that is used to map ints to chars
	dict = mapFile(argv[1], dict);		//Function that parses the file and fills dictionary	
	matrixSize = getMapSize(dict);	//Based on the dictionary size we can get the size of the matrix
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
	ajMatrix->populate(dict, argv[1], matrix);				//Based on the edge list and the dictionary associated, populate the matrix
	ajMatrix->printMatrix(matrix);							//Print the populated matrix
	ajList = ajMatrix->matrixToList(dict, matrix, ajList);		//Convert the matrix into a list based on the dictionary
	matrix = ajMatrix->listToMatrix(dict, ajList, matrix);	//Convert the list into a matrix based on the dictionary
	printList(ajList);										//Print the list
	ajMatrix->printMatrix(matrix);							//Use matrix operations object to print the matrix
	
	//int *order=DFS(ajList,traverse);    //Perform DFS on the list based on the traverse order
	int *order = DFS(ajList);
	//cout << endl;
	printDFSorder(order, popOrder);		//Output the order each vertex was visited and the order it was popped off the stack
	getClicks(matrix,3);	

	system("PAUSE");
	return 0;
}


/*Creates the dictionary based on the edge list passed. Creates a list of chars
then reads each letter from the file into the list. Sorts the list and then inserts
a pair<int, char> into the list (skipping duplicates) using the char from the sorted list
and an interator that I defined to keep try of the number of chars*/
map<int, int>mapFile(string filename, map<int, int>dict)
{
	list<int>alpha;
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
			dict.insert(std::pair<int, int>(inter, last));
			alpha.pop_front();
			inter++;
		}
		else
			alpha.pop_front();
	}
	return dict;
}
//Helper function to get the size of the dictionary
int getMapSize(map<int, int> dict)
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
int *DFS(list<Node*>L)
{
	int *order = new int[L.size()];
	for (int i = 0; i < L.size(); i++)
	{
		order[i] = i;
	}
		

	for (auto const& i : L)		//https://stackoverflow.com/questions/22269435/how-to-iterate-through-a-list-of-objects-in-c
	{

		if (i->getVisit()==0)
		{
			int value = i->getValue();
			i->setVisit(L.front()->getDFScount());
			list<int> temp = i->getNodeValues();
			temp.reverse();
			order[L.front()->getDFScount()-1] = value;	//array to keep track of traverse order after dfs
			dfs(value,L,temp,order);
			popOrder.push_back(value);	//once a deadend is found at a vertex. place that in the poporder vector
		}
		
	}

	int a = 0;
	return order;
}
void dfs(int value, list<Node*>L, list<int>X,int *order)
{
	
	L.front()->incDFScount();
	for (auto const&i : X)
	{
		for (auto const&j : L)
		{
			if (j->getValue() == i)
			{
				
			 if (j->getVisit() == 0)
			{
				value = j->getValue();
				j->setVisit(L.front()->getDFScount());
				list<int> temp = j->getNodeValues();
				temp.reverse();
				order[L.front()->getDFScount() - 1] = value;
				dfs(value, L, temp, order);
				popOrder.push_back(value);
			}
			}
		}
	}
}
/*void dfs(int value, list<Node*>L, list<int>X, int *order, int start)
{
	L.front()->incDFScount();
	for (auto const&i : X)
	{
		for (auto const&j : L)
		{
			if (j->getValue() == i)
			{
				
				 if (j->getVisit() == 0)
				{
					value = j->getValue();
					j->setVisit(L.front()->getDFScount());
					list<int> temp = j->getNodeValues();
					temp.reverse();
					order[L.front()->getDFScount() - 1] = value;
					dfs(value, L, temp, order);
					popOrder.push_back(value);
				}
			}
		}
	}
}*/
int *DFS(list<Node*>L, int traverse[])		//Function called if the traverse array is provided
{
	int count = 0;
	int *order = new int[L.size()];
	for (int i = 0; i < L.size(); i++)
	{
		order[i] = i;
	}
	for (int j = 0; j < sizeof(traverse); j++)		//https://stackoverflow.com/questions/22269435/how-to-iterate-through-a-list-of-objects-in-c
	{
		for (auto const& i : L)
		{
			if (i->getValue() == traverse[j])
			{
				if (i->getVisit() == 0)
				{
					int value = i->getValue();
					i->setVisit(L.front()->getDFScount());
					list<int> temp = i->getNodeValues();
					temp.reverse();
					order[L.front()->getDFScount() - 1] = value; //array to keep track of traverse order after dfs
					dfs(value, L, temp, order);
					popOrder.push_back(value);    //once a deadend is found at a vertex. place that in the poporder vector
				}
			}
		}
	
	}

	return order;
}
void printDFSorder(int* order, vector<int>popOrder)
{
	cout << "The List is traversed in the following order: ";
	for (int i = 0; i < popOrder.size(); i++)
	{
		cout << order[i] << " ";
	}
	cout << endl;
	cout << "The values are popped in the following order: ";
	for (auto const& i : popOrder)
	{
		cout << i << " ";
	}
	cout << endl;
}



//TODO
void getClicks(int **matrix, int clicksize)
{
	vector<int>set1;
	vector<int>set2;
	vector<int>click;
	for (int i = 0; i < matrixSize - 2; i++) //top pointer
	{
		set1.clear();
		set2.clear();
		click.clear();
		int j = i + 1;
			for (int k = 0; k < matrixSize; k++)
			{
				if (matrix[i][k] == 1)
				{
					set1.push_back(k);
				}
				if (matrix[j][k] == 1)
				{
					set2.push_back(k);
				}
			}
			set1.push_back(i);
			set2.push_back(j);
			sort(set1.begin(), set1.end());
			sort(set2.begin(), set2.end());
			//vector<int>::iterator p;		http://www.codecogs.com/library/computing/stl/algorithms/set/set_union.php
			set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), back_inserter(click));
					
			vector<vector<int>> test;
			vector<int>temp1;
			vector<vector<int>>temp2;
			test = getAllSubsets(click);
			sort(test.begin(), test.end());
			for (auto &i : test)
			{
				for (auto &k : i)
				{
					//k size=i.end - i.begin
					if (distance(i.begin(), i.end()) > 2){
						cout << k;
						temp1.push_back(k);
					}
					/*if (find(temp2.begin(), temp2.end(), temp1) == temp2.end())
					{
						temp2.push_back(temp1);
					}
					temp1.clear();*/
					
			
				}
				cout << endl;
			}
		
		}
	
	}
vector< vector<int> > getAllSubsets(vector<int> set)	//https://stackoverflow.com/questions/728972/finding-all-the-subsets-of-a-set
{
	vector< vector<int> > subset;
	vector<int> empty;
	subset.push_back(empty);

	for (int i = 0; i < set.size(); i++)
	{
		vector< vector<int> > subsetTemp = subset;

		for (int j = 0; j < subsetTemp.size(); j++)
			subsetTemp[j].push_back(set[i]);

		for (int j = 0; j < subsetTemp.size(); j++)
			subset.push_back(subsetTemp[j]);
	}
	return subset;
}

