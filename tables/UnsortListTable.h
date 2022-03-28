#pragma once
#include "TTable.h"

class UnsortListTable final : public TTable {
private:
  TList<std::shared_ptr<PolinomObj>> list;

public:
  UnsortListTable() {}

  void Insert(std::shared_ptr<PolinomObj> obj);
  std::shared_ptr<PolinomObj> Find(std::string name);
  void Delete(std::string _name);
  void Print();
};

