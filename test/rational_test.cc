#include "gtest/gtest.h"
#include "rational.h"

///////////////////////////////////////////////////////////
//
// Helper subroutines for validation

void validateRational(Rational rat, int p, int q) {
	EXPECT_EQ(p, rat.getNumerator());
	EXPECT_EQ(q, rat.getDenominator());
}

void intArrayEqual(int size, int *a, int *b) {
	for(int i = 0; i < size; i++) {
		EXPECT_EQ(a[i], b[i]);
	}
}

void charArrayEqual(int size, const char *a, const char *b) {
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
	Rational myRat = Rational(5.1);
	Rational myFriendsRat = Rational(10.25);
	Rational hisFriendsRat = Rational(1111.3333);
	Rational myDownerRat = Rational(-10.44);

	validateRational(myRat, 51, 10);
	validateRational(myFriendsRat, 41, 4);
	validateRational(hisFriendsRat, 11113333,10000);
	validateRational(myDownerRat, -261, 25);
}

TEST(Rational, RationalFromPandQConstructor) {
	Rational myRat = Rational(1,2);

	validateRational(myRat, 1, 2);
}

TEST(Rational, RationalFromNegativePandQConstructor) {
	Rational myRat = Rational(-1,2);
	Rational myOtherRat = Rational(1,-2);
	Rational myThirdRat = Rational(-1,-2);

	validateRational(myRat, -1, 2);
	validateRational(myOtherRat, -1, 2);
	validateRational(myThirdRat, 1, 2);
}

TEST(Rational, RationalFromRationalConstructor) {
	Rational mySourceRat = Rational(1,2);
	Rational myRatRat = Rational(mySourceRat);

	validateRational(myRatRat, 1, 2);
}

TEST(Rational, RationalFromPandQUnreducedConstructor) {
	Rational myRat = Rational(20,5);

	validateRational(myRat, 4, 1);
}

TEST(Rational, CopyConstructorTest) {
	Rational * myRat = new Rational(20,5);
	Rational * friendlyRat = new Rational(*myRat);

	delete [] myRat;
	myRat = new Rational(100,101);

	validateRational((*friendlyRat), 4 ,1);
}

TEST(Rational, AssignmentTest) {
	Rational friendlyRat = Rational(5,5);
	Rational meanRat = friendlyRat;
	friendlyRat.set(2,3);

	validateRational(meanRat, 1 ,1);
	validateRational(friendlyRat, 2, 3);
}

////////////////////////////////
//
// Arithmatic Tests


//////////////////
// 
// Addition

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

	validateRational(myResultRat, 5, 4);
}

TEST(Rational, AdditionWithANegativeRational) {
	Rational myRat = Rational(1,2);
	Rational myAddingRat = Rational(-3,4);

	Rational myResultRat = myRat.add(myAddingRat);

	validateRational(myResultRat, -1, 4);
}

TEST(Rational, AdditionWithAZeroRational) {
	Rational myRat = Rational(1,2);
	Rational myAddingRat = Rational(0);

	Rational myResultRat = myRat.add(myAddingRat);

	validateRational(myResultRat, 1, 2);
}

TEST(Rational, AdditionWithFloats) {
	Rational myRat = Rational(1,2);

	Rational myResultRat = myRat.add(3.5);

	validateRational(myResultRat, 4, 1);

	myResultRat = myRat.add(0.0);
	validateRational(myResultRat, 1 , 2);
}

TEST(Rational, AddtionWithNegativeFloats) {
	Rational myRat = Rational(-1,2);
	Rational myFriendsRat = Rational(1,2);

	Rational myResultRat = myRat.add(0.5);
	Rational myFriendsResultRat = myFriendsRat.add(-2.5);

	validateRational(myResultRat, 0, 1);
	validateRational(myFriendsResultRat, -2, 1);	
}

TEST(Rational, AdditionWithAnotherRationalConst) {
	Rational myRat = Rational(1,2);
	Rational const myAddingRat = Rational(3,4);

	Rational myResultRat = myRat.add(myAddingRat);

	validateRational(myResultRat, 5, 4);
}

//////////////////
// 
// Subtraction

TEST(Rational, SubtractionWithWholeNumber) {
	Rational myRat = Rational(4,3);

	Rational myDifferenceRat = myRat.subtract(5);

	validateRational(myDifferenceRat, -11, 3);
}

TEST(Rational, SubtractionWithNegativeWholeNumber) {
	Rational myRat = Rational(4,3);

	Rational myDifferenceRat = myRat.subtract(-5);

	validateRational(myDifferenceRat, 19, 3);
}

TEST(Rational, SubtractionWithZero) {
	Rational myRat = Rational(4,3);

	Rational myDifferenceRat = myRat.subtract(0);

	validateRational(myDifferenceRat, 4, 3);
}

