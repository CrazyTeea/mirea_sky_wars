#pragma once

#ifndef POINT_H
#define POINT_H
#include "point.h"
#endif // !POINT_H


class bullet
{
private:
	point _pointers[3];
public:
	bullet();
	bullet(const point& start);
	void move(const bool& up);
	void show();
};

