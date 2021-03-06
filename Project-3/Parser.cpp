#include "Parser.h"


Parser::Parser()
{
	this->vars["x"].first = "x";
	this->vars["x"].second = 0;
	this->vars["y"].first = "y";
	this->vars["y"].second = 0;
}

void Parser::setInput(string input)
{
	string temp = "";

	for (const char& c : input)
	{
		if (c != ' ')
			temp = temp + c;
	}

	this->input = temp;

	while (this->input.find("sin") != string::npos)
	{
		auto i = this->input.find("sin");
		this->input.replace(i, 3, "@");
	}
	while (this->input.find("cos") != string::npos)
	{
		auto i = this->input.find("cos");
		this->input.replace(i, 3, "#");
	}
	while (this->input.find("tan") != string::npos)
	{
		auto i = this->input.find("tan");
		this->input.replace(i, 3, "$");
	}

	if (this->input.find("y") == string::npos && this->input.find("=") == string::npos)
	{
		this->input = "y=" + this->input;
	}

}

bool Parser::canUse(Variable var)
{
	if (var.name == "")							//璸衡筁挡狦
		return true;

	bool isDigit = true;
	for (auto c : var.name) {
		if ((c > '9' || c < '0') && c != '.' && c != '-' && c != '+') {
			isDigit = false;
			break;
		}
	}
	if (isDigit) {								//琌计临琌跑计
		return true;
	}
	else
	{
		return (this->vars.count(var.name));	//琩高跑计琌
	}
}

int Parser::type()
{
	if (input[0] == 'y' && input[1] == '=')
		return 0;
	else if (input[0] == 'x' && input[1] == '=')
		return 1;
	else
	{
		return 2;
	}
}

vector<int> Parser::findd(char in) {
	vector<int> out;
	out.resize(2);//0计1舦
	int time = 0;
	char opr[15] = { '(',')','=','=','+','-','*','/','~','~','^','^','@','#','$' };
	for (int i = 0; i < 15 + 1; i++) {


		if (i < 15) {
			if (in == opr[i]) {
				out.at(0) = i;
				out.at(1) = i / 2;
				break;
			}
		}
		else
		{
			out.at(0) = -1;
			out.at(1) = -1;
		}
		out.at(1) = i / 2;
	}
	if (out.at(0) == 14) {
		out.at(1) = 7;
	}
	return  out;

}

vector<string> Parser::Postfix(string inp) {
	vector<int> number;
	vector<int> lastnumber;
	vector<string> out;
	stack<int> stack;
	bool wronginput = false;
	bool isnegetive = false;
	string opr[15] = { "(",")","=","=", "+", "-", "*", "/","~","~","^","^","@","#","$" };
	string temp;

	lastnumber.resize(2); lastnumber.at(0) = -1; lastnumber.at(1) = -1;

	string in = inp;
	string plus;

	int index = 0;
	for (int i = 0; i < in.length(); i++) {

		if (index == 1 && in[i] != '-') {
			plus = plus + '-';
		}


		if (in[i] != '-') {
			plus = plus + in[i];
			index = 0;
		}
		else if (in[i] == '-' && index == 1)
		{
			plus = plus + '+';
			index = 0;
		}
		else if (in[i] == '-')
		{
			index++;
		}
	}

	if (index == 1) {
		plus = plus + '-';
	}
	in = plus;

	int buf = -1;
	int time = 0;


	for (int i = 0; i < in.length(); i++) {
		number = findd(in[i]);
		isnegetive = lastnumber.at(0) != -1 && lastnumber.at(0) != 1 && number.at(0) == 5;

		if (stack.size() != 0)buf = stack.top() / 2; else buf = -1;

		if (number.at(0) != -1 && temp.size() != 0) {
			out.push_back(temp);
			temp.clear();
		}

		if (stack.size() == 0)
		{
			buf = -1;
		}


		if (number.at(0) == 0) {
			stack.push(number.at(0));
			buf = -1;
		}
		else if ((i == 0 && number.at(0) == 5) || isnegetive)//-
		{
			//temp = temp + in[i];
			isnegetive = false;
			stack.push(8);
		}
		else if (number.at(0) == 1) {

			time = stack.size();
			for (int j = 0; j < time; j++) {
				wronginput = true;
				if (stack.top() == 0) {
					wronginput = false;

					stack.pop();
					if (stack.size() != 0)buf = stack.top() / 2; else buf = -1;
					break;
				}
				else
				{
					//cout << opr[stack.top()] << endl;
					out.push_back(opr[stack.top()]);
					stack.pop();
					if (stack.size() != 0)buf = stack.top() / 2; else buf = -1;
				}
			}
		}
		else if (number.at(0) == -1)
		{
			temp = temp + in[i];
		}
		else if (number.at(1) > buf)
		{
			stack.push(number.at(0));
			if (stack.size() != 0)buf = stack.top() / 2;
		}
		else if (number.at(1) <= buf)
		{
			time = stack.size();
			for (int k = 0; k < time; k++) {
				if (stack.size() != 0)buf = stack.top() / 2; else buf = -1;
				if (number.at(1) > buf) {
					break;
				}
				else if (number.at(1) <= buf)
				{
					out.push_back(opr[stack.top()]);
					stack.pop();

				}
			}
			stack.push(number.at(0));
			if (stack.size() != 0)buf = stack.top() / 2; else buf = -1;
		}
		lastnumber = number;
	}


	if (temp.size() != 0) {
		out.push_back(temp);
	}
	time = stack.size();
	for (int i = 0; i < time; i++)
	{
		//cout << "!!!!" << endl;
		if (stack.top() != 0) {
			out.push_back(opr[stack.top()]);
			stack.pop();
		}
	}


	return out;
}

