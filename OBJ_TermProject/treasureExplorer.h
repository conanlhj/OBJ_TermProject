#include <windows.h>
#include <iostream>
#include <conio.h>
#include <fstream>
#include <atomic>
#include <future>
#include <thread>
#include <random>
#include <string>
#include <vector>
#include <stack>
#include <set>
using namespace std;
// hiび涯訓いし軒;たいしいしい
// 古滴稽 舛税
#define INF 2147483647
#define MAX_MAP_SIZE 100

// <int int>研 蟹展鎧奄 是敗
typedef pair<int, int> Pair;
// <double, pair<int, int> >研 蟹展鎧奄 是敗
typedef pair<double, pair<int, int>> pPair;

class Map {
private:
	char map[MAX_MAP_SIZE][MAX_MAP_SIZE];
	vector<Monster*> monsters;
	vector<Village*> villages;
	vector<Ruin*> ruins;
	vector<Ore*> ores;
	vector<Mountain*> mountains;
	Player* p;
public:
	Map();
	void printMap();
	char* getMap();
};

class Object {
protected:
	// 崇送績戚 亜管廃 神崎詮闘昔走 妊獣
	bool isMovable;
	// 波穣亜管廃 神崎詮闘昔走 妊獣
	bool isCollectable;
	// 脊舌亜管廃 舌社昔走 妊獣
	bool isPlace;
	// 背雁 疎妊
	int x, y;

public:
	Object(bool move, bool collect, bool place);
	// 惟斗
	virtual char getChar();
	bool getIsMovable();
	bool getIsCollectable();
	bool getIsPlace();
	int getX();
	int getY();
};

class MovingObject : public Object {
protected:
	int money;
	int health;
	int AD;
public:
	MovingObject();
	MovingObject(int money, int health, int AD);

	void operator -(MovingObject& amount);
	void operator +(MovingObject& amount);
	bool move(char dir);
	virtual char getDirection();

	bool isDead();
	int getMoney();
	int getHealth();
	int getAD();
};

class Player : public MovingObject {
private:
	string name;
	int score;
	int food;
	int luck;
	int dead_code;
public:
	Player();
	char getDirection();
	char getChar();
};

class Monster : public MovingObject {
private:
	struct cell {
		// 背雁 cell税 採乞cell税 亜稽 室稽 idx煽舌
		int parent_i, parent_j;
		// f = g + h
		double f, g, h;
	};
	char difficulty;
	Pair aStarSearch(int grid[MAX_MAP_SIZE][MAX_MAP_SIZE], Pair src, Pair dest);
	bool isValid(int r, int c);
	bool isDest(int r, int c, Pair dest);
	Pair findNextMove(cell cellDetails[MAX_MAP_SIZE][MAX_MAP_SIZE], Pair dest);
	double calcHValue(int r, int c, Pair dest);
public:
	Monster(int y, int x);
	char getDirection(Player* p, Map* m);
	char getChar();
};

class Mountain : public Object {
public:
	Mountain(int y, int x);
	char getChar();
};

class Ore : public Object {
private:
	int value;
public:
	Ore(int y, int x, int value);
	char getChar();
};

class Place : public Object {
public:
	Place();
	virtual void printSelectPage();
};

class Ruin : public Place {
public:
	Ruin(int y, int x);
	void printSelectPage();
	char getChar();
};

class Village : public Place {
public:
	Village(int y, int x);
	void printSelectPage();
	char getChar();
};

void run_game();
void gotoxy(int x, int y);
void story(int part);
void intro();
void gameStartInit();
void gameInit();
void blink(unsigned int interval_msecs, atomic<bool>& keep_at_it);
void printUIBox();