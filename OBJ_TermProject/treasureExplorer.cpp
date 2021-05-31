#include "treasureExplorer.h"

void gameStartInit() {
	system("mode con cols=109 lines=38");
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void gameInit() {
	system("mode con cols=64 lines=38");
}

void gotoxy(int x, int y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void blink(unsigned int interval_msecs, atomic<bool>& keep_at_it) {
	while (keep_at_it)
	{
		gotoxy(0, 28);

		cout << " |                                     > Press any key to start!                                           |\r";
		this_thread::sleep_for(chrono::milliseconds(interval_msecs));
		cout << " |                                                                                                         |\r";
		this_thread::sleep_for(chrono::milliseconds(interval_msecs));
	}
}

void printUIBox() {
	ifstream file;
	file.open("box.txt");
	if (!file.is_open()) {
		cout << "intro.txt" << " 파일을 찾을 수 없습니다." << endl;
		return;
	}

	while (!file.eof()) {
		string str;
		getline(file, str);
		cout << str << endl;
	}
}

void run_game() {
	Map map;
	gameStartInit();
	intro();
	system("cls");
	gameInit();

	printUIBox();
	printINFO(&p);
}

void intro() {
	ifstream file;
	file.open("intro.txt");

	if (!file.is_open()) {
		cout << "intro.txt" << " 파일을 찾을 수 없습니다." << endl;
		return;
	}

	while (!file.eof()) {
		string str;
		getline(file, str);
		cout << str << endl;
	}

	std::atomic<bool> keep_blinking(true);
	auto future = async(launch::async, blink, 500, ref(keep_blinking));
	_getch();
	keep_blinking = false;

}

void printINFO() {
	gotoxy(1, 1);
	ifstream file;
	file.open("ObjInfo.txt");

	if (!file.is_open()) {
		cout << "intro.txt" << " 파일을 찾을 수 없습니다." << endl;
		return;
	}

	while (!file.eof()) {
		string str;
		getline(file, str);
		cout << str << endl;
	}

}

/* Main 함수입니다. */
int main() {
	run_game();
	return 0;
}