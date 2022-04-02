#pragma once
#include "TTable.h"
#include "avl_tree.hpp"

class AVLTable final : public TTable {
private:
  AVLTree tree;
public:
  AVLTable() { };
  int getSize() { return tree.getSize(); }
  void Insert(std::shared_ptr<PolinomObj> data) { tree.Insert(data); }
  std::shared_ptr<PolinomObj>* Find(std::string key) { return tree.Find(key); }
  void Delete(std::string key) { tree.Delete(key); }
  void Print() { tree.Print(); }
};
