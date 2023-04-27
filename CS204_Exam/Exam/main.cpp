#include <stdlib.h>
#include <malloc.h>
#include <iostream>
#include <vector>
#include <iomanip>
#include <cassert>
#include <string>
using namespace std;

#define INTEGER int

#ifndef NDEBUG
	
#endif

INTEGER main()
{
	int* ok = (int*) calloc(5, sizeof(int));

	//free(ok);

	_CrtDumpMemoryLeaks();
}