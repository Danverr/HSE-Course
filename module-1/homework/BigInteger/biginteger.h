#include <iostream>
#include <vector>
#include <string>
#include <cmath>

class BigInteger {
public:
	const int BASE = 10;
	const int DIGITS_LEN = log10(BASE);

	BigInteger();
	BigInteger(int);
	BigInteger(long long int);
	BigInteger(std::string);

	std::string toString() const;

	bool operator==(const BigInteger&) const;
	bool operator!=(const BigInteger&) const;
	bool operator>(const BigInteger&) const;
	bool operator>=(const BigInteger&) const;
	bool operator<(const BigInteger&) const;
	bool operator<=(const BigInteger&) const;

	friend BigInteger abs(const BigInteger&);
	friend BigInteger max(const BigInteger&, const BigInteger&);
	friend BigInteger min(const BigInteger&, const BigInteger&);

	BigInteger& operator=(const BigInteger&);
	BigInteger  operator-() const;
	BigInteger  operator+(const BigInteger&) const;
	BigInteger  operator-(const BigInteger&) const;
	BigInteger  operator*(const BigInteger&) const;
	BigInteger  operator/(const int&) const;
	BigInteger  operator/(const BigInteger&) const;
	BigInteger  operator%(const BigInteger&) const;
	BigInteger& operator+=(const BigInteger&);
	BigInteger& operator-=(const BigInteger&);
	BigInteger& operator*=(const BigInteger&);
	BigInteger& operator/=(const int&);
	BigInteger& operator/=(const BigInteger&);
	BigInteger& operator%=(const BigInteger&);
	BigInteger& operator--();
	BigInteger  operator--(int);
	BigInteger& operator++();
	BigInteger  operator++(int);

	operator bool() const;

	friend std::ostream& operator<<(std::ostream&, const BigInteger&);
	friend std::istream& operator>>(std::istream&, BigInteger&);

private:
	int sign;
	std::vector<int> digits;

	int getDigit(const int) const;
	BigInteger& add(const BigInteger&, const bool);
	void trim();
};

std::ostream& operator<<(std::ostream&, const BigInteger&);
std::istream& operator>>(std::istream&, BigInteger&);