#include "gtest/gtest.h"
#include "rational.h"

///////////////////////////////////////////////////////////
//
// Helper subroutines

void validateRational(Rational rat, int p, int q) {
	EXPECT_EQ(p, rat.getNumerator());
	EXPECT_EQ(q, rat.getDenominator());
}

void validateArraySameOrderedMembers(int size, int *a, int *b) {
	for(int i = 0; i < size; i++) {
		EXPECT_EQ(a[i], b[i]);
	}
}

///////////////////////////////////////////////////////////
//
// Tests

////////////////////////////////
//
// Constructor Tests

// Test zero numerator
TEST(Rational, RationalFromZeroPConstructor) {
	Rational myRat = Rational(0);

	validateRational(myRat, 0, 1);
}

// Test some arbitrary (or is it?) number for the numerator
TEST(Rational, RationalFromArbitraryPConstructor) {
	Rational myRat = Rational(42);

	validateRational(myRat, 42, 1);
}

// Test using negative numbers for the numberator
TEST(Rational, RationalFromNegativePConstructor) {
	Rational myRat = Rational(-28);

	validateRational(myRat, -28, 1);
}

TEST(Rational, RationalFromFloatingPointConstructor) {
	Rational myRat = Rational(5.1f);

	validateRational(myRat, 51, 10);
}

TEST(Rational, RationalFromPandQConstructor) {
	Rational myRat = Rational(1,2);

	validateRational(myRat, 1, 2);
}

TEST(Rational, RationalFromNegativePandQConstructor) {
	Rational myRat = Rational(-1,2);
	Rational myOtherRat = Rational(1,-2);

	validateRational(myRat, -1, 2);
	validateRational(myOtherRat, 1, -2);
}

TEST(Rational, RationalFromRationalConstructor) {
	Rational mySourceRat = Rational(1,2);
	Rational myRatRat = Rational(mySourceRat);

	validateRational(myRatRat, 1, 2);
}

////////////////////////////////
//
// Arithmatic Tests

TEST(Rational, Addition) {
	Rational myRat = Rational(1,2);

	Rational myResultRat = myRat.add(3);

	validateRational(myResultRat, 7, 2);
}

TEST(Rational, AddtionWithNegatives) {
	Rational myRat = Rational(-1,2);
	Rational myFriendsRat = Rational(1,2);

	Rational myResultRat = myRat.add(5);
	Rational myFriendsResultRat = myFriendsRat.add(-5);

	validateRational(myResultRat, 9, 2);
	validateRational(myFriendsResultRat, -9, 2);	
}

TEST(Rational, AdditionWithAnotherRational) {
	Rational myRat = Rational(1,2);
	Rational myAddingRat = Rational(3,4);

	Rational myResultRat = myRat.add(myAddingRat);

//	validateRational(myResultRat, 5, 4);
}

TEST(Rational, ReduceRationalToLowestTerms) {
	// When creating a non-reduced rational it should
	// automaticaly reduce it to lowest terms
	Rational myRat = Rational(6,4);

//	validateRational(myRat, 3,2);
}

TEST(Rational, FindPrimeFactors) {
	int *primeFactors = Rational::findPrimeFactors(20);
	int expectedArray[3] = {2,2,5};

	validateArraySameOrderedMembers(3, expectedArray, primeFactors);
}

TEST(Rational, AdditionIntoAWholeNumber) {
	Rational myRat = Rational(1,2);
}

