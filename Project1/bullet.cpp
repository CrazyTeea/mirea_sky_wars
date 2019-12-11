#include "bullet.h"

bullet::bullet()
{
}

bullet::bullet(const point& start)
{
	_pointers = start;
	//_pointers.setChar('^');
}

void bullet::move(const bool& up)
{
	_pointers.moveY(up ? -1 : 1);
}

void bullet::show()
{
	_pointers.show();
}

const int& bullet::getY()
{
	return _pointers.getY();
}

const int& bullet::getX()
{
	return _pointers.getX();
	// TODO: вставьте здесь оператор return
}

