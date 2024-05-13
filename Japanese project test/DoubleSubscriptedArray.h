#pragma once

#include <iostream>


class DoubleSubscriptedArray
{
	friend std::ostream& operator<< (std::ostream&, const DoubleSubscriptedArray&);
	friend std::istream& operator>> (std::istream&, DoubleSubscriptedArray&);

public:
	DoubleSubscriptedArray(int = 10, int = 10);
	DoubleSubscriptedArray(const DoubleSubscriptedArray&);
	~DoubleSubscriptedArray();
	int getSizeX() const;
	int getSizeY() const;

	const DoubleSubscriptedArray& operator=(const DoubleSubscriptedArray&);
	bool operator==(const DoubleSubscriptedArray&) const;

	bool operator !=(const DoubleSubscriptedArray& right) const
	{
		return !(*this == right);
	}

	char& operator()(int, int);
	char operator()(int, int) const;

private:
	int xSize, ySize;
	char* ptr;
};
