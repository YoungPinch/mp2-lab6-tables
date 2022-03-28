#include "OpenHashTable.h"

unsigned int OpenHashTable::Hash(const std::string& key) {
  unsigned int h = 0;
  for (char c : key)
    h = (h * 1664525) + c + 1013904223;
  return h % size;
}

void OpenHashTable::Insert(std::shared_ptr<PolinomObj> obj) {
  if (size != curSize) // no free space
    return;
  unsigned int h = Hash(obj->GetName());
  while (!table[h].isDeleted) {
    if (table[h].po == nullptr)
      break;
    if (table[h].po->GetName() == obj->GetName())
      return; // already exist
    else
      h = (h + step) % size;
  }
  table[h] = Bucket{ obj, false };
  ++curSize;
}

std::shared_ptr<PolinomObj> OpenHashTable::Find(std::string name) {
  unsigned int h = Hash(name), i = 0;
  while (!(table[h].isDeleted || i == size))
    if (table[h].po == nullptr)
      return nullptr;
  if (table[h].po->GetName() == name)
    return table[h].po;
  else {
    h = (h + step) % size;
    ++i;
  }
  return nullptr;
}

void OpenHashTable::Delete(std::string name) {
  unsigned int h = Hash(name), i = 0;
  while (!(table[h].isDeleted || i == size))
    if (table[h].po == nullptr)
      return;
  if (table[h].po->GetName() == name) {
    table[h].isDeleted = true;
    --curSize;
  }
  else {
    h = (h + step) % size;
    ++i;
  }
}

void OpenHashTable::Print() {
  for (unsigned i = 0; i < size; ++i)
    if (table[i].isDeleted || table[i].po == nullptr)
      std::cout << std::endl;
    else
      std::cout << table[i].po->GetName() << " : " << table[i].po->GetStrPol() << std::endl;
}
