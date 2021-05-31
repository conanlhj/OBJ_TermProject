#include "treasureExplorer.h"

MovingObject::MovingObject() : Object(true, false, false) {
	money = 0;
	health = 0;
	AD = 0;
}

MovingObject::MovingObject(int money, int health, int AD)
	: Object(true, false, false), money(money), health(health), AD(AD) { }

void MovingObject::operator -(MovingObject& attacker) {
	health -= attacker.getAD();
}

void MovingObject::operator +(MovingObject& attacker) {
	money += attacker.getMoney();
}

bool MovingObject::move(char dir) {
	switch (dir) {
	case 'w':
		if (y - 1 < 0) return false;
		y--;
		break;
	case 's':
		if (y + 1 >= MAX_MAP_SIZE) return false;
		y++;
		break;
	case 'a':
		if (x - 1 < 0) return false;
		x--;
		break;
	case 'd':
		if (x + 1 >= MAX_MAP_SIZE) return false;
		x++;
		break;
	}
	return true;
}

bool MovingObject::isDead() { return (health <= 0); }

int MovingObject::getMoney() { return money; }
int MovingObject::getHealth() { return health; }
int MovingObject::getAD() { return AD; }
