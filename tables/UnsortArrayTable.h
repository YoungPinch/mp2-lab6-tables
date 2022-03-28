#pragma once
#include <vector>
#include "TTable.h"

template <class TKey, class TData>
class UnsortArrayTable final : public TTable<class TKey, class TData> {
private:
  std::vector<TData> data;
  int size;

public:
  UnsortArrayTable(int sz) : size(sz), data(size) {}

  void Insert(TData data) {};

  TData& Find(TKey) {
    for (int i = 0; i < size; i++)
      if (data[i].get() != nullptr && data[i].get()->getName() == name)
        return data[i];
    return TData();  
  }

  void Delete(TKey name) {};

  void Print() {};
};

