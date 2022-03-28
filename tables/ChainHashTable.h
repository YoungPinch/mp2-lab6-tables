#pragma once
#include "TTable.h"
#include <vector>

class ChainHashTable final : public TTable {
private:
  std::vector<TList<std::shared_ptr<PolinomObj>>> tables;
  int size;

  unsigned int Hash(const std::string& key);
public:
  ChainHashTable(int sz) : size(sz), tables(size) {}

  std::shared_ptr<PolinomObj> Find(std::string key) override;
  void Insert(std::shared_ptr<PolinomObj> obj) override;
  void Delete(std::string key) override;
  void Print() override;
};

