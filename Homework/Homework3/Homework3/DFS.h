#ifndef DFS_H
#define DFS_H
#include <list>
#include "Node.h"
class DFSclass
{
private:
	int* order;
	int* popOrder;
public:
	DFSclass(){};
	int *DFS(list<Node*>);
	void dfs(int, list<Node*>, list<int>, int *);
	int *DFS(list<Node*>, int[]);
	void traverseOrder();

};

#endif