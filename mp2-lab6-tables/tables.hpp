#pragma once
#include <string.h>
#include "polinom.hpp"

class PolinomObj {
private:
  std::string name;
  std::string strPol;
  Polinom pol;

  PolinomObj(std::string _name, std::string _strPol) : pol(_strPol), name(_name), strPol(_strPol) { }

public:
  static PolinomObj* Create(std::string _name, std::string _strPol) {
    return &PolinomObj(_name, _strPol);
  }
};

class TTable {
private: 
  void ShowTableHeader();
protected:
  virtual PolinomObj* FindObj(std::string name);
public:
  virtual void Delete();
  virtual const Polinom& Find(std::string name);
  virtual void Insert(std::string _name, std::string _strPol);
  virtual void Show();
  virtual ~TTable() = 0;
};

class SortArrayTable final : public TTable {
private:
  virtual PolinomObj* FindObj(std::string name);

  PolinomObj* arr[];

public:
  void Show();
  void Delete();
  const Polinom& Find(std::string name);
  void Insert(std::string _name, std::string _strPol);
};

class UnsortArrayTable final : public TTable {
private:
  virtual PolinomObj* FindObj(std::string name);

  PolinomObj* arr[];

public:
  void Show();
  void Delete();
  const Polinom& Find(std::string name);
  void Insert(std::string _name, std::string _strPol);
};

class UnsortListTable final : public TTable {
private:
  virtual PolinomObj* FindObj(std::string name);

  TList<PolinomObj*> list;

public:
  void Show();
  void Delete();
  const Polinom& Find(std::string name);
  void Insert(std::string _name, std::string _strPol);
};

class BinaryTable final : public TTable {
private:
  virtual PolinomObj* FindObj(std::string name);
public:
  void Show();
  void Delete();
  const Polinom& Find(std::string name);
  void Insert(std::string _name, std::string _strPol);
};

class ChainHashTable final : public TTable {
private:
  virtual PolinomObj* FindObj(std::string name);
public:
  void Show();
  void Delete();
  const Polinom& Find(std::string name);
  void Insert(std::string _name, std::string _strPol);
};

class OpenHashTable final : public TTable {
private:
  virtual PolinomObj* FindObj(std::string name);
public:
  void Show();
  void Delete();
  const Polinom& Find(std::string name);
  void Insert(std::string _name, std::string _strPol);
};
