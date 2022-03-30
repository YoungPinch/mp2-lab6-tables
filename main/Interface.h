#pragma once
#include "TableManager.h"

class Interface {

  bool showStats = false;
  TableManager* tabMan = nullptr;
  static const std::vector<std::string> FuncNames;
  void(Interface::* modeptr[12])() = { &Interface::mode0, &Interface::mode1, &Interface::mode2,
                                      &Interface::mode3, &Interface::mode4, &Interface::mode5,
                                      &Interface::mode6, &Interface::mode7, &Interface::mode8,
                                      &Interface::mode9, &Interface::mode10, &Interface::mode11 };

  bool executableFunc();
  void printFunctions();
  void setTableManager();

  void mode0(); void mode1(); void mode2();
  void mode3(); void mode4(); void mode5();
  void mode6(); void mode7(); void mode8();
  void mode9(); void mode10(); void mode11();

public:
  Interface() {}

  static void Cleaner();
  static int Clamp(int border1, int border2);

  static const std::vector<std::string> FuncNames;

  void Run() { while (executableFunc()); }

};

const std::vector<std::string> Interface::FuncNames = { "Alg Polinoms", "Print Table",
                                                        "Insert Elem", "Find Elem","Delete Elem"
                                                        "Cur Information", "Change Active Table",
                                                        "Change Showing Of Stats", "Clearing Screen",
                                                        "Settings", "Help", "Exit" };
