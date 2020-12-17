#include "set.h"


std::ostream& operator << (std::ostream& f, const Set& temp)
{
	f << "Set:\n";
	f << BoolVector(temp) << '\n';
	return f;
}


std::istream& operator >> (std::istream& f, Set& temp)						//
{
	std::cout << "Enter set:\n";
	
	char newVector[256];

	int count = 0;

	f >> newVector;

	while ((count < MAX_COUNT_FOR_INPUT) && (newVector[count] != '\0') && (count < 256))
	{
		count++;
	}

	//std::cout << count;

	Set result(count, newVector);

	temp = result;
	return f;
}


char Set::searchMin()
{
	if (power_ == 0) return '\0';
	
	for (int i = 0; i < 256; i++)
		if (operator [](i)) return char(i - 128);
}


char Set::searchMax()
{
	if (power_ == 0) return '\0';
	
	for (int i = 255; i >= 0; i--)
		if (operator [](i)) return char(i - 128);
}


const Set& Set::operator =(const Set& term)
{
	if (this != &term)
	{
		BoolVector::operator = (term);
		power_ = term.power_;
	}

	return *this;
}


bool Set::operator ==(Set& term)
{
	if (term.power_ != power_) return false;
	else
	{
		if (term.getCount() != getCount()) return false;
		Set copyThis(*this);
		copyThis /= term;
		return (copyThis.power_ == 0);
	}
}

bool Set::operator !=(Set& term)
{
	if (term.power_ != power_) return true;
	else
	{
		if (term.getCount() != getCount()) return true;
		Set copyThis(*this);
		copyThis /= term;
		return (copyThis.power_ != 0);
	}
}

Set Set::operator |(const Set& term)
{
	Set result(*this);
	result.BoolVector::operator |=(BoolVector(term));

	result.power_ = result.BoolVector::searchWeight();
	return result;
}


void Set::operator |= (const Set& term)
{
	BoolVector::operator |=(BoolVector(term));

	power_ = BoolVector::searchWeight();
}


Set Set::operator &(const Set& term)
{
	Set result(*this);
	result.BoolVector::operator &=(BoolVector(term));

	result.power_ = result.BoolVector::searchWeight();
	return result;
}


void Set::operator &= (const Set& term)
{
	BoolVector::operator &=(BoolVector(term));

	power_ = BoolVector::searchWeight();
}


void Set::operator ~()
{
	BoolVector::operator ~();
	
	power_ = BoolVector::getCount() - power_;
}


Set Set::operator /(Set& term)
{
	Set result(*this);
	int minCount;
	getCount() < term.getCount() ? minCount = getCount() : minCount = term.getCount();
	for (int i = 0; i < minCount; i++)
		if ((term[i] == true) && (result.operator [](i) == true))
		{
			result.setZeroInd(i);
			result.power_--;
		}
	return result;
}


void Set::operator /= (Set& term)
{
	int minCount;
	getCount() < term.getCount() ? minCount = getCount() : minCount = term.getCount();
	for (int i = 0; i < minCount; i++)
		if ((term[i] == true) && (operator [](i) == true))
		{
			setZeroInd(i);
			power_--;
		}
}


Set Set::operator +(char index)
{
	Set result(*this);
	int ind = index;
	ind += 128;
	if (operator [](ind) == 0)
	{
		result.setOneInd(ind);
		result.power_--;
	}
	return result;
}

void Set::operator += (char index)
{
	int ind = index;
	ind += 128;
	if (operator [](ind) == 0)
	{
		setOneInd(ind);
		power_--;
	}
}


Set Set::operator -(char index)
{
	Set result(*this);
	int ind = index;
	ind += 128;
	
	if (operator [](ind) == 1)
	{
		result.setZeroInd(ind);
		result.power_--;
	}
	return result;
}

void Set::operator -= (char index)
{
	int ind = index;
	ind += 128;
	if (operator [](ind) == 1)
	{
		setZeroInd(ind);
		power_--;
	}
}