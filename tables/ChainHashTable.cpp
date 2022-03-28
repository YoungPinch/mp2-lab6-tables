#include "ChainHashTable.h"

unsigned int ChainHashTable::Hash(const std::string& key) {
  unsigned int h = 0;
  for (char c : key)
    h = (h * 1664525) + c + 1013904223;
  return h % size;
}

std::shared_ptr<PolinomObj> ChainHashTable::Find(std::string key) {
  int index = Hash(key);
  for (auto it = tables[index].begin(); it != tables[index].end(); ++it)
    if ((it)->get()->GetName() == key)
      return *it;
  return nullptr;
}

void ChainHashTable::Insert(std::shared_ptr<PolinomObj> obj) {
  if (Find(obj->GetName()) == nullptr)
    return;
  else
  {
    int index = Hash(obj->GetName());
    tables[index].InsertFirst(obj);
  }
}

void ChainHashTable::Delete(std::string key) {
  int index = Hash(key);
  for (auto it = tables[index].begin(); it != tables[index].end(); ++it)
    if ((it)->get()->GetName() == key)
      return tables[index].Delete(it);
}

void ChainHashTable::Print() {
  for (size_t i = 0; i < size; i++)
  {
    for (auto it = tables[i].begin(); it != tables[i].end(); ++it)
    {
      std::cout << *it;
    }
  }
}
