#include "Interface.h"

const std::vector<std::string> Interface::FuncNames = { "Alg Polinoms", "Print Table",
                                                        "Insert Elem", "Find Elem", "Delete Elem",
                                                        "Cur Information", "Change Active Table",
                                                        "Clearing Screen", "Help", "Exit" };

void Interface::setTableManager() {
  std::cout << "Choose size of all tables: ";
  int choice = Clamp(INT_MIN + 1, INT_MAX - 1);
  tabMan = new TableManager(choice);
  system("cls");
  std::cout << "Successfully created " << tabMan->getCountTables() <<
    " tables with " << tabMan->getMaxSize() << " elements!\n";
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
// Будет добавлено по завершении полиномов
void Interface::mode0() {

}

// Print Table +
void Interface::mode1() {
  tabMan->Print();
}

// Insert Elem +
void Interface::mode2() {
  istreamCleaner();
  std::string tmpName, tmpStrPol;
  std::cout << "name = ";
  getline(std::cin, tmpName);
  if (tmpName.find_first_of("0123456789") == 0)
    throw std::string("Invalid name");
  for (auto& c : tmpName) {
    if (c == ' ') {
      c = '_';
    }
  }
  std::cout << "pol = ";
  getline(std::cin, tmpStrPol);
  if (tmpStrPol.find_first_not_of("0123456789.xyz") != string::npos)
    throw std::string("Invalid polinomial");
  int sizeBefore = tabMan->getCurSize();
  tabMan->Insert(tmpName, tmpStrPol);
  if (sizeBefore != tabMan->getCurSize()) {
    std::cout << "Object inserted\n";
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
    std::cout << tmpName << " was not found in the table.\n";
  }
  else {
    std::cout << "The element was found in the table:\n" << *result << '\n';
  }
}

// Delete Elem +
void Interface::mode4() {
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
  std::cout << "5) Supported operations: " << Operations::str_op() << '\n';
  std::cout << "6) The screen displays 9 characters of the name and\n   19 characters of the polynomial\n";
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
