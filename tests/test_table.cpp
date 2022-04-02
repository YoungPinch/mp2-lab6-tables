#include "gtest/gtest.h"
#include "TableManager.h"

// Common tests for all tables
typedef UnsortListTable Tab;
// typedef UnsortArrayTable Tab;
// typedef SortArrayTable Tab;
// typedef OpenHashTable Tab;
// typedef ChainHashTable Tab;
// typedef AVLTreeTable Tab;

TEST(TTable, can_create_table)
{
  ASSERT_NO_THROW(Tab t);
}

TEST(TTable, new_table_is_empty) ////////
{
  ADD_FAILURE();
}

TEST(TTable, can_add_elem_in_table)
{
  Tab t;
  ASSERT_NO_THROW(t.Insert(PolinomObj::Create("x", "x")));
}

TEST(TTable, throws_when_add_existing_elem_in_table) ////////
{
  ADD_FAILURE();
}

TEST(TTable, can_find_existing_elem_in_table)
{
  Tab t;
  t.Insert(PolinomObj::Create("x", "x"));
  EXPECT_EQ(t.Find("x")->get(), PolinomObj::Create("x", "x").get());
}

TEST(TTable, cant_find_non_existing_elem_in_table)
{
  Tab t;
  EXPECT_EQ(t.Find("x"), nullptr);
}

//TEST(TTable, can_delete_existing_elem_from_table)
//{
//  Tab t;
//  t.Insert(PolinomObj::Create("x", "x"));
//  t.Delete("x");
//  EXPECT_EQ(t.Find("x"), nullptr);
//}

TEST(TTable, can_delete_non_existing_elem_from_table)
{
  Tab t;
  ASSERT_NO_THROW(t.Delete("x"));
}

// Tests for TableManager

TEST(TableManager, can_set_active_table)
{
  TableManager m(2);
  ASSERT_NO_THROW(m.setActiveTable(1));
}

TEST(TableManager, can_add_elem_into_all_tables)
{
  TableManager m(2);
  ASSERT_NO_THROW(m.Insert("x", "x"));
}

TEST(TableManager, cant_add_existing_elem_into_all_tables)
{
  TableManager m(2);
  m.Insert("x", "x");
  ASSERT_ANY_THROW(m.Insert("x", "x"));
}

//TEST(TableManager, can_delete_existing_elem_from_all_tables)
//{
//  TableManager m(2);
//  m.Insert("x", "x");
//  ASSERT_NO_THROW(m.Delete("x"));
//}

TEST(TTable, can_delete_non_existing_elem_from_all_tables)
{
  TableManager m(2);
  ASSERT_NO_THROW(m.Delete("x"));
}
