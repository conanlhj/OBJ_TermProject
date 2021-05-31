#include "treasureExplorer.h"

Ore::Ore(int _y, int _x, int _value) : Object(false, true, false) {
	x = _x;
	y = _y;
	value = _value;
}