#include "rational.h"
#include <vector>
using namespace std;

class RationalArray {
private:
	vector<Rational> ratArray;

public:
	
	RationalArray() {}

	bool add(Rational);
	Rational retrieve(int);
	void replace(int, Rational);
	void remove(int);
	size_t size();
};