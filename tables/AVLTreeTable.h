#pragma once
#include "TTable.h"

class AVLTable final : public TTable {
private:
public:
  AVLTable() { };
  void Print();
  void Delete(std::string _name);
  std::shared_ptr<PolinomObj> Find(std::string name);
  void Insert(std::shared_ptr<PolinomObj> obj);
};
