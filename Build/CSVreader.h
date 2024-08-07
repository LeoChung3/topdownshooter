#pragma once
#include "Initialise.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <string> 
using namespace std;

class CSVreader
{
private:
	fstream fin;
	std::vector<string> row;
	string line, word, temp;

	fstream fin2;
	std::vector<string> row2;
	string line2, word2, temp2;

public:
	void readfile(string location);
	int readfile2(string location);
};