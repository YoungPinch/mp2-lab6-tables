#pragma once
#include "TTable.h"
#include <vector>

class SortArrayTable final : public TTable {
private:
  std::vector<std::shared_ptr<PolinomObj>> row;
  int size;

  void Rewrite(int index);

public:
  SortArrayTable(int sz) : size(sz), row(size) {}

  std::shared_ptr<PolinomObj> Find(std::string key) override;
  void Insert(std::shared_ptr<PolinomObj> obj) override;
  void Delete(std::string key) override;
  void Print() override;
};

