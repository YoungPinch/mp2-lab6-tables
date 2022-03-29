#pragma once
#include "TTable.h"
#include "avl_tree.hpp"

template <class TKey, class TData>
class AVLTable final : public TTable<class TKey, class TData> {
private:
  AVLTree<TData> tree;
public:
  AVLTable() { };
  void Insert(TData data) { tree.Insert(data); }
  TData& Find(TKey key) { tree.Find(key); }
  void Delete(TKey key) { tree.Delete(key); }
  void Print() { tree.Print(); }
};
