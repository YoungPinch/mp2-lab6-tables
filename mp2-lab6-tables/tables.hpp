#pragma once
#include <string.h>
#include "polinom.hpp"
#define COUNTTABLES 6

class PolinomObj {
private:
  std::string name;
  std::string strPol;
  Polinom* pol;

  PolinomObj(std::string _name, std::string _strPol);
  PolinomObj(std::string _name, Polinom* pol);

public:
  static PolinomObj* Create(std::string _name, std::string _strPol) {
    return &PolinomObj(_name, _strPol);
  }

  static PolinomObj* Create(std::string _name, Polinom* pol) {
    return &PolinomObj(_name, pol);
  }
};

class TableManager {
private:
  TTable* activeTable;
  TTable* tables[COUNTTABLES];

  enum TableKind
  {
    SORTARR = 0,
    UNSORTARR,
    BINTREE,
    UNSORTLIST,
    CHAINHASH,
    OPENHASH
  };

  void Insert(PolinomObj* obj) {
    for (int i = 0; i < COUNTTABLES; i++)
      tables[i]->Insert(obj);
  }

public:
  TableManager() {
    tables[SORTARR] = new SortArrayTable();
    tables[UNSORTARR] = new UnsortArrayTable();
    tables[BINTREE] = new BinaryTable();
    tables[UNSORTLIST] = new UnsortListTable();
    tables[CHAINHASH] = new ChainHashTable();
    tables[OPENHASH] = new OpenHashTable();
  }

  inline void SetActiveTable(int ind) { activeTable = tables[ind]; }

  void Insert(std::string _name, Polinom* pol) { Insert(PolinomObj::Create(_name, pol)); }

  void Insert(std::string _name, std::string _strPol) { Insert(PolinomObj::Create(_name, _strPol)); }

  const Polinom& Find(std::string name) { return activeTable->Find(name); }

  void Delete(std::string _name);

  void Print() { std::cout << activeTable; }

};

class TTable {
protected:
  virtual PolinomObj* FindObj(std::string name);
public:
  virtual void Delete(std::string _name);
  virtual const Polinom& Find(std::string name);
  virtual void Insert(PolinomObj* obj);
  virtual friend std::ostream& operator<<(std::ostream& os, const TTable* table);
  virtual ~TTable() = 0;
};

class SortArrayTable final : public TTable {
private:
  PolinomObj** arr;
public:
};

class UnsortArrayTable final : public TTable {
private:
  PolinomObj** arr;
public:
};

class BinaryTable final : public TTable {
private:
public:
};

class UnsortListTable final : public TTable {
private:
  TList<PolinomObj*> list;
public:
};

class ChainHashTable final : public TTable {
private:
public:
};

class OpenHashTable final : public TTable {
private:
public:
};
