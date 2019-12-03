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

	point();
	point(WINDOW *w,int _x, int _y,const char *_char);
	void moveY(const int& _y);
	void moveX(const int& _x);
	int getX();
	int getY();
	void setX(const int& _x);
	void setY(const int& _y);
	void show();
	void setWindow(WINDOW* w);
	WINDOW* getWindow();
};