TEST(Rational, SubtractionWithAnotherRational) {
	Rational myRat = Rational(5,2);
	Rational mySubtrahendRat = Rational(1,4);
	Rational myDifferenceRat = myRat.subtract(mySubtrahendRat);

	validateRational(myDifferenceRat, 9, 4);
}

TEST(Rational, SubtractionWithANegativeRational) {
	Rational myRat = Rational(1,2);
	Rational myDifferenceRat = Rational(-3,4);

	Rational myResultRat = myRat.subtract(myDifferenceRat);

	validateRational(myResultRat, 5, 4);
}

TEST(Rational, SubtractionWithAZeroRational) {
	Rational myRat = Rational(1,2);
	Rational myDifferenceRat = Rational(0);

	Rational myResultRat = myRat.subtract(myDifferenceRat);

	validateRational(myResultRat, 1, 2);
}

TEST(Rational, SubtractionWithFloats) {
	Rational myRat = Rational(1,2);

	Rational myResultRat = myRat.subtract(3.5);

	validateRational(myResultRat, -3, 1);

	myResultRat = myRat.subtract(0.0);
	validateRational(myResultRat, 1 , 2);
}

TEST(Rational, SubtractionWithNegativeFloats) {
	Rational myRat = Rational(-1,2);
	Rational myFriendsRat = Rational(1,2);

	Rational myResultRat = myRat.subtract(0.5);
	Rational myFriendsResultRat = myFriendsRat.subtract(-2.5);

	validateRational(myResultRat, -1, 1);
	validateRational(myFriendsResultRat, 3, 1);	
}

//////////////////
// 
// Multiplication

TEST(Rational, MultiplicationWithWholeNumber) {
	Rational myRat = Rational(4,3);

	Rational myProductiveRat = myRat.multiply(5);

	validateRational(myProductiveRat, 20, 3);
}

TEST(Rational, MultiplicationWithNegativeWholeNumber) {
	Rational myRat = Rational(4,-3);

	Rational myProductiveRat = myRat.multiply(-5);

	validateRational(myProductiveRat, 20, 3);
}

TEST(Rational, MultiplicationWithAnotherRational) {
	Rational myRat = Rational(1,2);
	Rational myProductiveRat = Rational(3,4);

	Rational myResultRat = myRat.multiply(myProductiveRat);

	validateRational(myResultRat, 3, 8);
}

TEST(Rational, MultiplicationWithANegativeRational) {
	Rational myRat = Rational(1,2);
	Rational myProductiveRat = Rational(-3,4);

	Rational myResultRat = myRat.multiply(myProductiveRat);

	validateRational(myResultRat, -3, 8);
}

TEST(Rational, MultiplicationWithAZeroRational) {
	Rational myRat = Rational(1,2);
	Rational myProductiveRat = Rational(0);

	Rational myResultRat = myRat.multiply(myProductiveRat);

	validateRational(myResultRat, 0, 1);
}

TEST(Rational, MultiplicationWithFloats) {
	Rational myRat = Rational(1,2);

	Rational myResultRat = myRat.multiply(3.5);

	validateRational(myResultRat, 7, 4);

	myResultRat = myRat.multiply(0.0);
	validateRational(myResultRat, 0, 1);
}

TEST(Rational, MultiplicationWithNegativeFloats) {
	Rational myRat = Rational(-1,2);
	Rational myFriendsRat = Rational(1,2);

	Rational myResultRat = myRat.multiply(0.5);
	Rational myFriendsResultRat = myFriendsRat.multiply(-2.5);

	validateRational(myResultRat, -1, 4);
	validateRational(myFriendsResultRat, -5, 4);	
}

//////////////////
// 
// Division

TEST(Rational, DivisionWithWholeNumber) {
	Rational myRat = Rational(4,3);

	Rational myDividedRat = myRat.divide(5);

	validateRational(myDividedRat, 4, 15);
}

TEST(Rational, DivisionWithNegativeWholeNumber) {
	Rational myRat = Rational(4,-3);

	Rational myDividedRat = myRat.divide(-5);

	validateRational(myDividedRat, 4, 15);
}

TEST(Rational, DivisionWithAnotherRational) {
	Rational myRat = Rational(1,2);
	Rational myDividedRat = Rational(3,4);

	Rational myResultRat = myRat.divide(myDividedRat);

	validateRational(myResultRat, 2, 3);
}

TEST(Rational, DivisionWithANegativeRational) {
	Rational myRat = Rational(1,2);
	Rational myDividedRat = Rational(3,-4);

	Rational myResultRat = myRat.divide(myDividedRat);

	validateRational(myResultRat, -2, 3);
}

