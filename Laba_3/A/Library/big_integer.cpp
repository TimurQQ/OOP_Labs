#include "big_integer.h"

#include <cmath>
#include <iostream>
#include <iomanip>

namespace bigint_ns {

	BigInteger& BigInteger::Rev(const int sign) noexcept {
		if (sign == kPlus) return *this;
		for (int i = 0; i < kMaxSize_; ++i) {
			digits_[i] = 9 - digits_[i];
		}
		return *this;
	}

	BigInteger::BigInteger(long number) noexcept {
		BigInteger::ClearDigits();
		if (number < 0L) {
			number *= -(sign_ = kMinus);
		}
		do {
			digits_[length_++] = number % 10;
			number /= 10;
		} while (number > 0);
		BigInteger::Rev(sign_);
	}
	
	BigInteger::BigInteger(const char* number_string, const int sign) {
		BigInteger::SetDigits(number_string);
		sign_ = sign;
		BigInteger::Rev(sign);
	}

	void BigInteger::ClearDigits() noexcept{
		for (int i = 0; i < kMaxSize_; i++) {
			digits_[i] = 0;
		}
	}

	void BigInteger::SetSign(const int sign) {
		if (sign != kPlus && sign != kMinus) {
			throw std::invalid_argument("Sign value should be 0 (+) or 1 (-)");
		}
		BigInteger::Rev(sign_ != sign);
		sign_ = sign;
	}

	void BigInteger::SetLength(const int length) {
		int d_length = length - length_;
		if (d_length < 0) {
			DecreaseOrder(abs(d_length));
		}
		else {
			IncreaseOrder(abs(d_length));
		}
	}

	void BigInteger::SetDigits(const char* digits) {
		int length = strlen(digits);
		if (length > kMaxSize_) {
			throw std::range_error("The Length of the input number upper than the MaxSize");
		}
		BigInteger::ClearDigits();
		length_ = length;
		for (int i = 0; i < length; ++i) {
			digits_[i] = digits[length - i - 1] - '0';
		}
	}

	BigInteger& BigInteger::ChangeLength()  noexcept{
		const char digit = (sign_ == kMinus) ? 9 : 0;
		for (int i = kMaxSize_ - 1; i >= 0; --i) {
			if (digits_[i] != digit) {
				length_ = i + 1;
				return *this;
			}
		}
		length_ = 1;
		return *this;
	}

	BigInteger BigInteger::GetSumWith(const BigInteger& x) const{
		BigInteger res;
		int d_res = 0;
		for (int i = 0; i < kMaxSize_; ++i) {
			int digits_sum = digits_[i] + x.digits_[i] + d_res;
			res.digits_[i] = digits_sum % 10;
			d_res = (digits_sum >= 10) ? 1 : 0;
		}
		int sign_sum = sign_ + x.sign_ + d_res;
		res.sign_ = sign_sum % 2;
		if (sign_ == x.sign_) {
			if (sign_ == kMinus && res.sign_ == kPlus) {
				throw std::overflow_error("Negative overflow!");
			}
			if (sign_ == kPlus && res.sign_ == kMinus) {
				throw std::overflow_error("Positive overflow!");
			}
		}
		if (d_res != 0) {
			return res.GetSumWith(1);
		}
		return res;
	}

	BigInteger BigInteger::Plus(const BigInteger& x) const {
		return BigInteger::GetSumWith(x).ChangeLength();
	}

	BigInteger BigInteger::Minus(const BigInteger& x) const {
		BigInteger x_rev(x);
		x_rev.SetSign((x.sign_ == kPlus) ? kMinus : kPlus);
		return BigInteger::GetSumWith(x_rev).ChangeLength();
	}

	BigInteger& BigInteger::IncreaseOrder(const int x) {
		if (length_ + x > kMaxSize_) {
			throw std::range_error("You can't increase the order, because the order equals to MaxSize!!!");
		}
		memcpy_s(digits_ + x, length_, digits_, length_);
		for (int i = 0; i < x; ++i) {
			digits_[i] = (sign_ == kPlus) ? 0 : 9;
		}
		return BigInteger::ChangeLength();
	}

	BigInteger& BigInteger::DecreaseOrder(const int x) {
		if (length_ - x < 1) {
			throw std::range_error("You can't decrease the order, because the order minimum is \"1\"!!!");
		}
		memcpy_s(digits_, length_ - x, digits_ + x, length_ - x);
		for (int i = length_ - 1; i >= length_ - x; --i) {
			digits_[i] = (sign_ == kPlus) ? 0 : 9;
		}
		return BigInteger::ChangeLength();
	}

	std::ostream& BigInteger::Print(std::ostream& st) const noexcept {
		if (sign_ == kMinus) {
			if (length_ != 1 || digits_[0] != 9) st << '-';
			for (int i = length_ - 1; i >= 0; --i) {
				st << 9 - digits_[i];
			}
			st << std::endl;
			return st;
		}
		for (int i = length_ - 1; i >= 0; --i) {
			st << int(digits_[i]);
		}
		st << std::endl;
		return st;
	}

	std::istream& BigInteger::Input(std::istream& st) {
		char s[kMaxSize_];
		st.getline(s, kMaxSize_ , '\n');
		if (st) {
			BigInteger::SetDigits(s);
			sign_ = kPlus;
			BigInteger::Rev(sign_);
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
}