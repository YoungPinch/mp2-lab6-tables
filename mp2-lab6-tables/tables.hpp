#pragma once
#include <string.h>
#include "polinom.hpp"

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

class TTable {
private: 
  void ShowTableHeader();
protected:
  virtual PolinomObj* FindObj(std::string name);
public:
  virtual void Delete(std::string _name);
  virtual const Polinom& Find(std::string name);
  virtual void Insert(std::string _name, std::string _strPol);
  virtual void Insert(std::string _name, Polinom* pol);
  virtual void Show();
  virtual ~TTable() = 0;
};

class SortArrayTable final : public TTable {
private:
  virtual PolinomObj* FindObj(std::string name);

  PolinomObj* arr[];

public:
  void Show();
  void Delete(std::string _name);
  const Polinom& Find(std::string name);
  void Insert(std::string _name, std::string _strPol);
  void Insert(std::string _name, Polinom* pol);
};

class UnsortArrayTable final : public TTable {
private:
  virtual PolinomObj* FindObj(std::string name);

  PolinomObj* arr[];

public:
  void Show();
  void Delete(std::string _name);
  const Polinom& Find(std::string name);
  void Insert(std::string _name, std::string _strPol);
  void Insert(std::string _name, Polinom* pol);
};

class UnsortListTable final : public TTable {
private:
  virtual PolinomObj* FindObj(std::string name);

  TList<PolinomObj*> list;

public:
  void Show();
  void Delete(std::string _name);
  const Polinom& Find(std::string name);
  void Insert(std::string _name, std::string _strPol);
  void Insert(std::string _name, Polinom* pol);
};

class BinaryTable final : public TTable {
private:
  virtual PolinomObj* FindObj(std::string name);
public:
  void Show();
  void Delete(std::string _name);
  const Polinom& Find(std::string name);
  void Insert(std::string _name, std::string _strPol);
  void Insert(std::string _name, Polinom* pol);
};

class ChainHashTable final : public TTable {
private:
  virtual PolinomObj* FindObj(std::string name);
public:
  void Show();
  void Delete(std::string _name);
  const Polinom& Find(std::string name);
  void Insert(std::string _name, std::string _strPol);
  void Insert(std::string _name, Polinom* pol);
};

class OpenHashTable final : public TTable {
private:
  virtual PolinomObj* FindObj(std::string name);
public:
  void Show();
  void Delete(std::string _name);
  const Polinom& Find(std::string name);
  void Insert(std::string _name, std::string _strPol);
  void Insert(std::string _name, Polinom* pol);
};
