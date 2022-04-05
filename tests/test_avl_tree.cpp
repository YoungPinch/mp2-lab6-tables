#include "gtest/gtest.h"
#include "avl_tree.hpp"
#include "TTable.h"

TEST(AVLTree, can_create_tree)
{
  ASSERT_NO_THROW(AVLTree t);
}

TEST(AVLTree, new_tree_is_empty)
{
  AVLTree t;
  EXPECT_EQ(0, t.getSize());
}

TEST(AVLTree, can_add_elem_in_tree)
{
  AVLTree t;
  ASSERT_NO_THROW(t.Insert(PolinomObj::Create("name", "xyz")));
}

TEST(AVLTree, insert_elem_increases_size)
{
  AVLTree t;
  int sizeBefore = t.getSize();
  t.Insert(PolinomObj::Create("name", "xyz"));
  int sizeAfter = t.getSize();
  EXPECT_NE(sizeBefore, sizeAfter);
}

TEST(AVLTree, insert_existing_elem_doesnt_change_size)
{
  AVLTree t;
  t.Insert(PolinomObj::Create("name", "xyz"));
  int sizeBefore = t.getSize();
  t.Insert(PolinomObj::Create("name", "xyz"));
  int sizeAfter = t.getSize();
  EXPECT_EQ(sizeBefore, sizeAfter);
}

TEST(AVLTree, can_find_existing_elem_in_tree)
{
  AVLTree t;
  t.Insert(PolinomObj::Create("name", "xyz"));
  EXPECT_EQ(t.Find("name")->get(), PolinomObj::Create("name", "xyz").get());
}

TEST(AVLTree, cant_find_non_existing_elem_in_tree)
{
  AVLTree t;
  EXPECT_EQ(t.Find("name"), nullptr);
}

TEST(AVLTree, can_delete_existing_elem_from_tree)
{
  AVLTree t;
  t.Insert(PolinomObj::Create("name", "xyz"));
  t.Delete("name");
  EXPECT_EQ(t.Find("name"), nullptr);
}

TEST(AVLTree, no_throw_when_delete_non_existing_elem_from_tree)
{
  AVLTree t;
  ASSERT_NO_THROW(t.Delete("name"));
}
