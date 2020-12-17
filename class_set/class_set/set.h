//#pragma once

#ifndef set
#define set

#include "boolean_vector.h"

class Set: public BoolVector
{
	int power_;
public:

	Set() : BoolVector(256, false) { power_ = 0; };
	Set(int count, char* arr) : BoolVector(count, arr) { power_ = searchWeight(); };
	Set(Set& copy) : BoolVector(copy) { power_ = copy.power_; };
	~Set() {};

	bool checkElem(char index) { return operator[](index + 128); };
	int getPower() { return power_; };

	friend std::ostream& operator << (std::ostream& f, const Set& temp);
	friend std::istream& operator >> (std::istream& f, Set& temp);

	char searchMin();
	char searchMax();

	const Set& operator =(const Set& term);

	bool operator ==(Set& term);
	bool operator !=(Set& term);

	Set operator |(const Set& term);
	void operator |= (const Set& term);

	Set operator &(const Set& term);
	void operator &= (const Set& term);

	void operator ~();

	Set operator /(Set& term);
	void operator /= (Set& term);

	Set operator +(char index);
	void operator += (char index);

	Set operator -(char index);
	void operator -= (char index);
};

#endif
