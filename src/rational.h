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
	Rational(const int);
	// C'tor for given numerator and denominators
	Rational(const int, const int);
	// C'tor for floating point argument
	Rational(const double);
	
	// Copy c'tor for deep copies yo
	Rational(const Rational& original);

	enum WriteOutput {FRACTION, DECIMAL};

 	////////////////////////////////////////////////////////////
  	//
  	// Getters and Setters

	int getNumerator() const { return numerator_; }
	int getDenominator() const { return denominator_; }
	void set(const int, const int);
	void set(const int);
	void set(const double);
	double toDouble() const;

 	////////////////////////////////////////////////////////////
  	//
  	// Reduction and Sanity

	Rational floatToRational(const double) const;
	void reduceSelfToLowestTerms();
	void simplifySelf();

 	////////////////////////////////////////////////////////////
  	//
  	// Arithmetic Functions

	Rational add(const int) const;
	Rational add(const double) const;
	Rational add(const Rational) const;
	Rational subtract(const int) const;
	Rational subtract(Rational) const;
	Rational subtract(const double) const;
	Rational multiply(const int) const;
	Rational multiply(const Rational) const;
	Rational multiply(const double) const;
	Rational divide(const int) const;
	Rational divide(const double) const;
	Rational divide(const Rational) const;
	Rational pow(const int) const;
	int pow(const int,const int) const;

	void neg();
	void recip();
	void abs();
	void square();

 	////////////////////////////////////////////////////////////
  	//
  	// Comparison Functions

	bool lessThan(const Rational) const;
	bool greaterThan(const Rational) const;
	bool equal(const Rational) const;
	bool lessThanOrEqual(const Rational) const;
	bool greaterThanOrEqual(const Rational) const;

	////////////////////////////////////////////////////////////
  	//
  	// Stream Functions

	void read(std::istream&);
	void write(std::ostream&);
	void write(std::ostream&, int);

 	////////////////////////////////////////////////////////////
  	//
  	// Static Helpers

	static int *findPrimeFactors(const int, int&);
	static Rational reduceFractionToLowestTerms(Rational);

	
private:
	///////////////////////////////////////////////////////////
	//
	// Helpers

	double abs(const double) const;
};