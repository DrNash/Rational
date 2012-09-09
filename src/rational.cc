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


///////////////////////////////////////////////////////////
//
// Static Rational oriented math helpers

int *Rational::findPrimeFactors(int number, int &finalArraySize) {
	// Lets pretend negative numbers have prime factors
	// (Math is digusted at me for saying this)
	number < 0 ? number *= -1 : number;

	// The number 1 is prime and its only prime factor
	if(number == 1) {
		int *arrayOfOne = new int[1];
		arrayOfOne[0] = 1;
		return arrayOfOne;
	}

	// For any other number, keep finding prime factors
	// and dividing the number by them until all factors
	// have been found
	int *workArray = new int[50];
	finalArraySize = 0;

	for(int i=0; i < number; i++) {
		for(int x=2; x <= number; x++) {
			if(number % x == 0) {
				workArray[i] = x;
				number /= x;
				finalArraySize++;
				break;
			}
		}
	}

	// We want the returned array to only be the size of the 
	// amount of prime factors
	int *primeFactorArray = new int[finalArraySize];
	for(int i=0; i < finalArraySize; i++){
		primeFactorArray[i] = workArray[i];
	}

	return primeFactorArray;
}

Rational Rational::reduceFractionToLowestTerms(Rational fatRat) {
	int numeratorSize, denominatorSize;
	int *numeratorPrimeFactors = findPrimeFactors(fatRat.getNumerator(), numeratorSize);
	int *denominatorPrimeFactors = findPrimeFactors(fatRat.getDenominator(), denominatorSize);

	int numberOfSharedFactors;
	// workArray won't need to be greater than the smallest prime factors
	int *workArray[(numeratorSize<denominatorSize ? numeratorSize : denominatorSize)];
	for(int i = 0; i < numeratorSize; i++) {
		for(int j = 0; j < denominatorSize; j++) {
			if(numeratorPrimeFactors[i] == denominatorPrimeFactors[j]) {
				numberOfSharedFactors++;
//				workArray[i] = numeratorPrimeFactors[i];
			}
		}
	}

}

///////////////////////////////////////////////////////////
//
// Helpers

double Rational::abs(double number)  {  
  return (number > 0.0 ? number : number * -1);  
} 