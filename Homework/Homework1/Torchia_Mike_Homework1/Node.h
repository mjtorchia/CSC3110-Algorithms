#ifndef NODE_H
#define NODE_H
#include <list>
using namespace std;

/*Imported this code from another project*/

class Node
{
private:
	char value;
	Node *next;
	int size;
public:
	Node();
	Node(char);
	void addNode(char); //add a node at the end of the list
	void printList(); //prints list
	list<char> getNodeValues();
};
#endif