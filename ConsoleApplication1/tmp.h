#pragma once
#include<iostream>
template<int ArrayLength>
class MegaInt1 {
public:
	MegaInt1(void);
	MegaInt1(const MegaInt1 &megaInt);
	MegaInt1(int theInt);
	~MegaInt1();
	MegaInt1<ArrayLength> & operator+=(MegaInt1 &tmpObject);
	MegaInt1<ArrayLength> & operator+=(int theInt);
	MegaInt1<ArrayLength> const operator+(MegaInt1 &megaInt);
	MegaInt1<ArrayLength> const operator+(int theInt);
	MegaInt1<ArrayLength> & operator++();
	MegaInt1<ArrayLength> operator++(int);
	MegaInt1<ArrayLength> & operator-=(MegaInt1 &tmpObject);
	MegaInt1<ArrayLength> & operator-=(int theInt);
	MegaInt1<ArrayLength> operator-(MegaInt1 &megaInt);
	MegaInt1<ArrayLength> operator-(int theInt);
	MegaInt1<ArrayLength> & operator--();
	MegaInt1<ArrayLength> operator--(int);
	MegaInt1<ArrayLength> & operator*=(MegaInt1 &megaInt);
	MegaInt1<ArrayLength> & operator*=(int theInt);
	MegaInt1<ArrayLength> const operator*(MegaInt1 &megaInt);
	MegaInt1<ArrayLength> const operator*(int theInt);
	MegaInt1<ArrayLength> & operator=(MegaInt1 const &tmpInt);
	bool const operator>(MegaInt1 &megaInt);
	bool const operator<(MegaInt1 &megaInt);
	bool const operator==(MegaInt1 &megaInt);
	bool const operator!=(MegaInt1 &megaInt);
	int getTheDigit();
	friend std::ostream & operator<<(std::ostream & os, MegaInt1<ArrayLength> const &megaInt) {
		if (megaInt.isNegative == true) {
			os << '-';
		}
		for (int index = megaInt.digit - 1; index > -1; --index) {
			os << megaInt.intArray[index];
		}
		return os;
	};
	friend MegaInt1<ArrayLength> const operator+(int Int, MegaInt1 & megaInt) {
		return MegaInt1(Int) += megaInt;
	}
	friend MegaInt1<ArrayLength> const operator-(int Int, MegaInt1 & megaInt) {
		return MegaInt1(Int) -= megaInt;
	}
	friend MegaInt1<ArrayLength> const operator*(int Int, MegaInt1 & megaInt) {
		return MegaInt1(Int) *= megaInt;
	}
private:
	bool isNegative = false;
	unsigned int digit = 0;
	int *intArray = nullptr;
};

template<int ArrayLength>
inline MegaInt1<ArrayLength>::MegaInt1(void)
{
	intArray = new int[ArrayLength];
	digit = 1;
	isNegative = false;
	for (unsigned int index = 0; index < ArrayLength; ++index) {
		intArray[index] = 0;
	}
}

template<int ArrayLength>
inline MegaInt1<ArrayLength>::MegaInt1(const MegaInt1 & megaInt)
{
	digit = megaInt.digit;
	this->intArray = new int[ArrayLength];
	for (unsigned int index = 0; index < ArrayLength; ++index) {
		this->intArray[index] = megaInt.intArray[index];
	}
	isNegative = megaInt.isNegative;
}

template<int ArrayLength>
inline MegaInt1<ArrayLength>::MegaInt1(int theInt)
{
	if (theInt < 0) {
		isNegative = true;
		theInt *= -1;
	}
	else
		isNegative = false;
	intArray = new int[ArrayLength];
	unsigned int index;
	int theDigit = 0;
	for (index = 0; index < ArrayLength; ++index) {
		intArray[index] = theInt % 10;
		theInt /= 10;
		if (theInt != 0) {
			theDigit = index + 1;
		}
	}
	digit = theDigit + 1;
}

template<int ArrayLength>
inline MegaInt1<ArrayLength>::~MegaInt1()
{
	delete[] intArray;
}

template<int ArrayLength>
inline MegaInt1<ArrayLength>& MegaInt1<ArrayLength>::operator+=(MegaInt1 & tmpObject)
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
		if (digit != 1 && intArray[0] != 0)
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

