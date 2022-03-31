#pragma once
#include "TTable.h"
#include "list.hpp"

class UnsortListTable final : public TTable {
private:
  TList<std::shared_ptr<PolinomObj>> list;

public:
  UnsortListTable() {}

  void Insert(std::shared_ptr<PolinomObj> data) {
    list.InsertFirst(data);
  }

  std::shared_ptr<PolinomObj>* Find(std::string name) {
    for (auto it = list.begin(); it != list.end(); ++it)
      if (*it == name)
        return &(*it);
    return nullptr;
  }

 void Delete(std::string name) {
   for (auto it = list.begin(); it != list.end(); ++it)
     if (*it == name)
       list.Delete(it);
 }

 void Print() {
   for (auto it = list.cbegin(); it != list.cend(); ++it)
     std::cout << *it << std::endl;
 }

};

