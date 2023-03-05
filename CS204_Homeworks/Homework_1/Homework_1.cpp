#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

bool is_file_matrix(ifstream& inputf)
{
	int column_counter = 0;
}

// this should be a recursive function
void input_query_handler(string& query)
{

}

void matrix_constructor(vector<vector<char>>(&dumbo), ifstream& inputf)
{

}

int main()
{
	vector<vector<char>> Matrix;
	ifstream input;
	string inputFile;
	string query;

	cout << "Please enter the file name:";
	cin >> inputFile;
	input.open(inputFile);

	while (input.fail())
	{
		cout << "Incorrect File";
		cin >> inputFile;
		input.open(inputFile);
	}

	if (is_file_matrix(input))
	{
		matrix_constructor(Matrix, input);

		cout << "The matrix file contains:" << endl;

		for (int i = 0; i < Matrix.size(); i++)
		{
			for (int j = 0; j < Matrix[i].size(); j++)
			{
				cout << Matrix[i][j];
			}

			cout << endl;
		}

		cout << "Enter the string query for a shape or \"Quit\" to terminate the program:";
		cin >> query;

		while (query != "Quit")
		{

		}
	}
}