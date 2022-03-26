#pragma once
#include <string.h>
#include <memory>
#include "polinom.hpp"

#define COUNTTABLES 6

struct PolinomObj {
private:
  PolinomObj(std::string _name, std::string _strPol);
  PolinomObj(std::string _name, Polinom pol);

public:
  std::string name;
  std::string strPol;
  Polinom pol;

  static std::shared_ptr<PolinomObj> Create(std::string _name, std::string _strPol) {
    return std::make_shared<PolinomObj>(_name, _strPol);
  }

  static std::shared_ptr<PolinomObj> Create(std::string _name, Polinom pol) {
    return std::make_shared<PolinomObj>(_name, pol);
  }

  const std::string& getName() { return name; }
  const std::string& getStrPol() { return strPol; }
  const Polinom& getPol() { return pol; }

};

class TTable {
public:
  virtual void Print();
  virtual void Delete(std::string _name);
  virtual std::shared_ptr<PolinomObj> Find(std::string name);
  virtual void Insert(std::shared_ptr<PolinomObj> obj);
  virtual ~TTable() = 0;
};

class TableManager {
private:
  TTable* activeTable;
  TTable* tables[COUNTTABLES];
  int curSize = 0;

  enum TableKind
  {
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

class UnsortArrayTable final : public TTable {
private:
  std::shared_ptr<PolinomObj>* arr;
public:
  UnsortArrayTable(int sz);
};

class AVLTable final : public TTable {
private:
public:
};
