#include "DoubleSubscriptedArray.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>


DoubleSubscriptedArray::DoubleSubscriptedArray(int xSizeTemp, int ySizeTemp)
{
	if (xSizeTemp > 0)
		xSize = xSizeTemp;
	else
		throw std::invalid_argument("Array size must be greater than 0");
	if (ySizeTemp > 0)
		ySize = ySizeTemp;
	else
		throw std::invalid_argument("Array size must be greater than 0");

	ptr = new char[ySize * xSize];

	for (int i = 0; i < ySize; ++i)
		for (int j = 0; j < xSize; ++j)
			ptr[i * ySize + j] = 0;
}


DoubleSubscriptedArray::DoubleSubscriptedArray(const DoubleSubscriptedArray& arrayToCopy) : xSize(arrayToCopy.xSize), ySize(arrayToCopy.ySize)
{
	ptr = new char[ySize * xSize];
	for (int i = 0; i < ySize; ++i)
		for (int j = 0; j < xSize; ++j)
			ptr[i * ySize + j] = arrayToCopy(i, j);
}


DoubleSubscriptedArray::~DoubleSubscriptedArray()
{
	delete[] ptr;
}


int DoubleSubscriptedArray::getSizeX() const
{
	return xSize;
}


int DoubleSubscriptedArray::getSizeY() const
{
	return ySize;
}


const DoubleSubscriptedArray& DoubleSubscriptedArray::operator=(const DoubleSubscriptedArray& right)
{
	if (&right != this)
	{
		if (xSize != right.xSize || ySize != right.ySize)
		{
			delete[] ptr;
			xSize = right.xSize;
			ySize = right.ySize;
			ptr = new char[ySize * xSize];
		}
		for (int i = 0; i < ySize; ++i)
			for (int j = 0; j < xSize; ++j)
				ptr[i * ySize + j] = right.ptr[i * ySize + j];
	}

	return *this;
}


bool DoubleSubscriptedArray::operator==(const DoubleSubscriptedArray& right) const
{
	if (xSize != right.xSize || ySize != right.ySize)
		return false;

	for (int i = 0; i < ySize; ++i)
		for (int j = 0; j < xSize; ++j)
			if (ptr[i * ySize + j] != right.ptr[i * ySize + j])
				return false;

	return true;
}


char& DoubleSubscriptedArray::operator()(int subscriptY, int subscriptX)
{
	if (subscriptX < 0 || subscriptX >= xSize || subscriptY < 0 || subscriptY >= ySize)
		throw std::out_of_range("Subscript out of range");

	return ptr[subscriptY * ySize + subscriptX];
}

char DoubleSubscriptedArray::operator()(int subscriptY, int subscriptX) const
{
	if (subscriptX < 0 || subscriptX >= xSize || subscriptY < 0 || subscriptY >= ySize)
		throw std::out_of_range("Subscript out of range");

	return ptr[subscriptY * ySize + subscriptX];
}


std::istream& operator>>(std::istream& input, DoubleSubscriptedArray& a)
{
	for (int i = 0; i < a.ySize; ++i)
		for (int j = 0; j < a.xSize; ++j)
			input >> a.ptr[i * a.ySize + j];

	return input;
}


std::ostream& operator<<(std::ostream& output, const DoubleSubscriptedArray& a)
{
	int i = 0;

	for (int i = 0; i < a.ySize; ++i)
	{
		for (int j = 0; j < a.xSize; ++j)
		{
			output << std::setw(3) << a.ptr[i * a.ySize + j];
		}
		output << std::endl;
	}

	return output;
}