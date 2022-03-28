#pragma once
#include <string>
#include <vector>
#include <map>
#include "stack.hpp"
#include "polinom.hpp"

using namespace std;

class Operations // �����, �������� �������������� ��������
{
private:
  map<string, vector<int>> ops; // string - name of operation; vector<int> - priority, arity; ops - OPerationS
public:
  Operations() // ��� ���������� �������� � �����������, ����������� ����� ����������� ������ ���� �������� � Calc � �������� ������������ � static string str_op()
  {
    ops.emplace("*", vector<int>{ 2, 2 });
    ops.emplace("+", vector<int>{ 1, 2 });
    ops.emplace("-", vector<int>{ 1, 2 });
    ops.emplace("(", vector<int>{ 0, 0 });
    ops.emplace(")", vector<int>{ 0, 0 });
    ops.emplace("d", vector<int>{ 3, 1 });
    ops.emplace("i", vector<int>{ 3, 1 });
  }

  static string str_op() { return string("*, +, -, (, ), d, I"); }

  bool IsOperation(const string& elem) const { return ops.find(elem) != ops.end(); } // �������� �������� �� ������ ������� ���������, ������� ��������� � ������

  int GetPriority(const string& elem) { return ops[elem][0]; } // �������� ��������� � �������� ��������, �������� ������������� �� ������������� 

  int GetArity(const string& elem) { return ops[elem][1]; } // �������� ������� � �������� ��������, �������� ������������� �� ������������� 

  Polinom Calc(const string& elem, Polinom right, Polinom left = Polinom()) // ���������
  {
    if (elem == "*")
      return right * left;
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
  Operations operations;
  TPostfix(const TPostfix&) = delete; // ������ �� �����������
  void operator=(const TPostfix&) = delete; // ������ �� ������������
  bool BracketsCorrect(const string& str) const; // �������� �� ������������ ����������� ������ � ���������� �� ���� ������
  void ToInfix(const string& str); // �������������� ���������� ������ � vector<string> infix
  void ToPostfix(); // �������������� infix � vector<string> postfix

public:
  TPostfix(string str) // �����������
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

  double Calculate() const;
};

