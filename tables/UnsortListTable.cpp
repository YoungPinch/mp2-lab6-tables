#include "UnsortListTable.h"

void UnsortListTable::Insert(std::shared_ptr<PolinomObj> obj) {
  list.InsertFirst(obj);
}

std::shared_ptr<PolinomObj> UnsortListTable::Find(std::string name) {
  for (auto it = list.cbegin(); it != list.cend(); ++it)
    if ((*it)->GetName() == name)
      return *it;
  return nullptr;
}

void UnsortListTable::Delete(std::string _name) {
  for (auto it = list.begin(); it != list.end(); ++it)
    if ((*it)->GetName() == _name)
      list.Delete(it);
}

void UnsortListTable::Print() {
  for (auto it = list.cbegin(); it != list.cend(); ++it)
    std::cout << (*it)->GetName() << " : " << (*it)->GetStrPol() << std::endl;
}
