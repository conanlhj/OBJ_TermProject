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


// ��ũ�� ����
#define INF 2147483647
#define MAX_MAP_SIZE 100

// <int int>�� ��Ÿ���� ����
typedef pair<int, int> Pair;
// <double, pair<int, int> >�� ��Ÿ���� ����
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
	// �������� ������ ������Ʈ���� ǥ��
	bool isMovable;
	// �Ⱦ������� ������Ʈ���� ǥ��
	bool isCollectable;
	// ���尡���� ������� ǥ��
	bool isPlace;
	// �ش� ��ǥ
	int x, y;

public:
	Object(bool move, bool collect, bool place);
	// ����
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
		// �ش� cell�� �θ�cell�� ���� ���� idx����
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