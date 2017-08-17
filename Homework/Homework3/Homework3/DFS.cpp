#include "DFS.h"
#include <iostream>
using namespace std;

int *DFSclass::DFS(list<Node*>L)
{
	
	for (int i = 0; i < L.size(); i++)
	{
		this->order[i] = i;
	}


	for (auto const& i : L)		//https://stackoverflow.com/questions/22269435/how-to-iterate-through-a-list-of-objects-in-c
	{

		if (i->getVisit() == 0)
		{
			int value = i->getValue();
			i->setVisit(L.front()->getDFScount());
			list<int> temp = i->getNodeValues();
			temp.reverse();
			this->order[L.front()->getDFScount() - 1] = value;
			dfs(value, L, temp, this->order);
		}
	}

	int a = 0;
	return this->order;
}

int *DFSclass::DFS(list<Node*>L, int traverse[])
{
	int count = 0;
	for (int i = 0; i < L.size(); i++)
	{
		this->order[i] = i;
	}
	for (int j = 0; j < sizeof(traverse); j++)		//https://stackoverflow.com/questions/22269435/how-to-iterate-through-a-list-of-objects-in-c
	{
		for (auto const& i : L)
		{
			if (i->getValue() == traverse[j])
			{
				if (i->getVisit() == 0)
				{
					int forSize = i->getSize();
					int value = i->getValue();
					i->setVisit(L.front()->getDFScount());
					list<int> temp = i->getNodeValues();
					temp.reverse();
					this->order[L.front()->getDFScount() - 1] = value;
					dfs(value, L, temp, this->order);
				}
			}
		}
	}

	int a = 0;
	return this->order;
}

void DFSclass::dfs(int value, list<Node*>L, list<int>X, int *order)
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
					this->order[L.front()->getDFScount() - 1] = value;
					dfs(value, L, temp, this->order);
				}
			}
		}
	}

}

void DFSclass::traverseOrder()
{
	
	cout << "The List is traversed in the following order: ";
	for (int i = 0; i < sizeof(this->order); i++)
	{
		cout << this->order[i] << " ";
	}
}