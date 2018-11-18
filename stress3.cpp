#include <iostream>
#include "rational.h"


int main(int charc, const char* argw[])
{
	BigInteger a(argw[1]);
	BigInteger b(argw[2]);
	BigInteger p(argw[4]);
	BigInteger q(argw[5]);
	Rational c;
	switch (argw[3][0])
	{
		case '+':
			c = Rational(a, b) + Rational(p, q);
			break;

		case '-':
			c = Rational(a, b) - Rational(p, q);
			break;

		case '*':
			c = Rational(a, b) * Rational(p, q);
			break;

		case '/':
			c = Rational(a, b) / Rational(p, q);
			break;
	}
	std::cout << c;
}