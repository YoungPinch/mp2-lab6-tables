#include <iostream>
#include "Interface.h"

void useInterface() {
  Interface gui;
  gui.Run();
  system("pause");
}

int main() {
  useInterface();
  return 0;
}
