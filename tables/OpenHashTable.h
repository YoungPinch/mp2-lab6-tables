#pragma once
#include "TTable.h"

class OpenHashTable final : public TTable {
private:
  struct Bucket {
    std::shared_ptr<PolinomObj> po;
    bool isDeleted;
  };
  Bucket* table;
  unsigned int size;
  unsigned int curSize;
  unsigned int step = 7;

  unsigned int Hash(const std::string& key);
public:
  OpenHashTable(unsigned int s) : size(s) {
    table = new Bucket[s]{ nullptr, false };
    curSize = 0;
  }
  ~OpenHashTable() { delete[] table; }

  void Insert(std::shared_ptr<PolinomObj> obj);
  std::shared_ptr<PolinomObj> Find(std::string name);
  void Delete(std::string name);
  void Print();
};

