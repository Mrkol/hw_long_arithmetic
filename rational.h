#include <iostream>
#include <vector>
#include <cmath>
#include <string>

#pragma once


// BIGINTEGER.HPP

class BigInteger;

const BigInteger operator""_bi(unsigned long long int);

const BigInteger operator-(const BigInteger&);
const BigInteger operator+(const BigInteger&, const BigInteger&);
const BigInteger operator-(const BigInteger&, const BigInteger&);
BigInteger& operator++(BigInteger& op);
BigInteger& operator--(BigInteger& op);
BigInteger operator++(BigInteger& op, int);
BigInteger operator--(BigInteger& op, int);
BigInteger& operator+=(BigInteger&, const BigInteger&);
BigInteger& operator-=(BigInteger&, const BigInteger&);
const BigInteger operator|(const BigInteger&, const BigInteger&);
const BigInteger operator&(const BigInteger&, const BigInteger&);
const BigInteger operator<<(const BigInteger&, const int&);
const BigInteger operator>>(const BigInteger&, const int&);
const BigInteger operator*(const BigInteger&, const BigInteger&);
const BigInteger operator/(const BigInteger&, const BigInteger&);
const BigInteger operator%(const BigInteger&, const BigInteger&);
BigInteger& operator*=(BigInteger&, const BigInteger&);
BigInteger& operator/=(BigInteger&, const BigInteger&);
BigInteger& operator%=(BigInteger&, const BigInteger&);
const BigInteger pow(const BigInteger&, const BigInteger&);
const BigInteger gcd(const BigInteger&, const BigInteger&);
const BigInteger lcm(const BigInteger&, const BigInteger&);

bool operator==(const BigInteger&, const BigInteger&);
bool operator!=(const BigInteger&, const BigInteger&);
bool operator>(const BigInteger&, const BigInteger&);
bool operator<(const BigInteger&, const BigInteger&);
bool operator>=(const BigInteger&, const BigInteger&);
bool operator<=(const BigInteger&, const BigInteger&);

std::ostream& operator<<(std::ostream&, const BigInteger&);
std::istream& operator>>(std::istream&, const BigInteger&);

template<typename T>
inline const T max(T lhs, T rhs);

class BigInteger
{
	std::vector<bool> _data; //digits go from least significant
	bool _sign;

	void normalize();

	friend const BigInteger operator-(const BigInteger&);
	friend const BigInteger operator+(const BigInteger&, const BigInteger&);
	friend const BigInteger operator-(const BigInteger&, const BigInteger&);
	friend const BigInteger operator&(const BigInteger&, const BigInteger&);
	friend const BigInteger operator|(const BigInteger&, const BigInteger&);
	friend const BigInteger operator<<(const BigInteger&, const int&);
	friend const BigInteger operator>>(const BigInteger&, const int&);
	friend const BigInteger operator*(const BigInteger&, const BigInteger&);
	friend const BigInteger operator/(const BigInteger&, const BigInteger&);
	friend const BigInteger operator%(const BigInteger&, const BigInteger&);
	friend const BigInteger pow(const BigInteger&, const BigInteger&);

	friend std::ostream& operator<<(std::ostream&, const BigInteger&);
	friend std::istream& operator>>(std::istream&, BigInteger&);

	friend bool operator==(const BigInteger&, const BigInteger&);
	friend bool operator<(const BigInteger&, const BigInteger&);

public:

	BigInteger();

	BigInteger(long long val);

	explicit BigInteger(std::string str);

	bool operator[](size_t index) const;

	size_t log2() const;

	const BigInteger abs() const;

	const BigInteger sgn() const;

	explicit operator bool() const;

	explicit operator int() const;

	explicit operator long long() const;

	const std::string toBinaryString() const;

	const std::string toString() const;
};

BigInteger::BigInteger()
{
	_data.push_back(0);
	_sign = false;
}

BigInteger::BigInteger(long long val)
{
	_sign = false;
	if (val < 0) 
	{
		_sign = true;
		val = -val;
	}
	
	if (val == 0)
	{
		_data.push_back(0);
	}

	while (val != 0)
	{
		_data.push_back(val & 1);
		val >>= 1;
	}

	normalize();
}

