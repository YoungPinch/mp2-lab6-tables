#include "UnsortArrayTable.h"

void UnsortArrayTable::Print() {
  for (int i = 0; i < maxInd; i++) {
    if (data[i] != nullptr)
      std::cout << data[i];
    else
      std::cout << '\n';
  }
}

void UnsortArrayTable::Delete(std::string _name) {
  int i = 0;
  for (; i < maxInd; i++) {
    if (data[i].get() != nullptr && data[i].get()->getName() == _name) {
      data[i].reset();
      break;
    }
  }
  // Убираем из рассмотрения все nullptr в конце
  if (i == maxInd - 1) { 
    for (; i > 0; i--) {
      if (data[i].get() == nullptr)
        maxInd--;
      else
        break;
    }
  }
}

std::shared_ptr<PolinomObj> UnsortArrayTable::Find(std::string name) {
  for (int i = 0; i < maxInd; i++)
    if (data[i].get() != nullptr && data[i].get()->getName() == name)
      return data[i];
  return nullptr;
}

void UnsortArrayTable::Insert(std::shared_ptr<PolinomObj> obj) {
  if (data.size() == maxInd)
    throw 1;
  for (int i = 0; i < data.size(); i++) {
    if (data[i].get() == nullptr) {
      data[i] = obj;
      if (i == maxInd)
        maxInd++;
      break;
    }
  }
}
