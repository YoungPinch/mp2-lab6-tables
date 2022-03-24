#pragma once
#include <string.h>
#include <memory>
#include "polinom.hpp"

#define COUNTTABLES 6

class PolinomObj {
private:
  std::string name;
  std::string strPol;
  Polinom pol;

  PolinomObj(std::string _name, std::string _strPol);
  PolinomObj(std::string _name, Polinom pol);

public:
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

  void Insert(std::shared_ptr<PolinomObj> obj) {
    for (int i = 0; i < COUNTTABLES; i++)
      tables[i]->Insert(obj);
  }

public:
  TableManager() {
    tables[SORTARR] = new SortArrayTable();
    tables[UNSORTARR] = new UnsortArrayTable();
    tables[BINTREE] = new BinaryTable();
    tables[UNSORTLIST] = new UnsortListTable(24);
    tables[CHAINHASH] = new ChainHashTable();
    tables[OPENHASH] = new OpenHashTable(24);
  }

  inline void SetActiveTable(int ind) { activeTable = tables[ind]; }

  void Insert(std::string _name, Polinom pol) { Insert(PolinomObj::Create(_name, pol)); }

  void Insert(std::string _name, std::string _strPol) { Insert(PolinomObj::Create(_name, _strPol)); }

  const Polinom& Find(std::string name) { return activeTable->Find(name); }

  void Delete(std::string _name);

  void Print() { std::cout << activeTable; }

};

class TTable {
protected:
  unsigned int MAX_SIZE;
  virtual std::shared_ptr<PolinomObj> FindObj(std::string name);
public:
  virtual void Delete(std::string _name);
  virtual const Polinom& Find(std::string name);
  virtual void Insert(std::shared_ptr<PolinomObj> obj);
  virtual friend std::ostream& operator<<(std::ostream& os, const TTable* table);
  virtual ~TTable() = 0;
};

class SortArrayTable final : public TTable {
private:
  std::shared_ptr<PolinomObj>* arr;
public:
};

class UnsortArrayTable final : public TTable {
private:
  std::shared_ptr<PolinomObj>* arr;
public:
};

class BinaryTable final : public TTable {
private:
public:
};

class UnsortListTable final : public TTable {
private:
  TList<std::shared_ptr<PolinomObj>> list;
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
