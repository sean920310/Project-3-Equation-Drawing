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

	//判斷是否為數字或是已存在的變數
	bool canUse(NumWithName var);	

	//return 0: y在左式 1:x在左式 2:左式為數學式
	int type();	
	vector<int> findd(char in);
	vector<string> Postfix(string inp);
	int calculate(NumWithName& setVar,NumWithName& getVar);
};


