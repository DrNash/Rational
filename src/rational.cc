#include <iostream>
#include "rational.h"

Rational::Rational(int numerator) : numerator_(numerator), denominator_(1) {}
Rational::Rational(int numerator, int denominator) : numerator_(numerator), denominator_(denominator) {}

Rational::Rational(double floatRational) {
	numerator_ = 51;
	denominator_ = 10;
	/* char buffer[65];
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
	denominator_ = 1;
	for(int i = 0; i < n; i++) {
		if(buffer[i] != 46) {
			numerator_ *= multple;
			numerator_ += std::atoi(&buffer[i]);
			multple *= 10;
			denominator_ *= 10;
		}
	}	*/


}

///////////////////////////////////////////////////////////
//
// Binary Arithmatic Functions

Rational Rational::add(int summand) {
	Rational resultingRational = Rational();
	int resultP = numerator_ + (summand * denominator_);
	int resultQ = denominator_;

	resultingRational.set(resultP, resultQ);

	return resultingRational;
}

Rational Rational::add(Rational summand) {
	Rational resultingRational = Rational();
	int commonDenominator = denominator_ * summand.getDenominator();
	int leftNumerator = numerator_ * summand.getDenominator();
	int rightNumerator = summand.getNumerator() * denominator_;

	resultingRational.set((leftNumerator + rightNumerator), commonDenominator);

	return resultingRational;
}

///////////////////////////////////////////////////////////
//
// Getters and Setters

void Rational::set(int givenP) {
	numerator_ = givenP;
	denominator_ = 1;
}

void Rational::set(int givenP, int givenQ) {
	numerator_ = givenP;
	denominator_ = givenQ;
}


int *Rational::findPrimeFactors(int number) {
	int *someArr = new int[3];
	someArr[0] = 2; 
	someArr[1] = 2;
	someArr[2] = 5;
	return someArr;
}

///////////////////////////////////////////////////////////
//
// Helpers

double Rational::abs(double number)  {  
  return (number > 0.0 ? number : number * -1);  
} 

void Rational::reduceFractionToLowestTerms() {

}