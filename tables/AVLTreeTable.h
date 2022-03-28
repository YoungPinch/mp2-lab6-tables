#pragma once
#include "TTable.h"
#include "avl_tree.hpp"

class AVLTable final : public TTable {
private:
  AVLTree<std::shared_ptr<PolinomObj>> tree;
public:
  AVLTable() { };
  void Print() { tree.Print(); }
  void Delete(std::string _name);
  //{
  //  std::shared_ptr<PolinomObj>();
  //  tree.Delete(_name);
  //}
  std::shared_ptr<PolinomObj> Find(std::string name);
  //{ tree.Find(name); }
  void Insert(std::shared_ptr<PolinomObj> obj) { tree.Insert(obj); };
};
