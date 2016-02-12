#include "MegaInt.h"
#include"MegaInt.h"


MegaInt::MegaInt(void)
{
	intArray = new int[intLength];
	digit = 1;
	isNegative = false;
	for (unsigned int index = 0; index < intLength; ++index) {
		intArray[index] = 0;
	}
}

inline MegaInt::MegaInt(const MegaInt & megaInt)
{
	digit = megaInt.digit;
	this->intArray = new int[intLength];
	for (unsigned int index = 0; index < intLength; ++index) {
		this->intArray[index] = megaInt.intArray[index];
	}
	isNegative = megaInt.isNegative;
}

MegaInt::MegaInt(int theInt)
{
	if (theInt < 0) {
		isNegative = true;
		theInt *= -1;
	}
	else
		isNegative = false;
	intArray = new int[intLength];
	unsigned int index;
	int theDigit = 0;
	for (index = 0; index < intLength; ++index) {
		intArray[index] = theInt % 10;
		theInt /= 10;
		if (theInt != 0) {
			theDigit = index + 1;
		}
	}
	digit = theDigit + 1;
}

inline MegaInt::~MegaInt()
{
	delete[] intArray;
}

MegaInt & MegaInt::operator+=(MegaInt & tmpObject)
{
	if (!isNegative && tmpObject.isNegative) {
		tmpObject.isNegative = false;
		*this -= tmpObject;
		tmpObject.isNegative = true;
		return *this;
	}

	if (isNegative && !tmpObject.isNegative) {
		isNegative = false;
		*this -= tmpObject;
		if(digit != 1 && intArray[0] != 0)
			isNegative = !isNegative;
		return *this;
	}
	unsigned int biggerDigit;
	if (tmpObject.digit < this->digit) {
		biggerDigit = this->digit;
	}
	else {
		biggerDigit = tmpObject.digit;
	}

	int carry = 0;
	unsigned int index;
	for (index = 0; index < biggerDigit; ++index) {
		this->intArray[index] += (tmpObject.intArray[index] + carry);
		carry = this->intArray[index] / 10;
		this->intArray[index] %= 10;
	}
	this->digit = biggerDigit + carry;
	this->intArray[index] = carry;
	return *this;
}

MegaInt & MegaInt::operator+=(int theInt)
{
	return *this += MegaInt(theInt);
}

MegaInt const MegaInt::operator+(MegaInt & megaInt)
{
	return MegaInt(*this) += megaInt;
}

MegaInt const MegaInt::operator+(int theInt)
{
	return MegaInt(theInt) += *this;
}

MegaInt & MegaInt::operator++()
{
	if (isNegative) {
		isNegative = false;
		--*this;
		if (digit != 1 && intArray[0] != 0)
			isNegative = false;
		return *this;
	}
	unsigned int carry = 1;
	for (unsigned int index = 0; index < digit && carry != 0; ++index) {
		intArray[index] += carry;
		carry = intArray[index] / 10;
		intArray[index] %= 10;
	}
	intArray[digit] = carry;
	digit += carry;
	return *this;
}

MegaInt MegaInt::operator++(int)
{
	MegaInt tmpObject(*this);
	++*this;
	return tmpObject;
}

MegaInt & MegaInt::operator-=(MegaInt & tmpObject)
{
	if (isNegative ^ tmpObject.isNegative) {
		tmpObject.isNegative = !tmpObject.isNegative;
		*this += tmpObject;
		tmpObject.isNegative = !tmpObject.isNegative;
		return *this;
	}
	if (isNegative && tmpObject.isNegative) {
		isNegative = false;
		tmpObject.isNegative = false;
		*this -= tmpObject;
		tmpObject.isNegative = true;
		isNegative = !isNegative;
		return *this;
	}


	unsigned int biggerDigit;
	bool boolean = *this < tmpObject;
	if (boolean) {
		biggerDigit = tmpObject.digit;
	}
	else {
		biggerDigit = this->digit;
	}
	
	int offset = -1;
	if (!boolean) {
		offset *= -1;
	}
	int carry = 0;
	unsigned int digitChanged = 0;
	for (unsigned int index = 0; index < biggerDigit; ++index) {
		intArray[index] -= carry; 
		carry = 0;
		intArray[index] -= tmpObject.intArray[index];
		if (intArray[index] < 0 && !boolean || intArray[index] > 0 && boolean) { 
			intArray[index] += 10 * offset;
			carry = 1 * offset;
		}
		if (intArray[index] != 0) {
			digitChanged = index;
		}
		intArray[index] *= offset;
	}
	isNegative = boolean;
	this->digit = digitChanged + 1;
	if (intArray[0] == 0 && digit == 1)
		isNegative = false;
	return *this;
}

