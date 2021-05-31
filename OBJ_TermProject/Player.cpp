#include "treasureExplorer.h"

class Player : public MovingObject {
private:
	string name;
	int score;
	int food;
	int luck;
	int dead_code;
public:
	Player();
	Player(string name);
	char getDirection();
	char getChar();
	void addScore(int score);
	void addFood(int food);
	void addLuck();
	void setDC(int dc);

};

Player::Player(string name) : MovingObject(){
	this->name = name;
};

char Player::getDirection() {
	char dir;
	while (1) {
		cout << "방향키를 입력하세요 -> w(상)a(좌)s(하)d(우)";
		cin >> dir;
		if (dir != 'w' || dir != 'a' || dir != 's' || dir != 'd') {
			cout << "잘못 입력하셨습니다\n";
			continue;
		}
		if (move(dir)) {
			return dir;
			this->food--;
			break;
		}
		else {
			cout << "그 길은 막혀서 갈 수 없습니다!!!\n";
			continue;
		}
	}
}

char Player::getChar() {
	return 'P';
}

void Player::addScore(int score) {
	this->score += score;
}

void Player::addFood(int food) {
	this->food += food;
}

void Player::addLuck() {
	this->luck *= 2;
}

void Player::setDC(int dc) {
	this->dead_code = dc;
}



