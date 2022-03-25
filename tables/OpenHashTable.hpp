#pragma once
#include "tables.hpp"

class OpenHashTable final : public TTable {
private:
  struct Bucket {
    std::shared_ptr<PolinomObj> po;
    bool isDeleted;
  };

  Bucket* table;
  unsigned int size;
  unsigned int step = 7;

  unsigned int Hash(std::string key) { // HashLy
    unsigned int h = 0;
    for (char c : key)
      h = (h * 1664525) + c + 1013904223;
    return h % size;
  }

public:
  OpenHashTable(unsigned int s) {
    table = new Bucket[s]{ nullptr, false };
    size = s;
    size = 0;
  }
  void Insert(std::shared_ptr<PolinomObj> obj) {
    unsigned int h = Hash(obj->getName());
    while (!table[h].isDeleted)
      if (table[h].po == nullptr)
        break;
    if (table[h].po->getName() == obj->getName())
      throw - 1; // already exist
    else
      h = (h + step) % size;

    table[h] = Bucket{ obj, false };
    ++size;
  }
  const Polinom& Find(std::string name) {
    unsigned int h = Hash(name), i = 0;
    while (!(table[h].isDeleted || i == size))
      if (table[h].po == nullptr)
        throw - 1;
    if (table[h].po->getName() == name)
      return table[h].po->getPol();
    else {
      h = (h + step) % size;
      ++i;
    }
    throw - 1;
  }
  void Delete(std::string name) {
    unsigned int h = Hash(name), i = 0;
    while (!(table[h].isDeleted || i == size))
      if (table[h].po == nullptr)
        return;
    if (table[h].po->getName() == name) {
      table[h].isDeleted = true;
      --size;
    }
    else {
      h = (h + step) % size;
      ++i;
    }
  }
  ~OpenHashTable() {
    delete[] table;
  }
};