TEST(Rational, DivisionWithAZeroRational) {
	Rational myRat = Rational(1,2);
	Rational myDividedRat = Rational(0);

	EXPECT_ANY_THROW(myRat.divide(myDividedRat));
}

TEST(Rational, DivisionWithFloats) {
	Rational myRat = Rational(1,2);

	Rational myResultRat = myRat.divide(3.5);

	validateRational(myResultRat, 1, 7);
}

TEST(Rational, DivisionWithNegativeFloats) {
	Rational myRat = Rational(-1,2);
	Rational myFriendsRat = Rational(1,2);

	Rational myResultRat = myRat.divide(0.5);
	Rational myFriendsResultRat = myFriendsRat.divide(-2.5);

	validateRational(myResultRat, -1, 1);
	validateRational(myFriendsResultRat, -1, 5);	
}

TEST(Rational, DivisionWithAZeroFloat) {
	Rational myRat = Rational(1,2);
	Rational myDividedRat = Rational(0.0);

	EXPECT_ANY_THROW(myRat.divide(myDividedRat));
}

TEST(Rational, DivideWholeNumberByWholeNumer) {
	Rational myRat = Rational(9,1);
	Rational myDividedRat = Rational(18,1);

	Rational myResultRat = myRat.divide(myDividedRat);

	validateRational(myResultRat, 1, 2);
}

//////////////////
// 
// Power

TEST(Rational, PowerWithWholeNumber) {
	Rational myRat = Rational(4,3);

	Rational myEmpoweredRat = myRat.pow(5);

	validateRational(myEmpoweredRat, 1024, 243);
}

TEST(Rational, PowerWithNegativeWholeNumber) {
	Rational myRat = Rational(4,-3);

	Rational myEmpoweredRat = myRat.pow(-5);

	validateRational(myEmpoweredRat, -243, 1024);
}

//////////////////
// 
// Negation

TEST(Rational, NegateRational) {
	Rational myRat = Rational(4, -3);
	Rational myOtherRat = Rational(1, 3);

	myRat.neg();
	myOtherRat.neg();

	validateRational(myRat, 4, 3);
	validateRational(myOtherRat, -1, 3);
}

//////////////////
// 
// Reciprocal

TEST(Rational, ReciprocalOfRational) {
	Rational myRat = Rational(1, 2);
	Rational myDownerRat = Rational(-4, 3);

	myRat.recip();
	myDownerRat.recip();

	validateRational(myRat, 2, 1);
	validateRational(myDownerRat, -3, 4);
}

//////////////////
// 
// Absolute Value

TEST(Rational, AbsoluteValueOfRational) {
	Rational myRat = Rational(1,2);
	Rational myDownerRat = Rational(-3, 4);

	myRat.abs();
	myDownerRat.abs();

	validateRational(myRat, 1, 2);
	validateRational(myDownerRat, 3, 4);
}

//////////////////
// 
// Square 

TEST(Rational, SquareOfRational) {
	Rational myRat = Rational(1,2);
	Rational myDownerRat = Rational(-2, 4);

	myRat.square();
	myDownerRat.square();

	validateRational(myRat, 1, 4);
	validateRational(myDownerRat, 1, 4);
}

////////////////////////////////
//
// Comparison Functions

TEST(Rational, LessThan) {
	Rational myRat = Rational(1, 2);
	Rational myLesserRat = Rational(-4);

	EXPECT_TRUE(myLesserRat.lessThan(myRat));
	EXPECT_FALSE(myRat.lessThan(myLesserRat));
}

TEST(Rational, TestingDifferenceWhenEqual) {
	Rational myRat = Rational(1,2);
	Rational myEerilySimilarRat = Rational(1,2);

	EXPECT_FALSE(myRat.lessThan(myEerilySimilarRat));
	EXPECT_FALSE(myRat.greaterThan(myEerilySimilarRat));
}

TEST(Rational, GreaterThan) {
	Rational myRat = Rational(1, 2);
	Rational myLesserRat = Rational(-4);

	EXPECT_TRUE(myRat.greaterThan(myLesserRat));
	EXPECT_FALSE(myLesserRat.greaterThan(myRat));
}

TEST(Rational, EqualWhenEqual) {
	Rational myRat = Rational(1,2);
	Rational myEerilySimilarRat = Rational(1,2);

	EXPECT_TRUE(myRat.equal(myEerilySimilarRat));
	EXPECT_TRUE(myEerilySimilarRat.equal(myRat));
}

TEST(Rational, EqualWhenNot) {
	Rational myRat = Rational(1,2);
	Rational myDoppleRat = Rational(2);

	EXPECT_FALSE(myRat.equal(myDoppleRat));
}

