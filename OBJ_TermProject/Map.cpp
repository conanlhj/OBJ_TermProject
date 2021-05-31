#include "treasureExplorer.h"

Map::Map() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> random(0, 99);

	int tmp;
	for (int i = 0; i < MAX_MAP_SIZE; i++)
		for (int j = 0; j < MAX_MAP_SIZE; j++) {
			tmp = random(gen);
			if (tmp < 80)  map[i][j] = '_';
			else if (tmp < 95) {
				map[i][j] = 'T';
				Mountain* m = (Mountain*)malloc(sizeof(Mountain));
				*m = Mountain(i, j);
				mountains.push_back(m);
			}
			else if (tmp < 97) {
				map[i][j] = '+';
				Ore* o = (Ore*)malloc(sizeof(Ore));
				*o = Ore(i, j, 10);
				ores.push_back(o);
			}
			else if (tmp < 98) {
				map[i][j] = '*';
				Ore* o = (Ore*)malloc(sizeof(Ore));
				*o = Ore(i, j, 50);
				ores.push_back(o);
			}
			else if (tmp < 99) {
				map[i][j] = '?';
				Ruin* r = (Ruin*)malloc(sizeof(Ruin));
				*r = Ruin(i, j);
				ruins.push_back(r);
			}
			else {
				map[i][j] = '#';
				Village* v = (Village*)malloc(sizeof(Village));
				*v = Village(i, j);
				villages.push_back(v);
			}
		}
}

char* Map::getMap() { return &map[0][0]; }
Player* Map::getPlr() { return p; }