#pragma once
#include "tables.hpp"

class UnsortListTable final : public TTable {
private:
  TList<std::shared_ptr<PolinomObj>> list;
  friend class PolinomObj;
public:
  UnsortListTable(unsigned int s) { TTable::MAX_SIZE = s; };

  void Insert(std::shared_ptr<PolinomObj> obj) {
    if (list.GetSize() == MAX_SIZE)
      throw - 1;
    list.InsertFirst(obj);
  }
  const Polinom& Find(std::string name) {
    for (auto it = list.cbegin(); it != list.cend(); ++it)
      if ((*it)->getName() == name)
        return (*it)->getPol();
    throw - 1;
  }
  void Delete(std::string _name) {
    for (auto it = list.cbegin(); it != list.cend(); ++it)
      if ((*it)->getName() == _name)
        list.Delete(it);
  }
};
