#pragma once
#include "TTable.hpp"

class UnsortArrayTable final : public TTable {
private:
  std::shared_ptr<PolinomObj>* arr;
public:
  UnsortArrayTable(int sz);
};
