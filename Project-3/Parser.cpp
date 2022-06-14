#include "Parser.h"

Parser::Parser(string input)
{
	this->input = input;
}

vector<int> Parser::findd(char in)
{
	vector<int> out;
	out.resize(2);//0數字1權重
	int time = 0;
	char opr[12] = { '(',')','=','=','+','-','*','/','^','^','!','!' };
	for (int i = 0; i < 12 + 1; i++) {


		if (i < 12) {
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
	return  out;

}

vector<string> Parser::Postfix(string inp)
{
	vector<int> number;
	vector<int> lastnumber;
	vector<string> out;
	stack<int> stack;
	bool wronginput = false;
	bool isnegetive = false;
	string opr[12] = { "(",")","=","=", "+", "-", "*", "/","^","^","!","!" };
	string temp;

	lastnumber.resize(2); lastnumber.at(0) = -1; lastnumber.at(1) = -1;

	string in = "";
	string plus;

	for (auto c : inp)
	{
		if (c != ' ')
			in = in + c;
	}

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
	vector<string> postInput = Postfix(input);	//postInput: 中序轉後序後的資料
	/*cout << "postFix: ";
	for (int i = 0; i < postInput.size(); i++)
	{
		cout << postInput.at(i) << " ";
	}
	cout << endl;*/
	bool countNegative = false;	//奇數個負為true
	for (int i = 0; i < postInput.size(); i++) {
		if (postInput[i] == "+") {					//加法
			if (numbers.size() < 2)
				continue;
			//throw "輸入錯誤，缺少數值";
			double num1, num2;
			num2 = numbers.at(numbers.size() - 1);
			numbers.erase(numbers.end() - 1);
			num1 = numbers.at(numbers.size() - 1);
			numbers.erase(numbers.end() - 1);

			numbers.push_back(num1 + num2);

		}
		else if (postInput[i] == "-") {					//減法
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
		else if (postInput[i] == "*") {					//乘法
			if (numbers.size() < 2)
				return 1;
			//throw "輸入錯誤，缺少數值";
			double num1, num2;
			num2 = numbers.at(numbers.size() - 1);
			numbers.erase(numbers.end() - 1);
			num1 = numbers.at(numbers.size() - 1);
			numbers.erase(numbers.end() - 1);

			numbers.push_back(num1 * num2);
		}
		else if (postInput[i] == "/") {					//除法
			if (numbers.size() < 2)
				return 1;
			//throw "輸入錯誤，缺少數值";
			double num1, num2;
			num2 = numbers.at(numbers.size() - 1);
			numbers.erase(numbers.end() - 1);
			num1 = numbers.at(numbers.size() - 1);
			numbers.erase(numbers.end() - 1);

			if (num2 == 0)
				return 1;
			//throw "被除數不能等於0";

			numbers.push_back(num1 / num2);

		}
		else if (postInput[i] == "^") {					//冪次
			if (numbers.size() < 2)
				return 1;
			//throw "輸入錯誤，缺少數值";
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
			//throw "輸入錯誤，缺少數值";
			double num1, num2;
			num2 = numbers.at(numbers.size() - 1);
			numbers.erase(numbers.end() - 1);
			num1 = numbers.at(numbers.size() - 1);
			numbers.erase(numbers.end() - 1);

			num1 = num2;
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
			if (isDigit) {										//是數字還是變數
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
					//throw "找不到變數";
				}
			}
		}
	}
	return 0;
}
