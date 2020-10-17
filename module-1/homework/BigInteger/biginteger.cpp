#include "biginteger.h"

BigInteger::BigInteger() : digits({ 0 }), isNeg(0) { }

BigInteger::BigInteger(int x) {
	*this = BigInteger((long long int) x);
}

BigInteger::BigInteger(long long int x) {
	isNeg = x < 0;

	if (x == 0) {
		this->digits.push_back(0);
	}

	while (x) {
		this->digits.push_back(x % BASE);
		x /= BASE;
	}
}

BigInteger::BigInteger(std::string str) {
	this->isNeg = str.size() && str[0] == '-';

	for (int i = str.size(); i > 0; i -= DIGITS_LEN) {
		std::string substr = i < DIGITS_LEN ? str.substr(0, i) : str.substr(i - DIGITS_LEN, DIGITS_LEN);
		this->digits.push_back(atoi(substr.c_str()));
	}
}

std::string BigInteger::toString() const {
	std::string str = isNeg ? "-" : "";

	// Starting from highest digits
	for (int i = digits.size() - 1; i >= 0; i--) {
		str += std::to_string(digits[i]);
	}

	return str;
}

bool BigInteger::operator==(const BigInteger& x) const {
	bool sameSign = x.isNeg == this->isNeg;
	bool sameDigits = 1;

	// Comparing all digits
	for (int i = 0; i < x.digits.size() || i < this->digits.size(); i++) {
		if (this->getDigit(i) != x.getDigit(i)) {
			sameDigits = 0;
			break;
		}
	}

	return sameSign && sameDigits;
}

bool BigInteger::operator!=(const BigInteger& x) const {
	return !(*this == x);
}

bool BigInteger::operator>(const BigInteger& x) const {
	int res = false;

	// Comparing signs
	if (!this->isNeg && x.isNeg) {
		return true;
	}
	else if (this->isNeg && !x.isNeg) {
		return false;
	}

	// Comparing absolute values
	for (int i = std::max(x.digits.size(), this->digits.size()) - 1; i >= 0; i--) {
		if (this->getDigit(i) > x.getDigit(i)) {
			res = true;
			break;
		}
		else if (this->getDigit(i) < x.getDigit(i)) {
			res = false;
			break;
		}
	}

	// If both of numbers are negative
	// |a| > |b| => a < b 
	return this->isNeg ? !res : res;
}

bool BigInteger::operator>=(const BigInteger& x) const {
	return *this > x || *this == x;
}

bool BigInteger::operator<(const BigInteger& x) const {
	return !(*this >= x);
}

bool BigInteger::operator<=(const BigInteger& x) const {
	return !(*this > x);
}

BigInteger abs(const BigInteger& x) {
	BigInteger copy = x;
	copy.isNeg = 0;
	return copy;
}

BigInteger max(const BigInteger& a, const BigInteger& b) {
	return a > b ? BigInteger(a) : BigInteger(b);
}

BigInteger min(const BigInteger& a, const BigInteger& b) {
	return a < b ? BigInteger(a) : BigInteger(b);
}

BigInteger& BigInteger::operator=(const BigInteger& x) {
	if (*this != x) {
		isNeg = x.isNeg;
		digits = x.digits;
	}

	return *this;
}

BigInteger BigInteger::operator-() const {
	BigInteger copy = *this;
	copy.isNeg ^= 1;
	return copy;
}

BigInteger BigInteger::operator+(const BigInteger& x) const {
	return BigInteger(*this) += x;
}

BigInteger BigInteger::operator-(const BigInteger& x) const {
	return BigInteger(*this) -= x;
}

BigInteger BigInteger::operator*(const BigInteger& x) const {
	return BigInteger(*this) *= x;
}

BigInteger BigInteger::operator/(const int& x) const {
	return BigInteger(*this) /= x;
}

BigInteger BigInteger::operator/(const BigInteger& x) const {
	return BigInteger(*this) /= x;
}

BigInteger BigInteger::operator%(const BigInteger& x) const {
	return BigInteger(*this) %= x;
}

BigInteger& BigInteger::operator+=(const BigInteger& x) {
	return add(x, false);
}

