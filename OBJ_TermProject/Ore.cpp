#include "treasureExplorer.h"

Ore::Ore(int y, int x, int value) : Object(false, true, false) {
	this->x = x;
	this->y = y;
	this->value = value;
}

char Ore::getChar() {
	return '*';
}