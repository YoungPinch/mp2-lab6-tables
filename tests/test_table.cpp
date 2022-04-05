#include "gtest/gtest.h"
#include "TableManager.h"

// Tests for TableManager

TEST(TableManager, can_set_active_table)
{
  TableManager m(2);
  ASSERT_NO_THROW(m.setActiveTable(1));
}

TEST(TableManager, can_add_elem_into_all_tables)
{
  TableManager m(2);
  ASSERT_NO_THROW(m.Insert("name", "xyz"));
}

TEST(TableManager, cant_add_existing_elem_into_all_tables)
{
  TableManager m(2);
  m.Insert("name", "xyz");
  ASSERT_ANY_THROW(m.Insert("name", "xyz"));
}

//TEST(TableManager, can_delete_existing_elem_from_all_tables)
//{
//  TableManager m(2);
//  m.Insert("name", "xyz");
//  ASSERT_NO_THROW(m.Delete("name"));
//}

TEST(TTable, can_delete_non_existing_elem_from_all_tables)
{
  TableManager m(2);
  ASSERT_NO_THROW(m.Delete("name"));
}

// Common tests for all tables
// typedef UnsortListTable Tab;
// typedef UnsortArrayTable Tab;
// typedef SortArrayTable Tab;
// typedef OpenHashTable Tab;
// typedef ChainHashTable Tab;
// typedef AVLTreeTable Tab;
//
//TEST(TTable, can_create_table)
//{
//  ASSERT_NO_THROW(Tab t);
//}
//
//TEST(TTable, new_table_is_empty)
//{
//  Tab t;
//  EXPECT_EQ(0, t.getCurSize());
//}
//
//TEST(TTable, can_add_elem_in_table)
//{
//  Tab t;
//  ASSERT_NO_THROW(t.Insert(PolinomObj::Create("name", "xyz")));
//}
//
//TEST(TTable, insert_elem_increases_size)
//{
//  Tab t;
//  int sizeBefore = t.getCurSize();
//  t.Insert(PolinomObj::Create("name", "xyz"));
//  int sizeAfter = t.getCurSize();
//  EXPECT_NE(sizeBefore, sizeAfter);
//}
//
//TEST(TTable, insert_existing_elem_doesnt_change_size)
//{
//  Tab t;
//  t.Insert(PolinomObj::Create("name", "xyz"));
//  int sizeBefore = t.getCurSize();
//  t.Insert(PolinomObj::Create("name", "xyz"));
//  int sizeAfter = t.getCurSize();
//  EXPECT_EQ(sizeBefore, sizeAfter);
//}
//
//TEST(TTable, can_find_existing_elem_in_table)
//{
//  Tab t;
//  t.Insert(PolinomObj::Create("name", "xyz"));
//  EXPECT_EQ(t.Find("name")->get(), PolinomObj::Create("name", "xyz").get());
//}
//
//TEST(TTable, cant_find_non_existing_elem_in_table)
//{
//  Tab t;
//  EXPECT_EQ(t.Find("name"), nullptr);
//}
//
//TEST(TTable, can_delete_existing_elem_from_table)
//{
//  Tab t;
//  t.Insert(PolinomObj::Create("name", "xyz"));
//  t.Delete("name");
//  EXPECT_EQ(t.Find("name"), nullptr);
//}
//
//TEST(TTable, no_throw_when_delete_non_existing_elem_from_table)
//{
//  Tab t;
//  ASSERT_NO_THROW(t.Delete("name"));
//}
