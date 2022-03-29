#pragma once
#include "TTable.h"
#include "AVLTreeTable.h"
#include "ChainHashTable.h"
#include "OpenHashTable.h"
#include "SortArrayTable.h"
#include "UnsortArrayTable.h"
#include "UnsortListTable.h"

#define COUNTTABLES 6

class TableManager {
private:
  enum TableKind {
    UNSORTARR = 0,
    SORTARR,
    OPENHASH,
    UNSORTLIST,
    AVLTREE,
    CHAINHASH
  };

  TTable<std::string, std::shared_ptr<PolinomObj>>* tables[COUNTTABLES];
  TableKind cur = UNSORTARR;
  int curSize, maxSize;

  void Insert(std::shared_ptr<PolinomObj> obj) {
    if (curSize != maxSize) {
      for (int i = 0; i < COUNTTABLES; i++)
        tables[i]->Insert(obj);
    }
    else {
      throw std::string("Too many objects in Table.");
    }
  }

  TableManager(const TableManager& obj) = delete; // Запрещено копирование

  TableManager operator=(const TableManager& obj) = delete; // Запрещено присваивать

public:
  static const std::vector<std::string> TableNames;

  TableManager(int size) : curSize(0), maxSize(size) {
    tables[UNSORTARR] = new UnsortArrayTable<std::string, std::shared_ptr<PolinomObj>>(size);
    tables[SORTARR] = new SortArrayTable<std::string, std::shared_ptr<PolinomObj>>(size);
    tables[OPENHASH] = new OpenHashTable<std::string, std::shared_ptr<PolinomObj>>(size);
    tables[CHAINHASH] = new ChainHashTable<std::string, std::shared_ptr<PolinomObj>>(size);
    tables[UNSORTLIST] = new UnsortListTable<std::string, std::shared_ptr<PolinomObj>>();
    tables[AVLTREE] = new AVLTable<std::string, std::shared_ptr<PolinomObj>>();
  }

  inline void SetActiveTable(TableKind ind) { cur = ind; }

  void Insert(std::string _name, Polinom pol) { Insert(PolinomObj::Create(_name, pol)); }

  void Insert(std::string _name, std::string _strPol) { Insert(PolinomObj::Create(_name, _strPol)); }

  Polinom Find(std::string name) { tables[cur]->Find(name)->getPol(); }

  void Delete(std::string _name) {
    for (int i = 0; i < COUNTTABLES; i++)
      tables[i]->Delete(_name);
  }

  void Print() { tables[cur]->Print(); }

  ~TableManager() {
    for (int i = 0; i < COUNTTABLES; i++)
      delete tables[i];
  }
};

const std::vector<std::string> TableManager::TableNames = { "Unsort Array Table", "Sort Array Table",
                                                            "Open Hash Table", "Chain Hash Table",
                                                            "Unsort List Table", "AVL-Tree Table" };
