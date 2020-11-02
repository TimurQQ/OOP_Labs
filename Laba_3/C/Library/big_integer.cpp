#include "big_integer.h"

#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>

namespace bigint_ns {

	//<-------- Public Methods -------->

	BigInteger::BigInteger(long number) noexcept {
		digits_ = new char[cur_max_size_ + 1];
		BigInteger::ClearDigits();
		char sign = kPlus;
		if (number < 0L) {
			number *= -(sign = kMinus);
		}
		do {
			digits_[length_++] = number % 10L;
			number /= 10L;
		} while (number > 0L);
		digits_[cur_max_size_] = sign;
	}

	BigInteger::BigInteger(const char* str_number) {
		bool is_signed = false;
		if (!BigInteger::IsCorrect(str_number, is_signed)) {
			throw std::invalid_argument("The input string is not a number");
		}
		digits_ = new char[cur_max_size_ + 1];
		BigInteger::ClearDigits();
		char sign = (str_number[0] == '-') ? kMinus : kPlus;
		digits_[cur_max_size_] = sign;
		BigInteger::set_digits(str_number + is_signed); // This method can change cur_max_size_
	}

	BigInteger::BigInteger(const BigInteger& x) {
		cur_max_size_ = x.cur_max_size_;
		digits_ = new char[x.cur_max_size_ + 1];
		BigInteger::ClearDigits();
		memcpy(digits_, x.digits_, cur_max_size_ + 1);
		length_ = x.length_;
	}

	BigInteger::BigInteger(BigInteger&& x) noexcept {
		cur_max_size_ = x.cur_max_size_;
		digits_ = x.digits_;
		length_ = x.length_;
		x.digits_ = nullptr;
	}

	BigInteger& BigInteger::operator = (const BigInteger& x) {
		if (&x == this) return *this;
		delete[] digits_;
		cur_max_size_ = x.cur_max_size_;
		digits_ = new char[x.cur_max_size_ + 1];
		BigInteger::ClearDigits();
		memcpy(digits_, x.digits_, cur_max_size_ + 1);
		length_ = x.length_;
		return *this;
	}

	BigInteger& BigInteger::operator = (BigInteger&& x) noexcept {
		if (&x == this) return *this;
		delete[] digits_;
		cur_max_size_ = x.cur_max_size_;
		digits_ = x.digits_;
		length_ = x.length_;
		x.digits_ = nullptr;
		return *this;
	}

	void BigInteger::ClearDigits() noexcept {
		for (int i = 0; i < cur_max_size_; i++) {
			digits_[i] = 0;
		}
	}

	void BigInteger::set_sign(const int sign) {
		if (sign != kPlus && sign != kMinus) {
			throw std::invalid_argument("Sign value should be 0 (+) or 1 (-)");
		}
		digits_[cur_max_size_] = sign;
	}

	void BigInteger::set_digits(const char* digits) { 
		int length = strlen(digits);
		if (!BigInteger::IsDecimal(digits)) {
			throw std::invalid_argument("The input string is not a unsigned number");
		}
		if (length >= cur_max_size_) {
			int count = ceil(((long long)length - (long long)cur_max_size_ + 1LL) / (double)kQuota);
			BigInteger::AddMemoryBlocks(count);
		}
		BigInteger::ClearDigits();
		for (int i = 0; i < length; ++i) {
			digits_[i] = digits[length - i - 1] - '0';
		}
		BigInteger::ChangeLength();
	}

	BigInteger BigInteger::operator +(const BigInteger& x) const {
		BigInteger res = BigInteger::operator~();
		BigInteger tmp = ~x;
		int d_res = BigInteger::UnsignedSum(res, tmp);
		int sign_sum = BigInteger::sign() + x.sign() + d_res;
		res.set_sign(sign_sum % 2);
		return (~res).ChangeLength();
	}