int Parser::setVariable()
{
	string equation,varName;
	if (input.find("=") != string::npos)
	{
		equation = input.substr(input.find("=") + 1);
		varName = input.substr(0, input.find("=") );
	}
	else
		return -1;
	string tempEqu = equation;
	vector<string> post;
	for (const auto& n : vars)
	{
		post = Postfix(tempEqu);	//post: い锣戈
		for (const string& temp : post)
		{
			if (temp == varName)		//call
				return -1;
			if (!(temp == "+" || temp == "-" || temp == "*" || temp == "/" || temp == "^" || temp == "@" || temp == "#" || temp == "$" || temp == "(" || temp == ")" || temp == "~"))
			{
				if (canUse(Variable(temp)))
				{
					if (vars.count(temp))
					{
						tempEqu.replace(tempEqu.find(temp), temp.length(), '(' + vars[temp].first + ')');
					}
				}
				else
					return -1;
			}
		}
	}


	vars[varName].first = equation;
	input = equation;
	return 0;
}

void Parser::tranVar()
{
	for (const auto& n : vars)
	{
		postInput = Postfix(input);	//postInput: い锣戈
		for (auto& temp : postInput)
		{
			if (vars.count(temp))
			{
				input.replace(input.find(temp), temp.length(), '(' + vars[temp].first + ')');
			}
		}
	}
}

