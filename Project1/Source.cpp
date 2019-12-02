#include <cstdio>
#include <thread>
//#include <curses.h>
#include "ship.h"

using namespace std;
void _input(WINDOW*game,WINDOW *menu,ship *p,bool* exit) {
	int x = 1, y = 1;
	while (!*exit)
	{
		
		int key = getch();
		switch (key)
		{
		case KEY_RIGHT: {
			x = 1;
			p->moveX(&x);
			break;
		}
		case KEY_LEFT: {
			x = -1;
			p->moveX(&x);
			break;
		}
		case KEY_UP: {
			y = -1;
			p->moveY(&y);
			break;
		}
		case KEY_DOWN: {
			y = 1;
			p->moveY(&y);
			break;
		}
		case 0x71:
			*exit = !*exit;
			break;
		default:
			break;
		}
		//clear();
	//	wprintw(game,"x=%d y=%d", x, y);
		//refresh();

	}
}
void _draw(WINDOW *game,WINDOW *menu,bool *exit) {
//	printw("%b", *exit);
	//point* p = new point(game,5,5,"|");

	vector <point> vector_ship_player;
	vector_ship_player.push_back(point(game, 22, 26, "*"));
	vector_ship_player.push_back(point(game, 23, 25, "*"));
	vector_ship_player.push_back(point(game, 24, 24, "*"));
	vector_ship_player.push_back(point(game, 25, 25, "*"));
	vector_ship_player.push_back(point(game, 26, 26, "*"));
	ship* ship_player = new ship(&vector_ship_player);

	thread input(_input,game,menu,ship_player, exit);
	while (!*exit)
	{
	//	clear();
		//clear();
		wclear(game);
		wclear(menu);
		box(game, 0, 0);
		box(menu, 1, 1);
		ship_player->show();
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