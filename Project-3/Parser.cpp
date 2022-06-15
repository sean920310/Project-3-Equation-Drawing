#include "Parser.h"

Parser::Parser(string input)
{
	this->input = input;

	while (this->input.find("sin")!=string::npos)
	{
		auto i = this->input.find("sin");
		this->input.replace(i, 3,"@");
	}
	while(this->input.find("cos") != string::npos)
	{
		auto i = this->input.find("cos");
		this->input.replace(i, 3, "#");
	}
	while(this->input.find("tan") != string::npos)
	{
		auto i = this->input.find("tan");
		this->input.replace(i, 3, "$");
	}

	/*if (this->input.find("y") == string::npos&&this->input.find("=")==string::npos)
	{
		this->input = "y=" + this->input;
		NumWithName y("y",0);
		vars.push_back(y);
	}*/

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

int Parser::calculate(vector<NumWithName>& vars, vector<double>& numbers)
{
	vector<string> postInput = Postfix(input);	//postInput: �������ǫ᪺���
	/*cout << "postFix: ";
	for (int i = 0; i < postInput.size(); i++)
	{
		cout << postInput.at(i) << " ";
	}
	cout << endl;*/
	bool countNegative = false;	//�_�ƭӭt��true
	for (int i = 0; i < postInput.size(); i++) {
		if (postInput[i] == "+") {					//�[�k
			if (numbers.size() < 2)
				continue;
			//throw "��J���~�A�ʤּƭ�";
			double num1, num2;
			num2 = numbers.at(numbers.size() - 1);
			numbers.erase(numbers.end() - 1);
			num1 = numbers.at(numbers.size() - 1);
			numbers.erase(numbers.end() - 1);

			numbers.push_back(num1 + num2);

		}
		else if (postInput[i] == "-") {					//��k
			if (numbers.size() < 2) {					//bug: 1---5
				if (numbers.size() == 1) {
					if (!countNegative) {
						double num;
						num = numbers.at(numbers.size() - 1);
						numbers.erase(numbers.end() - 1);

						numbers.push_back(-num);

					}
				}
				else {
					countNegative = !countNegative;
				}
			}
			else
			{
				double num1, num2;
				num2 = numbers.at(numbers.size() - 1);
				numbers.erase(numbers.end() - 1);
				num1 = numbers.at(numbers.size() - 1);
				numbers.erase(numbers.end() - 1);

				numbers.push_back(num1 - num2);
			}
		}
		else if (postInput[i] == "*") {					//���k
			if (numbers.size() < 2)
				return 1;
			//throw "��J���~�A�ʤּƭ�";
			double num1, num2;
			num2 = numbers.at(numbers.size() - 1);
			numbers.erase(numbers.end() - 1);
			num1 = numbers.at(numbers.size() - 1);
			numbers.erase(numbers.end() - 1);

			numbers.push_back(num1 * num2);
		}
		else if (postInput[i] == "/") {					//���k
			if (numbers.size() < 2)
				return 1;
			//throw "��J���~�A�ʤּƭ�";
			double num1, num2;
			num2 = numbers.at(numbers.size() - 1);
			numbers.erase(numbers.end() - 1);
			num1 = numbers.at(numbers.size() - 1);
			numbers.erase(numbers.end() - 1);

			if (num2 == 0)
				return 1;
			//throw "�Q���Ƥ��൥��0";

			numbers.push_back(num1 / num2);

		}
		else if (postInput[i] == "^") {					//����
			if (numbers.size() < 2)
				return 1;
			//throw "��J���~�A�ʤּƭ�";
			double num1, num2;
			num2 = numbers.at(numbers.size() - 1);
			numbers.erase(numbers.end() - 1);
			num1 = numbers.at(numbers.size() - 1);
			numbers.erase(numbers.end() - 1);

			if (isnan(pow(num1, num2)))
				return 1;
			//throw "NaN";
			numbers.push_back(pow(num1, num2));
		}
		else if (postInput[i] == "=") {
			if (numbers.size() < 2)			//assign
				return 1;
			//throw "��J���~�A�ʤּƭ�";
			double num1, num2;
			num2 = numbers.at(numbers.size() - 1);
			numbers.erase(numbers.end() - 1);
			num1 = numbers.at(numbers.size() - 1);
			numbers.erase(numbers.end() - 1);

			num1 = num2;
		}
		else if (postInput[i] == "@") {					//sin
			if (numbers.size() < 1)
				return 1;
			//throw "��J���~�A�ʤּƭ�";
			double num1 = numbers.at(numbers.size() - 1);
			numbers.erase(numbers.end() - 1);

			numbers.push_back(sin(num1));
		}
		else if (postInput[i] == "#") {					//cos
		if (numbers.size() < 1)
			return 1;
		//throw "��J���~�A�ʤּƭ�";
		double num1 = numbers.at(numbers.size() - 1);
		numbers.erase(numbers.end() - 1);

		numbers.push_back(cos(num1));
		}
		else if (postInput[i] == "$") {					//tan
		if (numbers.size() < 1)
			return 1;
		//throw "��J���~�A�ʤּƭ�";
		double num1 = numbers.at(numbers.size() - 1);
		numbers.erase(numbers.end() - 1);

		if (isnan(tan(num1)))
			return 1;
		//throw "NaN";
		numbers.push_back(tan(num1));
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
				numbers.push_back(temp);
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

				for (const auto& var : vars) {
					if (postInput[i] == var.name) {
						if (negtive)
							numbers.push_back(var.num * -1);
						else
							numbers.push_back(var.num);
						findVar = true;
						break;
					}
				}
				if (!findVar) {
					return 1;
					//throw "�䤣���ܼ�";
				}
			}
		}
	}
	return 0;
}
