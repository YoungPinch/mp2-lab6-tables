#pragma once
#include <vector>
#include "TTable.h"

template <class TKey, class TData>
class UnsortArrayTable final : public TTable<class TKey, class TData> {
private:
  std::vector<TData> data;
  int maxInd;

public:
  UnsortArrayTable(int sz) : data(sz), maxInd(0) {}

  void Insert(TData _data) {
    if (data.size() == maxInd)
      throw 1;
    for (int i = 0; i < data.size(); i++) {
      if (data[i] == TData()) {
        data[i] = _data;
        if (i == maxInd)
          maxInd++;
        break;
      }
    }
  }

  TData& Find(TKey name) {
    for (int i = 0; i < size; i++)
      if (data[i] != TData() && data[i] == name)
        return data[i];
    return TData();  
  }

  void Delete(TKey name) {
    int i = 0;
    for (; i < maxInd; i++) {
      if (data[i] != TData() && data[i] == name) {
        data[i] = TData();
        break;
      }
    }

    if (i == maxInd - 1) {
      for (; i > 0; i--) {
        if (data[i] == TData())
          maxInd--;
        else
          break;
      }
    }
  }

  void Print() {
    for (int i = 0; i < maxInd; i++) {
      if (data[i] != TData())
        std::cout << data[i];
      else
        std::cout << '\n';
    }
  }
};

