#include "header.h"

linkedArray::linkedArray()
{
	kalender_cavus = new Node("default_name", NULL);
}

linkedArray::linkedArray(Node* node)
{
	kalender_cavus = node;
}

linkedArray::linkedArray(string name)
{
	kalender_cavus = new Node(name, NULL);
}

linkedArray::linkedArray(int** head)
{
	
}

void linkedArray::setArray(int size, int size2)
{
	kalender_cavus->dynarray = new int* [size];
	
	while (kalender_cavus->dynarray++ != NULL)
	{
		kalender_cavus->dynarray++ = new int[];
	}
}