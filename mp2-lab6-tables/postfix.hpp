#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include <vector>
#include <map>
#include "stack.hpp"

using namespace std;

class Operations // Класс, хранящий поддерживаемые операции
{
private:
  map<string, vector<int>> ops; // string - name of operation; vector<int> - priority, arity; ops - OPerationS
public:
  Operations() // При добавлении операции в конструктор, обязательно нужно реализовать логику этой операции в Calc и добавить наименование в static string str_op()
  {
    ops.emplace("sqrt", vector<int>{ 3, 1 });
    ops.emplace("sin", vector<int>{ 3, 1 });
    ops.emplace("cos", vector<int>{ 3, 1 });
    ops.emplace("*", vector<int>{ 2, 2 });
    ops.emplace("/", vector<int>{ 2, 2 });
    ops.emplace("+", vector<int>{ 1, 2 });
    ops.emplace("-", vector<int>{ 1, 2 });
    ops.emplace("(", vector<int>{ 0, 0 });
    ops.emplace(")", vector<int>{ 0, 0 });
  }

  static string str_op() { return string("sqrt(v), sin(v), cos(v), *, /, +, -, (, )"); }

  bool IsOperation(const string& elem) const { return ops.find(elem) != ops.end(); } // Проверка является ли данный элемент операцией, которая объявлена в классе

  int GetPriority(const string& elem) { return ops[elem][0]; } // Получить приоритет у заданной операции, контроль использования за программистом 

  int GetArity(const string& elem) { return ops[elem][1]; } // Получить арность у заданной операции, контроль использования за программистом 

  double Calc(const string& elem, double right, double left = 0) // Вычислить
  {
    if (elem == "sqrt")
      return sqrt(right);
    if (elem == "sin")
      return sin(right);
    if (elem == "cos")
      return cos(right);
    if (elem == "*")
      return right * left;
    if (elem == "/")
      return  right / left;
    if (elem == "+")
      return  right + left;
    if (elem == "-")
      return right - left;
  }
};


class TPostfix
{
private:
  vector<string> infix;
  vector<string> postfix;
  TPostfix(const TPostfix&) = delete; // Запрет на копирование
  void operator=(const TPostfix&) = delete; // Запрет на присваивание
  bool BracketsCorrect(string& str) const; // Проверка на корректность раставления скобок в полученной на вход строке
  void ToInfix(string& str); // Преобразование полученной строки в vector<string> infix
  void ToPostfix(); // Преобразование infix в vector<string> postfix
  vector<string> GetVecOfVariables() const; // Получить вектор переменных из постфиксной формы

public:
  TPostfix(string str) // Конструктор
  {
    if (!BracketsCorrect(str))
      throw string("The brackets in expression are incorrect");
    ToInfix(str);
    ToPostfix();
  }

  vector<string> GetInfix() const { return infix; }

  vector<string> GetPostfix() const { return postfix; }

  string GetStringInfix() const
  {
    string tmp;
    for (const string& elem : infix)
      tmp += elem + ' ';
    return tmp;
  }

  string GetStringPostfix() const
  {
    string tmp;
    for (const string& elem : postfix)
      tmp += elem + ' ';
    return tmp;
  }

  double Calculate(bool interface = true, vector<double> vecofvalues = {}) const; // Ввод переменных, вычисление по постфиксной форме
};

#endif