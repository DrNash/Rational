#include <iostream>
#include <stdio.h>
#include "rational.h"

Rational::Rational(int numerator) : numerator_(numerator), denominator_(1) {}
Rational::Rational(int numerator, int denominator) : numerator_(numerator), denominator_(denominator) {
	reduceSelfToLowestTerms();
}

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

// reduceSelfToLowestTerms
//		Given a Rational object (this), if it is not in lowest terms
//		already, reduce it so. This function gets 2 arrays of the 
//		prime factors of the numerator and denominator for the
//		Rational, finds their like terms, then multiples those like
//		terms to find the Greatest Common Factor of both. Divide the
//		GCF into each and bam, reduced fraction.
//
void Rational::reduceSelfToLowestTerms() {
	int numeratorSize, denominatorSize;
	int *numeratorPrimeFactors = findPrimeFactors(numerator_, numeratorSize);
	int *denominatorPrimeFactors = findPrimeFactors(denominator_, denominatorSize);

	// workArray won't need to be greater than the smallest prime factors
	int *workArray = new int[(numeratorSize<denominatorSize ? numeratorSize : denominatorSize)];
	int numberOfSharedFactors = 0;
	int x = 0;

	for(int i = 0; i < numeratorSize; i++) {
		for(int j = x; j < denominatorSize; j++) {
			if(numeratorPrimeFactors[i] == denominatorPrimeFactors[j]) {
				x = j + 1;
				workArray[numberOfSharedFactors] = numeratorPrimeFactors[i];
				numberOfSharedFactors++;
				break;
			}
		}
	} 

	// Now the greatest common factor is the common primes multiplied
	int gcf = 0;  // greatest common factor
	for(int i = 0; i < numberOfSharedFactors; i++) {
		gcf += workArray[i];
	}
	delete [] workArray; 

	// If no GCF, num and den stay the same
	if(gcf > 0) {
		numerator_ /= gcf;
		denominator_ /= gcf;
	}
}

///////////////////////////////////////////////////////////
//
// Binary Arithmatic Functions

Rational Rational::add(int summand) {
	Rational resultingRational = Rational();
	int resultP = numerator_ + (summand * denominator_);

	resultingRational.set(resultP, denominator_);

	return resultingRational;
}

Rational Rational::add(Rational summand) {
	Rational resultingRational = Rational();
	int commonDenominator = denominator_ * summand.getDenominator();
	int leftNumerator = numerator_ * summand.getDenominator();
	int rightNumerator = summand.getNumerator() * denominator_;

	resultingRational.set((leftNumerator + rightNumerator), commonDenominator);
	// Since we did addition, ensure Rational is still in lowest terms
	resultingRational.reduceSelfToLowestTerms();

	return resultingRational;
}

Rational Rational::subtract(int subtrahend) {
	Rational resultingRational = Rational();
	int resultP = numerator_ - (subtrahend * denominator_);

	resultingRational.set(resultP, denominator_);

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


//	findPrimeFactors
//		Given an int (number) and a int by reference (finalArraySize)
//		findPrimeFactors will return an array of the prime factors
//		of the number, and set the given reference int to the size
//		of the resulting array.
//
int *Rational::findPrimeFactors(int number, int &finalArraySize) {
	// Lets pretend negative numbers have prime factors
	// (Math is digusted at me for saying this)
	number < 0 ? number *= -1 : number;

	// The number 1 is special, return array of 1
	if(number == 1) {
		int *arrayOfOne = new int[1];
		arrayOfOne[0] = 1;
		finalArraySize = 1;
		return arrayOfOne;
	}

	// For any other number, keep finding prime factors
	// and dividing 'number' by them until all factors
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

	delete [] workArray;

	return primeFactorArray;
}

// reduceFractionToLowestTerms
//		Given a Rational object (fatRat), if it is not in lowest terms
//		already, reduce it so.  I created this as a static method because
//		I wanted to thoroughly test drive the implementation and the
// 		eventual reduceSelfToLowestTerms method would be private. After
//		the implementation was proved the refactoring left this static method
//		simple and still useful for the Rational class overall, so I left it.
//
Rational Rational::reduceFractionToLowestTerms(Rational fatRat) {
	fatRat.reduceSelfToLowestTerms();
	return fatRat;
}

///////////////////////////////////////////////////////////
//
// Helpers

double Rational::abs(double number)  {  
  return (number > 0.0 ? number : number * -1);  
} 