TEST(Rational, GreaterThanOrEqualTo) {
	Rational myRat = Rational(1, 2);
	Rational myEerilySimilarRat = Rational(1,2);
	Rational myLesserRat = Rational(-4);

	EXPECT_TRUE(myRat.greaterThanOrEqual(myLesserRat));
	EXPECT_FALSE(myLesserRat.greaterThanOrEqual(myRat));
	EXPECT_TRUE(myRat.greaterThanOrEqual(myEerilySimilarRat));
	EXPECT_TRUE(myEerilySimilarRat.greaterThanOrEqual(myRat));
}

TEST(Rational, LessThanOrEqualTo) {
	Rational myRat = Rational(1, 2);
	Rational myEerilySimilarRat = Rational(1,2);
	Rational myLesserRat = Rational(-4);

	EXPECT_FALSE(myRat.lessThanOrEqual(myLesserRat));
	EXPECT_TRUE(myLesserRat.lessThanOrEqual(myRat));
	EXPECT_TRUE(myRat.lessThanOrEqual(myEerilySimilarRat));
	EXPECT_TRUE(myEerilySimilarRat.lessThanOrEqual(myRat));
}


////////////////////////////////
//
// Reduction Tests

TEST(Rational, FindPrimeFactors) {
	int size;
	int *primeFactors = Rational::findPrimeFactors(21931283, size); 
	int expectedArray[size]; 
	expectedArray[0] = 11, expectedArray[1] = 509, expectedArray[2] = 3917;
	intArrayEqual(size, expectedArray, primeFactors);	
}

TEST(Rational, FindPrimeFactorsOfOne) {
	int size;
	int *primeFactorsOfOne = Rational::findPrimeFactors(1, size);
	int expectedArrayOfOne[size];
	expectedArrayOfOne[0] = 1;
	intArrayEqual(size, expectedArrayOfOne, primeFactorsOfOne);
}

TEST(Rational, FindPrimeFactorsOfZero) {
	int size;
	int *primeFactorsOfZero = Rational::findPrimeFactors(0, size);
	int expectedArrayOfZero[size];
	expectedArrayOfZero[0] = 0;
	intArrayEqual(size, expectedArrayOfZero, primeFactorsOfZero);
}

TEST(Rational, FindPrimeFactorsNegative) {
	int size;
	int *primeFactorsNegative = Rational::findPrimeFactors(-20, size);
	int expectedArrayNegative[size];
	expectedArrayNegative[0] = 2, expectedArrayNegative[1] = 2, expectedArrayNegative[2] = 5;
	intArrayEqual(size, expectedArrayNegative, primeFactorsNegative);
}

TEST(Rational, ReduceFractionToLowestTerms) {
	Rational myRat = Rational(6,4);
	Rational reducedRat = Rational::reduceFractionToLowestTerms(myRat);
	validateRational(reducedRat, 3,2);
}

TEST(Rational, ReduceFractionAlreadyReducedDoesntBomb) {
	Rational myRat = Rational(3,2);
	Rational reducedRat = Rational::reduceFractionToLowestTerms(myRat);
	validateRational(reducedRat, 3, 2);
}

TEST(Rational, ReduceFractionOnZeroDoesntBomb) {
	Rational myRat = Rational(0);
	Rational reducedRat = Rational::reduceFractionToLowestTerms(myRat);
	validateRational(reducedRat, 0, 1);	
}

TEST(Rational, ReduceFractionWholeNumberDoesntBomb) {
	Rational myRat = Rational(8011234);
	Rational reducedRat = Rational::reduceFractionToLowestTerms(myRat);
	validateRational(reducedRat, 8011234, 1);
}

////////////////////////////////
//
// IO Tests

TEST(Rational, RationalOutputToStreamInFraction) {
	Rational myRat = Rational(1,2);
	std::ostringstream stream;

	myRat.write(stream);

	std::string str = stream.str();
	const char* chr = str.c_str();
	const char expected[] = {'1','/','2','\0'};
	charArrayEqual(4, expected, chr);
}

TEST(Rational, RationalOutputToStreamInDecimal) {
	Rational myRat = Rational(1,2);
	std::ostringstream stream;

	myRat.write(stream, Rational::DECIMAL);

	std::string str = stream.str();
	const char* chr = str.c_str();
	const char expected[] = {'0', '.','5','\0'};
	charArrayEqual(3, expected, chr);
}

TEST(Rational, RationalReadInputFromStream) {
	Rational myReadingRat = Rational();

	std::istringstream stream("0.5");

	myReadingRat.read(stream);
	validateRational(myReadingRat, 1, 2);
}

////////////////////////////////
//
// Misc Helpers Tests

TEST(Rational, ToDoubleTest) {
	Rational myRat = Rational(1,2);

	double result = myRat.toDouble();

	EXPECT_FLOAT_EQ(0.5, result);
}

