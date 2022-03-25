#pragma once
#include <string.h>
#include <memory>
#include <vector>
#include "polinom.hpp"

#define COUNTTABLES 6

struct PolinomObj {
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
  TableManager(int size) {
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

  const Polinom& Find(std::string name) { return activeTable->Find(name); }

  void Delete(std::string _name);

  void Print() { std::cout << activeTable; }

};

class TTable {
protected:
  virtual std::shared_ptr<PolinomObj> FindObj(std::string name);
public:
  virtual void Print();
  virtual void Delete(std::string _name);
  virtual const Polinom& Find(std::string name);
  virtual void Insert(std::shared_ptr<PolinomObj> obj);
  virtual ~TTable() = 0;
};

class UnsortArrayTable final : public TTable {
private:
    std::shared_ptr<PolinomObj>* arr;
public:
  UnsortArrayTable(int sz);
};

class SortArrayTable final : public TTable {
private:
    std::vector<std::shared_ptr<PolinomObj>> row;
    int size;
    void Rewrite(int index);
public:
    SortArrayTable(int sz):size(sz), row(size)
    {};
    const Polinom* Find(std::string key) override;
    void Insert(std::shared_ptr<PolinomObj> obj) override;
    void Delete(std::string key) override;
    void Print() override;
};

class ChainHashTable final : public TTable {
private:
    std::vector<TList<std::shared_ptr<PolinomObj>>> tables;
    int size;
public:
    ChainHashTable(int sz) :size(sz), tables(size)
    {};
    unsigned int Hash(const std::string& key);
    const Polinom* Find(std::string key) override;
    void Insert(std::shared_ptr<PolinomObj> obj) override;
    void Delete(std::string key) override;
    void Print() override;
};

class OpenHashTable final : public TTable {
private:
public:
};

class UnsortListTable final : public TTable {
private:
  TList<std::shared_ptr<PolinomObj>> list;
public:
};

class AVLTable final : public TTable {
private:
public:
};
