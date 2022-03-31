#pragma once
#include <string>
#include <vector>
#include <map>
#include "stack.hpp"
#include "polinom.hpp"

using namespace std;

class Operations // Класс, хранящий поддерживаемые операции
{
private:
  map<string, vector<int>> ops; // string - name of operation; vector<int> - priority, arity; ops - OPerationS
public:
  Operations() // При добавлении операции в конструктор, обязательно нужно реализовать логику этой операции в Calc и добавить наименование в static string str_op()
  {
    ops.emplace("*", vector<int>{ 2, 2 });
    ops.emplace("+", vector<int>{ 1, 2 });
    ops.emplace("-", vector<int>{ 1, 2 });
    ops.emplace("(", vector<int>{ 0, 0 });
    ops.emplace(")", vector<int>{ 0, 0 });
    ops.emplace("d", vector<int>{ 3, 1 });
    ops.emplace("I", vector<int>{ 3, 1 });
  }

  static string str_op() { return string("*, +, -, (, ), d, I"); }

  bool IsOperation(const string& elem) const { return ops.find(elem) != ops.end(); } // Проверка является ли данный элемент операцией, которая объявлена в классе

  int GetPriority(const string& elem) { return ops[elem][0]; } // Получить приоритет у заданной операции, контроль использования за программистом 

  int GetArity(const string& elem) { return ops[elem][1]; } // Получить арность у заданной операции, контроль использования за программистом 

  Polinom Calc(const string& elem, Polinom left, Polinom right = Polinom()) // Вычислить
  {
    if (elem == "*")
      return left * right;
    if (elem == "+")
      return  left + right;
    if (elem == "-")
      return left - right;
    if (elem == "d")
      return left.Differentiate(right.ToString()[0]); //нужно каким-то образом получить от пользователю переменную, по которой диф
	if (elem == "I")
	{
	  return left.Integrate(right.ToString()[0]); // аналогично
	}
      
  }
};

class TPostfix
{
private:
  vector<string> infix;
  vector<string> postfix;
  Operations operation;
  map<string, string> difVariable;
  map<string, string> intVariable;
  TPostfix(const TPostfix&) = delete; // Запрет на копирование
  void operator=(const TPostfix&) = delete; // Запрет на присваивание
  bool BracketsCorrect(const string& str) const; // Проверка на корректность раставления скобок в полученной на вход строке
  void ToInfix(const string& str); // Преобразование полученной строки в vector<string> infix
  void ToPostfix(); // Преобразование infix в vector<string> postfix
  bool IsInterface = false;
  bool IsMonom(const string& lexem);
  bool IsNumber(const string& lexem);
  void Differentiate(const string& str);
  void DeleteSpaces(string& str);
  string IsDiff(const char& str);
public:
  TPostfix(string str) // Конструктор
  {
    if (!BracketsCorrect(str))
      throw string("The brackets in expression are incorrect");
    ToInfix(str);
    ToPostfix();
  }

  vector<string> GetInfix() const { return infix; }
  Polinom GetValueVarialbe(const string& valueVariable);
  Polinom GetValueVariableFromUser(const string& variable);
  vector<string> GetPostfix() const { return postfix; }

  string GetStringInfix() const
  {
    string tmp;
    for (const string& elem : infix)
      tmp += elem + ' ';
    return tmp;
  }

  void NewInfix(const string& infixStr) {
    if (BracketsCorrect(infixStr))
    {
      ToInfix(infixStr);
      ToPostfix();
    }
    throw string("The brackets in expression are incorrect");
  }

  string GetStringPostfix() const
  {
    string tmp;
    for (const string& elem : postfix)
      tmp += elem + ' ';
    return tmp;
  }

  Polinom Calculate();
};

bool TPostfix::BracketsCorrect(const string& str) const
{
  TStack<bool> stack; // Стек для проверки наличия '('
  for (const char& elem : str)
  {
	if (elem == '(')
	{
	  stack.push(true);
	  continue;
	}
	if (elem == ')')
	{
	  if (stack.empty()) // Если стек пуст, то нет пары для ')' -> ошибка
		return false;
	  stack.pop();
	  continue;
	}
  }
  if (!stack.empty()) // Если стек не пуст, то слишком мало ')' -> ошибка
	return false;
  return true;
}

