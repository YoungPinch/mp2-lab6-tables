#pragma once
#include "TTable.h"

template <class TKey, class TData>
class OpenHashTable final : public TTable<class TKey, class TData> {
private:
  struct Bucket {
    TData data;
    bool isDeleted;
  };
  Bucket* table;
  unsigned int size;
  unsigned int curSize;
  unsigned int step = 7;

  unsigned int Hash(const TData& data) {
    unsigned int h = 0;
    for (char c : key)
      h = (h * 1664525) + c + 1013904223;
    return h % size;
  }

public:
  OpenHashTable(unsigned int s) : size(s), curSize(0) {
    table = new Bucket[s]{ nullptr, false };
  }

  ~OpenHashTable() { delete[] table; }

  void Insert(TData data) {
    if (size != curSize) // no free space
      return;
    unsigned int h = Hash(data);
    while (!table[h].isDeleted) {
      if (table[h].data == TData())
        break;
      if (table[h].data == data)
        return; // already exist
      else
        h = (h + step) % size;
    }
    table[h] = Bucket{ data, false };
    ++curSize;
  }

  TData& Find(TKey key){
    unsigned int h = Hash(key), i = 0;
    while (!(table[h].isDeleted || i == size))
      if (table[h].data == TData())
        return TData();
    if (table[h].data == key)
      return table[h].po;
    else {
      h = (h + step) % size;
      ++i;
    }
    return TData();
  }

  void Delete(TKey key){
    unsigned int h = Hash(name), i = 0;
    while (!(table[h].isDeleted || i == size))
      if (table[h].data == TData())
        return;
    if (table[h].data == key) {
      table[h].isDeleted = true;
      --curSize;
    }
    else {
      h = (h + step) % size;
      ++i;
    }
  }

  void Print() {
    for (unsigned i = 0; i < size; ++i)
      if (table[i].isDeleted || table[i].data == TData())
        std::cout << std::endl;
      else
        std::cout << table[i].data << std::endl;
  }

};

