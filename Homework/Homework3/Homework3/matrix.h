#ifndef MATRIX_H
#define MATRIX_H
#include <map>
#include <string>
#include "Node.h"
#include <list>
#include <vector>
using namespace std;

/*This class is used to preform operations on a specific matrix.
Each matrix needs its own Matrix Operations class associated with.
Need to wrap the operations into each matrix so each matrix doesnt need
to create its own version of this class but for now this works sufficiently*/

//NOTE: THIS CLASS ONLY WORKS WITH SQUARE MATRICIES//

class MatrixOps
{
private:
	int matrixSize;
	int **matrix;
public:
	MatrixOps(int);
	void initMatrix(int**);
	void printMatrix(int**);
	void populate(map<int, int>, string, int**);
	list<Node*> matrixToList(map<int, int>, int**, list<Node*>);
	int ** listToMatrix(map<int, int>, list<Node*>, int**);
	int getMatrixSize(){ return matrixSize; }
	
};
#endif