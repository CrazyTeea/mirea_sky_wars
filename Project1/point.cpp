#include "point.h"

point::point(WINDOW *_w)
{
	x = 0;
	y = 0;
	_ch = "*";
	_window = _w;
}

point::point(WINDOW *w,int _x, int _y,const char *_char)
{
	x = _x;
	y = _y;
	_ch = _char;
	_window = w;
}

void point::moveY(int* _y)
{
	y += *_y;
}

void point::moveX(int* _x)
{
	x += *_x;
}

int point::getX()
{
	return x;
}

int point::getY()
{
	return y;
}

void point::show()
{
	mvwaddstr(_window,y,x,_ch);
}
