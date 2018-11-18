#include <iostream>
#include <iomanip>
#include <string>
#include "rational.hpp"


int main(int argc, const char* argw[])
{
	if (argc == 2)
	{
		BigInteger a(argw[1]);
		std::cout << a;
	}
	else if (argc == 3)
	{
		BigInteger p = BigInteger(argw[1]);
		BigInteger q = BigInteger(argw[2]);
		Rational a(p, q);
		std::cout << std::fixed << std::setprecision(18) << double(a);
	}
	else if (argc == 4)
	{
		BigInteger p = BigInteger(argw[1]);
		BigInteger q = BigInteger(argw[2]);
		size_t precision = std::stod(argw[3]);
		Rational a(p, q);
		std::cout << std::fixed << std::setprecision(precision) << a.asDecimal(precision);
	}
}
