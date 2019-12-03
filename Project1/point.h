#pragma once
#include <curses.h>
class point
{
private:
	int x;
	int y;
	WINDOW* _window;
	const char *_ch;
public:
	point(WINDOW* _w);
	point(WINDOW *w,int _x, int _y,const char *_char);
	void moveY(int* _y);
	void moveX(int* _x);
	int getX();
	int getY();
	void show();
};

