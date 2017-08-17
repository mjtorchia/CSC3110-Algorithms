#include "Node.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;
//Default Constructor
Node::Node()
{
	value = ' ';
	next = NULL;
	size++;
}

//Overloaded constructor
Node::Node(char value)
{
	this->value = value;
	next = NULL;
	size++;
}

//Goes to the end of the Node and attaches another based on passed value
void Node::addNode(char value)
{
	Node *temp = this;
	while (temp->next != NULL){
		temp = temp->next;
	}
	temp->next = new Node(value);
	size++;
}


void Node::printList()
{
	int nodeNum = size - (size - 1);
	Node *temp = this;
	cout << temp->value;
	nodeNum++;
	while (temp->next != NULL){
		temp = temp->next;
		cout << "->";
		cout << temp->value;
		nodeNum++;
	}
}


//Gathers all of the values for the current Node and pushes them
//onto a list and then returns the list
list<char> Node::getNodeValues()
{
	list<char>tempV;
	Node *temp = this;
	tempV.push_front(temp->value);
	for (int i = 0; i < this->size; i++)
	{
		if (temp->next != NULL){
			temp = temp->next;
			tempV.push_front(temp->value);
		}
	}
	return tempV;
}