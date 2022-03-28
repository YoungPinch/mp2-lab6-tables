#include "UnsortArrayTable.h"

void UnsortArrayTable::Print() {

}

void UnsortArrayTable::Delete(std::string _name) {

}

std::shared_ptr<PolinomObj> UnsortArrayTable::Find(std::string name) {
  for (int i = 0; i < size; i++)
    if (data[i].get() != nullptr && data[i].get()->getName() == name)
      return data[i];
  return nullptr;
}

void UnsortArrayTable::Insert(std::shared_ptr<PolinomObj> obj) {

}