BigInteger::BigInteger(std::string str)
{
	//No leading zeros are allowed.
	if (str == "")
	{
		BigInteger(0);
		return;
	}

	if (str[0] == '-')
	{
		str = str.substr(1, str.size() - 1);
		_sign = true;
	}
	else _sign = false;

	if (str == "0")
	{
		BigInteger(0);
		return;
	}

	_data.clear();
	while (str != "")
	{
		int rem = 0;
		for (size_t i = 0; i < str.size(); i++)
		{
			int div = ((str[i] - '0') + 10*rem) / 2;
			rem = ((str[i] - '0') + 10*rem) % 2;
			str[i] = '0' + div;
		}

		while (str.size() > 0 && str[0] == '0') 
			str = str.substr(1, str.size() - 1);

		if (rem) _data.push_back(1);
		else _data.push_back(0);
	}

	normalize();
}

void BigInteger::normalize()
{
	size_t zeros = 0;
	while (zeros < _data.size() && _data[_data.size() - 1 - zeros] == 0) zeros++;
	if (zeros == _data.size()) zeros--;
	_data.resize(_data.size() - zeros);
	if (_data.size() == 1 && _data[0] == 0) _sign = false;
}

bool BigInteger::operator[](size_t index) const
{
	if (index >= this->_data.size()) return false;
	return this->_data[index];
}

size_t BigInteger::log2() const
{
	return _data.size();
}

const BigInteger BigInteger::abs() const
{
	BigInteger lhs = *this;
	lhs._sign = false;
	return lhs;
}

const BigInteger BigInteger::sgn() const
{
	return *this > 0_bi ? 1_bi : (*this < 0_bi ? -1_bi : 0_bi);
}

BigInteger::operator bool() const
{
	return !(_data.size() == 1 && _data[0] == 0);
}

BigInteger::operator int() const
{
	int ret = 0;
	for (size_t i = 0; i < sizeof(int)*8 - 1; i++)
	{
		ret |= ((int) operator[](i)) << i;
	}
	if (_sign) return -ret;
	return ret;
}

BigInteger::operator long long() const
{
	long long ret = 0;
	for (size_t i = 0; i < sizeof(long long)*8 - 1; i++)
	{
		ret |= ((long long) operator[](i)) << i;
	}
	if (_sign) return -ret;
	return ret;
}

const std::string BigInteger::toBinaryString() const
{
	std::string str = "";
	for (size_t i = 0; i < _data.size(); i++)
	{
		str += _data[_data.size() - 1 - i] ? '1' : '0';
	}
	return str;
}

const std::string BigInteger::toString() const
{
	if (*this == 0) return "0";

	BigInteger tmp = this->abs();
	std::vector<char> digits;
	while (tmp != 0)
	{
		digits.push_back(int(tmp % 10));
		tmp /= 10;
	}

	std::string s = "";
	for (size_t i = 0; i < digits.size(); i++) s += digits[digits.size() - 1 - i] + '0';
	return _sign ? "-" + s : s;
}

const BigInteger operator""_bi(unsigned long long int literal)
{
    return BigInteger(literal);
}

const BigInteger operator-(const BigInteger& op)
{
	BigInteger result = op;
	result._sign = !result._sign;
	result.normalize();
	return result;
}

const BigInteger operator+(const BigInteger& lhs, const BigInteger& rhs)
{
	if (lhs._sign == false && rhs._sign == true) return lhs - (-rhs);
	if (lhs._sign == true && rhs._sign == false) return rhs - (-lhs);
	bool negative = lhs._sign && rhs._sign;

	BigInteger result;
	result._data.resize(max(lhs.log2(), rhs.log2()) + 1, 0);
	bool rem = 0;
	for (size_t i = 0; i < result.log2(); i++)
	{
		//!= for bools is the same as XOR
		result._data[i] = (lhs[i] != rhs[i]) != rem;
		rem = (lhs[i] && rhs[i]) || (rem && (lhs[i] != rhs[i]));
	}

	result._sign = negative;
	result.normalize();
	return result;
}

