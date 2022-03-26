#pragma once
#include <string.h>
#include <vector>
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
