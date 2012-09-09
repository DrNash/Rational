class Rational {
private:
	int numerator_;
	int denominator_;
public:

  	////////////////////////////////////////////////////////////
  	//
  	// C'tors

  	// The default c'tor constructs an empty object with NULL num/den
	Rational() {}

	// C'tor for numerator only
	Rational(int);
	// C'tor for given numerator and denominators
	Rational(int, int);
	// C'tor for floating point argument
	Rational(double);

	int getNumerator() { return numerator_; }
	int getDenominator() { return denominator_; }

	Rational add(int);
	Rational add(Rational);

	void set(int, int);
	void set(int);
// TODO:	void set(double);

	static int *findPrimeFactors(int, int&);
	static Rational reduceFractionToLowestTerms(Rational);
private:
	///////////////////////////////////////////////////////////
	//
	// Helpers

	double abs(double);
};