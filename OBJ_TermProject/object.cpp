#include "treasureExplorer.h"

Object::Object(bool move, bool collect, bool place)
	: isMovable(move), isCollectable(collect), isPlace(place) {
	x = 0;
	y = 0;
};

bool Object::getIsMovable() { return isMovable; }
bool Object::getIsCollectable() { return isCollectable; }
bool Object::getIsPlace() { return isPlace; }
int Object::getX() { return x; }
int Object::getY() { return y; }