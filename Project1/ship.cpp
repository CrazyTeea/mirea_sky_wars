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

bool ship::ifLeft()
{
	return std::find_if(pointers.begin(), pointers.end(), [](point _p) {return _p.getX() <= 1; }) != pointers.end() ? true : false;
}

bool ship::ifRight()
{
	return std::find_if(pointers.begin(), pointers.end(), [](point _p) {return _p.getX() >= (COLS - 22); }) != pointers.end() ? true : false;
}
