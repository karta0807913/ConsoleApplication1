#pragma once
#ifndef _MEGA_INT
#define _MEGA_INT

#include<iostream>

class MegaInt {
public:
	MegaInt(void);
	MegaInt(const MegaInt &megaInt);
	MegaInt(int theInt);
	~MegaInt();
	MegaInt & operator+=(MegaInt &tmpObject);
	MegaInt & operator+=(int theInt);
	MegaInt const operator+(MegaInt &megaInt);
	MegaInt const operator+(int theInt);
	MegaInt & operator++();
	MegaInt operator++(int);
	MegaInt & operator-=(MegaInt &tmpObject);
	MegaInt & operator-=(int theInt);
	MegaInt operator-(MegaInt &megaInt);
	MegaInt operator-(int theInt);
	MegaInt & operator--();
	MegaInt operator--(int);
	MegaInt & operator*=(MegaInt &megaInt);
	MegaInt & operator*=(int theInt);
	MegaInt const operator*(MegaInt &megaInt);
	MegaInt const operator*(int theInt);
	MegaInt & operator=(MegaInt const &tmpInt);
	bool const operator>(MegaInt &megaInt);
	bool const operator<(MegaInt &megaInt);
	bool const operator==(MegaInt &megaInt);
	bool const operator!=(MegaInt &megaInt);
	friend std::ostream & operator<<(std::ostream & os, MegaInt const &megaInt);
	friend MegaInt const operator+(int Int, MegaInt & megaInt);
	friend MegaInt const operator-(int Int, MegaInt & megaInt);
	friend MegaInt const operator*(int Int, MegaInt & megaInt);
private:
	bool isNegative = false;
	unsigned int digit = 0;
	int *intArray = nullptr;
	unsigned const int intLength = 100000;
};

#endif // !_MEGA_INT