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
  string copyStr(str);
  DeleteSpaces(copyStr);
  if (!infix.empty())
    infix.clear();
  //проходка по массиву строки:
  for (int i = 0; i < copyStr.size();)
  {
    string lexem;
    elem = copyStr[i];
    //проверка на то, операци€ ли это или нет, если да, то в tmp записываем эту операцию и увеличиваем счетчик на 1
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

    if ((lexem == "-") && (infix.size() == 0 || (infix.size() > 0 && infix[infix.size() - 1] == "("))) // ѕревращение унарного минуса в бинарный
      infix.push_back("0");
    //проверка на моном
    if (IsMonom(lexem))
    {
      infix.push_back(lexem);
      continue;
    }
    //проверка на правильность введенной переменной
    if (lexem.find_first_of("0123456789") == 0 && lexem.find_first_not_of("0123456789.") != string::npos) // ѕроверка на корректность имени переменной, если это переменна€
    {
      std::string exc = "Invalid format of variable: " + lexem;
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
        //«аполн€ем постфикс всеми лексемами между ()
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

      //ѕока на вершине стека находитс€ операци€ с большим приоритетом, чем текуща€ добавл€ем в постфикс
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
  std::cout << "¬ведите значение переменной " << variable << " = ";
  std::cin >> strPol;
  return Polinom(strPol);
}

Polinom TPostfix::Calculate()
{
  TStack<Polinom> result;
  for (size_t i = 0; i < postfix.size(); i++)
  {
    if (operation.IsOperation(postfix[i])) //лексема операци€
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
    else //переменна€
    {
      result.push(GetValueVariableFromUser(postfix[i]));
      //result.push(tabMan->Find(postfix[i]).pol); »зменить
    }
  }
  return result.pop();
}