template<int ArrayLength>
inline MegaInt1<ArrayLength>& MegaInt1<ArrayLength>::operator+=(int theInt)
{
	return *this += MegaInt1(theInt);
}

template<int ArrayLength>
inline MegaInt1<ArrayLength> const MegaInt1<ArrayLength>::operator+(MegaInt1 & megaInt)
{
	return MegaInt1(*this) += megaInt;
}

template<int ArrayLength>
inline MegaInt1<ArrayLength> const MegaInt1<ArrayLength>::operator+(int theInt)
{
	return MegaInt1(theInt) += *this;
}

template<int ArrayLength>
inline MegaInt1<ArrayLength>& MegaInt1<ArrayLength>::operator++()
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

template<int ArrayLength>
inline MegaInt1<ArrayLength> MegaInt1<ArrayLength>::operator++(int)
{
	MegaInt1 tmpObject(*this);
	++*this;
	return tmpObject;
}

template<int ArrayLength>
inline MegaInt1<ArrayLength>& MegaInt1<ArrayLength>::operator-=(MegaInt1 & tmpObject)
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

template<int ArrayLength>
inline MegaInt1<ArrayLength>& MegaInt1<ArrayLength>::operator-=(int theInt)
{
	return *this -= MegaInt1(theInt);
}

template<int ArrayLength>
inline MegaInt1<ArrayLength> MegaInt1<ArrayLength>::operator-(MegaInt1 & megaInt)
{
	return MegaInt1(*this) -= megaInt;
}

template<int ArrayLength>
inline MegaInt1<ArrayLength> MegaInt1<ArrayLength>::operator-(int theInt)
{
	return MegaInt1(*this) -= MegaInt1(theInt);
}

template<int ArrayLength>
inline MegaInt1<ArrayLength>& MegaInt1<ArrayLength>::operator--()
{
	return *this;
}

template<int ArrayLength>
inline MegaInt1<ArrayLength> MegaInt1<ArrayLength>::operator--(int)
{
	MegaInt1 tmpObject(*this);
	--*this;
	return tmpObject;
}

template<int ArrayLength>
inline MegaInt1<ArrayLength>& MegaInt1<ArrayLength>::operator*=(MegaInt1 & megaInt)
{
	unsigned int carry = 0;
	unsigned int megaIntDigit = megaInt.digit;
	MegaInt1 tmpObject;
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
		for (loop = digit + index; loop < ArrayLength && carry != 0; ++loop) {
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

template<int ArrayLength>
inline MegaInt1<ArrayLength>& MegaInt1<ArrayLength>::operator*=(int theInt)
{
	return *this *= MegaInt1(theInt);
}

template<int ArrayLength>
inline MegaInt1<ArrayLength> const MegaInt1<ArrayLength>::operator*(MegaInt1 & megaInt)
{
	return MegaInt1(*this) *= megaInt;
}

template<int ArrayLength>
inline MegaInt1<ArrayLength> const MegaInt1<ArrayLength>::operator*(int theInt)
{
	return MegaInt1(theInt) *= *this;
}

template<int ArrayLength>
inline MegaInt1<ArrayLength>& MegaInt1<ArrayLength>::operator=(MegaInt1 const & tmpInt)
{
	digit = tmpInt.digit;
	isNegative = tmpInt.isNegative;
	for (unsigned int index = 0; index < ArrayLength; ++index) {
		this->intArray[index] = tmpInt.intArray[index];
	}
	return *this;
}

template<int ArrayLength>
inline bool const MegaInt1<ArrayLength>::operator>(MegaInt1 & megaInt)
{
	if (!isNegative && !megaInt.isNegative) {
		if (digit > megaInt.digit)
			return true;
		else if (digit < megaInt.digit)
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

template<int ArrayLength>
inline bool const MegaInt1<ArrayLength>::operator<(MegaInt1 & megaInt)
{
	return megaInt > *this;
}

template<int ArrayLength>
inline bool const MegaInt1<ArrayLength>::operator==(MegaInt1 & megaInt)
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

template<int ArrayLength>
inline bool const MegaInt1<ArrayLength>::operator!=(MegaInt1 & megaInt)
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

template<int ArrayLength>
inline int MegaInt1<ArrayLength>::getTheDigit()
{
	return digit;
}
