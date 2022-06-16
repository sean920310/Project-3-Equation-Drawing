#include "Parser.h"


Parser::Parser(string input)
{
	this->input = input;

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

Parser::Parser()
{
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

bool Parser::canUse(NumWithName var)
{
	if (var.name == "")							//�p��L�᪺���G
		return true;

	bool isDigit = true;
	for (auto c : var.name) {
		if ((c > '9' || c < '0') && c != '.' && c != '-' && c != '+') {
			isDigit = false;
			break;
		}
	}
	if (isDigit) {								//�O�Ʀr�٬O�ܼ�
		return true;
	}
	else
	{
		return (this->vars.count(var.name));	//�d���ܼƬO�_�w�s�b
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
	out.resize(2);//0�Ʀr1�v��
	int time = 0;
	char opr[15] = { '(',')','=','=','+','-','*','/','^','^','!','!','@','#','$' };
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
	string opr[15] = { "(",")","=","=", "+", "-", "*", "/","^","^","!","!","@","#","$" };
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
			temp = temp + in[i];
			isnegetive = false;
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

int Parser::calculate(NumWithName& setVar, NumWithName& getVar)
{
	this->vars[setVar.name] = setVar.num;
	this->vars[getVar.name] = getVar.num;
	vector<NumWithName> tempVars;
	vector<string> postInput = Postfix(input);	//postInput: �������ǫ᪺���
	/*cout << "postFix: ";
	for (int i = 0; i < postInput.size(); i++)
	{
		cout << postInput.at(i) << " ";
	}
	cout << endl;*/
	bool countNegative = false;	//�_�ƭӭt��true
	for (int i = 0; i < postInput.size(); i++) {
		if (postInput[i] == "+") {						//�[�k
			if (tempVars.size() < 2)
				return -1;	//continue
			//throw "��J���~�A�ʤּƭ�";
			NumWithName num1, num2, result;
			num2 = tempVars.back();
			tempVars.pop_back();
			num1 = tempVars.back();
			tempVars.pop_back();

			if (!canUse(num1))
				return -1; //�䤣���ܼ�

			if (!canUse(num2))
				return -1; //�䤣���ܼ�

			result.num = num1.num + num2.num;
			tempVars.push_back(result);

		}
		else if (postInput[i] == "-") {					//��k
			if (tempVars.size() < 2) {					//bug: 1---5
				if (tempVars.size() == 1) {
					if (!countNegative) {
						NumWithName num1 = tempVars.back(), result;
						tempVars.pop_back();

						if (!canUse(num1))
							return -1; //�䤣���ܼ�

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
				NumWithName num1, num2, result;
				num2 = tempVars.back();
				tempVars.pop_back();
				num1 = tempVars.back();
				tempVars.pop_back();

				if (!canUse(num1))
					return -1; //�䤣���ܼ�

				if (!canUse(num2))
					return -1; //�䤣���ܼ�

				result.num = num1.num - num2.num;
				tempVars.push_back(result);
			}
		}
		else if (postInput[i] == "*") {					//���k
			if (tempVars.size() < 2)
				return -1;
			//throw "��J���~�A�ʤּƭ�";
			NumWithName num1, num2, result;
			num2 = tempVars.back();
			tempVars.pop_back();
			num1 = tempVars.back();
			tempVars.pop_back();

			if (!canUse(num1))
				return -1; //�䤣���ܼ�

			if (!canUse(num2))
				return -1; //�䤣���ܼ�

			result.num = num1.num * num2.num;
			tempVars.push_back(result);
		}
		else if (postInput[i] == "/") {					//���k
			if (tempVars.size() < 2)
				return -1;
			//throw "��J���~�A�ʤּƭ�";
			NumWithName num1, num2, result;
			num2 = tempVars.back();
			tempVars.pop_back();
			num1 = tempVars.back();
			tempVars.pop_back();

			if (!canUse(num1))
				return -1; //�䤣���ܼ�

			if (!canUse(num2))
				return -1; //�䤣���ܼ�

			if (num2.num == 0)
				return 1;
			//throw "�Q���Ƥ��൥��0";
			result.num = num1.num / num2.num;
			tempVars.push_back(result);
		}
		else if (postInput[i] == "^") {					//����
			if (tempVars.size() < 2)
				return -1;
			//throw "��J���~�A�ʤּƭ�";
			NumWithName num1, num2, result;
			num2 = tempVars.back();
			tempVars.pop_back();
			num1 = tempVars.back();
			tempVars.pop_back();

			if (!canUse(num1))
				return -1; //�䤣���ܼ�

			if (!canUse(num2))
				return -1; //�䤣���ܼ�

			if (isnan(pow(num1.num, num2.num)))
				return 1;
			//throw "NaN";
			result.num = pow(num1.num, num2.num);
			tempVars.push_back(result);
		}
		else if (postInput[i] == "@") {					//sin
			if (tempVars.size() < 1)
				return -1; //throw "��J���~�A�ʤּƭ�";
			NumWithName num1 = tempVars.back(), result;
			tempVars.pop_back();

			if (!canUse(num1))
				return -1; //�䤣���ܼ�

			result.num = sin(num1.num);
			tempVars.push_back(result);
		}
		else if (postInput[i] == "#") {					//cos
			if (tempVars.size() < 1)
				return -1; //throw "��J���~�A�ʤּƭ�";
			NumWithName num1 = tempVars.back(), result;
			tempVars.pop_back();

			if (!canUse(num1))
				return -1; //�䤣���ܼ�

			result.num = cos(num1.num);
			tempVars.push_back(result);
		}
		else if (postInput[i] == "$") {					//tan
			if (tempVars.size() < 1)
				return -1; //throw "��J���~�A�ʤּƭ�";
			NumWithName num1 = tempVars.back(), result;
			tempVars.pop_back();

			if (!canUse(num1))
				return -1; //�䤣���ܼ�

			if (isnan(tan(num1.num)))
				return 1;
			//throw "NaN";

			result.num = tan(num1.num);
			tempVars.push_back(result);

		}
		else if (postInput[i] == "=") {
			if (tempVars.size() < 2)					//assign
				return -1;
			//throw "��J���~�A�ʤּƭ�";
			NumWithName num1, num2;
			num2 = tempVars.back();
			tempVars.pop_back();
			num1 = tempVars.back();
			tempVars.pop_back();

			if (!canUse(num2))
				return -1; //�䤣���ܼ�

			this->vars[num1.name] = num2.num;
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
			if (isDigit) {										//�O�Ʀr�٬O�ܼ�
				stringstream ss;
				ss << postInput[i];
				double temp;
				ss >> temp;
				NumWithName tempNum(postInput[i], temp);
				tempVars.push_back(tempNum);					//����J�Ȧs
				//numbers.push_back(temp);
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

				if (this->vars.count(postInput[i]))		//�d���ܼƬO�_�w�s�b
				{
					NumWithName tempVar(postInput[i], this->vars[postInput[i]]);
					if (negtive)
						tempVar.num *= -1;
					tempVars.push_back(tempVar);

				}
				else
				{
					NumWithName tempVar(postInput[i], 0);	//���Ȧs ����T�{�O�_���s�ܼ�
					tempVars.push_back(tempVar);
					//return 1;
					//throw "�䤣���ܼ�";
				}
			}
		}
	}
	getVar.num = this->vars[getVar.name];
	if (input.find(getVar.name) == string::npos)
		return 1;
	return 0;
}