MegaInt & MegaInt::operator-=(int theInt)
{
	return *this -= MegaInt(theInt);
}

MegaInt MegaInt::operator-(MegaInt & megaInt)
{
	return MegaInt(*this) -= megaInt;
}

MegaInt MegaInt::operator-(int theInt)
{
	return MegaInt(*this) -= MegaInt(theInt);
}

MegaInt & MegaInt::operator--()
{
	return *this;
}

MegaInt MegaInt::operator--(int)
{
	MegaInt tmpObject(*this);
	--*this;
	return tmpObject;
}

MegaInt & MegaInt::operator*=(MegaInt & megaInt)
{
	unsigned int carry = 0;
	unsigned int megaIntDigit = megaInt.digit;
	MegaInt tmpObject;
	for (unsigned int index = 0; index < megaIntDigit; ++index) {
		if (megaInt.intArray[index] == 0)
			continue;

		for (unsigned int multiplier = 0; multiplier < digit; ++multiplier) {
			int tmp = index + multiplier;
			tmpObject.intArray[tmp] += intArray[multiplier] * megaInt.intArray[index] + carry;
			carry = tmpObject.intArray[tmp] / 10;
			tmpObject.intArray[tmp] %= 10;
		}
		unsigned int loop;
		for (loop = digit + index; loop < intLength && carry != 0; ++loop) {
			tmpObject.intArray[loop] += carry % 10;
			carry /= 10;
		}
		if (tmpObject.digit < loop)
			tmpObject.digit = loop;
	}
	bool negative = isNegative ^ megaInt.isNegative;
	*this = tmpObject;

	if (digit == 1 && intArray[0] == 0)
		isNegative = true;
	else
		isNegative = negative;
	return *this;

}

MegaInt & MegaInt::operator*=(int theInt)
{
	return *this *= MegaInt(theInt);
}

MegaInt const MegaInt::operator*(MegaInt & megaInt)
{
	return MegaInt(*this) *= megaInt;
}

MegaInt const MegaInt::operator*(int theInt)
{
	return MegaInt(theInt) *= *this;
}

MegaInt & MegaInt::operator=(MegaInt const & tmpInt)
{
	digit = tmpInt.digit;
	isNegative = tmpInt.isNegative;
	for (unsigned int index = 0; index < intLength; ++index) {
		this->intArray[index] = tmpInt.intArray[index];
	}
	return *this;
}

bool const MegaInt::operator>(MegaInt & megaInt)
{
	if (!isNegative && !megaInt.isNegative) {
		if (digit > megaInt.digit)
			return true;
		else if(digit < megaInt.digit)
			return false;
		for (int index = digit - 1; index > -1; --index) {
			if (intArray[index] > megaInt.intArray[index])
				return true;
			else if (intArray[index] < megaInt.intArray[index])
				return false;
		}
		return false;
	}
	else if (!isNegative && megaInt.isNegative) {
		return true;
	}
	else if (isNegative && !megaInt.isNegative) {
		return false;
	}
	
	if (digit < megaInt.digit)
		return true;
	else
		return false;

	for (int index = digit - 1; index > -1; --index) {
		if (intArray[index] < megaInt.intArray[index])
			return true;
		else if (intArray[index] < megaInt.intArray[index])
			return false;
	}
	return false;
}

bool const MegaInt::operator<(MegaInt & megaInt)
{
	return megaInt > *this;
}

bool const MegaInt::operator==(MegaInt & megaInt)
{
	if (isNegative != megaInt.isNegative)
		return false;
	if (digit != megaInt.digit)
		return false;

	for (unsigned int index = 0; index < digit; ++index) {
		if (intArray[index] != megaInt.intArray[index])
			return false;
	}
	return true;
}

bool const MegaInt::operator!=(MegaInt & megaInt)
{
	if (isNegative != megaInt.isNegative)
		return true;
	if (digit != megaInt.digit)
		return true;

	for (unsigned int index = 0; index < digit; ++index) {
		if (intArray[index] != megaInt.intArray[index])
			return true;
	}
	return false;
}

std::ostream & operator<<(std::ostream & os, MegaInt const & megaInt)
{
	if (megaInt.isNegative == true) {
		os << '-';
	}
	for (int index = megaInt.digit - 1; index > -1; --index) {
		os << megaInt.intArray[index];
	}
	return os;
}

MegaInt const operator+(int Int, MegaInt & megaInt)
{
	return MegaInt(Int) += megaInt;
}

MegaInt const operator-(int Int, MegaInt & megaInt)
{
	return MegaInt(Int) -= megaInt;
}

MegaInt const operator*(int Int, MegaInt & megaInt)
{
	return MegaInt(Int) *= megaInt;
}