#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include "rational.h"

// Constructor with just num
// Make the denominator 1
//
Rational::Rational(const int numerator) : numerator_(numerator), denominator_(1) {}

// Constructor with both numerator and denominator
// Set internal variables appropriately, simplify and reduce
//
Rational::Rational(const int numerator, const int denominator) : numerator_(numerator), denominator_(denominator) {

	simplifySelf();
	reduceSelfToLowestTerms();
}

// Constructor fom double
// Create a Rational from double (lots of work) then
// properly assign the num/den. Simplification and 
// lowest terms done in floatToRational
//
Rational::Rational(const double floatRational) {
	Rational futureSelf = floatToRational(floatRational);
	numerator_ = futureSelf.getNumerator();
	denominator_ = futureSelf.getDenominator();
}

// Copy constructor
// Be sure we make deep copies of the internal variables, not just
// reference the original's variables in case the original goes
// out of scope or gets deleted
//
Rational::Rational(const Rational& original) {
	numerator_ = original.getNumerator();
	denominator_ = original.getDenominator();
}

// Assignment operator
// Ensure 
//Rational &operator=(const Rational& rightSide) {

// }

// floatToRational
//		Rather than mathematically compute the rational of the float
//		I push the float into a string (char *) to presrve its accuracy
//		(or lack of). In this format it is easier to move through each
//		position and build up the rational. When tried with math the
//		precision errors of floats kept skewing the results.
Rational Rational::floatToRational(const double floatRational) const {
	char buffer[65];
	int n;
	n=sprintf(buffer, "%f", floatRational);
	for(int x = n-1; x >= 0; x--) {
		if(buffer[x] == 48) {
			n--;
		}
		else {
			break;
		}
	}

	int num = 0;
	int den = 1;
	bool pastDecimal = false;
	for(int i = 0; i < n; i++) {
		if(buffer[i] != 46) {
			num *= 10;
			// To avoid atoi eating the whole number
			char temp = buffer[i];
			num += atoi(&temp);
			if(pastDecimal) { den *= 10; }
		} else {
			pastDecimal = true;
		}
	}

	if(floatRational < 0.0) { num *= -1; }

	Rational resultRational = Rational(num, den);
	resultRational.reduceSelfToLowestTerms();
	resultRational.simplifySelf();
	return resultRational;
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
	int gcf = 1;  // greatest common factor
	for(int i = 0; i < numberOfSharedFactors; i++) {
		gcf *= workArray[i];
	}
	delete [] workArray; 

	// If no GCF, num and den stay the same
	if(gcf > 0) {
		numerator_ /= gcf;
		denominator_ /= gcf;
	} 

	numerator_ == 0 ? denominator_ = 1 : denominator_;
}

// SimplifySelf
// 	Keep the negative always in the numerator, compensate
// 	for double negatives
//
void Rational::simplifySelf() {
	if(denominator_ < 0) {
		numerator_ *= -1;
		denominator_ *= -1;
	}
}

///////////////////////////////////////////////////////////
//
// Binary Arithmatic Functions

Rational Rational::add(const int summand) const {
	Rational resultingRational = Rational();
	int resultP = numerator_ + (summand * denominator_);

	resultingRational.set(resultP, denominator_);

	return resultingRational;
}

Rational Rational::add(const Rational summand) const {
	Rational resultingRational = Rational();
	int commonDenominator = denominator_ * summand.getDenominator();
	int leftNumerator = numerator_ * summand.getDenominator();
	int rightNumerator = summand.getNumerator() * denominator_;

	resultingRational.set((leftNumerator + rightNumerator), commonDenominator);

	return resultingRational;
}

Rational Rational::add(const double summand) const {
	Rational resultRational = Rational();
	Rational summandRational = floatToRational(summand);

	resultRational = add(summandRational);

	return resultRational;
}

Rational Rational::subtract(const int subtrahend) const {
	Rational resultingRational = Rational();
	int resultP = numerator_ - (subtrahend * denominator_);

	resultingRational.set(resultP, denominator_);

	return resultingRational;
}

Rational Rational::subtract(const Rational subtrahend) const {
	Rational resultingRational = Rational();
	int commonDenominator = denominator_ * subtrahend.getDenominator();
	int leftNumerator = numerator_ * subtrahend.getDenominator();
	int rightNumerator = subtrahend.getNumerator() * denominator_;

	resultingRational.set((leftNumerator - rightNumerator), commonDenominator);

	return resultingRational;
}

Rational Rational::subtract(const double subtrahend) const {
	Rational resultingRational = Rational();
	Rational subtrahendRational = floatToRational(subtrahend);

	resultingRational = subtract(subtrahendRational);
	return resultingRational;
}

Rational Rational::multiply(const int factor) const {
	Rational resultingRational = Rational();
	int resultP = numerator_ * factor;

	resultingRational.set(resultP, denominator_);

	return resultingRational;
}

Rational Rational::multiply(const Rational factor) const {
	Rational resultingRational = Rational();
	int newNumerator = numerator_ * factor.getNumerator();
	int newDenominator =  denominator_ * factor.getDenominator();

	resultingRational.set(newNumerator, newDenominator);

	return resultingRational;
}

Rational Rational::multiply(const double factor) const {
	Rational resultingRational = Rational();
	Rational factorRational = floatToRational(factor);

	resultingRational = multiply(factorRational);
	return resultingRational;
}