	BigInteger BigInteger::operator -(const BigInteger& x) const {
		BigInteger tmp(x);
		tmp.set_sign((x.sign() + 1) % 2);
		return BigInteger::operator+(tmp);
	}

	BigInteger& BigInteger::IncreaseOrder(const int x) {
		if (length_ + x >= cur_max_size_) {
			int count = ceil((((long long)length_ + (long long)x - (long long)cur_max_size_) + 1.0) / kQuota);
			BigInteger::AddMemoryBlocks(count);
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

	std::ostream& operator <<(std::ostream& st, const BigInteger& a) noexcept {
		st << ((a.sign() == kMinus) ? '-' : ' ');
		for (int i = a.length_ - 1; i >= 0; --i) {
			st << int(a.digits_[i]);
		}
		st << std::endl;
		return st;
	}

	std::istream& operator >>(std::istream& st, BigInteger& a) {
		std::string s;
		getline(st, s, '\n');
		if (st) {
			bool is_signed = false;
			if (!BigInteger::IsCorrect(s, is_signed)) {
				throw std::invalid_argument("The input string is not a number");
			}
			int sign = (s[0] == '-') ? kMinus : kPlus;
			a.set_digits(s.c_str() + is_signed);
			a.set_sign(sign);
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

	BigInteger BigInteger::operator ~() const noexcept {
		if (BigInteger::sign() == kPlus) return *this;
		BigInteger res(*this);
		for (int i = 0; i < cur_max_size_; ++i) {
			res.digits_[i] = 9 - digits_[i];
		}
		BigInteger additional_1(1);
		int d_res = BigInteger::UnsignedSum(res, additional_1);
		res.set_sign(!d_res);
		return res;
	}

	void BigInteger::AddMemoryBlocks(int count) {
		if (count == 0) return;
		int old_max_size = cur_max_size_;
		cur_max_size_ += kQuota * count;
		char* old_buf = digits_;
		digits_ = new char[cur_max_size_ + 1];
		BigInteger::ClearDigits();
		for (int i = 0; i < old_max_size; ++i) {
			digits_[i] = old_buf[i];
		}
		BigInteger::set_sign(old_buf[old_max_size]);
		delete[] old_buf;
	}

	int BigInteger::UnsignedSum(BigInteger& a, BigInteger& b) noexcept {
		int d_res = 0;
		if (a.cur_max_size_ < b.cur_max_size_) {
			int count = ceil((((long long)b.cur_max_size_ - (long long)a.cur_max_size_)) / kQuota);
			a.AddMemoryBlocks(count);
		}
		else if (b.cur_max_size_ < a.cur_max_size_) {
			int count = ceil((((long long)a.cur_max_size_ - (long long)b.cur_max_size_)) / kQuota);
			b.AddMemoryBlocks(count);
		}
		for (int i = 0; i < a.cur_max_size_; ++i) {
			int digits_sum = a.digits_[i] + b.digits_[i] + d_res;
			a.digits_[i] = digits_sum % 10;
			d_res = (digits_sum >= 10) ? 1 : 0;
		}
		return d_res;
	}

	BigInteger& BigInteger::ChangeLength() {
		length_ = 1;
		for (int i = cur_max_size_ - 1; i >= 0; --i) {
			if (digits_[i] != 0) {
				length_ = i + 1;
				break;
			}
		}
		BigInteger::AddMemoryBlocks(length_ == cur_max_size_);
		return *this;
	}

	bool BigInteger::IsDecimal(const char* string) noexcept {
		int length = strlen(string);
		for (int i = 0; i < length; ++i) {
			if (!(string[i] <= '9' && string[i] >= '0')) {
				return false;
			}
		}
		return true;
	}

	bool BigInteger::IsCorrect(const std::string number, bool& is_signed) noexcept {
		if (number[0] == '+' || number[0] == '-') is_signed = true;
		int length = number.length() - is_signed;
		return BigInteger::IsDecimal(number.c_str() + is_signed);
	}
}