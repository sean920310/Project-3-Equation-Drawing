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

	//�P�_�O�_���Ʀr�άO�w�s�b���ܼ�
	bool canUse(NumWithName var);	

	//return 0: y�b���� 1:x�b���� 2:�������ƾǦ�
	int type();	
	vector<int> findd(char in);
	vector<string> Postfix(string inp);
	int calculate(NumWithName& setVar,NumWithName& getVar);
};


