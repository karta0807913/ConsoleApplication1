#pragma once
typedef int Data;

/*template<typename Data>
class Manager2DArray{
public:
	Manager2DArray(int heighBorader);
	Manager2DArray(int heighBorader, int wideBorader);
	void setWideBorader(int index);
	int length();
	const Array<Data> &operator[](int &index);
private:
	Array<Data> *proxyData;
	int border = 0;
};*/

template<typename Data>
class Array {
public:
	Array(int border);
	const Data &operator[](int &index);
	int length();
	virtual ~Array();
private:
	Data *clientData = nullptr;
	int border = 0;
};