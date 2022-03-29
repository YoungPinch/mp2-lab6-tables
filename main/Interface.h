#pragma once
#include "TableManager.h"

class Interface {

  void(Interface::* modeptr[12])() = { &Interface::mode0, &Interface::mode1, &Interface::mode2,
                                      &Interface::mode3, &Interface::mode4, &Interface::mode5,
                                      &Interface::mode6, &Interface::mode7, &Interface::mode8,
                                      &Interface::mode9, &Interface::mode10, &Interface::mode11 };

  bool showStats = false;

  bool executableFunc() {
    
    return false;
  }

  void mode0() {

  }
  void mode1() {

  }
  void mode2() {

  }
  void mode3() {

  }
  void mode4() {

  }
  void mode5() {

  }
  void mode6() {

  }
  void mode7() {

  }
  void mode8() {

  }
  void mode9() {

  }
  void mode10() {

  }
  void mode11() {

  }

public:
  static const std::vector<std::string> FuncNames;

  static void Cleaner() {
    while (getchar() != '\n');
    std::cin.clear();
  }

  static int Clamp(int border1, int border2) {
    int choice = INT_MIN;
    while (choice < border1 || choice > border2) {
      std::cin >> choice;
      if (choice < border1 || choice > border2) {
        std::cout << "Invalid number entered. Try again\n";
        Cleaner();
      }
    }
  }

  Interface() { }

  void Run() { while (executableFunc()); }

};

static const std::vector<std::string> FuncNames = { "Alg Polinoms", "Print Table", "Insert Elem",
                                                    "Find Elem","Delete Elem", "Change Active Table",
                                                    "Change Showing Of Stats", "Clearing Screen",
                                                    "Settings", "Help", "Exit" };
