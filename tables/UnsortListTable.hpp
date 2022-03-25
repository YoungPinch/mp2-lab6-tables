#pragma once
#include "tables.hpp"

class UnsortListTable final : public TTable {
private:
  TList<std::shared_ptr<PolinomObj>> list;
  friend class PolinomObj;
public:
  UnsortListTable() {} // Добавить реализацию

  void Insert(std::shared_ptr<PolinomObj> obj) {
    list.InsertFirst(obj);
  }

  const Polinom& Find(std::string name) {
    for (auto it = list.cbegin(); it != list.cend(); ++it)
      if ((*it)->getName() == name)
        return (*it)->getPol();
    throw - 1;
  }

  // Временное решение
  /*void Delete(std::string _name) {
    for (auto it = list.cbegin(); it != list.cend(); ++it)
      if ((*it)->getName() == _name)
        list.Delete(it);
  }*/
};
