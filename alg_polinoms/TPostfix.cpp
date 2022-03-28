#include "TPostfix.h"

bool TPostfix::BracketsCorrect(const string& str) const
{
  TStack<bool> stack; // ���� ��� �������� ������� '('
  for (const char& elem : str)
  {
	if (elem == '(')
	{
	  stack.push(true);
	  continue;
	}
	if (elem == ')')
	{
	  if (stack.empty()) // ���� ���� ����, �� ��� ���� ��� ')' -> ������
		return false;
	  stack.pop();
	  continue;
	}
  }
  if (!stack.empty()) // ���� ���� �� ����, �� ������� ���� ')' -> ������
	return false;
  return true;
}

void TPostfix::ToInfix(const string& str)
{
  string elem;
  if (!infix.empty())
	infix.clear();
  //�������� �� ������� ������:
  for (int i = 0; i < str.size();)
  {
	string lexem;
	elem = str[i];

	//�������� �� ��, �������� �� ��� ��� ���, ���� ��, �� � tmp ���������� ��� �������� � ����������� ������� �� 1
	if (operations.IsOperation(elem))
	{
	  lexem = elem;
	  i++;
	}
	else
	{
	  while (!operations.IsOperation(elem) && i < str.size())
	  {
		if (elem != " ")
		  lexem += elem;
		elem = str[++i];
	  }
	}

	if ((lexem == "-") && (infix.size() == 0 || (infix.size() > 0 && infix[infix.size() - 1] == "("))) // ����������� �������� ������ � ��������
	  infix.push_back("0");

	if (lexem.find_first_of("0123456789") == 0 && lexem.find_first_not_of("0123456789.") != string::npos) // �������� �� ������������ ����� ����������, ���� ��� ����������
	{
	  string exc = "Invalid format of variable: " + lexem;
	  throw exc;
	}

	if (lexem.size() != 0)
	  infix.push_back(lexem);
  }
}

void TPostfix::ToPostfix()
{
  if (!postfix.empty())
	postfix.clear();
  TStack<string> opStack;
  /*
  �) ���������� �� ����� ������� infix:
	  0) ���� ����� ���� �������, �������� � � postfix
	  1) ���� ��������� ������������� ������, ����� ���������� � � ����
	  2) ���� ��������� ������������� ������, (�������� � postfix) � ��������� �� ����� ��� ��������
	  �� ������������� ������ (������� ����� �������),
	  ��������� �������� �������� � postfix
	  3) ���� ��������� �������� � ����� ����� ������� ���������, ��� � ������� ��������, ��
	  �������� � postfix (� ��������� �� �����) ��� ��������, ���� ����������� ��� �������
	  4) ���� ���� ������, �� ��������� ��� ������� ���������, �����, ���� ���������
	  ������� �������� ������, ��� ��������� ��������� �������� � �����, �� ��������� � ����� �����
	  ������� ��������
  �) ���������� � ����� �������� �������� � postfix
  */

  for (int i = 0; i < infix.size(); i++)
  {
	string lexem = infix[i];
	if (!operations.IsOperation(lexem))
	{
	  //����� ���� �������
	  postfix.push_back(lexem);
	  continue;
	}
	else
	{
	  if (lexem == "(")
	  {
		opStack.push(lexem);
		continue;
	  }

	  if (lexem == ")")
	  {
		//��������� �������� ����� ��������� ����� ()
		while (opStack.tos() != "(")
		  postfix.push_back(opStack.pop());
		opStack.pop();
		continue;
	  }

	  //���� �� ������� ����� ��������� �������� � ������� �����������, ��� ������� ��������� � ��������
	  while (!opStack.empty() && operations.GetPriority(opStack.tos()) >= operations.GetPriority(lexem))
		postfix.push_back(opStack.pop());

	  if (opStack.empty())
	  {
		opStack.push(lexem);
		continue;
	  }
	  else
	  {
		if (operations.GetPriority(opStack.tos()) < operations.GetPriority(lexem))
		{
		  opStack.push(lexem);
		  continue;
		}
	  }
	}
  }
  while (!opStack.empty())
	postfix.push_back(opStack.pop());
}

double TPostfix::Calculate() const
{
 // map<string, double> values;
 // vector<string> variables = GetVecOfVariables();
 // if (interface)
 // {
	//if (variables.size() > 0)
	//{
	//  cout << "\nEnter the values of the undefined variables:\n";
	//  for (string& elem : variables)
	//  {
	//	double value;
	//	cout << "\t" << elem << " = ";
	//	cin >> value;
	//	values.emplace(elem, value);
	//  }
	//}
 // }
 // else
 // {
	//if (variables.size() != vecofvalues.size())
	//  throw string("Arrays of names and values have different sizes");
	//for (int i = 0; i < variables.size(); i++)
	//  values.emplace(variables[i], vecofvalues[i]);
 // }

 // double res = 0;
 // TStack<double> arguments;
 // Operations op;
 // for (const string& elem : postfix)
 // {
	//if (!op.IsOperation(elem))
	//{
	//  if (find(variables.begin(), variables.end(), elem) != variables.end()) // ���� elem - ����������
	//	arguments.push(values[elem]);
	//  else
	//	arguments.push(stod(elem));
	//}
	//else
	//{
	//  if (op.GetArity(elem) == 1)
	//	arguments.push(op.Calc(elem, arguments.pop())); // ������� ��� ���������� ��������� ��������
	//  else // if (op.GetArity(elem) == 2), �.�. � postfix ��� ������
	//	arguments.push(op.Calc(elem, arguments.pop(), arguments.pop())); // ������� ��� ���������� ��������� ��� ��������
	//}
 // }
 // res = arguments.pop(); // ��������� ������� � ����� - �����
 // return res;
  TStack<Polinom> result;
  for (size_t i = 0; i < postfix.size(); i++)
  {

  }
}
