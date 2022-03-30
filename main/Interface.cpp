#include "Interface.h"

void Interface::setTableManager() {
  std::cout << "Choose size of all tables: ";
  int choice = Clamp(INT_MIN, INT_MAX);
  tabMan = new TableManager(choice);
  std::cout << "Successfully created " << tabMan->getCountTables() <<
    " tables with " << tabMan->getMaxSize() << " elements!\n";
  system("pause");
  system("cls");
}

bool Interface::executableFunc() {
  try {
    if (tabMan == nullptr) {
      setTableManager();
      return true;
    }
    printFunctions();
    int choice = Clamp(1, 12) - 1;
    (this->*modeptr[choice])();
  }
  catch (std::string str) {
    std::cout << str << '\n';
  }
  catch (...) {
    std::cout << "Unexpected error.\n";
  }
  return true;
}


void Interface::mode0() {

}

void Interface::mode1()
{
}

void Interface::mode2()
{
}

void Interface::mode3()
{
}

void Interface::mode4()
{
}

void Interface::mode5()
{
}
void Interface::mode6()
{
}

void Interface::mode7()
{
}

void Interface::mode8()
{
}

void Interface::mode9()
{
}

void Interface::mode10()
{
}

void Interface::mode11()
{
}

void Interface::Cleaner() {
  while (getchar() != '\n');
  std::cin.clear();
}

int Interface::Clamp(int border1, int border2) {
  int choice = INT_MIN;
  while (choice < border1 || choice > border2) {
    std::cin >> choice;
    if (choice < border1 || choice > border2) {
      std::cout << "Invalid number entered. Try again.\n";
      Interface::Cleaner();
    }
  }
}

void Interface::printFunctions() {
  int i = 0;
  std::cout << "\nAll functions: ";
  for (; i < FuncNames.size(); i++) {
    if (i % 3 == 0) {
      std::cout << '\n';
    }
    std::cout << i + 1 << ") " << FuncNames[i];
  }
  if (i % 3 != 0) {
    std::cout << '\n';
  }
  std::cout << "Your choice: ";
}
