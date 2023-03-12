//macros are like inline functions

//please do not forget #define asdasd removes the previous definitions. 

// good for debugging

// also know <cassert>



// POINTERS

// data is represented in bits, which are voltage values

// hexadecimal numbers, you know this

// word size 32 bit 64 bit etc

/*
char ch = 'A';
char* p;
p = &ch;
*/

#include <iostream>
using namespace std;

int main()
{
	char c = 'a';
	char* p;
	p = &c;

	cout << p;

	int* pa = new int[100];
	(*pa++);
	
	cout << (*pa);

	return 0;
}