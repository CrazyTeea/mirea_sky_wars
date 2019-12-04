#pragma once
#ifndef POINT_H
#define POINT_H
#include "point.h"
#endif // !POINT_H
#include <vector>
#include <iterator>
#include <algorithm>
class ship
{
private:
	std::vector <point> pointers;
public:
	ship(std::vector <point>* _pointers);
	void moveY(const int& y);
	void moveX(const int& x);
	void show();
	std::vector<point> getWeapons();
	bool ifLeft();
	bool ifRight();
};

