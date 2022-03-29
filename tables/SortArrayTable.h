#pragma once
#include "TTable.h"
#include <vector>

template <class TKey, class TData>
class SortArrayTable final : public TTable<class TKey, class TData> {
private:
  std::vector<TData> row;
  int countElem;

  void AddRewrite(int index) {
    for (int i = countElem - 1; i >= index; i--)
      row[i] = row[i - 1];
  }

  void DelRewrite(int index) {
    for (size_t i = index; i < countElem; i++) {
      row[i] = row[i + 1];
    }
  }

public:
  SortArrayTable(int sz) : countElem(0), row(sz) {}

  void Insert(TData data){
    int left = 0;
    int right = countElem;
    int lastCompare = 0; //1 - left 2 - right
    int mid = 0;
    if (countElem == row.size())
    {
      std::cout << "MAX" << std::endl;
      return;
    }
    while (left <= right) {
      mid = (right + left) / 2;
      if (row[mid] == TData()) {
        row[mid] = data;
        countElem++;
        return;
      }
      if (data == row[mid])
        return;
      if (data > row[mid]) {
        left = mid + 1;
        lastCompare = 1;
      }
      else {
        right = mid - 1;
        lastCompare = 2;
      }
    }
    countElem++;
    if (lastCompare == 1) {
      AddRewrite(left + 1);
      row[left] = data;

    }
    else {
      AddRewrite(right + 1);
      row[right + 1] = data;
    }
  }

  TData& Find(TKey key){
    int left = 0;
    int right = countElem - 1;
    int mid = 0;
    while (left <= right) {
      mid = (right + left) / 2;
      if (row[mid] == key)
        return row[mid];
      else if (row[mid] < key)
        left = mid + 1;
      else
        right = mid - 1;
    }
    return TData();
  }

  void Delete(TKey key) {
    int left = 0;
    int right = countElem - 1;
    int mid = 0;
    if (countElem == 0)
      return;
    while (left <= right) {
      mid = (right + left) / 2;
      if (row[mid] == key) {
        row[mid] = TData();
        countElem--;
        DelRewrite(mid);
        break;
      }
      else if (row[mid] < key)
        left = mid + 1;
      else
        right = mid - 1;
    }
  }
  
  void Print() {
    for (size_t i = 0; i < countElem; i++)
    {
      std::cout << "|" << row[i] << "|" << row[i] << std::endl;
    }
  }

};

