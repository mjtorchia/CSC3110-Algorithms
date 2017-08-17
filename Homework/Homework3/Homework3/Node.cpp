#include "Node.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int Node::DFScount = 1;
//Default Constructor
Node::Node()
{
	value = 0;
	visit = 0;
	next = NULL;
	size++;
}

//Overloaded constructor
Node::Node(int value)
{
	this->value = value;
	next = NULL;
	size++;
}
void Node::setValue(int value)
{
	this->value = value;
}
void Node::setVisit(int visit)
{
	this->visit = visit;
}

//Goes to the end of the Node and attaches another based on passed value
void Node::addNode(int value)
{
	Node *temp = this;
	while (temp->next != NULL){
		temp = temp->next;
	}
	temp->next = new Node(value);
	size++;
}

Node* Node::nextNode()
{
	Node* temp = this;
	if (temp->next != NULL)
	{
		temp = temp->next;
		return temp;
	}
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
	cout << endl;
}


//Gathers all of the values for the current Node and pushes them
//onto a list and then returns the list
list<int> Node::getNodeValues()
{
	list<int>tempV;
	Node *temp = this;
	tempV.push_front(temp->getValue());
	for (int i = 0; i < this->size; i++)
	{
		if (temp->next != NULL){
			temp = temp->next;
			tempV.push_front(temp->getValue());
		}
	}
	return tempV;
}
bool Node::searchList(Node* n,int num)
{
	Node* temp = this;
	if (this->getValue() == num)
	{
		return true;
	}
	else
		while (temp->next != NULL)
		{
			temp = temp->next;
			if (temp->getValue() == num)
			{
				return true;
			}
		}
	return false;
}