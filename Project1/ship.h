#pragma once
#include "point.h"
#include <vector>
class ship
{
private:
	std::vector <point> pointers;
public:
	ship(std::vector <point>* _pointers);
	void moveY(int *y);
	void moveX(int *x);
	void show();
};

