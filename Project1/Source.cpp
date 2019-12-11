#include <cstdio>
#include <thread>
#include <string>
#include <random>
//#include <curses.h>
#include "ship.h"
#include "bullet.h"

using namespace std;

#define BULLET_COUNT 2

int randint(int max, int min = 0)
{
	return (min <= max) ?
		((rand() % ((max + 1) - min)) + min) :
		((rand() % ((min + 1) - max)) + max);
}


struct game_inputs
{
private:
	bool exit;
	bool start;
	bool shoot;
	int m_item;
	int frame_rate;

public:
	game_inputs() {
		exit = 0;
		m_item = 0;
		start = 0;
		frame_rate = 100;
		shoot = false;
	}
	game_inputs(const bool& _exit, const int& _m_item,const bool& _start,const int& f_r) {
		exit = _exit;
		m_item = _m_item;
		start = _start;
		frame_rate = f_r;
		shoot = false;
	}
	const bool& getExit() {
		return exit;
	}
	const bool& canShoot() {
		return shoot;
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
	void setShoot(const bool& s) {
		shoot = s;
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
		case 0x20: {
			//Beep(9000,500);
			_g_i->setShoot(true);
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
			wresize(game, LINES, COLS - 20);
			wresize(menu, LINES, 19);
			mvwin(menu, 0, COLS - 20);
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
	vector <point> vector_ship_enemy;
	vector <bullet*> vector_bullet;
	string menu_items[3] = { "Start","From save","Exit" };

	vector_ship_player.push_back(point(game, 19, LINES - 3, "|"));
	vector_ship_player.push_back(point(game, 20, LINES - 3, "<"));
	vector_ship_player.push_back(point(game, 20, LINES - 2, "*"));
	vector_ship_player.push_back(point(game, 21, LINES - 3, "{"));
	vector_ship_player.push_back(point(game, 21, LINES - 2, "*"));
	vector_ship_player.push_back(point(game, 22, LINES - 5, "_"));
	vector_ship_player.push_back(point(game, 22, LINES - 4, "("));
	vector_ship_player.push_back(point(game, 22, LINES - 3, "/"));
	vector_ship_player.push_back(point(game, 22, LINES - 2, "*"));
	vector_ship_player.push_back(point(game, 23, LINES - 5, "_"));
	vector_ship_player.push_back(point(game, 23, LINES - 4, "*"));
	vector_ship_player.push_back(point(game, 23, LINES - 3, "/"));
	vector_ship_player.push_back(point(game, 24, LINES - 5, "/"));
	vector_ship_player.push_back(point(game, 24, LINES - 3, "_"));
	vector_ship_player.push_back(point(game, 25, LINES - 5, "\\"));
	vector_ship_player.push_back(point(game, 25, LINES - 4, "^"));
	vector_ship_player.push_back(point(game, 25, LINES - 3, "_"));
	vector_ship_player.push_back(point(game, 26, LINES - 5, "_"));
	vector_ship_player.push_back(point(game, 26, LINES - 4, "*"));
	vector_ship_player.push_back(point(game, 26, LINES - 3, "\\"));
	vector_ship_player.push_back(point(game, 27, LINES - 5, "_"));
	vector_ship_player.push_back(point(game, 27, LINES - 4, ")"));
	vector_ship_player.push_back(point(game, 27, LINES - 3, "\\"));
	vector_ship_player.push_back(point(game, 27, LINES - 2, "*"));
	vector_ship_player.push_back(point(game, 28, LINES - 3, "}"));
	vector_ship_player.push_back(point(game, 28, LINES - 2, "*"));
	vector_ship_player.push_back(point(game, 29, LINES - 3, ">"));
	vector_ship_player.push_back(point(game, 29, LINES - 2, "*"));
	vector_ship_player.push_back(point(game, 30, LINES - 3, "|"));


	srand(time(0));

	int x_start = rand() % COLS + 1;
	vector_ship_enemy.push_back(point(game, x_start, 2, "^"));
	vector_ship_enemy.push_back(point(game, x_start, 1, "*"));
	vector_ship_enemy.push_back(point(game, x_start + 1, 1, "*"));
	vector_ship_enemy.push_back(point(game, x_start + 2, 1, "*"));
	vector_ship_enemy.push_back(point(game, x_start + 3, 2, "*"));
	vector_ship_enemy.push_back(point(game, x_start + 4, 3, "*"));
	vector_ship_enemy.push_back(point(game, x_start + 4, 4, "|"));
	vector_ship_enemy.push_back(point(game, x_start + 5, 2, "*"));
	vector_ship_enemy.push_back(point(game, x_start + 6, 1, "*"));
	vector_ship_enemy.push_back(point(game, x_start + 7, 1, "*"));
	vector_ship_enemy.push_back(point(game, x_start + 8, 1, "*"));
	vector_ship_enemy.push_back(point(game, x_start + 8, 2, "^"));


	
	ship* ship_player = new ship(&vector_ship_player);
	vector<ship*> ships_enemy;
	ships_enemy.push_back(new ship(&vector_ship_enemy));
	thread input(_input,game,menu,ship_player, _g_i);

	

	while (!_g_i->getExit())
	{
		
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
			
			
			if (ships_enemy.size()<BULLET_COUNT)
			{
				
				int x_start = rand() % COLS + 1;

				vector_ship_enemy.clear();

				vector_ship_enemy.push_back(point(game, x_start, 2, "^"));
				vector_ship_enemy.push_back(point(game, x_start, 1, "*"));
				vector_ship_enemy.push_back(point(game, x_start + 1, 1, "*"));
				vector_ship_enemy.push_back(point(game, x_start + 2, 1, "*"));
				vector_ship_enemy.push_back(point(game, x_start + 3, 2, "*"));
				vector_ship_enemy.push_back(point(game, x_start + 4, 3, "*"));
				vector_ship_enemy.push_back(point(game, x_start + 4, 4, "|"));
				vector_ship_enemy.push_back(point(game, x_start + 5, 2, "*"));
				vector_ship_enemy.push_back(point(game, x_start + 6, 1, "*"));
				vector_ship_enemy.push_back(point(game, x_start + 7, 1, "*"));
				vector_ship_enemy.push_back(point(game, x_start + 8, 1, "*"));
				vector_ship_enemy.push_back(point(game, x_start + 8, 2, "^"));
				ships_enemy.push_back(new ship(&vector_ship_enemy));
			}
		
			vector<point> kek = ship_player->getWeapons();
			if (_g_i->canShoot())
			{
				for (auto weapon_point : kek) {
					vector_bullet.push_back(new bullet(weapon_point));
				}
				_g_i->setShoot(false);
			}

			for (auto& enemy : ships_enemy) {
				
				bool del = false;
				if (enemy->ifLeft())
					enemy->moveX(randint(COLS, 0));
				else if (enemy->ifRight())
					enemy->moveX(randint(0, -COLS));
				else enemy->moveX(randint(1, -1));
				enemy->moveY(randint(1, 0));
				
				for (auto& _b : vector_bullet)
				{
					enemy->decrementHealth(*_b);
					if (enemy->isDie())
					{
						del = true;
						
					}
				}
				enemy->show();
				if (enemy->isDown() || del)
				{
					enemy->clearP();
					ships_enemy.erase(find(ships_enemy.cbegin(), ships_enemy.cend(), enemy));
				}
			}
			for (auto& b1:vector_bullet)
			{
				
				b1->move(true);
				b1->show();
				if (b1->getY() < -LINES) {
					vector_bullet.erase(vector_bullet.begin());
				}
			}
			this_thread::sleep_for(std::chrono::milliseconds(_g_i->getFrameRate()));
			ship_player->show();
			
		}
		
		wrefresh(game);
		wrefresh(menu);

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
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	noecho();
	raw();
	//nonl();
	curs_set(false);
	clear();
	WINDOW* game = newwin(LINES, COLS-20, 0, 0);
	WINDOW* menu = newwin(LINES, 19, 0, COLS / 2);
	nodelay(game, true);
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