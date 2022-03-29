#pragma once
#include "TTable.h"
#include <vector>

template <class TKey, class TData>
class ChainHashTable final : public TTable<class TKey, class TData> {
private:
  std::vector<TList<TData>> tables;
  int size;
  
  unsigned int ChainHashTable::Hash(const TKey key) {
    unsigned int h = 0;
    for (char c : key)
      h = (h * 1664525) + c + 1013904223;
    return h % size;
  }

public:
  ChainHashTable(int sz) : size(sz), tables(size) {}

  ~ChainHashTable() {
    tables.clear();
  }

  void Insert(TData data){
    if (Find(data) != TData())
      return;
    else
    {
      int index = Hash(data);
      tables[index].InsertFirst(data);
    }
  }

  TData& Find(TKey key){
    int index = Hash(key);
    for (auto it = tables[index].begin(); it != tables[index].end(); ++it)
      if (*it == key)
        return *it;
    return TData();
  }

  void Delete(TKey key) {
    int index = Hash(key);
    for (auto it = tables[index].begin(); it != tables[index].end(); ++it)
      if (*it == key)
        return tables[index].Delete(it);
  }

  void Print(){
    for (size_t i = 0; i < size; i++) {
      for (auto it = tables[i].begin(); it != tables[i].end(); ++it) {
        std::cout << "| " << *it << "| " << *it << std::endl;
      }
    }
  }

  
};

