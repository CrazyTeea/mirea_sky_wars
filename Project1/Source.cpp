#include <cstdio>
#include <thread>
#include <string>
//#include <curses.h>
#include "ship.h"

using namespace std;

struct game_inputs
{
private:
	bool exit;
	bool start;
	int m_item;

public:
	game_inputs() {
		exit = 0;
		m_item = 0;
		start = 0;
	}
	game_inputs(const bool& _exit, const int& _m_item,const bool& _start) {
		exit = _exit;
		m_item = _m_item;
		start = _start;
	}
	bool getExit() {
		return exit;
	}
	int getMenuItem() {
		return m_item;
	}
	void setExit(const bool& e) {
		exit = e;
	}
	void setMenuItem(const int& i) {
		m_item = i;
	}
	bool getStart() {
		return start;
	}
	void setStart(const bool& s) {
		start = s;
	}

};

void _input(WINDOW*game,WINDOW *menu,ship *p,game_inputs *_g_i) {
	int x = 1, menu_choice = 1;
	while (!_g_i->getExit())
	{
		
		int key = getch();
		switch (key)
		{
		case KEY_RIGHT: {
			x = 1;
			if (!p->ifRight())
				p->moveX(&x);
			break;
		}
		case KEY_LEFT: {
			x = -1;
			if (!p->ifLeft())
				p->moveX(&x);
			break;
		}
		case KEY_UP: {
			if (_g_i->getMenuItem() < 1)
				_g_i->setMenuItem(2);
			else
				_g_i->setMenuItem(_g_i->getMenuItem()-1);
		//	p->moveY(&y);
			break;
		}
		case KEY_DOWN: {
			if (_g_i->getMenuItem() > 1)
				_g_i->setMenuItem(0);
			else
				_g_i->setMenuItem(_g_i->getMenuItem() + 1);
			//p->moveY(&y);
			break;
		}
		case 0xA: {
			//beep();
			switch (_g_i->getMenuItem())
			{
			case 0: {
				_g_i->setStart(true);
				break;
			}
			case 1: {
				//beep();

				break;
			}
			case 2: {
				_g_i->setExit(true);
			}
			default:
				break;
			}
			break;
		}
		default:
			//wprintw(menu, "%X", key);
			break;
		}


	}
}
void _draw(WINDOW *game,WINDOW *menu, game_inputs* _g_i) {

	vector <point> vector_ship_player;
	string menu_items[3] = { "Start","From save","Exit" };
	/**
				 *	
			*  *   *  *
			***	    ***
	**/
	vector_ship_player.push_back(point(game, 20, 27, "|"));
	vector_ship_player.push_back(point(game, 20, 28, "*"));
	vector_ship_player.push_back(point(game, 21, 28, "*"));
	vector_ship_player.push_back(point(game, 22, 28, "*"));
	vector_ship_player.push_back(point(game, 23, 27, "*"));
	vector_ship_player.push_back(point(game, 24, 26, "*"));
	vector_ship_player.push_back(point(game, 24, 25, "|"));
	vector_ship_player.push_back(point(game, 25, 27, "*"));
	vector_ship_player.push_back(point(game, 26, 28, "*"));
	vector_ship_player.push_back(point(game, 27, 28, "*"));
	vector_ship_player.push_back(point(game, 28, 28, "*"));
	vector_ship_player.push_back(point(game, 28, 27, "|"));

	ship* ship_player = new ship(&vector_ship_player);

	thread input(_input,game,menu,ship_player, _g_i);
	while (!_g_i->getExit())
	{

		wclear(game);

		wclear(menu);

		box(game, 0, 0);
		box(menu, 1, 1);
		for (int i = 0; i < sizeof(menu_items) / sizeof(menu_items[0]); i++)
		{
			if (i == _g_i->getMenuItem()) {
				mvwaddch(menu, 10 + i, 4, '>');
				wattroff(menu, COLOR_PAIR(2));
				wattron(menu, COLOR_PAIR(1));
			}
			else {
				mvwaddch(menu, 10 + i, 4, ' ');
				wattroff(menu, COLOR_PAIR(1));
				wattron(menu, COLOR_PAIR(2));
			}
			mvwprintw(menu, 10 + i, 5, menu_items[i].c_str());
		}

		if (_g_i->getStart())
		{
			ship_player->show();
		}
		wrefresh(game);
		wrefresh(menu);

	}
	input.join();
}


int main(int argc, char* argv[]) {
	initscr();

	if (!has_colors())
	{
		endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_WHITE, COLOR_BLACK);
	noecho();
	//raw();
	//nonl();
	curs_set(false);
	WINDOW* game = newwin(LINES, COLS-20, 0, 0);
	WINDOW* menu = newwin(LINES, 19, 0, COLS / 2);
	mvwin(game, 0, 0);
	mvwin(menu, 0, COLS - 20);
	keypad(stdscr, true);
	game_inputs _game_inputs(false, 0, false);

	thread draw(_draw,game, menu,&_game_inputs);
	draw.join();
	delwin(game);
	delwin(menu);
	endwin();
	return (0);
}