const BigInteger operator-(const BigInteger& lhs, const BigInteger& rhs)
{
	if (lhs._sign == true && rhs._sign == false) return -((-lhs) + rhs);
	if (lhs._sign == false && rhs._sign == true) return lhs + (-rhs);
	bool negative = lhs._sign && rhs._sign;
	BigInteger result;
	BigInteger lhs_ = lhs;
	BigInteger rhs_ = rhs;
	if (lhs_.abs() < rhs_.abs()) 
	{
		std::swap(lhs_, rhs_);
		negative = !negative;
	}
	result._data.resize(max(lhs_.log2(), rhs_.log2()), 0);
	bool borrow = 0;
	for (size_t i = 0; i < result.log2(); i++)
	{
		//lhs rhs bor | res bor
		// 0   0   0  |  0   0
		// 0   0   1  |  1   1
		// 0   1   0  |  1   1
		// 0   1   1  |  0   1
		// 1   0   0  |  1   0
		// 1   0   1  |  0   0
		// 1   1   0  |  0   0
		// 1   1   1  |  1   1
		//DNF of the above table
		result._data[i] = 
			(!lhs_[i] && !rhs_[i] && borrow) || 
			(!lhs_[i] && rhs_[i] && !borrow) || 
			(lhs_[i] && !rhs_[i] && !borrow) || 
			(lhs_[i] && rhs_[i] && borrow);
		borrow = 
			(!lhs_[i] && !rhs_[i] && borrow) || 
			(!lhs_[i] && rhs_[i] && !borrow) || 
			(!lhs_[i] && rhs_[i] && borrow) || 
			(lhs_[i] && rhs_[i] && borrow);
	}
	result._sign = negative;
	result.normalize();
	return result;
}

BigInteger& operator++(BigInteger& op)
{
	op += 1;
	return op;
}

BigInteger& operator--(BigInteger& op)
{
	op -= 1;
	return op;
}

BigInteger operator++(BigInteger& op, int)
{
	BigInteger tmp = op;
	op += 1;
	return tmp;
}

BigInteger operator--(BigInteger& op, int)
{
	BigInteger tmp = op;
	op -= 1;
	return tmp;
}

const BigInteger operator<<(const BigInteger& lhs, const int& rhs)
{
	if (rhs < 0) return lhs >> -rhs;
	BigInteger result;
	result._sign = lhs._sign;
	result._data.resize(lhs.log2() + rhs, 0);
	for (size_t i = 0; i < lhs.log2(); i++) result._data[rhs + i] = lhs[i];
	result.normalize();
	return result;
}

const BigInteger operator>>(const BigInteger& lhs, const int& rhs)
{
	if (rhs < 0) return lhs << -rhs;
	if ((size_t) rhs >= lhs.log2()) return 0;
	BigInteger result;
	result._sign = lhs._sign;
	result._data.resize(lhs.log2() - rhs, 0);
	for (size_t i = 0; i < result.log2(); i++) result._data[i] = lhs[i + rhs];
	result.normalize();
	return result;
}

const BigInteger operator&(const BigInteger& lhs, const BigInteger& rhs)
{
	BigInteger result;
	result._sign = lhs._sign && rhs._sign;
	result._data.resize(max(lhs.log2(), rhs.log2()), 0);
	for (size_t i = 0; i < result.log2(); i++) result._data[i] = lhs[i] && rhs[i];
	result.normalize();
	return result;
}

const BigInteger operator|(const BigInteger& lhs, const BigInteger& rhs)
{
	BigInteger result;
	result._sign = lhs._sign || rhs._sign;
	result._data.resize(max(lhs.log2(), rhs.log2()), 0);
	for (size_t i = 0; i < result.log2(); i++) result._data[i] = lhs[i] || rhs[i];
	result.normalize();
	return result;
}

