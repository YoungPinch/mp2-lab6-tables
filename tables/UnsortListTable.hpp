#pragma once
#include "TTable.hpp"

class UnsortListTable final : public TTable {
private:
  TList<std::shared_ptr<PolinomObj>> list;
  friend class PolinomObj;
public:
  UnsortListTable() {} // Добавить реализацию

  void Insert(std::shared_ptr<PolinomObj> obj) {
    list.InsertFirst(obj);
  }

  std::shared_ptr<PolinomObj> Find(std::string name) {
    for (auto it = list.cbegin(); it != list.cend(); ++it)
      if ((*it)->getName() == name)
        return *it;
    return nullptr;
  }

  void Delete(std::string _name) {
    for (auto it = list.begin(); it != list.end(); ++it)
      if ((*it)->getName() == _name)
        list.Delete(it);
  }
};
