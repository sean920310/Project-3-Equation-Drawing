#pragma once
#include "MainHeader.h"
using namespace std;

typedef struct NumWithName
{
	string name;
	double num;

	NumWithName():name(""),num(0){};
	NumWithName(string name,double num):name(name),num(num) {};


}NumWithName;



class Parser
{
private:
	string input;
	map<string,double> vars;
public:
	Parser(string input);
	Parser();

	void setInput(string input);
	bool canUse(NumWithName var);	//�P�_�O�_���Ʀr�άO�w�s�b���ܼ�
	vector<int> findd(char in);
	vector<string> Postfix(string inp);
	int calculate(NumWithName& setVar,NumWithName& getVar);
};


