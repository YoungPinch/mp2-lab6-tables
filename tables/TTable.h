#pragma once
#define COUNTTABLES 6
#include <string.h>
#include "polinom.hpp"

struct PolinomObj {
private:
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

public:

  static std::shared_ptr<PolinomObj> Create(std::string _name, std::string _strPol) {
    std::shared_ptr<PolinomObj> shptr(new PolinomObj(_name, _strPol));
    return shptr;
  }

  static std::shared_ptr<PolinomObj> Create(std::string _name, Polinom pol) {
    std::shared_ptr<PolinomObj> shptr(new PolinomObj(_name, pol));
    return shptr;
  }

  const std::string& getName() { return name; }
  const std::string& getStrPol() { return strPol; }
  const Polinom& getPol() { return pol; }

  friend std::ostream& operator<< (std::ostream& out, const PolinomObj& polObj) {
    out << polObj.name << " = " << polObj.strPol.substr(0, 19);
    return out;
  }

  bool operator==(const PolinomObj& other) const noexcept { return name == other.name; }
  bool operator!=(const PolinomObj& other) const noexcept { return name != other.name; }
  bool operator<(const PolinomObj& other) const noexcept { return name < other.name; }
  bool operator>(const PolinomObj& other) const noexcept { return name > other.name; }

};

class TTable {
public:
  virtual void Print() = 0;
  virtual void Delete(std::string _name) = 0;
  virtual std::shared_ptr<PolinomObj> Find(std::string name) = 0;
  virtual void Insert(std::shared_ptr<PolinomObj> obj) = 0;
  virtual ~TTable() = 0;
};

