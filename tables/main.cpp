#include "ChainHashTable.h"

int main()
{
  ChainHashTable table(10);
  table.Insert(PolinomObj::Create("a", "3x2y5z2 - 77y5z4"));
  table.Insert(PolinomObj::Create("c", "3x2y5z2 + 77y5z4"));
  table.Insert(PolinomObj::Create("f", "3x2y5z2 + 77y5z4"));
  table.Insert(PolinomObj::Create("o", "77y5z4"));
  table.Insert(PolinomObj::Create("i", "277x2"));
  table.Insert(PolinomObj::Create("d", "z5"));
  table.Insert(PolinomObj::Create("al", "3x2y5z2 - 77y5z4"));
  table.Insert(PolinomObj::Create("l", "5z4"));
  table.Print();
}