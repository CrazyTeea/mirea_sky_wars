#pragma once

#include "bullet.h"
#include <vector>
#include <iterator>
#include <algorithm>
class ship
{
private:
	std::vector <point> pointers;
	int health;
public:
	ship(std::vector <point>* _pointers);
	void moveY(const int& y);
	void moveX(const int& x);
	void show();
	std::vector<point> getWeapons();
	bool ifLeft();
	bool ifRight();
	bool isUp();
	bool isDown();
	void decrementHealth(bullet& b);
	void decrementHealth();
	const bool& isDie();
	void clearP();
	void setHealth(const int& h);
	int getHealth();
};

