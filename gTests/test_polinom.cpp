#include "pch.h"

TEST(TList, can_create_polinom)
{
	ASSERT_NO_THROW(Polinom p);
}

TEST(TList, can_init_polinom)
{
	Polinom p;
	ASSERT_NO_THROW(p = Polinom("2xy5z"));
}

TEST(TList, can_print_polinom)
{
	Polinom p("2x5y");
	EXPECT_EQ(p.ToString(), "2x5y");
}

TEST(TList, can_copy_polinom)
{
	Polinom p1("2x5y"), p2;
	p2 = p1;
	EXPECT_EQ(p2.ToString(), "2x5y");
}

TEST(TList, can_compare_polinom)
{
	Polinom p1("2x5y"), p2("2x5y");
	bool l = p1 == p2;
	EXPECT_EQ(true, l);
}

TEST(TList, can_add_polinom)
{
	Polinom p1("2x5y"), p2("3y"), p3;
	p3 = p1 + p2;
	EXPECT_EQ(p3.ToString(), "2x5y+3y");
}

TEST(TList, can_inverse_polinom)
{
	Polinom p1("2x5y"), p2;
	p2 = -p1;
	EXPECT_EQ("-2x5y", p2.ToString());
}

TEST(TList, can_subtract_polinom)
{
	Polinom p1("2x5y"), p2("3y"), p3;
	p3 = p1 - p2;
	EXPECT_EQ(p3.ToString(), "2x5y-3y");
}

TEST(TList, can_multiply_polinom)
{
	Polinom p1("2x5y"), p2("3y"), p3; 
	p3 = p1 * p2;
	EXPECT_EQ(p3.ToString(), "6x5y2");
}

TEST(TList, can_calculate_polinom)
{
	Polinom p1("2x5y");
	EXPECT_EQ(p1.Calculate(1, 1, 0), 2);
}

TEST(TList, can_differentiate_polinom)
{
	Polinom p1("2x5y");
	EXPECT_EQ(p1.Differentiate('x').ToString(), "10x4y");
}

TEST(TList, can_integrate_polinom)
{
	Polinom p1("2x5y");
	EXPECT_EQ(p1.Integrate('y').ToString(), "x5y2");
}
