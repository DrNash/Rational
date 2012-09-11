#include "gtest/gtest.h"
#include "rational_array.h"


///////////////////////////////////////////////////////////
//
// Helper subroutines for validation

void charArrayEqual(int size, const char *a, const char *b) {
	for(int i = 0; i < size; i++) {
		EXPECT_EQ(a[i], b[i]);
	}
}

///////////////////////////////////////////////////////////
//
// Tests

TEST(RationalArray, AddRationalToRatArray) {
	RationalArray myRatRay = RationalArray();
	Rational myRat = Rational(1,2);

	EXPECT_TRUE(myRatRay.add(myRat)) << "Failed to add Rational";
}

// Tests add and retrieve
TEST(RationalArray, AddRationalToRatArrayCheckItsThere) {
	RationalArray myRatRay = RationalArray();
	Rational myRat = Rational(1,2);

	myRatRay.add(myRat);

	Rational myRatReborn = myRatRay.retrieve(0);
	EXPECT_TRUE(myRatReborn.equal(myRat));
}

TEST(RationalArray, RetriveRatOutOfBounds) {
	RationalArray myRatRay = RationalArray();
	Rational myRat = Rational(1,2);
	myRatRay.add(myRat);

	// Redirect cerr
	std::stringstream buffer;
	std::streambuf * old = std::cerr.rdbuf(buffer.rdbuf());
	
	Rational myRatReborn = myRatRay.retrieve(1);

	std::string text = buffer.str(); 

	// Put cerr back
	std::cerr.rdbuf(old);

	const char error[] = "No Rational at that Index";
	const char* returnStr = text.c_str();

	charArrayEqual(24, error, returnStr);
}

TEST(RationalArray, ReplaceRationalAtIndex) {
	RationalArray myRatRay = RationalArray();
	Rational myRat = Rational(1,2);
	myRatRay.add(myRat);
	myRatRay.add(myRat);
	myRatRay.add(myRat);

	Rational myImprovedRat = Rational(4.0);

	myRatRay.replace(1, myImprovedRat);

	Rational myFirstRat = myRatRay.retrieve(0);
	Rational mySecondRat = myRatRay.retrieve(1);
	Rational myThirdRat = myRatRay.retrieve(2);
	EXPECT_TRUE(myRat.equal(myFirstRat));
	EXPECT_TRUE(myImprovedRat.equal(mySecondRat));
	EXPECT_TRUE(myRat.equal(myThirdRat));
}

TEST(RationalArray, RemoveElement) {
	RationalArray myRatRay = RationalArray();
	Rational myRat = Rational(1,2);
	Rational myRat1 = Rational(3,4);
	Rational myRat2 = Rational(5,6);
	myRatRay.add(myRat);
	myRatRay.add(myRat1);
	myRatRay.add(myRat2);

	myRatRay.remove(1);
	Rational myFirstRat = myRatRay.retrieve(0);
	Rational mySecondRat = myRatRay.retrieve(1);

	// Redirect cerr
	std::stringstream buffer;
	std::streambuf * old = std::cerr.rdbuf(buffer.rdbuf());
	Rational myThirdRat = myRatRay.retrieve(2);
	
	// Put cerr back
	std::cerr.rdbuf(old);
	size_t expectedSize = 2;

	EXPECT_TRUE(myFirstRat.equal(myRat));
	EXPECT_TRUE(mySecondRat.equal(myRat2));
	EXPECT_EQ(expectedSize, myRatRay.size());
}

TEST(RationalArray, RatArraySize) {
	RationalArray myRatRay = RationalArray();
	Rational myRat = Rational(1,2);
	myRatRay.add(myRat);

	size_t count = myRatRay.size();
	size_t expectedCount = 1;
	EXPECT_EQ(expectedCount, count);
}