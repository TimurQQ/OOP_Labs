#include "big_integer.h"

#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>

namespace bigint_ns {
	
	//<-------- Public Methods -------->
	
	BigInteger::BigInteger(long number) noexcept {
		BigInteger::ClearDigits();
		char sign = kPlus;
		if (number < 0L) {
			number *= -(sign = kMinus);
		}
		do {
			digits_[length_++] = number % 10L;
			number /= 10L;
		} while (number > 0L);
		digits_[kMaxSize_] = sign;
	}
	
	BigInteger::BigInteger(const char* str_number) {
		bool is_signed = false;
		if (!BigInteger::IsCorrect(str_number, is_signed)) {
			throw std::invalid_argument("The input string is not a number");
		}
		char sign = (str_number[0] == '-') ? kMinus : kPlus;
		BigInteger::set_digits(str_number + is_signed);
		digits_[kMaxSize_] = sign;
	}
	
	void BigInteger::ClearDigits() noexcept {
		for (int i = 0; i < kMaxSize_; i++) {
			digits_[i] = 0;
		}
	}
	
	void BigInteger::set_sign(const char sign) {
		if (sign != kPlus && sign != kMinus) {
			throw std::invalid_argument("Sign value should be 0 (+) or 1 (-)");
		}
		digits_[kMaxSize_] = sign;
	}
	
	void BigInteger::set_digits(const char* digits) {
		int length = strlen(digits);
		if (length > kMaxSize_) {
			throw std::range_error("The Length of the input number in the direct code format upper than the MaxSize");
		}
		if (!BigInteger::IsDecimal(digits)) {
			throw std::invalid_argument("The input string is not a unsigned number");
		}
		BigInteger::ClearDigits();
		for (int i = 0; i < length; ++i) {
			digits_[i] = digits[length - i - 1] - '0';
		}
		BigInteger::ChangeLength();
	}
	
	BigInteger BigInteger::Plus(const BigInteger& x) const {
		BigInteger res = BigInteger::TensComplement();
		BigInteger tmp = x.TensComplement();
		int d_res = BigInteger::UnsignedSum(res, tmp);
		int sign_sum = BigInteger::sign() + x.sign() + d_res;
		res.set_sign(sign_sum % 2);
		if (BigInteger::sign() == x.sign()) {
			if (BigInteger::sign() == kMinus && res.sign() == kPlus) {
				throw std::overflow_error("Negative overflow!");
			}
			if (BigInteger::sign() == kPlus && res.sign() == kMinus) {
				throw std::overflow_error("Positive overflow!");
			}
		}
		return res.TensComplement().ChangeLength();
	}
	
	BigInteger BigInteger::Minus(const BigInteger& x) const {
		BigInteger tmp(x);
		tmp.set_sign((x.sign() + 1) % 2);
		return BigInteger::Plus(tmp);
	}
	
	BigInteger& BigInteger::IncreaseOrder(const int x) {
		if (length_ + x > kMaxSize_ - 1) {
			throw std::range_error("You can't increase the order, because the order equals to MaxSize!!!");
		}
		memcpy_s(digits_ + x, length_, digits_, length_);
		for (int i = 0; i < x; ++i) {
			digits_[i] = 0;
		}
		return BigInteger::ChangeLength();
	}

	BigInteger& BigInteger::DecreaseOrder(const int x) {
		if (length_ - x < 1) {
			throw std::range_error("You can't decrease the order, because the order minimum is \"1\"!!!");
		}
		memcpy_s(digits_, length_ - x, digits_ + x, length_ - x);
		for (int i = length_ - 1; i >= length_ - x; --i) {
			digits_[i] = 0;
		}
		return BigInteger::ChangeLength();
	}

	std::ostream& BigInteger::Print(std::ostream& st) const noexcept {
		st << ((BigInteger::sign() == kMinus) ? '-' : ' ');
		for (int i = length_ - 1; i >= 0; --i) {
			st << int(digits_[i]);
		}
		st << std::endl;
		return st;
	}

	std::istream& BigInteger::Input(std::istream& st) {
		char s[kMaxSize_ + 1];
		st.getline(s, kMaxSize_ + 1, '\n');
		if (st) {
			bool is_signed = false;
			if (!IsCorrect(s, is_signed)) {
				throw std::invalid_argument("The input string is not a number");
			}
			int sign = (s[0] == '-') ? kMinus : kPlus;
			BigInteger::set_digits(s + is_signed);
			digits_[kMaxSize_] = sign;
		}
		return st;
	}
	
	bool BigInteger::DigitsCompare(const char* test_digits) const noexcept {
		int test_length = strlen(test_digits);
		if (test_length != length_) return false;
		for (int i = 0; i < length_; ++i) {
			if (digits_[i] != (test_digits[length_ - i - 1] - '0')) {
				return false;
			}
		}
		return true;
	}
	
	//<-------- Private Methods --------> 
	
	BigInteger BigInteger::TensComplement() const noexcept {
		if (BigInteger::sign() == kPlus) return *this;
		BigInteger res;
		for (int i = 0; i < kMaxSize_; ++i) {
			res.digits_[i] = 9 - digits_[i];
		}
		int d_res = BigInteger::UnsignedSum(res, 1);
		res.set_sign(!d_res);
		return res;
	}
	
	int BigInteger::UnsignedSum(BigInteger& a, const BigInteger& b) noexcept {
		int d_res = 0;
		for (int i = 0; i < kMaxSize_; ++i) {
			int digits_sum = a.digits_[i] + b.digits_[i] + d_res;
			a.digits_[i] = digits_sum % 10;
			d_res = (digits_sum >= 10) ? 1 : 0;
		}
		return d_res;
	}
	
	BigInteger& BigInteger::ChangeLength() noexcept{
		length_ = 1;
		for (int i = kMaxSize_ - 1; i >= 0; --i) {
			if (digits_[i] != 0) {
				length_ = i + 1;
				break;
			}
		}
		return *this;
	}

	bool BigInteger::IsDecimal(const char* string) const noexcept {
		int length = strlen(string);
		for (int i = 0; i < min(length, kMaxSize_); ++i) {
			if (!(string[i] <= '9' && string[i] >= '0')) {
				return false;
			}
		}
		return true;
	}

	bool BigInteger::IsCorrect(const char* number, bool& is_signed) const noexcept {
		if (number[0] == '+' || number[0] == '-') is_signed = true;
		int length = strlen(number + is_signed);
		return BigInteger::IsDecimal(number + is_signed) && length <= kMaxSize_;
	}
}