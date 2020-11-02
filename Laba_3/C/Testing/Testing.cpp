// Testing.cpp : Defines the entry point for the Unit test
//
#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING
#include <iostream>
#include "../Library/big_integer.h"
#include "../framework.h"
#include "gtest/gtest.h"

namespace bigint_ns {

	TEST(BigIntegerConstructor, DefaultConstructor) {
		BigInteger a;
		EXPECT_EQ(1, a.length());
		EXPECT_EQ(48, a.cur_max_size());
		EXPECT_EQ(kPlus, a.sign());
		EXPECT_TRUE(a.DigitsCompare("0"));
	}

	TEST(BigIntegerConstructor, InitConstructor_1) {
		BigInteger a(67664544L);
		EXPECT_EQ(8, a.length());
		EXPECT_EQ(kPlus, a.sign());
		EXPECT_TRUE(a.DigitsCompare("67664544"));
		// When the number is negative
		BigInteger b(-67664544L);
		EXPECT_EQ(8, b.length());
		EXPECT_EQ(kMinus, b.sign());
		EXPECT_TRUE(b.DigitsCompare("67664544"));
	}

	TEST(BigIntegerConstructor, InitConstructor_2) {
		// When the number is implicitly positive
		BigInteger a("478324832957485437587435438574857345893745843");
		// When the number is negative
		BigInteger b("-478324832957485437587435438574857345893745843");
		// When the number is forcibly positive 
		BigInteger c("+478324832957485437587435438574857345893745843");
		EXPECT_EQ(45, a.length());
		EXPECT_EQ(45, b.length());
		EXPECT_EQ(45, c.length());
		EXPECT_EQ(kPlus, a.sign());
		EXPECT_EQ(kMinus, b.sign());
		EXPECT_EQ(kPlus, c.sign());
		EXPECT_TRUE(a.DigitsCompare("478324832957485437587435438574857345893745843"));
		EXPECT_TRUE(b.DigitsCompare("478324832957485437587435438574857345893745843"));
		EXPECT_TRUE(c.DigitsCompare("478324832957485437587435438574857345893745843"));
		EXPECT_EQ(48, a.cur_max_size());
		EXPECT_EQ(48, b.cur_max_size());
		EXPECT_EQ(48, c.cur_max_size());
		// When the number contains leading zeros
		BigInteger d("000000123");
		// When the number is forcibly positive 
		BigInteger e("+000000123");
		// When the number is negative
		BigInteger f("-000000123");
		EXPECT_EQ(3, d.length());
		EXPECT_EQ(3, e.length());
		EXPECT_EQ(3, f.length());
		EXPECT_EQ(kPlus, d.sign());
		EXPECT_EQ(kPlus, e.sign());
		EXPECT_EQ(kMinus, f.sign());
		EXPECT_TRUE(d.DigitsCompare("123"));
		EXPECT_TRUE(e.DigitsCompare("123"));
		EXPECT_TRUE(f.DigitsCompare("123"));
		// When the number overflows the original maximum size one time
		BigInteger d1("47832483295748543758743543857485734589374584399999");
		EXPECT_EQ(58, d1.cur_max_size());
		EXPECT_EQ(50, d1.length());
		EXPECT_EQ(kPlus, d1.sign());
		EXPECT_TRUE(d1.DigitsCompare("47832483295748543758743543857485734589374584399999"));
		// When the number overflows the original maximum size two times
		BigInteger e1("-478324832957485437587435438574857345893745843999998372483274385743");
		EXPECT_EQ(68, e1.cur_max_size());
		EXPECT_EQ(66, e1.length());
		EXPECT_EQ(kMinus, e1.sign());
		EXPECT_TRUE(e1.DigitsCompare("478324832957485437587435438574857345893745843999998372483274385743"));
		// When the number length equals to the maximum size
		BigInteger f1("478324832957485437587435438574857345893745843999");
		EXPECT_EQ(58, f1.cur_max_size());
		EXPECT_EQ(48, f1.length());
		EXPECT_EQ(kPlus, f1.sign());
		EXPECT_TRUE(f1.DigitsCompare("478324832957485437587435438574857345893745843999"));
	}