const BigInteger operator*(const BigInteger& lhs, const BigInteger& rhs)
{
	if (lhs._sign || rhs._sign)
	{
		BigInteger result = lhs.abs()*rhs.abs();
		result._sign = lhs._sign != rhs._sign;
		result.normalize();
		return result;
	}

	if (lhs > rhs) return rhs*lhs;
	if (lhs == 1) return rhs;
	if (lhs == 0) return 0;
	if (rhs == 1) return lhs;
	if (rhs == 0) return 0;

	if (rhs & 1)
	{
		BigInteger result = lhs*(rhs >> 1);
		result.normalize();
		return result + result + lhs;
	}
	else
	{
		BigInteger result = lhs*(rhs >> 1);
		result.normalize();
		return result + result;
	}
}

const BigInteger operator/(const BigInteger& lhs, const BigInteger& rhs)
{
	if (rhs == 0) throw 1;
	if (lhs == 0) return 0;

	if (lhs._sign || rhs._sign)
	{
		BigInteger result = lhs.abs()/rhs.abs();
		result._sign = lhs._sign != rhs._sign;
		result.normalize();
		return result;
	}

	if (lhs < rhs) return 0;
	
	BigInteger rem = lhs >> (lhs.log2() - rhs.log2() + 1);
	BigInteger div;
	div._data.clear();
	for (int i = lhs.log2() - rhs.log2(); i >= 0; i--)
	{
		rem = (rem << 1) | lhs[i];
		if (rem >= rhs) 
		{
			div._data.push_back(1);
			rem -= rhs;
		}
		else div._data.push_back(0);
	}

	for (size_t i = 0; 2*i < div.log2(); i++)
		std::swap(div._data[i], div._data[div.log2() - 1 - i]);
	
	div.normalize();
	return div;
}

const BigInteger operator%(const BigInteger& lhs, const BigInteger& rhs)
{
	if (rhs == 0) throw 1;
	return lhs - (lhs / rhs)*rhs;
}

const BigInteger pow(const BigInteger& lhs, const BigInteger& rhs)
{
	if (rhs._sign) throw 1;
	if (lhs._sign)
	{
		BigInteger result = pow(-lhs, rhs);
		if (rhs & 1) result._sign = true;
		result.normalize();
		return result;
	}

	if (rhs == 0) return 1;
	if (lhs == 0) return 0;

	if (rhs & 1)
	{
		BigInteger result = pow(lhs, rhs >> 1);
		result.normalize();
		return result*result*lhs;
	}
	else
	{
		BigInteger result = pow(lhs, rhs >> 1);
		result.normalize();
		return result*result;
	}
}

const BigInteger gcd(const BigInteger& lhs, const BigInteger& rhs)
{
	if (rhs == 0_bi && lhs == 0_bi) 
		return 1;
	if (rhs == 0_bi)
		return lhs;
	return gcd(rhs, lhs % rhs);
}

const BigInteger lcm(const BigInteger& lhs, const BigInteger& rhs)
{
	return (lhs/gcd(lhs, rhs))*rhs;
}

bool operator==(const BigInteger& lhs, const BigInteger& rhs)
{
	if (lhs._sign != rhs._sign) return false;
	if (lhs.log2() != rhs.log2()) return false;
	for (size_t i = 0; i < lhs.log2(); i++)
	{
		if (lhs[i] != rhs[i]) return false;
	}
	return true;
}

bool operator!=(const BigInteger& lhs, const BigInteger& rhs)
{
	return !(lhs == rhs);
}

bool operator<(const BigInteger& lhs, const BigInteger& rhs)
{
	if (lhs._sign == true && rhs._sign == false) return true;
	if (lhs._sign == false && rhs._sign == true) return false;
	bool negative = lhs._sign && rhs._sign;
	if (lhs.log2() < rhs.log2()) return !negative;
	for (int i = max(lhs.log2(), rhs.log2()) - 1; i >= 0; i--)
	{
		if (lhs[i] && !rhs[i]) return negative;
		if (!lhs[i] && rhs[i]) return !negative;
	}

	return false;
}

bool operator>(const BigInteger& lhs, const BigInteger& rhs)
{
	return rhs < lhs;
}

bool operator<=(const BigInteger& lhs, const BigInteger& rhs)
{
	return (lhs < rhs) || (lhs == rhs);
}

bool operator>=(const BigInteger& lhs, const BigInteger& rhs)
{
	return (lhs > rhs) || (lhs == rhs);
}

