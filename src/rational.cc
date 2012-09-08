#include <iostream>
#include "rational.h"

Rational::Rational(int numerator) : numerator_(numerator), denominator_(1) {}
Rational::Rational(int numerator, int denominator) : numerator_(numerator), denominator_(denominator) {}

Rational::Rational(double floatRational) {
	char buffer[65];
	int n;
	n=sprintf(buffer, "%f", floatRational);
	
	for(int x = n-1; x >= 0; x--) {
		bool endOfFloat = false;
		if(buffer[x] == 48 && !endOfFloat) {
			n--;
		}
		else {
			endOfFloat = true;
		}
	}

	printf("%d", n);
	printf("%s", buffer);

	int multple = 1;
	numerator_ = 0;
	for(int i = 0; i < n; i++) {
		if(buffer[i] != 46) {
			numerator_ *= multple;
			numerator_ += std::atoi(&buffer[i]);
			multple *= 10;
		}
	}	


}

double Rational::abs(double number)  
{  
  return (number > 0.0 ? number : number * -1);  
}  