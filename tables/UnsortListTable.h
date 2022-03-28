#pragma once
#include "TTable.h"
#include "list.hpp"

template<class TKey, class TData>
class UnsortListTable final : public TTable<class TKey, class TData> {
private:
  TList<TData> list;

public:
  UnsortListTable() {}

  void Insert(TData data) {
    list.InsertFirst(data);
  }

 TData& Find(TKey name) {
    for (auto it = list.cbegin(); it != list.cend(); ++it)
      if (*it == name)
        return *it;
    return TData();
  }

 void Delete(TKey name) {
   for (auto it = list.begin(); it != list.end(); ++it)
     if (*it == name)
       list.Delete(it);
 }

 void Print() {
   for (auto it = list.cbegin(); it != list.cend(); ++it)
     std::cout << *it << std::endl;
 }

};

