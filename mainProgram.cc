#include <iostream>
#include "rational_array.h"
#include <vector>
using namespace std;

int main(int argc, char **argv) {
	cout << "Part A and B:\n"
	"I figured the essence of credit for test work on the "
	"two classes is all contained in the tests themselves.\n\n";

	cout << "Hello observer, if you'd like to see the "
	"workings of class Rational or RationalArray "
	"please run 'make test' "
	"from this directory. You will see the 73 test "
	"cases pass (hopefully) covering most all of "
	"Rational's behaviors. The classes were test "
	"driven so the majority of behaviors are backed by tests.\n\n"
	"If you look in the test/ directory below this you'll "
	"see rational_test.cc and rational_array_test.cc. " 
	"These files contain all of the test cases for each "
	"class.\n\n";

	vector<string> inputVector;
	string s;

	cout << "Part C:\n";
	cout << "To business, enter a space delimited series "
	"of words, followed by Ctrl+D, please:\n";

	cin >> s;
	do {
		inputVector.push_back(s);
	} while(cin >> s);

	enum Indices {
		ALPHA,
		DECIM,
		PUNCT,
		LOWER,
		UPPER,
		SYMBO,
		UPTOL,
		UPTOP
	};

	cout << "\n\nPart D:\n";
	RationalArray myRatRay = RationalArray();

	for(int i = 0; i < 6; i++) {
		Rational rat = Rational(0);
		myRatRay.add(rat);
	}

	vector<string>::iterator it;
	for(it=inputVector.begin(); it < inputVector.end(); it++) {
		string str = *it;
		string::iterator str_it;
		for(str_it=str.begin(); str_it < str.end(); str_it++) {
			char ch = *str_it;

			// The SYMBOs
			if(ch >= 0 && ch < 33) {
				myRatRay.replace(SYMBO, myRatRay.retrieve(SYMBO).add(1));
			} 
			// The punctuation
			else if ((ch >= 33 && ch < 48) ||
					(ch >= 58 && ch < 65 ) ||
					(ch >= 91 && ch < 97 ) ||
					(ch >= 123))
			{
				myRatRay.replace(PUNCT, myRatRay.retrieve(PUNCT).add(1));
			} 
			// The decimals
			else if (ch >= 48 && ch < 58) {
				myRatRay.replace(DECIM, myRatRay.retrieve(DECIM).add(1));
			} 
			// The uppers
			else if (ch >= 65 && ch < 91) {
				myRatRay.replace(UPPER, myRatRay.retrieve(UPPER).add(1));
				myRatRay.replace(ALPHA, myRatRay.retrieve(ALPHA).add(1));
			}
			// The lowers
			else if (ch >= 97 && ch < 123) {
				myRatRay.replace(LOWER, myRatRay.retrieve(LOWER).add(1));
				myRatRay.replace(ALPHA, myRatRay.retrieve(ALPHA).add(1));
			} else {
				myRatRay.replace(SYMBO, myRatRay.retrieve(SYMBO).add(1));
			}
		}
	}

	if((myRatRay.retrieve(LOWER).add(myRatRay.retrieve(UPPER))).equal(myRatRay.retrieve(ALPHA))) {
		cout << "Looks like things worked out alright:\n"
			"The value of lower is: " << myRatRay.retrieve(LOWER).getNumerator() << "\n"
			"The value of upper is: " << myRatRay.retrieve(UPPER).getNumerator() << "\n"
			"And thus, the value of alpha is: "
			<< myRatRay.retrieve(ALPHA).getNumerator() << "\n";
	} else {
		cout << "Things don't look so good....\n";
	}

	cout << "\n\nPart E:\n";
	RationalArray anotherRatRay = RationalArray();
	for(int i=0; i < 8; i++) {
		Rational aRat = Rational(0);
		anotherRatRay.add(aRat);
	}

	int totalCharacters = myRatRay.retrieve(ALPHA).add(
						  myRatRay.retrieve(PUNCT)).add(
						  myRatRay.retrieve(DECIM)).add(
					 	  myRatRay.retrieve(SYMBO)).getNumerator();

	cout << "\nWe have " << totalCharacters << " total characters.\n\n";

	anotherRatRay.replace(ALPHA, myRatRay.retrieve(ALPHA).divide(totalCharacters));
	anotherRatRay.replace(DECIM, myRatRay.retrieve(DECIM).divide(totalCharacters));
	anotherRatRay.replace(PUNCT, myRatRay.retrieve(PUNCT).divide(totalCharacters));
	anotherRatRay.replace(LOWER, myRatRay.retrieve(LOWER).divide(totalCharacters));
	anotherRatRay.replace(UPPER, myRatRay.retrieve(UPPER).divide(totalCharacters));
	anotherRatRay.replace(SYMBO, myRatRay.retrieve(SYMBO).divide(totalCharacters));
	if(myRatRay.retrieve(LOWER).greaterThan(0)) 
		anotherRatRay.replace(UPTOL, myRatRay.retrieve(UPPER).divide(myRatRay.retrieve(LOWER)));
	if(myRatRay.retrieve(PUNCT).greaterThan(0))
		anotherRatRay.replace(UPTOP, myRatRay.retrieve(UPPER).divide(myRatRay.retrieve(PUNCT)));

	Rational ratioSum = anotherRatRay.retrieve(ALPHA).add(
						anotherRatRay.retrieve(PUNCT)).add(
						anotherRatRay.retrieve(DECIM)).add(
					 	anotherRatRay.retrieve(SYMBO));

	Rational expectedSum = Rational(1,1);
	if(ratioSum.equal(expectedSum)) {
		cout << "We're all good, ratio sum is: ";
		ratioSum.write(cout);
		cout << "\n";

	} else {
		cout << "Erm, something went horribly, horribly wrong. I blame brackets\n"
		"Ration sum is: ";
		ratioSum.write(cout);
		cout << "\n";
	}
	cout << "Check out these ratios: \n"
	"ALPHA: ";
	anotherRatRay.retrieve(ALPHA).write(cout);
	cout << "\nDECIM: ";
	anotherRatRay.retrieve(DECIM).write(cout);
	cout << "\nPUNCT: ";
	anotherRatRay.retrieve(PUNCT).write(cout);
	cout << "\nLOWER: ";
	anotherRatRay.retrieve(LOWER).write(cout);
	cout << "\nUPPER: ";
	anotherRatRay.retrieve(UPPER).write(cout);
	cout << "\nSYMBO: ";
	anotherRatRay.retrieve(SYMBO).write(cout);
	cout << "\nUPTOL: ";
	anotherRatRay.retrieve(UPTOL).write(cout);
	cout << "\nUPTOP: ";
	anotherRatRay.retrieve(UPTOP).write(cout);
	cout << "\n\n Thanks for running!\n";
}