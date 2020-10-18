#pragma once
#ifndef _BIG_INTEGER_H_INCLUDED_
#define _BIG_INTEGER_H_INCLUDED_
#include "../framework.h"
#include <iostream>

namespace bigint_ns {
	constexpr int kPlus = 0;
	constexpr int kMinus = 1;

	class BigInteger {
	public:
		BigInteger(long number = 0L) noexcept;
		BigInteger(const char* number_string, const int sign = kPlus);
		void ClearDigits() noexcept;
		int GetLength() const { return length_; }
		int GetSign() const { return sign_; }
		static int GetMaxSize() { return kMaxSize_; }
		void SetSign(const int sign);
		void SetLength(const int length);
		void SetDigits(const char* digits);
		BigInteger Plus(const BigInteger& x) const;
		BigInteger Minus(const BigInteger& x) const;
		BigInteger& IncreaseOrder(const int x);
		BigInteger& DecreaseOrder(const int x);
		std::ostream& Print(std::ostream&) const noexcept;
		std::istream& Input(std::istream&);
		bool DigitsCompare(const char* test_digits) const noexcept;
	protected:
		//No protected fields and methods
	private:
		static const int kMaxSize_ = 48;
		char digits_[kMaxSize_];
		int sign_ = kPlus;
		int length_ = 0;
		BigInteger& Rev(const int sign) noexcept;
		BigInteger GetSumWith(const BigInteger& x) const;
		BigInteger& ChangeLength() noexcept;
	};
}

#endif // _BIG_INTEGER_H_INCLUDED_