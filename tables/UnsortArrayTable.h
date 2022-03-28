#pragma once
#include <vector>
#include "TTable.h"

class UnsortArrayTable final : public TTable {
private:
  std::vector<std::shared_ptr<PolinomObj>> data;
  int maxInd;

public:
  UnsortArrayTable(int sz) : data(sz), maxInd(0) {}

  void Print();
  void Delete(std::string _name);
  std::shared_ptr<PolinomObj> Find(std::string name);
  void Insert(std::shared_ptr<PolinomObj> obj);
};

