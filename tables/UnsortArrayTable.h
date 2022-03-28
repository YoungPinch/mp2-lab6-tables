#pragma once
#include <vector>
#include "TTable.h"

class UnsortArrayTable final : public TTable {
private:
  std::vector<std::shared_ptr<PolinomObj>> data;
  int size;

public:
  UnsortArrayTable(int sz) : size(sz), data(size) {}

  void Print();
  void Delete(std::string _name);
  std::shared_ptr<PolinomObj> Find(std::string name);
  void Insert(std::shared_ptr<PolinomObj> obj);
};