	TEST(BigIntegerConstructors, Copy_Move_Destruct) {
		//Testing copy constructor
		{
			BigInteger y("153");
			BigInteger x(y);
			EXPECT_EQ(x.cur_max_size(), y.cur_max_size());
			EXPECT_EQ(x.length(), y.length());
			EXPECT_EQ(x.sign(), y.sign());
			EXPECT_TRUE(x.DigitsCompare("153"));
			EXPECT_TRUE(y.DigitsCompare("153"));
		}
		//Testing move constructor
		{
			BigInteger x("143232"), y("-4232");
			{
				BigInteger tmp(std::move(x));
			}
			BigInteger z(std::move(y));
			EXPECT_EQ(nullptr, x.digits());
			EXPECT_EQ(nullptr, y.digits());
			EXPECT_EQ(z.cur_max_size(), y.cur_max_size());
			EXPECT_EQ(z.length(), y.length());
			EXPECT_EQ(z.sign(), kMinus);
			EXPECT_TRUE(z.DigitsCompare("4232"));
		}
		//Testing destructor
		{
			BigInteger* x_ptr = nullptr;
			{
				BigInteger x("123");
				x_ptr = &x;
			}
			EXPECT_EQ(nullptr, x_ptr->digits());
		}
	}

	TEST(BigIntegerMethods, Setters) {
		// We already test all Constructors. So we can use any of them
		BigInteger a("8378784375");
		// Testing set_sign() method
		{
			EXPECT_THROW(a.set_sign(387248723), std::invalid_argument);
			EXPECT_EQ(kPlus, a.sign());
			a.set_sign(kMinus);
			EXPECT_EQ(kMinus, a.sign());
			EXPECT_EQ(10, a.length());
			EXPECT_TRUE(a.DigitsCompare("8378784375"));
			a.set_sign(kPlus);
			EXPECT_EQ(kPlus, a.sign());
			EXPECT_EQ(10, a.length());
			EXPECT_TRUE(a.DigitsCompare("8378784375"));
		}
		// Test set_digits method
		{
			EXPECT_NO_THROW(a.set_digits("3984932598743578435773209454873857438574385743574395"));
			a.set_digits("72832");
			EXPECT_EQ(kPlus, a.sign());
			EXPECT_EQ(5, a.length());
			EXPECT_TRUE(a.DigitsCompare("72832"));
			a.set_sign(kMinus);
			a.set_digits("123");
			EXPECT_EQ(kMinus, a.sign());
			EXPECT_EQ(3, a.length());
			EXPECT_TRUE(a.DigitsCompare("123"));
			EXPECT_THROW(a.set_digits("-83947324"), std::invalid_argument);
			EXPECT_THROW(a.set_digits("+83947324"), std::invalid_argument);
			EXPECT_THROW(a.set_digits("\n\tjf 8328r9327rhj2"), std::invalid_argument);
		}
	}