BigInteger& BigInteger::operator-=(const BigInteger& x) {
	return add(x, true);
}

BigInteger& BigInteger::operator*=(const BigInteger& x) {
	BigInteger res;
	int ost = 0;

	res.isNeg = isNeg ^ x.isNeg;

	for (int i = 0; i < digits.size(); i++) {
		for (int j = 0; j < x.digits.size() || ost; j++) {
			int k = i + j;

			if (k >= res.digits.size()) {
				res.digits.push_back(0);
			}

			res.digits[k] += getDigit(i) * x.getDigit(j) + ost;
			ost = 0;

			if (res.digits[k] >= BASE) {
				ost = res.digits[k] / BASE;
				res.digits[k] %= BASE;
			}
		}
	}

	res.trim();
	return *this = res;
}

BigInteger& BigInteger::operator/=(const int& x) {
	if (x == 0) throw "Division by zero";

	BigInteger res;
	std::string dividend = "";

	res.digits.assign(digits.size() + 1, 0);

	for (int i = digits.size() - 1; i >= 0; i--) {
		dividend += std::to_string(digits[i]);
		int temp = stol(dividend);

		if (temp / x > 0) {
			res.digits[i] = temp / x;
			dividend = std::to_string(temp % x);
		}
	}

	res.trim();
	return *this = res;
}

BigInteger& BigInteger::operator/=(const BigInteger& x) {
	if (x == BigInteger(0)) throw "Division by zero";
	BigInteger l = 0, r = abs(*this) + BigInteger(1);

	while (r - l > BigInteger(1)) {
		BigInteger mid = (l + r) / 2;

		if (abs(x) * mid > abs(*this)) {
			r = mid;
		}
		else {
			l = mid;
		}
	}

	l.isNeg = isNeg ^ x.isNeg;
	return *this = l;
}

BigInteger& BigInteger::operator%=(const BigInteger& x) {
	return *this -= *this / x * x;
}

BigInteger& BigInteger::operator--() {
	return *this -= 1;
}

BigInteger BigInteger::operator--(int) {
	BigInteger copy = *this;
	*this -= 1;
	return copy;
}

BigInteger& BigInteger::operator++() {
	return *this += 1;
}

BigInteger BigInteger::operator++(int) {
	BigInteger copy = *this;
	*this += 1;
	return copy;
}

BigInteger::operator bool() const {
	return *this != BigInteger(0);
}

std::ostream& operator<<(std::ostream& out, const BigInteger& x) {
	if (x.isNeg) out << "-";

	out << x.digits.back();

	for (int i = x.digits.size() - 2; i >= 0; i--) {
		std::string digit = std::to_string(x.digits[i]);

		while (digit.size() != x.DIGITS_LEN) {
			digit = "0" + digit;
		}

		out << digit;
	};

	return out;
}

std::istream& operator>>(std::istream& in, BigInteger& x) {
	std::string str;
	in >> str;
	x = BigInteger(str);
	return in;
}

int BigInteger::getDigit(int i) const {
	return i < digits.size() ? digits[i] : 0;
}

BigInteger& BigInteger::add(const BigInteger& x, const bool minus) {
	int ost = 0;
	const bool isThisBigger = abs(*this) > abs(x), isSubtraction = isNeg ^ x.isNeg ^ minus;

	if (!isThisBigger) {
		isNeg = x.isNeg ^ minus;
	}

	for (int i = 0; i < digits.size() || i < x.digits.size() || ost != 0; i++) {
		if (i >= digits.size()) {
			digits.push_back(0);
		}

		if (isSubtraction) {
			if (isThisBigger) {
				digits[i] -= x.getDigit(i);
			}
			else {
				digits[i] = x.getDigit(i) - getDigit(i);
			}
		}
		else {
			digits[i] += x.getDigit(i);
		}

		digits[i] += ost;
		ost = 0;

		if (digits[i] >= BASE) {
			digits[i] -= BASE;
			ost++;
		}
		else if (digits[i] < 0) {
			digits[i] += BASE;
			ost--;
		}
	}

	trim();
	return *this;
};

void BigInteger::trim() {
	while (this->digits.size() > 1 && this->digits.back() == 0) {
		this->digits.pop_back();
	}
}