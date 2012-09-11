#include <iostream>
#include <stdexcept>
#include "rational_array.h"

bool RationalArray::add(Rational ratToAdd) {
	try {
		ratArray.push_back(ratToAdd);
	} catch (bad_alloc& ba) {
		cerr << "Couldn't allocate for new rational in array";
		return false;
	}
	return true;
}

Rational RationalArray::retrieve(int index) {
	Rational rat;
	try {
		rat = ratArray.at(index);
	} catch (out_of_range& oor) {
		cerr << "No Rational at that Index";
	}
	return rat;
}

void RationalArray::replace(int index, Rational ratReplacement) {
	vector<Rational>::iterator it;
	it = ratArray.begin();

	ratArray.insert(it+index, ratReplacement);

	// Here's a tricky animal, when you insert or erase from
	// a vector is invalidates all interators, you only run into
	// issues though if you've crossed memory lines... like oh
	// say erasing some accounting blocks used in a given alloc...
	it = ratArray.begin();
	ratArray.erase(it+index+1);
}

void RationalArray::remove(int index) {
	vector<Rational>::iterator it;
	it = ratArray.begin();
	ratArray.erase(it+index);
}

size_t RationalArray::size() {
	return ratArray.size();
}