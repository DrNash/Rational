#include "gtest/gtest.h"
#include "rational.h"

// Test zero numerator
TEST(Rational, ZeroAsNumeratorConstructor) {
	Rational zero = Rational(0);

	ASSERT_EQ(0, zero.getNumerator());
	ASSERT_EQ(1, zero.getDenominator());
}

// Test some arbitrary (or is it?) number for the numerator
TEST(Rational, ArbitraryNumeratorConstructor) {
	Rational arbNumber = Rational(42);

	ASSERT_EQ(42, arbNumber.getNumerator());
	ASSERT_EQ(1, arbNumber.getDenominator());
}

// Test using negative numbers for the numberator
TEST(Rational, NegativeNumeratorConstructor) {
	Rational negNumber = Rational(-28);

	ASSERT_EQ(-28, negNumber.getNumerator());
	ASSERT_EQ(1, negNumber.getDenominator());
}

TEST(Rational, FloatingPointConstructorLowDecimals) {
	Rational myRat = Rational(5.1f);

	EXPECT_EQ(51, myRat.getNumerator());
	EXPECT_EQ(10, myRat.getDenominator());
}