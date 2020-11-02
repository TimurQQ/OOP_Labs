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
		BigInteger(const BigInteger&);
		BigInteger(BigInteger&&) noexcept;
		~BigInteger() { delete[] digits_, digits_ = nullptr; }
		BigInteger& operator = (const BigInteger&);
		BigInteger& operator = (BigInteger&&) noexcept;
		void ClearDigits() noexcept;
		int length() const { return length_; }
		char* digits() const { return digits_; }
		int sign() const { return digits_[cur_max_size_]; }
		int cur_max_size() const { return cur_max_size_; }
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
		static const int kQuota = 10;
		int cur_max_size_ = 48;
		char* digits_ = nullptr;
		int length_ = 0;
		BigInteger operator ~() const noexcept;
		void AddMemoryBlocks(int count);
		static int UnsignedSum(BigInteger& a, BigInteger& b) noexcept; // The result is stored in the first argument
		BigInteger& ChangeLength();
		static bool IsDecimal(const char* string) noexcept;
		static bool IsCorrect(const std::string signed_number, bool& is_signed) noexcept;
	};
}

#endif // _BIG_INTEGER_H_INCLUDED_