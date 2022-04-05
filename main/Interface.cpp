#include "Interface.h"

const std::vector<std::string> Interface::FuncNames = { "Alg Polinoms", "Print Table",
                                                        "Insert Elem", "Find Elem", "Delete Elem",
                                                        "Cur Information", "Change Active Table",
                                                        "Clearing Screen", "Help", "Exit" };

const std::vector<std::string> Interface::AlgPolFuncNames = { "Algebra of polynomials",
                                                              "The value of the polynomial at the point" };

void Interface::setTableManager() {
  std::cout << "Choose size of all tables: ";
  int choice = Clamp(INT_MIN + 1, INT_MAX - 1);
  tabMan = new TableManager(choice);
  system("cls");
  std::cout << "Successfully created " << tabMan->getCountTables() <<
    " tables with " << tabMan->getMaxSize() << " elements!\n";
}

std::string Interface::getNameInInterface(bool checkUnique) {
  istreamCleaner();
  std::string tmpName;
  std::cout << "name = ";
  getline(std::cin, tmpName);
  if (tmpName.find_first_of("0123456789") == 0)
    throw std::string("Invalid name");
  for (auto& c : tmpName) {
    if (c == ' ') {
      c = '_';
    }
  }
  if (checkUnique == true) {
    if (tabMan->Find(tmpName) != nullptr) {
      throw std::string("An object with that name already exists");
    }
  }
  return tmpName;
}

std::string Interface::getStrPolInInterface() {
  std::string tmpStrPol;
  std::cout << "pol = ";
  getline(std::cin, tmpStrPol);
  if (tmpStrPol.find_first_not_of("0123456789.xyz+- ") != string::npos)
    throw std::string("Invalid polinomial");
  return tmpStrPol;
}

void Interface::executableFunc() {
  try {
    if (tabMan == nullptr) {
      setTableManager();
      return;
    }
    COORD curPos = getPos();
    printFunctions();
    int choice = Clamp(1, 10) - 1;
    screenCleaner(curPos);
    std::cout << "\nYou have chosen \"" << FuncNames[choice] << "\"\n\n";
    (this->*modeptr[choice])();
  }
  catch (std::string str) {
    std::cout << str << '\n';
  }
  catch (...) {
    std::cout << "Unexpected error.\n";
  }
}

// Alg Polinoms
void Interface::mode0() {
  COORD curPos = getPos();
  for (int i = 0; i < AlgPolFuncNames.size(); i++)
    std::cout << i + 1 << ") " << AlgPolFuncNames[i] << '\n';
  std::cout << "\nChoose one of these modes: ";
  int choice = Clamp(1, 2) - 1;
  screenCleaner(curPos);
  std::cout << "You have chosen \"" << AlgPolFuncNames[choice] << "\"\n\n";
  switch (choice) {
  case 0: algPolinoms(); break;
  case 1: valueInDot(); break;
  default: throw std::string("Incorrect data entry"); break;
  }
}

void Interface::algPolinoms() {
  string algExpr;
  std::cout << "Enter an algebraic expression: ";
  istreamCleaner();
  getline(std::cin, algExpr);
  TPostfix postfix(algExpr, tabMan);
  Polinom result = postfix.Calculate();
  std::cout << "Result: " << result << '\n';
  std::cout << "Save the result to tables?\n1) Yes\n2) No\n";
  int choice = Clamp(1, 2) - 1;
  if (choice == 0) {
    bool flag = false;
    std::string name;
    while (flag == false) {
      try {
        std::cout << "Enter the ";
        name = getNameInInterface();
        flag = true;
      }
      catch (std::string str) {
        std::cout << str << '\n';
      }
    }
    tabMan->Insert(name, result);
  }
}

void Interface::valueInDot() {
  string name;
  std::cout << "Enter the name of the polynomial:\n";
  name = getNameInInterface(false);
  auto obj = tabMan->Find(name);
  if (obj == nullptr)
  {
    std::cout << "There is no such polynomial in the table\n";
    return;
  }
  else
  {
    double x, y, z;
    std::cout << "x = ";
    x = Clamp(DBL_MIN + 1, DBL_MAX - 1);
    std::cout << "y = ";
    y = Clamp(DBL_MIN + 1, DBL_MAX - 1);
    std::cout << "z = ";
    z = Clamp(DBL_MIN + 1, DBL_MAX - 1);
    string resultStr = std::to_string(obj->get()->getPol().Calculate(x, y, z));
    std::cout << "Result: " << resultStr << '\n';
    std::cout << "Save the result to tables?\n1) Yes\n2) No";
    int choice = Clamp(1, 2) - 1;
    if (choice == 0) {
      bool flag = false;
      std::string name;
      while (flag == false) {
        try {
          name = getNameInInterface();
          flag = true;
        }
        catch (std::string str) {
          std::cout << str << '\n';
        }
      }
      tabMan->Insert(name, resultStr);
    }
  }
}

// Print Table +
void Interface::mode1() {
  tabMan->Print();
}

