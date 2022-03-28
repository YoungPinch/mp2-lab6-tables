#include "TPostfix.h"

bool TPostfix::BracketsCorrect(const string& str) const
{
  TStack<bool> stack; // —тек дл€ проверки наличи€ '('
  for (const char& elem : str)
  {
	if (elem == '(')
	{
	  stack.push(true);
	  continue;
	}
	if (elem == ')')
	{
	  if (stack.empty()) // ≈сли стек пуст, то нет пары дл€ ')' -> ошибка
		return false;
	  stack.pop();
	  continue;
	}
  }
  if (!stack.empty()) // ≈сли стек не пуст, то слишком мало ')' -> ошибка
	return false;
  return true;
}

void TPostfix::ToInfix(const string& str)
{
  string elem;
  if (!infix.empty())
	infix.clear();
  //проходка по массиву строки:
  for (int i = 0; i < str.size();)
  {
	string lexem;
	elem = str[i];

	//проверка на то, операци€ ли это или нет, если да, то в tmp записываем эту операцию и увеличиваем счетчик на 1
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

	if ((lexem == "-") && (infix.size() == 0 || (infix.size() > 0 && infix[infix.size() - 1] == "("))) // ѕревращение унарного минуса в бинарный
	  infix.push_back("0");

	if (lexem.find_first_of("0123456789") == 0 && lexem.find_first_not_of("0123456789.") != string::npos) // ѕроверка на корректность имени переменной, если это переменна€
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
  а) ѕроходимс€ по всему вектору infix:
	  0) ≈сли перед нами лексема, помещаем еЄ в postfix
	  1) ≈сли встречаем открывающуюс€ скобку, сразу записываем еЄ в стек
	  2) ≈сли встречаем закрывающуюс€ скобку, (помещаем в postfix) с удалением из стека все операции
	  до открывающейс€ скобки (которую также удал€ем),
	  забранные значени€ помещаем в postfix
	  3) ≈сли последн€€ операци€ в стеке имеет больший приоритет, чем у текущей операции, то
	  помещаем в postfix (с удалением из стека) все операции, пока выполн€етс€ это условие
	  4) ≈сли стек пустой, то заполн€ем его текущей операцией, иначе, если приоритет
	  текущей операции больше, чем приоритет последней операции в стеке, то добавл€ем в конец стека
	  текущую операцию
  б) ќставшиес€ в стеке операции помещаем в postfix
  */

  for (int i = 0; i < infix.size(); i++)
  {
	string lexem = infix[i];
	if (!operations.IsOperation(lexem))
	{
	  //перед нами лексема
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
		//«аполн€ем постфикс всеми лексемами между ()
		while (opStack.tos() != "(")
		  postfix.push_back(opStack.pop());
		opStack.pop();
		continue;
	  }

	  //ѕока на вершине стека находитс€ операци€ с большим приоритетом, чем текуща€ добавл€ем в постфикс
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
	//  if (find(variables.begin(), variables.end(), elem) != variables.end()) // ≈сли elem - переменна€
	//	arguments.push(values[elem]);
	//  else
	//	arguments.push(stod(elem));
	//}
	//else
	//{
	//  if (op.GetArity(elem) == 1)
	//	arguments.push(op.Calc(elem, arguments.pop())); // ѕередаЄм дл€ вычислени€ последнее значение
	//  else // if (op.GetArity(elem) == 2), т.к. в postfix нет скобок
	//	arguments.push(op.Calc(elem, arguments.pop(), arguments.pop())); // ѕередаЄм дл€ вычислени€ последние два значени€
	//}
 // }
 // res = arguments.pop(); // ѕоследний элемент в стеке - ответ
 // return res;
  TStack<Polinom> result;
  for (size_t i = 0; i < postfix.size(); i++)
  {

  }
	return DBL_MAX; // «аглушка, дописать
}
