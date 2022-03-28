#pragma once
#define COUNTTABLES 6
#include <string.h>
#include "polinom.hpp"

struct PolinomObj {
public:
  std::string name;
  std::string strPol;
  Polinom pol;

  PolinomObj(std::string _name, std::string _strPol) {
    name = _name;
    strPol = _strPol;
    pol = Polinom(strPol);
  };

  PolinomObj(std::string _name, Polinom _pol) {
    name = _name;
    strPol = pol.ToString();
    pol = _pol;
  }

  PolinomObj() {
    name = "";
    strPol = "";
    pol = Polinom();
  }

  static std::shared_ptr<PolinomObj> Create(std::string _name, std::string _strPol) {
    return std::make_shared<PolinomObj>(_name, _strPol);
  }

  static std::shared_ptr<PolinomObj> Create(std::string _name, Polinom pol) {
    return std::make_shared<PolinomObj>(_name, pol);
  }

  const std::string& GetName() { return name; }
  const std::string& GetStrPol() { return strPol; }
  const Polinom& GetPol() { return pol; }

};

class TTable {
public:
  virtual void Print() = 0;
  virtual void Delete(std::string _name) = 0;
  virtual std::shared_ptr<PolinomObj> Find(std::string name) = 0;
  virtual void Insert(std::shared_ptr<PolinomObj> obj) = 0;
  virtual ~TTable() = 0;
};

