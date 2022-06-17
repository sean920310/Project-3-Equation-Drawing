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

typedef struct Variable
{
	string name;
	string equation;
	double num;

	Variable() :name(""), equation(""),num(0) {};
	Variable(string name, string equation="", double num = 0) :name(name), equation(equation), num(num) {};

}Variable;

class Parser
{
private:
	string input;
	map<string,pair<string,double>> vars;
	vector<string> postInput;
public:
	Parser();

	void setInput(string input);

	//�P�_�O�_���Ʀr�άO�w�s�b���ܼ�
	bool canUse(Variable var);	

	//return 0: y�b���� 1:x�b���� 2:�������ƾǦ�
	int type();	
	vector<int> findd(char in);
	vector<string> Postfix(string inp);
	int setVariable();
	void tranVar();
	int calculate(Variable& setVar,Variable& getVar);
};


