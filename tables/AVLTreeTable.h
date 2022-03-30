#pragma once
#include "TTable.h"
#include "avl_tree.hpp"

template <class TKey, class TData>
class AVLTable final : public TTable<class TKey, class TData> {
private:
  AVLTree<TData> tree;
public:
  AVLTable() { };
  void Insert(TData data) { }
  TData& Find(TKey key) { }
  void Delete(TKey key) { }
  void Print() { tree.Print(); }
};
