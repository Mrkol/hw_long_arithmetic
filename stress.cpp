#include <iostream>
#include "biginteger.h"


int main(int charc, const char* argw[])
{
	BigInteger a(argw[1]);
	BigInteger b(argw[3]);
	BigInteger c;
	switch (argw[2][0])
	{
		case '+':
			c = a + b;
			break;

		case '-':
			c = a - b;
			break;

		case '*':
			c = a * b;
			break;

		case '%':
			c = a % b;
			break;

		case '/':
			c = a / b;
			break;

		case '^':
			c = pow(a, b);
			break;

		case 'g':
			c = gcd(a, b);
			break;

		case 'l':
			c = lcm(a, b);
			break;
	}
	std::cout << c;
}