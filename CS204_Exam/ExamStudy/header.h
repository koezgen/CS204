#ifndef _HEADER_H
#define _HEADER_H

#include <iostream>
#include <string>
using namespace std;

class linkedArray
{
	friend class linkedArrayIterator;

	private:

		struct Node
		{
			int** dynarray = NULL;
			string name;
			Node(string name, int** matrix = NULL)
				:name(name), dynarray(matrix)
			{}
		};

		Node* kalender_cavus;

	public:
		linkedArray();
		linkedArray(Node* node);
		linkedArray(int** head);
		linkedArray(string newname);
		~linkedArray();
		void setArray(int size, int size2);
		linkedArray(const linkedArray& array);
		int** clonedArray();
		int* operator[](int index);
		const Node*& operator=(Node* node);
		Node* operator+(Node* rhs);
		void ChangeName(string newname);
		string& NameArray() const;
};

class linkedArrayIterator
{
	private:
		const linkedArray& copy;
		int** currRow;
		int* currColumn;
	public:
		void copier(const linkedArray& tobecopied);
		bool More() const;
		void Iterate() const;
		int** beginning() const;
};

#endif