// Insert Elem +
void Interface::mode2() {
  std::string name, strPol;
  name = getNameInInterface();
  strPol = getStrPolInInterface();
  int sizeBefore = tabMan->getCurSize();
  tabMan->Insert(name, strPol);
  if (sizeBefore != tabMan->getCurSize()) {
    std::cout << "Object inserted\n";
  }
  else {
    std::cout << "Failed to insert an object\n";
  }
}

// Find Elem +
void Interface::mode3() {
  istreamCleaner();
  std::string tmpName;
  std::cout << "name = ";
  getline(std::cin, tmpName);
  auto result = tabMan->Find(tmpName);
  if (result == nullptr) {
    std::cout << "The element was not found\n";
  }
  else {
    std::cout << "The element was found:\n" << *result << '\n';
  }
}

// Delete Elem +
void Interface::mode4() {
  if (tabMan->getCurSize() <= 0) {
    throw std::string("The table is empty. Nothing to delete");
  }
  istreamCleaner();
  std::string tmpName;
  std::cout << "name = ";
  getline(std::cin, tmpName);
  int sizeBefore = tabMan->getCurSize();
  tabMan->Delete(tmpName);
  if (sizeBefore != tabMan->getCurSize()) {
    std::cout << "Object deleted\n";
  }
  else {
    std::cout << "No such object\n";
  }
}

// Current Information +
void Interface::mode5() {
  std::cout << tabMan->getTableName(tabMan->getActiveTableInd()) << " now is active\n";
  std::cout << "Total memory used in tables " << tabMan->getCurSize() << '/' << tabMan->getMaxSize() << '\n';
}

// Change Active Table +
void Interface::mode6() {
  COORD curPos = getPos();
  std::cout << "Select one of these tables:";
  printTables();
  int choice = Clamp(1, tabMan->getCountTables()) - 1;
  tabMan->setActiveTable(choice);
  screenCleaner(curPos);
  std::cout << tabMan->getTableName(tabMan->getActiveTableInd()) << " now is active\n";
}

// Clearing Screen +
void Interface::mode7() { system("cls"); }

// Help +
void Interface::mode8() {
  std::cout << "1) The names of polynomials with spaces are converted\n   to others (for example, \"a b\" -> \"a_b\")\n";
  std::cout << "2) The name of the polynomial does not start with a digit\n";
  std::cout << "3) Floating-point numbers are written with a dot\n   (for example: 3.7)\n";
  std::cout << "4) A polynomial of three variables (x, y, z), the\n   degree of each variable is less than 16\n";
  std::cout << "5) Monomes are introduced without any symbols\n   (-2*x^5*y^6*z^7 must be entered as -2x5y6z7)\n";
  std::cout << "6) Supported operations: " << Operations::str_op() << '\n';
  std::cout << "7) The screen displays 9 characters of the name and\n   19 characters of the polynomial\n";
}

// Exit +
void Interface::mode9() {
  std::cout << "See you soon!\n";
  delete tabMan;
  isWorks = false;
}

COORD Interface::getPos() {
  HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD pos = { -1, -1 };
  if (!Console)
    return pos;
  CONSOLE_SCREEN_BUFFER_INFO buf;
  GetConsoleScreenBufferInfo(Console, &buf);
  return buf.dwCursorPosition;
}

void Interface::istreamCleaner() {
  while (getchar() != '\n');
  std::cin.clear();
}

void Interface::screenCleaner(COORD pos) {
  HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
  if (!Console)
    return;
  CONSOLE_SCREEN_BUFFER_INFO buf;
  GetConsoleScreenBufferInfo(Console, &buf);
  WORD Attr;
  DWORD Count;
  ReadConsoleOutputAttribute(Console, &Attr, 1, pos, &Count);
  int col = Attr;
  int width = buf.dwSize.X;
  int height = buf.dwSize.Y;
  SetConsoleCursorPosition(Console, pos);
  FillConsoleOutputAttribute(Console, col, width * height, pos, &Count);
  FillConsoleOutputCharacter(Console, ' ', width * height, pos, &Count);
}

int Interface::Clamp(int border1, int border2) {
  int choice = INT_MIN;
  while (choice < border1 || choice > border2) {
    std::cin >> choice;
    if (choice < border1 || choice > border2) {
      std::cout << "Invalid number entered. Try again.\n";
      Interface::istreamCleaner();
    }
  }
  return choice;
}

double Interface::Clamp(double border1, double border2) {
  double choice = DBL_MIN;
  while (choice < border1 || choice > border2) {
    std::cin >> choice;
    if (choice < border1 || choice > border2) {
      std::cout << "Invalid number entered. Try again.\n";
      Interface::istreamCleaner();
    }
  }
  return choice;
}

void Interface::printFunctions() {
  std::cout << "\nAll functions: ";
  for (int i = 0; i < FuncNames.size(); i++) {
    if (i == 0 || i == 2 || i == 5 || i == 7) {
      std::cout << '\n';
    }
    std::cout << ' ' << i + 1 << ") " << FuncNames[i];
  }
  std::cout << "\nYour choice: ";
}

void Interface::printTables() {
  std::cout << "\nAll tables: ";
  for (int i = 0; i < tabMan->getCountTables(); i++) {
    std::cout << i + 1 << ") " << tabMan->getTableName(i) << '\n';
  }
  std::cout << '\n';
}
