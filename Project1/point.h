#pragma once
#ifdef _WIN32
	#include <curses.h>
#else
	#include <ncurses.h>
#endif // _WIN32

#include <string>


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
	const char* getChar();
	void setChar(const char& ch);
	int getX();
	int getY();
	void setX(const int& _x);
	void setY(const int& _y);
	void show();
	void setWindow(WINDOW* w);
	WINDOW* getWindow();
	void cleanPoint();
};

