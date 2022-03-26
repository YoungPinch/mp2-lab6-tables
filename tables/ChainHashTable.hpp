#pragma once
#include "TTable.hpp"

class ChainHashTable final : public TTable {
private:
  std::vector<TList<std::shared_ptr<PolinomObj>>> tables;
  int size;

  unsigned int Hash(const std::string& key) {
    unsigned int h = 0;
    for (char c : key)
      h = (h * 1664525) + c + 1013904223;
    return h % size;
  }

public:
  ChainHashTable(int sz) : size(sz), tables(size) {}

  std::shared_ptr<PolinomObj> Find(std::string key) override {
    int index = Hash(key);
    for (auto it = tables[index].begin(); it != tables[index].end(); ++it)
      if ((it)->get()->getName() == key)
        return *it;
    return nullptr;
  }

  void Insert(std::shared_ptr<PolinomObj> obj) override {
    if (Find(obj->getName()) == nullptr)
      return;
    else
    {
      int index = Hash(obj->getName());
      tables[index].InsertFirst(obj);
    }
  }

  void Delete(std::string key) override {
    int index = Hash(key);
    for (auto it = tables[index].begin(); it != tables[index].end(); ++it)
      if ((it)->get()->getName() == key)
        return tables[index].Delete(it);
  }

  void Print() override {

    // Нужно дописать

  }
};
