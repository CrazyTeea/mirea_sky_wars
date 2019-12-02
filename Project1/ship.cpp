#include "ship.h"

ship::ship(std::vector<point>* _pointers)
{
	pointers = *_pointers;
}

void ship::moveY(int *y)
{
	for (auto &_point:pointers)
	{
		_point.moveY(y);
	}
}

void ship::moveX(int *x)
{
	for (auto& _point : pointers)
	{
		_point.moveX(x);
	}
}

void ship::show()
{
	for (auto& _point : pointers)
	{
		_point.show();
	}
}