BigInteger& operator+=(BigInteger& lhs, const BigInteger& rhs)
{
	lhs = lhs + rhs;
	return lhs;
}

BigInteger& operator-=(BigInteger& lhs, const BigInteger& rhs)
{
	lhs = lhs - rhs;
	return lhs;
}

BigInteger& operator*=(BigInteger& lhs, const BigInteger& rhs)
{
	lhs = lhs * rhs;
	return lhs;
}

BigInteger& operator/=(BigInteger& lhs, const BigInteger& rhs)
{
	lhs = lhs / rhs;
	return lhs;
}

BigInteger& operator%=(BigInteger& lhs, const BigInteger& rhs)
{
	lhs = lhs % rhs;
	return lhs;
}

bool operator==(const BigInteger& lhs, const bool& rhs)
{
	return bool(lhs) == rhs;
}

bool operator==(const bool& lhs, const BigInteger& rhs)
{
	return lhs == bool(rhs);
}

bool operator!=(const BigInteger& lhs, const bool& rhs)
{
	return bool(lhs) == rhs;
}

bool operator!=(const bool& lhs, const BigInteger& rhs)
{
	return lhs == bool(rhs);
}

std::ostream& operator<<(std::ostream& out, const BigInteger& op)
{
	out << op.toString();
	return out;
}

template<typename T>
inline const T max(T lhs, T rhs)
{
	return lhs > rhs ? lhs : rhs;
}

std::istream& operator>>(std::istream& in, BigInteger& op)
{
	std::string str;
	in >> str;
	op = BigInteger(str);
	return in;
}

// RATIONAL.HPP


const char* ZERO_INVERSE_MSG = "Error: 0 has no inverse";
const int ZERO_INVERSE = 1;

const double EPSILON = 1e-18;

class Rational;

const Rational operator""_br(unsigned long long int);

const Rational operator-(const Rational&);
const Rational operator+(const Rational&, const Rational&);
const Rational operator-(const Rational&, const Rational&);
const Rational operator*(const Rational&, const Rational&);
const Rational operator/(const Rational&, const Rational&);
Rational& operator+=(Rational&, const Rational&);
Rational& operator-=(Rational&, const Rational&);
Rational& operator*=(Rational&, const Rational&);
Rational& operator/=(Rational&, const Rational&);
bool operator==(const Rational&, const Rational&);
bool operator!=(const Rational&, const Rational&);
bool operator<(const Rational&, const Rational&);
bool operator>(const Rational&, const Rational&);
bool operator<=(const Rational&, const Rational&);
bool operator>=(const Rational&, const Rational&);

class Rational
{
	BigInteger _numerator;
	BigInteger _denominator;

	void normalize();

	friend const Rational operator-(const Rational&);
	friend Rational& operator-=(Rational&, const Rational&);
	friend Rational& operator+=(Rational&, const Rational&);
	friend Rational& operator*=(Rational&, const Rational&);
	friend Rational& operator/=(Rational&, const Rational&);
	friend bool operator==(const Rational&, const Rational&);
	friend bool operator<(const Rational&, const Rational&);
	friend bool operator>(const Rational&, const Rational&);

public:

	Rational();

	Rational(const BigInteger&);

	Rational(const long long&);

	Rational(const BigInteger&, const BigInteger&);

	Rational(const long long&, const long long&);

	const std::string toString() const;

	const std::string asDecimal(size_t) const;

	explicit operator double() const;
};

Rational::Rational()
{
	_numerator = 0_bi;
	_denominator = 1_bi;
}

Rational::Rational(const BigInteger& val)
{
	_numerator = val;
	_denominator = 1_bi;
}

Rational::Rational(const long long& val) : Rational(BigInteger(val))
{
	
}

Rational::Rational(const BigInteger& num, const BigInteger& den)
{
	_numerator = num;
	_denominator = den;
	normalize();
}

Rational::Rational(const long long& num, const long long& den) : Rational(BigInteger(num), BigInteger(den))
{
	
}

