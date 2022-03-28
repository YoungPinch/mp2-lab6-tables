#pragma once
#include "TTable.h"
#include "AVLTreeTable.h"
#include "ChainHashTable.h"
#include "OpenHashTable.h"
#include "SortArrayTable.h"
#include "UnsortArrayTable.h"
#include "UnsortListTable.h"

class TableManager {
private:
  TTable* activeTable;
  TTable* tables[COUNTTABLES];
  int curSize = 0;

  enum TableKind {
    UNSORTARR = 0,
    SORTARR,
    OPENHASH,
    UNSORTLIST,
    AVLTREE,
    CHAINHASH
  };

  void Insert(std::shared_ptr<PolinomObj> obj) {
    for (int i = 0; i < COUNTTABLES; i++)
      tables[i]->Insert(obj);
  }

public:
  TableManager(int size) : curSize(size) {

    tables[UNSORTARR] = new UnsortArrayTable(size);
    tables[SORTARR] = new SortArrayTable(size);
    tables[OPENHASH] = new OpenHashTable(size);
    tables[CHAINHASH] = new ChainHashTable(size);
    tables[UNSORTLIST] = new UnsortListTable();
    tables[AVLTREE] = new AVLTable();
  }

  inline void SetActiveTable(int ind) { activeTable = tables[ind]; }

  void Insert(std::string _name, Polinom pol) { Insert(PolinomObj::Create(_name, pol)); }

  void Insert(std::string _name, std::string _strPol) { Insert(PolinomObj::Create(_name, _strPol)); }

  std::shared_ptr<PolinomObj> Find(std::string name) { activeTable->Find(name); }

  void Delete(std::string _name) {
    for (int i = 0; i < COUNTTABLES; i++)
      tables[i]->Delete(_name);
  }

  void Print() { activeTable->Print(); }

};

