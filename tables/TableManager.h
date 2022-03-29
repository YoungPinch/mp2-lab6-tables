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
  int curSize = 0;

  void Insert(std::shared_ptr<PolinomObj> obj) {
    for (int i = 0; i < COUNTTABLES; i++)
      tables[i]->Insert(obj);
  }

public:
  TableManager(int size) : curSize(size) {
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

