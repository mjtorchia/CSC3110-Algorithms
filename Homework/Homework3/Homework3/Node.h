#ifndef NODE_H
#define NODE_H
#include <list>
#include <map>
#include <vector>
using namespace std;

/*Imported this code from another project*/

class Node
{
private:
	int value;
	int visit;
	Node *next;
	int size;
	static int DFScount;
public:
	Node();
	Node(int);
	void addNode(int); //add a node at the end of the list
	void printList(); //prints list
	Node* nextNode();
	int getValue(){ return value; }
	int getVisit(){ return visit; }
	int getSize(){ return size; }
	int getDFScount(){ return DFScount; }
	void setValue(int);
	void setVisit(int);
	void incDFScount(){ DFScount++; }
	list<int> getNodeValues();
	bool searchList(Node*,int);
};
#endif