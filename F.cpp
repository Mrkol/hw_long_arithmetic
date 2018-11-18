#include <iostream>
#include "biginteger.h"



int main()
{
	std::cout << "Unary minus" << std::endl;

	std::cout << (-BigInteger(12345) == BigInteger(-12345));
	std::cout << (BigInteger(98765) == -BigInteger(-98765));

	std::cout << std::endl << "Addition" << std::endl;

	std::cout << (29_bi + 10_bi == 39_bi);
	std::cout << (29_bi + -10_bi == 19_bi);
	std::cout << (-29_bi + 10_bi == -19_bi);
	std::cout << (-10_bi + -11_bi == -21_bi);

	std::cout << std::endl << "Inc/decrement" << std::endl;

	BigInteger a = 15;
	std::cout << (a-- == 15);
	std::cout << (a++ == 14);
	std::cout << (--a == 14);
	std::cout << (++a == 15);

	std::cout << std::endl << "Shift" << std::endl;

	std::cout << (8_bi >> 1 == 4);
	std::cout << (31_bi >> 1 == 15);
	std::cout << (69_bi >> 1 == 34);
	std::cout << (8_bi << 1 == 16);
	std::cout << (31_bi << 1 == 62);
	std::cout << (69_bi << 1 == 138);

	std::cout << std::endl << "Bool cast" << std::endl;

	std::cout << (0_bi == false);
	std::cout << (1_bi == true);
	std::cout << (-12_bi == true);
	std::cout << (33_bi == true);

	std::cout << std::endl << "Multiplication" << std::endl;

	std::cout << (2_bi * 2_bi == 4_bi);
	std::cout << (-2_bi * 2_bi == -4_bi);
	std::cout << (-2_bi * -2_bi == 4_bi);
	std::cout << (6_bi * 3_bi == 18_bi);
	std::cout << (5_bi * 7_bi == 35_bi);
	std::cout << (9_bi * 9_bi == 81_bi);
	std::cout << (228_bi * 322_bi == 322_bi * 228_bi);

	std::cout << std::endl << "Division" << std::endl;

	std::cout << (10_bi / 5_bi == 2_bi);
	std::cout << (16_bi / 4_bi == 4_bi);
	std::cout << (30_bi / 2_bi == 15_bi);
	std::cout << (32_bi / 3_bi == 10_bi);
	std::cout << (17_bi / -4_bi == -4_bi);
	std::cout << (-17_bi / 4_bi == -4_bi);

	std::cout << std::endl << "Modulo" << std::endl;

	std::cout << (10_bi % 5_bi == 0_bi);
	std::cout << (16_bi % 4_bi == 0_bi);
	std::cout << (30_bi % 2_bi == 0_bi);
	std::cout << (32_bi % 3_bi == 2_bi);
	std::cout << (17_bi % -4_bi == 1_bi);
	std::cout << (-17_bi % 4_bi == -1_bi);

	std::cout << std::endl << "Power" << std::endl;

	std::cout << (pow(2_bi, 4_bi) == 16_bi);
	std::cout << (pow(3_bi, 3_bi) == 27_bi);
	std::cout << (pow(-3_bi, 3_bi) == -27_bi);
	std::cout << (pow(-2_bi, 4_bi) == 16_bi);
	std::cout << (pow(2_bi, 40_bi) >= pow(2_bi, 30_bi));
	std::cout << (pow(2_bi, 9_bi) * pow(2_bi, 13_bi) == pow(2_bi, 22_bi));

	std::cout << std::endl << "Bitwise and/or" << std::endl;

	std::cout << ((10_bi & 13_bi) == 8_bi);
	std::cout << ((4_bi & 15_bi) == 4_bi);
	std::cout << ((9_bi & 23_bi) == 1_bi);
	std::cout << !((bool) (4_bi & 1_bi));
	std::cout << ((bool) (5_bi & 1_bi));
	std::cout << std::endl;
	std::cout << ((11_bi | 8_bi) == 11_bi);
	std::cout << ((5_bi | 17_bi) == 21_bi);
	std::cout << ((9_bi | 33_bi) == 41_bi);

	std::cout << std::endl << "Order" << std::endl;

	std::cout << (10_bi < 13_bi);
	std::cout << (5_bi < 333_bi);
	std::cout << (13_bi < 16_bi);
	std::cout << (9_bi < 16_bi);
	std::cout << (8_bi < 32_bi);
	std::cout << (-10_bi > -13_bi);
	std::cout << (-5_bi > -333_bi);
	std::cout << (-13_bi > -16_bi);
	std::cout << (-9_bi > -16_bi);
	std::cout << (-8_bi > -32_bi);
	std::cout << (10_bi <= 10_bi);
	std::cout << (-10_bi >= -11_bi);
	std::cout << (-10_bi <= -10_bi);

	std::cout << std::endl << "To int" << std::endl;

	std::cout << (int(10_bi) == 10);
	std::cout << (int(223_bi) == 223);

	std::cout << std::endl << "To string" << std::endl;

	std::cout << ((1234_bi).toString() == "1234");
	std::cout << ((3585329_bi).toString() == "3585329");
	std::cout << ((-12345_bi).toString() == "-12345");
	std::cout << ((-BigInteger(12345)).toString() == "-12345");
	std::cout << ((-10000_bi).toString() == "-10000");

	std::cout << std::endl << "From string" << std::endl;

	std::cout << (1234_bi == BigInteger("1234"));
	std::cout << (-1234567_bi == BigInteger("-1234567"));
	std::cout << (-552375432_bi == BigInteger("-552375432"));
	std::cout << (123456789_bi == -BigInteger("-123456789"));

	std::cout << std::endl;
	
	return 0;
}