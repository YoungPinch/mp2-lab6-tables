#pragma once
#include "TTable.h"

class OpenHashTable final : public TTable {
private:
  struct Bucket {
    std::shared_ptr<PolinomObj> data;
    bool isNone;
    bool isDeleted;
  };
  Bucket* table;
  unsigned int size;
  unsigned int curSize;
  unsigned int step = 7;

  unsigned int Hash(const std::string& key) {
    unsigned int h = 0;
    for (char c : key)
      h = (h * 1664525) + c + 1013904223;
    return h % size;
  }

public:
  OpenHashTable(unsigned int s) : size(s), curSize(0) {
    table = new Bucket[s]{ std::shared_ptr<PolinomObj>(), true, false };
  }

  ~OpenHashTable() { delete[] table; }

  void Insert(std::shared_ptr<PolinomObj> data) {
    if (size == curSize) // no free space
      throw -1;
    unsigned int h = Hash(data.get()->getName());
    while (!table[h].isDeleted) {
      if (table[h].isNone)
        break;
      if (table[h].data == data)
        return; // already exist
      else
        h = (h + step) % size;
    }
    table[h] = Bucket{ data, false, false };
    ++curSize;
  }

  std::shared_ptr<PolinomObj>* Find(std::string key){
    unsigned int h = Hash(key), i = 0;
    while (!(table[h].isDeleted || i == size)) {
      if (table[h].isNone)
        return nullptr;
      if (table[h].data.get()->getName() == key)
        return &table[h].data;
      else {
        h = (h + step) % size;
        ++i;
      }
    }
    return nullptr;
  }

  void Delete(std::string key){
    unsigned int h = Hash(key), i = 0;
    while (!(table[h].isDeleted || i == size)) {
      if (table[h].isNone)
        return;
      if (table[h].data.get()->getName() == key) {
        table[h].isDeleted = true;
        --curSize;
      }
      else {
        h = (h + step) % size;
        ++i;
      }
    }
  }

  void Print() {
    for (unsigned i = 0; i < size; ++i)
      if (table[i].isDeleted || table[i].isNone)
        std::cout << std::endl;
      else
        std::cout << table[i].data << std::endl;
  }

};

