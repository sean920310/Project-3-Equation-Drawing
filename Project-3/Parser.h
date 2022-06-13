#pragma once
#include "MainHeader.h"
using namespace std;

typedef struct
{
	string name;
	double num;

}NumWithName;



class Parser
{
private:
	string input;
public:
	Parser(string input);

	vector<int> findd(char in);
	vector<string> Postfix(string inp);
	int calculate(vector<NumWithName>& vars, vector<double>& numbers);
};