const std::string Rational::toString() const
{
	std::string result = _numerator.toString();
	if (_denominator != 1_bi) result += "/" + _denominator.toString();
	return result;
}

const std::string Rational::asDecimal(size_t precision = 0) const
{
	BigInteger tmp = (_numerator.abs() * pow(10_bi, precision + 1)) / _denominator;
	if (tmp % 10_bi > 5_bi) tmp = (tmp / 10_bi) + 1_bi;
	else tmp /= 10_bi;
	std::string result = tmp.toString();
	
	while (result.size() <= precision) result = "0" + result;

	if (precision != 0)
	{
		size_t mantissa = result.size() - precision;
		result = result.substr(0, mantissa) + "." + result.substr(mantissa, precision);
	}
	
	if (_numerator < 0_bi) result = "-" + result;
	return result;
}

void Rational::normalize()
{
	BigInteger tmp = gcd(_numerator.abs(), _denominator);
	_numerator /= tmp;
	_denominator /= tmp;
}

Rational::operator double() const
{
	double result = (long long) (_numerator.abs() / _denominator); //integer part

	double old_result = result;
	BigInteger numerator = _numerator.abs() % _denominator;
	double denominator = 1;
	do
	{
		old_result = result;
		numerator *= 10;
		denominator *= 10;
		result += (long long)((numerator / _denominator) % 10) / denominator;
	}
	while (std::abs(old_result - result) > EPSILON); //do till we run out of precision

	return result * (*this < 0 ? -1 : 1);
}

const Rational operator""_br(unsigned long long int literal)
{
    return Rational(literal);
}

const Rational operator-(const Rational& op)
{
	Rational result = op;
	result._numerator = -result._numerator;
	result.normalize();
	return result;
}

const Rational operator+(const Rational& lhs, const Rational& rhs)
{
	Rational result = lhs;
	return result += rhs;
}

const Rational operator-(const Rational& lhs, const Rational& rhs)
{
	return lhs + -rhs;
}

const Rational operator*(const Rational& lhs, const Rational& rhs)
{
	Rational result = lhs;
	return result *= rhs;
}

const Rational operator/(const Rational& lhs, const Rational& rhs)
{
	Rational result = lhs;
	return result /= rhs;
}

Rational& operator+=(Rational& lhs, const Rational& rhs)
{
	lhs._numerator = lhs._numerator*rhs._denominator + rhs._numerator*lhs._denominator;
	lhs._denominator = lhs._denominator*rhs._denominator;
	lhs.normalize();
	return lhs;
}

Rational& operator-=(Rational& lhs, const Rational& rhs)
{
	return lhs += -rhs;
}

Rational& operator*=(Rational& lhs, const Rational& rhs)
{
	lhs._numerator *= rhs._numerator;
	lhs._denominator *= rhs._denominator;
	lhs.normalize();
	return lhs;
}

Rational& operator/=(Rational& lhs, const Rational& rhs)
{
	if (rhs == 0_br) 
	{
		std::cerr << ZERO_INVERSE_MSG << std::endl;
		throw ZERO_INVERSE;
	}

	lhs._numerator *= rhs._denominator * rhs._numerator.sgn();
	lhs._denominator *= rhs._numerator.abs();
	
	lhs.normalize();
	return lhs;
}

bool operator==(const Rational& lhs, const Rational& rhs)
{
	return lhs._numerator == rhs._numerator && lhs._denominator == rhs._denominator;
}

bool operator!=(const Rational& lhs, const Rational& rhs)
{
	return !(lhs == rhs);
}

bool operator<(const Rational& lhs, const Rational& rhs)
{
	return lhs._numerator*rhs._denominator < rhs._numerator*lhs._denominator;
}

bool operator>(const Rational& lhs, const Rational& rhs)
{
	return lhs._numerator*rhs._denominator > rhs._numerator*lhs._denominator;
}

bool operator<=(const Rational& lhs, const Rational& rhs)
{
	return !(lhs > rhs);
}

bool operator>=(const Rational& lhs, const Rational& rhs)
{
	return !(lhs < rhs);
}

std::ostream& operator<<(std::ostream& out, const Rational& op)
{
	out << op.toString();
	return out;
}
