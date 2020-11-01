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
		BigInteger(const char* signed_number);
		void ClearDigits() noexcept;
		int length() const { return length_; }
		int sign() const { return digits_[kMaxSize_]; }
		static int max_size() { return kMaxSize_; }
		void set_sign(const int sign);
		void set_digits(const char* digits);
		BigInteger operator +(const BigInteger& x) const;
		BigInteger operator -(const BigInteger& x) const;
		BigInteger& IncreaseOrder(const int x);
		BigInteger& DecreaseOrder(const int x);
		friend std::ostream& operator <<(std::ostream&, const BigInteger&) noexcept;
		friend std::istream& operator >>(std::istream&, BigInteger&);
		bool DigitsCompare(const char* test_digits) const noexcept;
	protected:
		//No protected fields and methods
	private:
		static const int kMaxSize_ = 48;
		char digits_[kMaxSize_ + 1]; // An additional byte is allocated for the sign
		int length_ = 0;
		BigInteger operator ~() const noexcept;
		static int UnsignedSum(BigInteger& a, const BigInteger& b) noexcept; // The result is stored in the first argument
		BigInteger& ChangeLength() noexcept;
		static bool IsDecimal(const char* string) noexcept;
		static bool IsCorrect(const char* signed_number, bool& is_signed) noexcept;
	};
}

#endif // _BIG_INTEGER_H_INCLUDED_