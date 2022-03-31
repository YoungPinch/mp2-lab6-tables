#pragma once
#include "TTable.h"
#include <vector>

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
  ChainHashTable(int sz) : size(sz), tables(sz) {}

  ~ChainHashTable() {
    tables.clear();
  }

  void Insert(std::shared_ptr<PolinomObj> data){
    if (Find(data.get()->getName()) != nullptr)
      return;
    else
    {
      int index = Hash(data.get()->getName());
      tables[index].InsertFirst(data);
    }
  }

  std::shared_ptr<PolinomObj>* Find(std::string key){
    int index = Hash(key);
    for (auto it = tables[index].begin(); it != tables[index].end(); ++it)
      if (it->get()->getName() == key)
        return &(*it);
    return nullptr;
  }

  void Delete(std::string key) {
    int index = Hash(key);
    for (auto it = tables[index].begin(); it != tables[index].end(); ++it)
      if (*it == key)
        tables[index].Delete(it);
  }

  void Print(){
    for (size_t i = 0; i < size; i++) {
      for (auto it = tables[i].begin(); it != tables[i].end(); ++it) {
        std::cout << *it << std::endl;
      }
    }
  }

  
};

