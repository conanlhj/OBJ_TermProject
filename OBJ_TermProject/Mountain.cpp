#include "treasureExplorer.h"

Mountain::Mountain(int y, int x) : Object(false, false, false) {
	this->x = x;
	this->y = y;

};

char Mountain:: getChar() {
	return 'T';
}