void TPostfix::ToInfix(const string& str)
{
  string elem;
  string copyStr(str);
  DeleteSpaces(copyStr);
  if (!infix.empty())
	infix.clear();
  //проходка по массиву строки:
  for (int i = 0; i < copyStr.size();)
  {
	string lexem;
	elem = copyStr[i];
	//проверка на то, операция ли это или нет, если да, то в tmp записываем эту операцию и увеличиваем счетчик на 1
	if (operation.IsOperation(elem))
	{
	  lexem = elem;
	  i++;
	  if (elem == "d")
	  {
		string variable = IsDiff(copyStr[i]);
		if (variable != "none")
		{
		  elem = variable;
		  infix.push_back(elem);
		  i++;
		  continue;
		}
	  }
	}
	else
	{
	  while (!operation.IsOperation(elem) && i < copyStr.size())
	  {
		lexem += elem;
		elem = copyStr[++i];
	  }
	}
	
	if ((lexem == "-") && (infix.size() == 0 || (infix.size() > 0 && infix[infix.size() - 1] == "("))) // Превращение унарного минуса в бинарный
	  infix.push_back("0");
	//проверка на моном
	if (IsMonom(lexem))
	{
	  infix.push_back(lexem);
	  continue;
	}
	//проверка на правильность введенной переменной
	if (lexem.find_first_of("0123456789") == 0 && lexem.find_first_not_of("0123456789.") != string::npos) // Проверка на корректность имени переменной, если это переменная
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
  а) Проходимся по всему вектору infix:
	  0) Если перед нами лексема, помещаем её в postfix
	  1) Если встречаем открывающуюся скобку, сразу записываем её в стек
	  2) Если встречаем закрывающуюся скобку, (помещаем в postfix) с удалением из стека все операции
	  до открывающейся скобки (которую также удаляем),
	  забранные значения помещаем в postfix
	  3) Если последняя операция в стеке имеет больший приоритет, чем у текущей операции, то
	  помещаем в postfix (с удалением из стека) все операции, пока выполняется это условие
	  4) Если стек пустой, то заполняем его текущей операцией, иначе, если приоритет
	  текущей операции больше, чем приоритет последней операции в стеке, то добавляем в конец стека
	  текущую операцию
  б) Оставшиеся в стеке операции помещаем в postfix
  */

  for (int i = 0; i < infix.size(); i++)
  {
	string lexem = infix[i];
	if (!operation.IsOperation(lexem))
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
		//Заполняем постфикс всеми лексемами между ()
		while (opStack.tos() != "(")
		  postfix.push_back(opStack.pop());
		opStack.pop();
		/*if (opStack.tos() == "d" || opStack.tos() == "I")
		{
		  postfix.push_back(opStack.pop());
		  postfix.push_back(infix[++i]);
		}*/
		continue;
	  }

	  //Пока на вершине стека находится операция с большим приоритетом, чем текущая добавляем в постфикс
	  while (!opStack.empty() && operation.GetPriority(opStack.tos()) >= operation.GetPriority(lexem))
		postfix.push_back(opStack.pop());

	  if (opStack.empty())
	  {
		opStack.push(lexem);
		continue;
	  }
	  else
	  {
		if (operation.GetPriority(opStack.tos()) < operation.GetPriority(lexem))
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

bool TPostfix::IsMonom(const string& lexem)
{
  if (lexem.find_first_of("xyz") != string::npos && lexem.find_first_not_of("xyz0123456789.") == string::npos)
	return true;
  return false;
}

bool TPostfix::IsNumber(const string& lexem)
{
  if (lexem.find_first_not_of("1234567890.") != string::npos)
	return false;
  return true;
}

inline void TPostfix::Differentiate(const string& str)
{

}

inline void TPostfix::DeleteSpaces(string& str)
{
  for (size_t i = 0; i < str.size(); i++)
  {
	if (str[i] == ' ')
	  str.erase(i, 1);
  }
}

inline string TPostfix::IsDiff(const char& str)
{
  if (str == 'x')
	return "x";
  else if (str == 'y')
	return "y";
  else if (str == 'z')
	return "z";
  else return "none";
}

Polinom TPostfix::GetValueVarialbe(const string& valueVariable)
{
  return Polinom(valueVariable);
}

Polinom TPostfix::GetValueVariableFromUser(const string& variable) {
  string strPol;
  std::cout << "Введите значение переменной " << variable << " = ";
  std::cin >> strPol;
  return Polinom(strPol);
}

Polinom TPostfix::Calculate()
{
  TStack<Polinom> result;
  for (size_t i = 0; i < postfix.size(); i++)
  {
	if (operation.IsOperation(postfix[i])) //лексема операция
	{
	  if (operation.GetArity(postfix[i]) == 1)
	  {
		result.push(operation.Calc(postfix[i], result.pop(), result.pop()));
	  }
	  else if (operation.GetArity(postfix[i]) == 2)
	  {
		result.push(operation.Calc(postfix[i], result.pop(), result.pop()));
	  }
		
	}
	else if (IsMonom(postfix[i]) || IsNumber(postfix[i])) //лексема моном или число
	{
	  result.push(Polinom(postfix[i]));
	}
	else //переменная
	{
	  result.push(GetValueVariableFromUser(postfix[i]));
	}
  }
  return result.pop();
}