	TEST(BigIntegerMethods, Operators) {
		// We already test all Constructors. So we can use any of them
		// We already test setters. So we can use any of them
		//Testing copy operator =
		{
			BigInteger y("123");
			BigInteger x("233");
			x = y;
			EXPECT_EQ(x.cur_max_size(), y.cur_max_size());
			EXPECT_EQ(x.length(), y.length());
			EXPECT_EQ(x.sign(), y.sign());
			EXPECT_TRUE(x.DigitsCompare("123"));
			EXPECT_TRUE(y.DigitsCompare("123"));
		}
		//Testing move operator =
		{
			BigInteger x("123"), y("-4545"), z;
			{
				BigInteger tmp("-8989");
				x = std::move(tmp);
				ASSERT_EQ(nullptr, tmp.digits());
			}
			EXPECT_EQ(x.cur_max_size(), 48);
			EXPECT_EQ(x.length(), 4);
			EXPECT_EQ(x.sign(), kMinus);
			EXPECT_TRUE(x.DigitsCompare("8989"));
			z = std::move(y);
			EXPECT_EQ(z.cur_max_size(), y.cur_max_size());
			EXPECT_EQ(z.length(), y.length());
			EXPECT_EQ(z.sign(), kMinus);
			EXPECT_TRUE(z.DigitsCompare("4545"));
		}
		//Testing Plus
		{
			BigInteger a(324), b(655);
			BigInteger c("212143143432432432432432432343423432423443242349");
			BigInteger d("943242344324234324343234234234234234234341341212");
			// X > 0, Y > 0, X + Y < 1
			EXPECT_TRUE((a + b).DigitsCompare("979"));
			BigInteger x = a + b;
			EXPECT_EQ(kPlus, (x).sign()); // The answer is positive
			EXPECT_EQ(3, (a + b).length());
			a.set_sign(kMinus);
			b.set_sign(kMinus);
			// X < 0, Y < 0, abs(X + Y) < 1
			EXPECT_TRUE((a + b).DigitsCompare("979"));
			EXPECT_EQ(kMinus, (a + b).sign()); // The answer is negative
			EXPECT_EQ(3, (a + b).length());
			// X > 0, Y > 0, X + Y >= 1 - Positive Overflow but actually NO
			EXPECT_NO_THROW(x = (c + d));
			c.set_sign(kMinus);
			d.set_sign(kMinus);
			// X < 0, Y < 0, abs(X + Y) >= 1 - Negative Overflow but actually NO
			EXPECT_NO_THROW(x = (c + d));
			d.set_sign(kPlus);
			// X > 0, Y < 0, X + Y > 0
			EXPECT_TRUE((d + c).DigitsCompare("731099200891801891910801801890810801810898098863"));
			EXPECT_EQ(kPlus, (d + c).sign()); // The answer is positive
			EXPECT_EQ(48, (d + c).length());
			d.set_sign(kMinus);
			c.set_sign(kPlus);
			// X > 0, Y < 0, X + Y < 0
			EXPECT_TRUE((c + d).DigitsCompare("731099200891801891910801801890810801810898098863"));
			EXPECT_EQ(kMinus, (c + d).sign()); // The answer is negative
			EXPECT_EQ(48, (c + d).length());

			// Test type conversion for operator +

			BigInteger p(291L);
			EXPECT_TRUE((p + "123").DigitsCompare("414"));
			EXPECT_TRUE((p + 123L).DigitsCompare("414"));
			EXPECT_TRUE((p + 123L).DigitsCompare("414"));
		}
		//Testing Minus : A - B = A + (-B) => We've already tested everything
		{
			BigInteger e(123), f(890), minus_e(-123), minus_f(-890);
			// X + Y > 0
			EXPECT_TRUE((f - e).DigitsCompare("767"));
			EXPECT_EQ(kPlus, (f - e).sign()); // The answer is positive
			EXPECT_EQ(3, (f - e).length());
			EXPECT_TRUE((f + minus_e).DigitsCompare("767"));
			EXPECT_EQ(kPlus, (f + minus_e).sign()); // The answer is positive
			EXPECT_EQ(3, (f + minus_e).length());
			// X + Y < 0
			EXPECT_TRUE((e - f).DigitsCompare("767"));
			EXPECT_EQ(kMinus, (e - f).sign()); // The answer is negative
			EXPECT_EQ(3, (e - f).length());
			EXPECT_TRUE((e + minus_f).DigitsCompare("767"));
			EXPECT_EQ(kMinus, (e + minus_f).sign()); // The answer is negative
			EXPECT_EQ(3, (e + minus_f).length());
		}
		//Testing IncreaseOrder
		{
			BigInteger x("-8378784375"), y("8378784375");
			// With Negative
			EXPECT_EQ(40, x.IncreaseOrder(30).length());
			EXPECT_EQ(kMinus, x.sign());
			EXPECT_TRUE(x.DigitsCompare("8378784375000000000000000000000000000000"));
			// With Positive
			EXPECT_EQ(40, y.IncreaseOrder(30).length());
			EXPECT_EQ(kPlus, y.sign());
			EXPECT_TRUE(y.DigitsCompare("8378784375000000000000000000000000000000"));
			int d = y.cur_max_size() + 10;
			EXPECT_NO_THROW(y.IncreaseOrder(d));
			EXPECT_EQ(40 + d, y.length());
			EXPECT_EQ(kPlus, y.sign());
			EXPECT_TRUE(y.DigitsCompare("83787843750000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"));
		}
		//Testing DecreaseOrder
		{
			BigInteger x("-8378784375"), y("8378784375");
			// With Negative
			EXPECT_EQ(5, x.DecreaseOrder(5).length());
			EXPECT_EQ(kMinus, x.sign());
			EXPECT_TRUE(x.DigitsCompare("83787"));
			// With Positive
			EXPECT_EQ(5, y.DecreaseOrder(5).length());
			EXPECT_EQ(kPlus, y.sign());
			EXPECT_TRUE(y.DigitsCompare("83787"));
			EXPECT_THROW(x.DecreaseOrder(x.cur_max_size() + 10), std::range_error);
		}
	}
}

int _tmain(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}