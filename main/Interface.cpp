#include "Interface.h"

const std::vector<std::string> Interface::FuncNames = { "Alg Polinoms", "Print Table",
                                                        "Insert Elem", "Find Elem", "Delete Elem",
                                                        "Cur Information", "Change Active Table",
                                                        "Clearing Screen", "Settings", "Help", "Exit" };

void Interface::setTableManager() {
  std::cout << "Choose size of all tables: ";
  int choice = Clamp(INT_MIN + 1, INT_MAX - 1);
  tabMan = new TableManager(choice);
  std::cout << "Successfully created " << tabMan->getCountTables() <<
    " tables with " << tabMan->getMaxSize() << " elements!\n";
}

void Interface::executableFunc() {
  try {
    if (tabMan == nullptr) {
      setTableManager();
      return;
    }
    printFunctions();
    int choice = Clamp(1, 11) - 1;
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

// Insert Elem
// Добавить проверки на string
void Interface::mode2() {
  Cleaner();
  std::string tmpName, tmpStrPol;
  std::cout << "name =\n";
  getline(std::cin, tmpName);
  std::cout << "pol =\n";
  getline(std::cin, tmpStrPol);
  tabMan->Insert(tmpName, tmpStrPol);
}

// Find Elem
// Добавить проверки на string
// Добавить проверки на Find (найдено или нет)
void Interface::mode3() {
  std::string tmpName;
  std::cout << "name =\n";
  getline(std::cin, tmpName);
  tabMan->Find(tmpName);
}

// Delete Elem
// Добавить проверки на string
void Interface::mode4() {
  std::string tmpName;
  std::cout << "name =\n";
  getline(std::cin, tmpName);
  tabMan->Delete(tmpName);
}

// Current Information +
void Interface::mode5() {
  std::cout << tabMan->getTableName(tabMan->getActiveTableInd()) << " now is active.\n";
  std::cout << "Total memory used in tables " << tabMan->getCurSize() << '/' << tabMan->getMaxSize() << '\n';
}

// Change Active Table +
void Interface::mode6() {
  std::cout << "Select one of these tables:";
  printTables();
  TableManager::TableKind choice = TableManager::TableKind(Clamp(1, tabMan->getCountTables()));
  tabMan->setActiveTable(choice);
}

// Clearing Screen +
void Interface::mode7() { system("cls"); }

// Settings
// Добавить изменение границ вывода
// Добавить Change Showing Of Stats
void Interface::mode8() {

}

// Help
// краткое их описание, какие поддерживаются алгебраические операции
// (интеграл, дифференцирование, + - *), расчёт значения в точке
// Добавить информацию про вывод определённого кол-ва символов в полиноме
// И его названии
void Interface::mode9() {
  std::cout << "Help";
  std::cout << "\n Rules for Alg Polinoms:\n0) You can write as many spaces as you want\n";
  std::cout << "1) Variable names are entered without spaces\n(for example, not like \"a b\" but like \"ab\")\n";
  std::cout << "2) The variable name does not start with a digit\n";
  std::cout << "3) Floating-point numbers are written with a dot (for example: 3.7)\n";
  //std::cout << "4) Supported operations:\n" << Operations::str_op() << "\n\n";
  // Раскоментировать после добавления к интерфейсу alg_polinoms
}

// Exit +
void Interface::mode10() {
  std::cout << "\nSee you soon!\n";
  delete tabMan;
  isWorks = false;
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
  return choice;
}

void Interface::printFunctions() {
  int i = 0;
  std::cout << "\nAll functions: ";
  for (; i < FuncNames.size(); i++) {
    if (i % 3 == 0) {
      std::cout << '\n';
    }
    std::cout << ' ' << i + 1 << ") " << FuncNames[i];
  }
  if (i % 3 != 0) {
    std::cout << '\n';
  }
  std::cout << "Your choice: ";
}

void Interface::printTables() {
  std::cout << "\nAll tables: ";
  for (int i = 0; i < tabMan->getCountTables(); i++) {
    std::cout << i + 1 << ") " << tabMan->getTableName(i) << '\n';
  }
  std::cout << '\n';
}
