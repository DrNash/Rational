class Rational {
private:
	int numerator_;
	int denominator_;
public:

  	////////////////////////////////////////////////////////////
  	//
  	// C'tors

  	// The default c'tor 
	Rational() {}
	// C'tor for numerator only
	Rational(int);
	// C'tor for given numerator and denominators
	Rational(int, int);
	// C'tor for floating point argument
	Rational(double);
	// Default copy contructor works fine 

	enum WriteOutput {FRACTION, DECIMAL};

 	////////////////////////////////////////////////////////////
  	//
  	// Getters and Setters

	int getNumerator() { return numerator_; }
	int getDenominator() { return denominator_; }
	void set(int, int);
	void set(int);
	void set(double);
	double toDouble();

 	////////////////////////////////////////////////////////////
  	//
  	// Reduction and Sanity

	Rational floatToRational(double);
	void reduceSelfToLowestTerms();
	void simplifySelf();

 	////////////////////////////////////////////////////////////
  	//
  	// Arithmetic Functions

	Rational add(int);
	Rational add(double);
	Rational add(Rational);
	Rational subtract(int);
	Rational subtract(Rational);
	Rational subtract(double);
	Rational multiply(int);
	Rational multiply(Rational);
	Rational multiply(double);
	Rational divide(int);
	Rational divide(double);
	Rational divide(Rational);
	Rational pow(int);
	int pow(int,int);

	void neg();
	void recip();
	void abs();
	void square();

 	////////////////////////////////////////////////////////////
  	//
  	// Comparison Functions

	bool lessThan(Rational);
	bool greaterThan(Rational);
	bool equal(Rational);
	bool lessThanOrEqual(Rational);
	bool greaterThanOrEqual(Rational);

	////////////////////////////////////////////////////////////
  	//
  	// Stream Functions

	void read(std::istream&);
	void write(std::ostream&);
	void write(std::ostream&, int);

 	////////////////////////////////////////////////////////////
  	//
  	// Static Helpers

	static int *findPrimeFactors(int, int&);
	static Rational reduceFractionToLowestTerms(Rational);

private:
	///////////////////////////////////////////////////////////
	//
	// Helpers

	double abs(double);
};