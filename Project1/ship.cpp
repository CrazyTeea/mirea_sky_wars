#include "ship.h"

ship::ship(std::vector<point>* _pointers)
{
	pointers = *_pointers;
	health = 2;
}

void ship::moveY(const int& y)
{
	for (auto &_point:pointers)
	{
		_point.moveY(y);
	}
}

void ship::moveX(const int& x)
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

std::vector<point> ship::getWeapons()
{
	std::vector<point> buff;
	std::copy_if(pointers.begin(), pointers.end(), std::back_inserter(buff), [](point point) {return point.getChar() == "|"; });
	//wprintw(stdscr, "%x", buff.size());
	return buff;
	// TODO: вставьте здесь оператор return
}

bool ship::ifLeft()
{
	return std::find_if(pointers.begin(), pointers.end(), [](point _p) {return _p.getX() <= 1; }) != pointers.end() ? true : false;
}

bool ship::ifRight()
{
	return std::find_if(pointers.begin(), pointers.end(), [](point _p) {return _p.getX() >= (COLS - 22); }) != pointers.end() ? true : false;
}

bool ship::isUp()
{
	return std::find_if(pointers.begin(), pointers.end(), [](point _p) {return _p.getY() < 1; }) != pointers.end() ? true : false;
}

bool ship::isDown()
{
	return std::find_if(pointers.begin(), pointers.end(), [](point _p) {return _p.getY() > LINES+1; }) != pointers.end() ? true : false;
}

void ship::decrementHealth(bullet& b)
{
	bool d = false;
	for (auto& p : pointers) {
		if (p.getX()==b.getX() && p.getY()==b.getY())
		{
			d = true;
		}
	}
	if (d) health--;
}

const bool& ship::isDie()
{
	return health <= 0 ? true : false;
	// TODO: вставьте здесь оператор return
}

void ship::clearP()
{
	for (auto& p : pointers)
		p.cleanPoint();
}
