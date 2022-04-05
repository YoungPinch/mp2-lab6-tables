#include "gtest/gtest.h"
#include "TableManager.h"

typedef UnsortListTable Tab;

TEST(UnsortListTable, can_create_table)
{
  ASSERT_NO_THROW(Tab t);
}

TEST(UnsortListTable, new_table_is_empty)
{
  Tab t;
  EXPECT_EQ(0, t.getCurSize());
}

TEST(UnsortListTable, can_add_elem_in_table)
{
  Tab t;
  ASSERT_NO_THROW(t.Insert(PolinomObj::Create("name", "xyz")));
}

TEST(UnsortListTable, insert_elem_increases_size)
{
  Tab t;
  int sizeBefore = t.getCurSize();
  t.Insert(PolinomObj::Create("name", "xyz"));
  int sizeAfter = t.getCurSize();
  EXPECT_NE(sizeBefore, sizeAfter);
}

TEST(UnsortListTable, insert_existing_elem_doesnt_change_size)
{
  Tab t;
  t.Insert(PolinomObj::Create("name", "xyz"));
  int sizeBefore = t.getCurSize();
  t.Insert(PolinomObj::Create("name", "xyz"));
  int sizeAfter = t.getCurSize();
  EXPECT_EQ(sizeBefore, sizeAfter);
}

TEST(UnsortListTable, can_find_existing_elem_in_table)
{
  Tab t;
  t.Insert(PolinomObj::Create("name", "xyz"));
  EXPECT_EQ(t.Find("name")->get(), PolinomObj::Create("name", "xyz").get());
}

TEST(UnsortListTable, cant_find_non_existing_elem_in_table)
{
  Tab t;
  EXPECT_EQ(t.Find("name"), nullptr);
}

TEST(UnsortListTable, can_delete_existing_elem_from_table)
{
  Tab t;
  t.Insert(PolinomObj::Create("name", "xyz"));
  t.Delete("name");
  EXPECT_EQ(t.Find("name"), nullptr);
}

TEST(UnsortListTable, no_throw_when_delete_non_existing_elem_from_table)
{
  Tab t;
  ASSERT_NO_THROW(t.Delete("name"));
}