int Parser::calculate(Variable& setVar, Variable& getVar)
{
	this->vars[setVar.name].first = setVar.equation;
	this->vars[setVar.name].second = setVar.num;
	this->vars[getVar.name].first = getVar.equation;
	this->vars[getVar.name].second = getVar.num;
	for (int i=1;i<postInput.size();i++)
	{
		if (postInput[i] == getVar.name)		//call
			return -1;
	}
	vector<Variable> tempVars;
	//vector<string> postInput = Postfix(input);	//postInput: い锣戈
	/*cout << "postFix: ";
	for (int i = 0; i < postInput.size(); i++)
	{
		cout << postInput.at(i) << " ";
	}
	cout << endl;*/

	bool countNegative = false;	//计璽true
	for (int i = 0; i < postInput.size(); i++) {
		if (postInput[i] == "+") {						//猭
			if (tempVars.size() < 2)
				return -1;	//continue
			//throw "块岿粇ぶ计";
			Variable num1, num2, result;
			num2 = tempVars.back();
			tempVars.pop_back();
			num1 = tempVars.back();
			tempVars.pop_back();

			if (!canUse(num1))
				return -1; //тぃ跑计

			if (!canUse(num2))
				return -1; //тぃ跑计

			result.num = num1.num + num2.num;
			tempVars.push_back(result);

		}
		else if (postInput[i] == "-") {					//搭猭
			if (tempVars.size() < 2) {					//bug: 1---5
				if (tempVars.size() == 1) {
					if (!countNegative) {
						Variable num1 = tempVars.back(), result;
						tempVars.pop_back();

						if (!canUse(num1))
							return -1; //тぃ跑计

						result.num = -num1.num;
						tempVars.push_back(result);
					}
				}
				else {
					countNegative = !countNegative;
				}
			}
			else
			{
				Variable num1, num2, result;
				num2 = tempVars.back();
				tempVars.pop_back();
				num1 = tempVars.back();
				tempVars.pop_back();

				if (!canUse(num1))
					return -1; //тぃ跑计

				if (!canUse(num2))
					return -1; //тぃ跑计

				result.num = num1.num - num2.num;
				tempVars.push_back(result);
			}
		}
		else if (postInput[i] == "*") {					//猭
			if (tempVars.size() < 2)
				return -1;
			//throw "块岿粇ぶ计";
			Variable num1, num2, result;
			num2 = tempVars.back();
			tempVars.pop_back();
			num1 = tempVars.back();
			tempVars.pop_back();

			if (!canUse(num1))
				return -1; //тぃ跑计

			if (!canUse(num2))
				return -1; //тぃ跑计

			result.num = num1.num * num2.num;
			tempVars.push_back(result);
		}
		else if (postInput[i] == "/") {					//埃猭
			if (tempVars.size() < 2)
				return -1;
			//throw "块岿粇ぶ计";
			Variable num1, num2, result;
			num2 = tempVars.back();
			tempVars.pop_back();
			num1 = tempVars.back();
			tempVars.pop_back();

			if (!canUse(num1))
				return -1; //тぃ跑计

			if (!canUse(num2))
				return -1; //тぃ跑计

			if (num2.num == 0)
				return -1;
			//throw "砆埃计ぃ单0";
			result.num = num1.num / num2.num;
			tempVars.push_back(result);
		}
		else if (postInput[i] == "~") {					//璽腹
			if (tempVars.size() < 1)
				return -1;
			//throw "块岿粇ぶ计";
			Variable num1, result;
			num1 = tempVars.back();
			tempVars.pop_back();

			if (!canUse(num1))
				return -1; //тぃ跑计

			result.num = -num1.num;
			tempVars.push_back(result);
		}
		else if (postInput[i] == "^") {					//经Ω
			if (tempVars.size() < 2)
				return -1;
			//throw "块岿粇ぶ计";
			Variable num1, num2, result;
			num2 = tempVars.back();
			tempVars.pop_back();
			num1 = tempVars.back();
			tempVars.pop_back();

			if (!canUse(num1))
				return -1; //тぃ跑计

			if (!canUse(num2))
				return -1; //тぃ跑计

			if (isnan(pow(num1.num, num2.num)))
				return 1;
			//throw "NaN";
			result.num = pow(num1.num, num2.num);
			tempVars.push_back(result);
		}
		else if (postInput[i] == "@") {					//sin
			if (tempVars.size() < 1)
				return -1; //throw "块岿粇ぶ计";
			Variable num1 = tempVars.back(), result;
			tempVars.pop_back();

			if (!canUse(num1))
				return -1; //тぃ跑计

			result.num = sin(num1.num);
			tempVars.push_back(result);
		}
		else if (postInput[i] == "#") {					//cos
			if (tempVars.size() < 1)
				return -1; //throw "块岿粇ぶ计";
			Variable num1 = tempVars.back(), result;
			tempVars.pop_back();

			if (!canUse(num1))
				return -1; //тぃ跑计

			result.num = cos(num1.num);
			tempVars.push_back(result);
		}
		else if (postInput[i] == "$") {					//tan
			if (tempVars.size() < 1)
				return -1; //throw "块岿粇ぶ计";
			Variable num1 = tempVars.back(), result;
			tempVars.pop_back();

			if (!canUse(num1))
				return -1; //тぃ跑计

			if (isnan(tan(num1.num)))
				return -1;
			//throw "NaN";

			result.num = tan(num1.num);
			tempVars.push_back(result);

		}
		else if (postInput[i] == "=") {
			if (tempVars.size() < 2)					//assign
				return -1;
			//throw "块岿粇ぶ计";
			Variable num1, num2;
			num2 = tempVars.back();
			tempVars.pop_back();
			num1 = tempVars.back();
			tempVars.pop_back();

			if (!canUse(num2))
				return -1; //тぃ跑计

			this->vars[num1.name].second = num2.num;
			num1.num = num2.num;

			tempVars.push_back(num1);
		}
		else
		{
			bool isDigit = true;
			for (auto c : postInput[i]) {
				if ((c > '9' || c < '0') && c != '.' && c != '-' && c != '+') {
					isDigit = false;
					break;
				}
			}
			if (isDigit) {										//琌计临琌跑计
				stringstream ss;
				ss << postInput[i];
				double temp;
				ss >> temp;
				Variable tempNum(postInput[i], postInput[i],temp);
				tempVars.push_back(tempNum);					//メ既
			}
			else
			{
				bool findVar = false, negtive = false;
				if (postInput[i][0] == '-')
				{
					negtive = true;
					postInput[i] = postInput[i].substr(1);
				}
				else if (postInput[i][0] == '+')
					postInput[i] = postInput[i].substr(1);

				if (this->vars.count(postInput[i]))		//琩高跑计琌
				{
					Variable tempVar(postInput[i], this->vars[postInput[i]].first, this->vars[postInput[i]].second);
					if (negtive)
						tempVar.num *= -1;
					tempVars.push_back(tempVar);

				}
				else
				{
					Variable tempVar(postInput[i]);	//既 ぇ絋粄琌穝跑计
					tempVars.push_back(tempVar);
					//return 1;
					//throw "тぃ跑计";
				}
			}
		}
	}
	getVar.num = this->vars[getVar.name].second;
	if (tempVars.size() > 1)
		return -1;
	if (input.find(getVar.name) == string::npos)
		return 1;
	return 0;
}
