#include "bullet.h"

bullet::bullet()
{
}

bullet::bullet(WINDOW *w,const int& startX, const int& startY)
{
	_pointers[0].setX(startX);
	_pointers[1].setX(startX);
	_pointers[2].setX(startX);
	_pointers[0].setX(startX);
	_pointers[1].setWindow(w);
	_pointers[2].setWindow(w);
	_pointers[0].setWindow(w);
	_pointers[1].setY(startY-1);
	_pointers[2].setY(startY-2);
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

