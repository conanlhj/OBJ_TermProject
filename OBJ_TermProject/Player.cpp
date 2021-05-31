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
		cout << "����Ű�� �Է��ϼ��� -> w(��)a(��)s(��)d(��)";
		cin >> dir;
		if (dir != 'w' || dir != 'a' || dir != 's' || dir != 'd') {
			cout << "�߸� �Է��ϼ̽��ϴ�\n";
			continue;
		}
		if (move(dir)) {
			return dir;
			this->food--;
			break;
		}
		else {
			cout << "�� ���� ������ �� �� �����ϴ�!!!\n";
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



