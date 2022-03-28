#pragma once
#include "TTable.h"
#include "avl_tree.hpp"

template <class TKey, class TData>
class AVLTable final : public TTable<class TKey, class TData> {
private:
  AVLTree<TData> tree;
public:
  AVLTable() { };

  //void Print() { tree.Print(); }
  //void Insert(std::shared_ptr<PolinomObj> obj) { tree.Insert(obj); };
  //{
  //  std::shared_ptr<PolinomObj>();
  //  tree.Delete(_name);
  //}
  //{ tree.Find(name); }
  void Insert(TData data) {}
  TData& Find(TKey key) {}
  void Delete(TKey key) {}
  void Print() {}
};
