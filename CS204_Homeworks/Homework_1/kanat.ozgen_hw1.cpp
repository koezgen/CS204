#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

// This file was written in Visual Studio 2022 by 
// Kanat Ozgen

// This function fits the shape into the matrix present in the text file.
void shape_finder(vector<vector<char>>(&shape), vector<vector<char>>(&matrix))
{
	bool bigness_flag = false;
	int star_count = 0;
	string coord_string = "";
	int placement_count = 0;
	int placement = 0;

	// This counts the amount of stars in the shape.
	for (int i = 0; i < shape.size(); i++)
	{
		for (int j = 0; j < shape[i].size(); j++)
		{
			if (shape[i][j] == '*')
			{
				star_count++;
			}
		}
	}

	// this checks for the size of the shape matrix. If it is bigger, the program should return
	// the default "not found" value. Otherwise, an exception would raise.
	if ((shape.size() > matrix.size()) || (shape[0].size() > matrix[0].size()))
	{
		bigness_flag = true;
	}

	// Here, the matrix is traversed by a matrix. If the pattern fits,
	// the coordinates gets appended to a string. 
	if (bigness_flag == false)
	{
		for (int i = 0; i <= matrix.size() - shape.size(); i++)
		{
			for (int j = 0; j <= matrix[i].size() - shape[0].size(); j++)
			{
				for (int k = 0; k < shape.size(); k++)
				{
					for (int l = 0; l < shape[k].size(); l++)
					{
						if ((matrix[i + k][j + l] == '-') && (shape[k][l] == '*'))
						{
							if (coord_string == "")
							{
								coord_string = coord_string + "(" + to_string(i + k) + "," + to_string(j + l) + ")";
								placement_count++;

								if (star_count == placement_count)
								{
									placement++;
									cout << "Placement number " << placement << ":" << endl;
									cout << coord_string << endl;
									coord_string = "";
								}
							}

							else
							{
								coord_string = coord_string + " (" + to_string(i + k) + "," + to_string(j + l) + ")";
								placement_count++;

								if (star_count == placement_count)
								{
									placement++;
									cout << "Placement number " << placement << ":" << endl;
									cout << coord_string << endl;
									coord_string = "";
								}
							}
						}
					}
				}

				coord_string = "";
				placement_count = 0;

			}
		}

		if (placement == 0)
		{
			cout << "No placements found." << endl;
		}
	}

	else
	{
		cout << "No placements found." << endl;
	}
}

// This function fits the shape into an arbitrary matrix of characters. This is done via string slicing and indexing.
void input_query_parser(string& input, vector<vector<char>>(&shape))
{
	// This buffer gets reset every iteration
	vector<char> buf;

	// The row size must begin by 1, since it is assumed that the first row is never empty.
	int rowsize = 1;

	// Clears out the matrix before appending items into it.
	shape.clear();

	int slashIndex = 0;

	for (int i = 0; i < input.length(); i++)
	{
		if (input.at(i) == '/')
		{
			rowsize++;
		}
	}

	// this will never overflow, because the j begins by 1.
	for (int j = 1; j <= rowsize; j++)
	{
		if (rowsize == 1)
		{
			for (int i = 1; i < input.length(); i = i + 2)
			{
				if (input[i] == 's')
				{
					// minus 48 to make up for the character integer conversion.
					for (int k = int(input[i - 1]) - 48; k > 0; k--)
					{
						buf.push_back('*');
					}
				}

				else
				{
					for (int k = int(input[i - 1]) - 48; k > 0; k--)
					{
						buf.push_back(' ');
					}
				}
			}

			shape.push_back(buf);
			buf.clear();

		}

		else
		{
			// begins from the last slash found in the string search. 
			for (int i = 1; i < input.substr(slashIndex, input.substr(slashIndex).find('/')).length(); i = i + 2)
			{
				if (input.substr(slashIndex, input.substr(slashIndex).find('/'))[i] == 's')
				{
					for (int k = int(input.substr(slashIndex, input.substr(slashIndex).find('/'))[i - 1]) - 48; k > 0; k--)
					{
						buf.push_back('*');
					}
				}

				// no other case is present
				else
				{
					for (int k = int(input.substr(slashIndex, input.substr(slashIndex).find('/'))[i - 1]) - 48; k > 0; k--)
					{
						buf.push_back(' ');
					}
				}
			}

			shape.push_back(buf);
			buf.clear();
			slashIndex = slashIndex + input.substr(slashIndex).find('/') + 1;
		}

	}
}

// Main function handles the data structures such as matrices, textfiles etc. Parsing and shape fitting is done in a separate function.
int main()
{
	vector<vector<char>> Matrix;
	vector<char> buf;

	vector<vector<char>> Shape;

	string inputFile;
	ifstream input;
	string query;
	string line;
	int placement = 0;
	int column_counter = 0;
	int row_counter = 0;
	bool flag_of_authenticity = true;

	cout << "Please enter the file name: ";
	cin >> inputFile;
	input.open(inputFile);

	while (input.fail())
	{
		cout << endl << "Could not open the file. Please enter a valid file name: ";
		cin >> inputFile;
		input.open(inputFile);
	}

	while (getline(input, line))
	{
		if (column_counter == 0)
		{
			column_counter = line.length();

			for (int i = 0; i < line.length(); i++)
			{
				if ((line[i] != '#') && (line[i] != '-'))
				{
					flag_of_authenticity = false;
				}
			}

			if (flag_of_authenticity)
			{

				for (int i = 0; i < line.length(); i++)
				{
					buf.push_back(line[i]);
				}

				Matrix.push_back(buf);
			}
		}

		else if (column_counter == line.length())
		{
			for (int i = 0; i < line.length(); i++)
			{
				if ((line[i] != '#') && (line[i] != '-'))
				{
					flag_of_authenticity = false;
				}
			}

			if (flag_of_authenticity)
			{
				buf.clear();

				for (int i = 0; i < line.length(); i++)
				{
					buf.push_back(line[i]);
				}

				Matrix.push_back(buf);

			}

		}

		else
		{
			flag_of_authenticity = false;
		}
	}


	if (flag_of_authenticity)
	{
		// printout of the matrix file
		cout << endl << "The matrix file contains:" << endl;

		for (int i = 0; i < Matrix.size(); i++)
		{
			for (int j = 0; j < Matrix[i].size(); j++)
			{
				cout << Matrix[i][j];
			}

			cout << endl;
		}

		// This loop iterates up until the point a "quit" entry is sent to the compiler from the cmd prompt.
		while (query != "Quit")
		{
			cout << "Enter the string query for a shape, or \"Quit\" to terminate the program:" << endl;
			cin >> query;

			if (query != "Quit")
			{
				input_query_parser(query, Shape);
				shape_finder(Shape, Matrix);
			}
		}

		return 0;
	}

	else
	{
		cout << endl << "Erroneous file content. Program terminates." << endl;
		return 0;
	}
}