Rational Rational::divide(const int divisor) const {
	Rational resultingRational = Rational();
	int newDenominator = denominator_ * divisor;

	resultingRational.set(numerator_, newDenominator);

	return resultingRational;
}

Rational Rational::divide(const Rational divisor) const {
	if(divisor.getNumerator() == 0 ) {
		throw std::overflow_error("Divide by zero expection");
	}

	Rational resultingRational = Rational();

	//Multiply by reciprocal
	int newNumerator = numerator_ * divisor.getDenominator();
	int newDenominator =  denominator_ * divisor.getNumerator();

	resultingRational.set(newNumerator, newDenominator);

	return resultingRational;
}

Rational Rational::divide(const double divisor) const {
	Rational resultingRational = Rational();
	Rational divisorRational = floatToRational(divisor);

	resultingRational = divide(divisorRational);
	return resultingRational;
}

Rational Rational::pow(const int exponent) const {
	Rational resultingRational = Rational();

	int newNumerator;
	int newDenominator;

	
	if(exponent < 0) {
		newNumerator = pow(denominator_, (exponent * -1));
		newDenominator = pow(numerator_, (exponent * -1));
	} else {
		newNumerator = pow(numerator_, exponent);
	 	newDenominator = pow(denominator_, exponent);
	}

	resultingRational.set(newNumerator, newDenominator);

	return resultingRational;
}

void Rational::neg() {
	numerator_ *= -1;
}

void Rational::recip() {
	// Swap numerator and denominator
	int temp = numerator_;
	numerator_ = denominator_;
	denominator_ = temp;

	simplifySelf();
}

void Rational::abs() {
	numerator_ < 0 ? numerator_ *= -1 : numerator_;
}

void Rational::square() {
	Rational tempRat = pow(2);

	numerator_ = tempRat.getNumerator();
	denominator_ = tempRat.getDenominator();
	reduceSelfToLowestTerms();
	simplifySelf();
}


///////////////////////////////////////////////////////////
//
// Comparison Functions

bool Rational::lessThan(const Rational rat) const {
	// Find common ground
	int myCommonNum = rat.getDenominator() * numerator_;
	int theirCommonNum = rat.getNumerator() * denominator_;

	return (myCommonNum < theirCommonNum ? true : false);
}

bool Rational::greaterThan(const Rational rat) const {
	// Find common ground
	int myCommonNum = rat.getDenominator() * numerator_;
	int theirCommonNum = rat.getNumerator() * denominator_;

	return (myCommonNum > theirCommonNum ? true : false);
}

bool Rational::equal(const Rational rat) const {
	// Find common ground
	int myCommonNum = rat.getDenominator() * numerator_;
	int theirCommonNum = rat.getNumerator() * denominator_;

	return (myCommonNum  == theirCommonNum ? true : false);
}

bool Rational::greaterThanOrEqual(const Rational rat) const {
	// Find common ground
	int myCommonNum = rat.getDenominator() * numerator_;
	int theirCommonNum = rat.getNumerator() * denominator_;

	return (myCommonNum  >= theirCommonNum ? true : false);
}

bool Rational::lessThanOrEqual(const Rational rat) const {
	// Find common ground
	int myCommonNum = rat.getDenominator() * numerator_;
	int theirCommonNum = rat.getNumerator() * denominator_;

	return (myCommonNum  <= theirCommonNum ? true : false);
}

///////////////////////////////////////////////////////////
//
// Getters and Setters

void Rational::set(const int givenP) {
	numerator_ = givenP;
	denominator_ = 1;
	reduceSelfToLowestTerms();
	simplifySelf();
}

void Rational::set(const int givenP, const int givenQ) {
	numerator_ = givenP;
	denominator_ = givenQ;
	reduceSelfToLowestTerms();
	simplifySelf();
}

void Rational::set(const double floatNumber) {
	Rational floatRat = floatToRational(floatNumber);
	numerator_ = floatRat.getNumerator();
	denominator_ = floatRat.getDenominator();
}

double Rational::toDouble() const {
	return (1.0 * numerator_) / denominator_;
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
int *Rational::findPrimeFactors(const int number, int &finalArraySize) {
	// Lets pretend negative numbers have prime factors
	// (Math is digusted at me for saying this)
	int number_ = number;
	number_ < 0 ? number_ *= -1 : number_;

	// The number 1 is special, return array of 1
	if(number_ == 1) {
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

	for(int i=0; i < number_; i++) {
		for(int x=2; x <= number_; x++) {
			if(number_ % x == 0) {
				workArray[i] = x;
				number_ /= x;
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
// Stream Functions

void Rational::write(std::ostream& output) {
	output << getNumerator() << "/" << getDenominator();
}

void Rational::write(std::ostream& output, int outputType) {
	if(outputType == DECIMAL) {
		output << toDouble();
	} 
}

void Rational::read(std::istream& input) {
	float floatRational;
	input >> floatRational;

	set(floatRational);
}

///////////////////////////////////////////////////////////
//
// Helpers

double Rational::abs(const double number) const {  
  return (number > 0.0 ? number : number * -1);  
} 

int Rational::pow(const int base, const int exponent) const {
	int result = 1;
	for(int i = 0; i < exponent; i++) {
		result *= base;
	}

	return result;
}