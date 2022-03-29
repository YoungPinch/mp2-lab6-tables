#pragma once
#include "TTable.h"
#include <vector>

template <class TKey, class TData>
class SortArrayTable final : public TTable<class TKey, class TData> {
private:
  std::vector<TData> row;
  int size;

  void Rewrite(int index) {
    for (int i = index; i < row.size() - 1; i++)
      row[i] = row[i + 1];
  }

public:
  SortArrayTable(int sz) : size(sz), row(size) {}

  void Insert(TData data){
    int left = 0;
    int right = size - 1;
    int mid = 0;
    while (left <= right) {
      mid = (right + left) / 2;
      if (data == row[mid])
        return;
      else if (data > row[mid])
        left = mid + 1;
      else
        right = mid - 1;
    }
    row[left] = data;
  }

  TData& Find(TKey key){
    int left = 0;
    int right = size - 1;
    int mid = 0;
    while (left <= right) {
      mid = (right + left) / 2;
      if (key == row[mid])
        return row[mid];
      else if (key > row[mid])
        left = mid + 1;
      else
        right = mid - 1;
    }
    return TData();
  }

  void Delete(TKey key) {
    int left = 0;
    int right = size - 1;
    int mid = 0;
    while (left <= right) {
      mid = (right + left) / 2;
      if (key == row[mid]) {
        delete row[mid];
        Rewrite(mid);
        break;
      }
      else if (key > row[mid])
        left = mid + 1;
      else
        right = mid - 1;
    }
  }
  
  void Print() {};

};

