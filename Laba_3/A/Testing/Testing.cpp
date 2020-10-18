// Testing.cpp : Defines the entry point for the Unit test
//
#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING
#include <iostream>
#include "../Library/big_integer_1.h"
#include "../framework.h"
#include "gtest/gtest.h"

namespace bigint_ns {

	TEST(BigIntegerConstructor, DefaultConstructor) {
		BigInteger a;
		EXPECT_EQ(1, a.GetLength());
		EXPECT_EQ(kPlus, a.GetSign());
		EXPECT_TRUE(a.DigitsCompare("0"));
	}

	TEST(BigIntegerConstructor, InitConstructor_1) {
		BigInteger a(67664544L);
		EXPECT_EQ(8, a.GetLength());
		EXPECT_EQ(kPlus, a.GetSign());
		EXPECT_TRUE(a.DigitsCompare("67664544"));
		// When the number is negative
		BigInteger b(-67664544L);
		EXPECT_EQ(8, b.GetLength());
		EXPECT_EQ(kMinus, b.GetSign());
		EXPECT_TRUE(b.DigitsCompare("32335455")); // In RevCode
	}

	TEST(BigIntegerConstructor, InitConstructor_2) {
		BigInteger a("478324832957485437587435438574857345893745843");
		EXPECT_EQ(45, a.GetLength());
		EXPECT_EQ(kPlus, a.GetSign());
		EXPECT_TRUE(a.DigitsCompare("478324832957485437587435438574857345893745843"));
		// When the number is negative
		BigInteger b("478324832957485437587435438574857345893745843", kMinus);
		EXPECT_EQ(45, b.GetLength());
		EXPECT_EQ(kMinus, b.GetSign());
		EXPECT_TRUE(b.DigitsCompare("521675167042514562412564561425142654106254156")); // In RevCode
	}

	TEST(BigIntegerConstructor, TestException) {
		// When the number is too long
		EXPECT_THROW(BigInteger("3984932598743578435773209454873857438574385743574395"), std::range_error);
	}

	TEST(BigIntegerMethods, Setters) {
		BigInteger a;
		EXPECT_THROW(a.SetSign(387248723), std::invalid_argument);
		a.SetDigits("8378784375");
		EXPECT_EQ(kPlus, a.GetSign());
		EXPECT_EQ(10, a.GetLength());
		EXPECT_TRUE(a.DigitsCompare("8378784375"));
		a.SetSign(kMinus);
		EXPECT_EQ(kMinus, a.GetSign());
		EXPECT_EQ(10, a.GetLength());
		EXPECT_TRUE(a.DigitsCompare("1621215624")); // In RevCode
		EXPECT_THROW(a.SetDigits("3984932598743578435773209454873857438574385743574395"), std::range_error);
		a.SetLength(5);
		EXPECT_EQ(5, a.GetLength());
		EXPECT_TRUE(a.DigitsCompare("16212")); // In RevCode
		a.SetSign(kPlus);
		a.SetDigits("8378784375");
		a.SetLength(5);
		EXPECT_EQ(5, a.GetLength());
		EXPECT_TRUE(a.DigitsCompare("83787")); // In RevCode
		a.SetLength(40);
		EXPECT_EQ(40, a.GetLength());
		EXPECT_TRUE(a.DigitsCompare("8378700000000000000000000000000000000000"));
		EXPECT_THROW(a.SetLength(BigInteger::GetMaxSize() + 10), std::range_error);
	}

	TEST(BigIntegerMethods, Operators) {
		//Testing Plus
		BigInteger a(324), b(655);
		BigInteger c("212143143432432432432432432343423432423443242349");
		BigInteger d("943242344324234324343234234234234234234341341212");
		EXPECT_TRUE(a.Plus(b).DigitsCompare("979")); // X > 0, Y > 0, X + Y < 1
		a.SetSign(kMinus);
		b.SetSign(kMinus);
		// X < 0, Y < 0, abs(X + Y) < 1
		EXPECT_TRUE(a.Plus(b).DigitsCompare("020")); // In RevCode
		EXPECT_THROW(c.Plus(d), std::overflow_error); // X > 0, Y > 0, X + Y >= 1 - Positive Overflow
		c.SetSign(kMinus);
		d.SetSign(kMinus);
		EXPECT_THROW(c.Plus(d), std::overflow_error); // X < 0, Y < 0, abs(X + Y) >= 1 - Negative Overflow
		d.SetSign(kPlus);
		// X > 0, Y < 0, X + Y > 0
		EXPECT_TRUE(d.Plus(c).DigitsCompare("731099200891801891910801801890810801810898098863"));
		d.SetSign(kMinus);
		c.SetSign(kPlus);
		// X > 0, Y < 0, X + Y < 0
		EXPECT_TRUE(c.Plus(d).DigitsCompare("268900799108198108089198198109189198189101901136")); // In RevCode
		//Testing Minus : A - B = A + (-B) => We've already tested everything
		BigInteger e(123), f(890), minus_e(-123);
		EXPECT_TRUE(f.Minus(e).DigitsCompare("767"));
		EXPECT_TRUE(f.Plus(minus_e).DigitsCompare("767"));
		//Testing IncreaseOrder :\
			We have already tested the SetLength() method which use these methods in his body!
		BigInteger test_order(123), test_order_copy(123);
		test_order.SetLength(10);
		test_order_copy.IncreaseOrder(10 - 3);
		EXPECT_TRUE(test_order.DigitsCompare("1230000000"));
		EXPECT_TRUE(test_order_copy.DigitsCompare("1230000000"));
		//Testing DecreaseOrder :\
			We have already tested the SetLength() method which use these methods in his body!
		test_order.SetLength(1);
		test_order_copy.DecreaseOrder(10 - 1);
		EXPECT_TRUE(test_order.DigitsCompare("1"));
		EXPECT_TRUE(test_order_copy.DigitsCompare("1"));
	}
}

int _tmain(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}