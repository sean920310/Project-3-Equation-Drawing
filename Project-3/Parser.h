#pragma once
#include "MainHeader.h"
using namespace std;

typedef struct NumWithName
{
	string name;
	double num;

	NumWithName() {};
	NumWithName(string name,double num):name(name),num(num) {};


}NumWithName;



class Parser
{
private:
	string input;
	vector<NumWithName> vars;
public:
	Parser(string input);

	vector<int> findd(char in);
	vector<string> Postfix(string inp);
	int calculate(vector<NumWithName>& vars, vector<double>& numbers);
};


