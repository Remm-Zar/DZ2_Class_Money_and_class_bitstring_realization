#include <iostream>
#include "Money.h"
using namespace std;
Money operator*(const Money& m, double n)
{
	double total = ((double)m.GetRubles() * 100 + m.GetKopeyki()) * n / 100;//оепедекюмн
	long R = int(total);
	unsigned char K = (int)(total * 100) % 100;
	return Money(R, K);
}
 Money operator*(double n, const Money& m)
 {
	 return m * n;
 }