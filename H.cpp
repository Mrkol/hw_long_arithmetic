#include <iostream>
#include <iomanip>
#include "rational.h"


int main()
{
	std::cout << std::fixed << std::setprecision(18);

	std::cout << std::endl << "Unary minus" << std::endl;

	std::cout << (-Rational(12345) == Rational(-12345));
	std::cout << (Rational(98765) == -Rational(-98765));
	std::cout << (-0_br == 0_br);

	std::cout << std::endl << "GCD" << std::endl;

	std::cout << (gcd(10_bi, 5_bi) == 5_bi);
	std::cout << (gcd(15_bi, 25_bi) == 5_bi);
	std::cout << (gcd(35_bi, 49_bi) == 7_bi);
	std::cout << (gcd(81_bi, 27_bi) == 27_bi);
	std::cout << (gcd(301_bi, 3_bi) == 1_bi);

	std::cout << std::endl << "Addition" << std::endl;

	std::cout << (13/20_br + 7/20_br == 1_br);
	std::cout << (11/40_br + 11/20_br == 33/40_br);
	std::cout << (3/4_br - 1/2_br == 1/4_br);
	std::cout << (0_br + 4_br - 3_br - 1_br == 0_br);

	std::cout << std::endl << "Multiplication" << std::endl;

	std::cout << (1/2_br * 1/4_br == 1/8_br);
	std::cout << (1/4_br * 2/3_br == 1/6_br);
	std::cout << (-1/4_br * -4/3_br == 1/3_br);
	std::cout << (1/4_br * 0_br == 0_br);
	std::cout << ((1/4_br) / (4/7_br) == 7/16_br);

	std::cout << std::endl << "As decimal" << std::endl;

	std::cout << ((1/322_br).asDecimal() == "0");
	std::cout << ((32/31_br).asDecimal() == "1");
	std::cout << ((-64/31_br).asDecimal() == "-2");
	std::cout << ((1/9_br).asDecimal(7) == "0.1111111");
	std::cout << ((-1/3_br).asDecimal(20) == "-0.33333333333333333333");
	std::cout << ((-7/3_br).asDecimal(20) == "-2.33333333333333333333");
	std::cout << ((66/100_br).asDecimal(1) == "0.7");
	std::cout << ((-66/100_br).asDecimal(1) == "-0.7");
	std::cout << ((64/100_br).asDecimal(1) == "0.6");
	std::cout << ((-64/100_br).asDecimal(1) == "-0.6");
	std::cout << ((65/100_br).asDecimal(1) == "0.6");
	std::cout << ((-65/100_br).asDecimal(1) == "-0.6");

	std::cout << std::endl << "To double" << std::endl;

	std::cout << (abs(double(1/9_br) - (1.0/9.0)) < 0.0000000001);
	std::cout << (abs(double(-1/3_br) - (-1.0/3.0)) < 0.0000000001);
	std::cout << (abs(double(-7/3_br) - (-7.0/3.0)) < 0.0000000001);

	std::cout << std::endl << "To string" << std::endl;

	std::cout << ((1/9_br).toString() == "1/9");
	std::cout << ((-1/3_br).toString() == "-1/3");
	std::cout << ((-7/3_br).toString() == "-7/3");
	std::cout << ((-322/3_br).toString() == "-322/3");
	std::cout << ((-0_br).toString() == "0");


	return 0;
}