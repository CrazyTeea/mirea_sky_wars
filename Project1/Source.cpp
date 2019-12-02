#include <cstdio>
#include <thread>
//#include <curses.h>
#include "point.h"

using namespace std;
void _input(WINDOW*game,WINDOW *menu,point *p,bool* exit) {
	
	while (!*exit)
	{
		
		int key = getch();
		switch (key)
		{
		case KEY_DOWN:
			p->moveDown();
			break;
		case KEY_UP: {
			int y = -1;
			p->moveY(&y);
			break;
		}
		case 0x71:
			*exit = !*exit;
			break;
		default:
			break;
		}
		

	}
}
void _draw(WINDOW *game,WINDOW *menu,bool *exit) {
//	printw("%b", *exit);
	point* p = new point(game,5,5,"|");
	thread input(_input,game,menu,p, exit);
	while (!*exit)
	{
	//	clear();
		//clear();
		wclear(game);
		wclear(menu);
		box(game, 0, 0);
		box(menu, 1, 1);
		p->show();
		//refresh(); 
		wrefresh(game);
		wrefresh(menu);

	}
	input.join();
}


int main(int argc, char* argv[]) {
	initscr();
	noecho();
	curs_set(false);
	WINDOW* game = newwin(LINES, COLS-20, 0, 0);
	WINDOW* menu = newwin(LINES, 19, 0, COLS / 2);
	
	mvwin(game, 0, 0);
	mvwin(menu, 0, COLS - 20);
	keypad(stdscr, true);

	bool exit = false;
	
	thread draw(_draw,game, menu,& exit);
	

	draw.join();
	

	delwin(game);
	delwin(menu);
	endwin();

	return (0);
}