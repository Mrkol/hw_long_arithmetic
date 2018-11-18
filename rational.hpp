#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include "biginteger.hpp"

#pragma once

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
