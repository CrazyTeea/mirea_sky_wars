#include "point.h"



point::point()
{
	x = 0;
	y = 0;
	_ch = "*";
	_window = nullptr;
}

point::point(WINDOW *w,int _x, int _y,const char *_char)
{
	x = _x;
	y = _y;
	_ch = _char;
	_window = w;
}

void point::cleanPoint()
{
	mvwaddch(_window, y, x, ' ');
}

void point::moveY(const int& _y)
{
	cleanPoint();
	y += _y;
}

void point::moveX(const int& _x)
{
	cleanPoint();
	x += _x;
}

const char* point::getChar()
{
	return _ch;
}

void point::setChar(const char& ch)
{
	std::string b;
	b.push_back(ch);
	_ch = b.c_str();
	delete &b;
}

int point::getX()
{
	return x;
}

int point::getY()
{
	return y;
}

void point::setX(const int& _x)
{
	x = _x;
}

void point::setY(const int& _y)
{
	y = _y;
}

void point::show()
{
	mvwaddstr(_window,y,x,_ch);
}

void point::setWindow(WINDOW* w)
{
	_window = w;
}

WINDOW* point::getWindow()
{
	return _window;
}
