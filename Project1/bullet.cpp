#include "bullet.h"

bullet::bullet()
{
}

bullet::bullet(const point& start)
{
	for (auto& p : _pointers)
		p = start;
	_pointers[1].moveY(-1);
	_pointers[2].moveY(-2);
}

void bullet::move(const bool& up)
{
	for (auto& p : _pointers)
		p.moveY(up ? -1 : 1);
}

void bullet::show()
{
	for (auto& p : _pointers)
		p.show();
}

