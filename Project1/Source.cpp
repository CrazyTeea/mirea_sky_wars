#include <cstdio>
#include <thread>
#include <string>
//#include <curses.h>
#include "ship.h"
#include "bullet.h"

using namespace std;

struct game_inputs
{
private:
	bool exit;
	bool start;
	int m_item;
	int frame_rate;

public:
	game_inputs() {
		exit = 0;
		m_item = 0;
		start = 0;
		frame_rate = 100;
	}
	game_inputs(const bool& _exit, const int& _m_item,const bool& _start,const int& f_r) {
		exit = _exit;
		m_item = _m_item;
		start = _start;
		frame_rate = f_r;
	}
	const bool& getExit() {
		return exit;
	}
	const int& getMenuItem() {
		return m_item;
	}
	void setExit(const bool& e) {
		exit = e;
	}
	void setMenuItem(const int& i) {
		m_item = i;
	}
	const bool& getStart() {
		return start;
	}
	void setStart(const bool& s) {
		start = s;
	}
	int& getFrameRate() {
		return frame_rate;
	}

};

void _input(WINDOW*game,WINDOW *menu,ship *p,game_inputs *_g_i) {
	while (!_g_i->getExit())
	{
		
		int key = getch();
		switch (key)
		{
		case KEY_RIGHT: {
			
			if (!p->ifRight())
				p->moveX(1);
			break;
		}
		case KEY_LEFT: {
			
			if (!p->ifLeft())
				p->moveX(-1);
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
		case 0xD:
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
		case KEY_RESIZE: {
			clear();
			wrefresh(game);
			wrefresh(menu);
			refresh();
			break;
		}
		default:
			wprintw(menu, "%X", key);
			break;
		}


	}
}
void _draw(WINDOW *game,WINDOW *menu, game_inputs* _g_i) {

	vector <point> vector_ship_player;
	vector <bullet> vector_bullet;
	string menu_items[3] = { "Start","From save","Exit" };
	/**
				 *	
			*  *   *  *
			***	    ***
	**/
	vector_ship_player.push_back(point(game, 20, LINES - 3, "|"));
	vector_ship_player.push_back(point(game, 20, LINES - 2, "*"));
	vector_ship_player.push_back(point(game, 21, LINES - 2, "*"));
	vector_ship_player.push_back(point(game, 22, LINES - 2, "*"));
	vector_ship_player.push_back(point(game, 23, LINES - 3, "*"));
	vector_ship_player.push_back(point(game, 24, LINES - 4, "*"));
	vector_ship_player.push_back(point(game, 24, LINES - 5, "|"));
	vector_ship_player.push_back(point(game, 25, LINES - 3, "*"));
	vector_ship_player.push_back(point(game, 26, LINES - 2, "*"));
	vector_ship_player.push_back(point(game, 27, LINES - 2, "*"));
	vector_ship_player.push_back(point(game, 28, LINES - 2, "*"));
	vector_ship_player.push_back(point(game, 28, LINES - 3, "|"));

	ship* ship_player = new ship(&vector_ship_player);

	thread input(_input,game,menu,ship_player, _g_i);



	while (!_g_i->getExit())
	{
		//
		//wclear(menu);
		//wclear(game);
		//this_thread::sleep_for(100ms);
		//
		wrefresh(game);
		wrefresh(menu);
		box(game, 0, 0);
		box(menu, 1, 1);
		for (size_t i = 0; i < sizeof(menu_items) / sizeof(menu_items[0]); i++)
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
			vector<point> kek = ship_player->getWeapons();
			
			//wprintw(menu, "%X", kek.size());

			for (auto weapon_point : kek) {
				vector_bullet.push_back(bullet(weapon_point));
			}
			for (auto& b:vector_bullet)
			{
				
				b.move(true);
				b.show();
			}
			this_thread::sleep_for(std::chrono::microseconds(_g_i->getFrameRate()));
			ship_player->show();
		}

		//refresh();
		//
	}
	input.join();
}


int main(int argc, char* argv[]) {
	initscr();
	int frame_rate = argc < 2 ? 100 : stoi(argv[1]);

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
	raw();
	//nonl();
	curs_set(false);
	clear();
	WINDOW* game = newwin(LINES, COLS-20, 0, 0);
	WINDOW* menu = newwin(LINES, 19, 0, COLS / 2);
	mvwin(game, 0, 0);
	mvwin(menu, 0, COLS - 20);
	keypad(stdscr, true);
	game_inputs _game_inputs(false, 0, false,frame_rate);

	thread draw(_draw,game, menu,&_game_inputs);
	draw.join();
	delwin(game);
	delwin(menu);
	endwin();
	return (0);
}