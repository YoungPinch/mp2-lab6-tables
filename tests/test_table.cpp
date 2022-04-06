#include "gtest/gtest.h"
#include "TableManager.h"

// Tests for TableManager

TEST(TableManager, can_create_table_manager_with_tables)
{
  ASSERT_NO_THROW(TableManager m(2););
}

TEST(TTable, cant_create_table_manager_with_incorrect_size)
{
  ASSERT_ANY_THROW(TableManager m(0));
  ASSERT_ANY_THROW(TableManager m(-1));
}

TEST(TableManager, can_set_active_table)
{
  TableManager m(2);
  ASSERT_NO_THROW(m.setActiveTable(1));
}

TEST(TableManager, can_get_size_of_table_manger)
{
  TableManager m(2);
  ASSERT_NO_THROW(m.getCurSize());
}

TEST(TableManager, new_table_manger_is_empty)
{
  TableManager m(2);
  EXPECT_EQ(m.getCurSize(), 0);
}

TEST(TableManager, can_add_elem_into_all_tables)
{
  TableManager m(2);
  ASSERT_NO_THROW(m.Insert("name", "xyz"));
}

TEST(TableManager, insert_elem_increases_size_in_table_manager)
{
  TableManager m(2);
  m.Insert("name", "xyz");
  EXPECT_EQ(m.getCurSize(), 1);
}

TEST(TableManager, can_find_elem)
{
  TableManager m(2);
  m.Insert("name", "xyz");
  EXPECT_EQ(m.Find("name")->get()->getStrPol(), "xyz");
}

TEST(TableManager, cant_change_existing_elem)
{
  TableManager m(2);
  m.Insert("name", "xyz");
  m.Insert("name", "x2");
  EXPECT_EQ(m.Find("name")->get()->getStrPol(), "xyz");
}

TEST(TableManager, can_delete_existing_elem_from_all_tables)
{
  TableManager m(2);
  m.Insert("name", "xyz");
  ASSERT_NO_THROW(m.Delete("name"));
}

TEST(TableManager, delete_elem_decreases_size_of_table_manager)
{
  TableManager m(2);
  m.Insert("name", "xyz");
  m.Insert("bob", "x2");
  m.Delete("name");
  EXPECT_EQ(m.getCurSize(), 1);
}

TEST(TTable, no_throw_deleting_non_existing_elem_from_all_tables)
{
  TableManager m(2);
  m.Insert("name", "xyz");
  ASSERT_NO_THROW(m.Delete("x"));
}

TEST(TTable, delete_non_existing_elem_doesnt_change_size_of_table_manager)
{
  TableManager m(2);
  m.Insert("name", "xyz");
  m.Delete("bob");
  ASSERT_NO_THROW(m.getCurSize(), 1);
}

TEST(TTable, throw_when_add_elem_to_full_table_manager)
{
  TableManager m(1);
  m.Insert("name", "xyz");
  ASSERT_ANY_THROW(m.Insert("bob", "x2"););
}

TEST(TTable, throw_when_delete_from_empty_table_manager)
{
  TableManager m(2);
  ASSERT_ANY_THROW(m.Delete("x"));
}


// Common tests for all tables
typedef UnsortListTable   Tab;
//typedef UnsortArrayTable  Tab;
//typedef SortArrayTable    Tab;
//typedef OpenHashTable     Tab;
//typedef ChainHashTable    Tab;
//typedef AVLTreeTable      Tab;

TEST(TTable, can_create_table)
{
  ASSERT_NO_THROW(Tab t);
}

TEST(TTable, can_get_size_of_table)
{
  Tab t;
  ASSERT_NO_THROW(t.getCurSize());
}

TEST(TTable, new_table_is_empty)
{
  Tab t;
  EXPECT_EQ(t.getCurSize(), 0);
}

TEST(TTable, can_add_elem_in_table)
{
  Tab t;
  ASSERT_NO_THROW(t.Insert(PolinomObj::Create("name", "xyz")));
}

TEST(TTable, insert_elem_increases_size_of_table)
{
  Tab t;
  t.Insert(PolinomObj::Create("name", "xyz"));
  EXPECT_EQ(t.getCurSize(), 1);
}

TEST(TTable, cant_change_existing_elem_in_table)
{
  Tab t;
  t.Insert(PolinomObj::Create("name", "xyz"));
  t.Insert(PolinomObj::Create("name", "x2"));
  EXPECT_EQ(t.Find("name")->get()->getStrPol(), "xyz");
}

TEST(TTable, can_find_existing_elem_in_table)
{
  Tab t;
  t.Insert(PolinomObj::Create("name", "xyz"));
  EXPECT_EQ(t.Find("name")->get()->getStrPol(), "xyz");
  EXPECT_EQ(t.Find("name")->get()->getName(), "name");
  EXPECT_EQ(t.Find("name")->get()->getPol(), Polinom("xyz"));
}

TEST(TTable, cant_find_non_existing_elem_in_table)
{
  Tab t;
  EXPECT_EQ(t.Find("x"), nullptr);
}

TEST(TTable, can_delete_existing_elem_from_table)
{
  Tab t;
  t.Insert(PolinomObj::Create("name", "xyz"));
  t.Delete("name");
  EXPECT_EQ(t.Find("name"), nullptr);
}

TEST(TTable, delete_elem_decreases_size_of_table)
{
  Tab t;
  t.Insert(PolinomObj::Create("name", "xyz"));
  t.Delete("name");
  EXPECT_EQ(t.getCurSize(), 0);
}

TEST(TTable, can_delete_non_existing_elem_from_table)
{
  Tab t;
  ASSERT_NO_THROW(t.Delete("x"));
}

TEST(TTable, delete_non_existing_elem_doesnt_change_size_of_table)
{
  Tab t;
  t.Insert(PolinomObj::Create("name", "xyz"));
  t.Delete("bob");
  EXPECT_EQ(t.getCurSize(), 1);
}