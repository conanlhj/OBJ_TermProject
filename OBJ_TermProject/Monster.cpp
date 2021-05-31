#include "treasureExplorer.h"

Monster::Monster(int y, int x) {
	// 난수 생성 준비 후 난수 생성
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> random(0, 9);
	int diff = random(gen);

	if (diff == 0) {
		difficulty = 'h';
		money = 100;
		health = 20;
		AD = 10;
	}
	else if (diff < 4) {
		difficulty = 'n';
		money = 50;
		health = 10;
		AD = 5;
	}
	else {
		difficulty = 'e';
		money = 25;
		health = 5;
		AD = 1;
	}
}

char Monster::getDirection(Player* p, Map* m) {

	/*	몬스터가 플레이어까지 가는 경로를 찾기 위해서 이동 가능한 사물과 불가능한 사물 분리
	0 --> 이동하지 못하는 산(T)의 경우
	1 --> 이동 가능한 나머지 */
	int grid[MAX_MAP_SIZE][MAX_MAP_SIZE];
	char* tmp = m->getMap();
	for (int i = 0; i < MAX_MAP_SIZE; i++)
		for (int j = 0; j < MAX_MAP_SIZE; j++) {
			grid[i][j] = (*tmp != 'T');
			tmp++;
		}

	// 현재 monster의 좌표, 시작점이 됨.
	Pair currentMonsterCord = make_pair(y, x);
	// 현재 플레이어의 좌표, 도착점이 됨.
	Pair currentPlayerCord = make_pair(p->getY(), p->getX());

	// A* 알고리즘으로 다음 움직일 곳 찾기
	Pair nextMove = aStarSearch(grid, currentMonsterCord, currentPlayerCord);

	// 찾은 r과 c에 따라 return
	int r = nextMove.first, c = nextMove.second;
	// 몬스터의 다음 움직임이 대각선이면, 상하로 조정
	// 몬스터가 상하좌우로 모두 움직일 수 있는 경우엔, 상하로 우선적으로 움직인다.
	if (r != y && c != x) {
		// 상하로 움직일 수 있으면 상하로 움직이고
		// 나머지는 좌우로 움직이기
		(grid[r][x] == 1) ? c = x : r = y;
	}
	
	if (y - 1 == r) return 'w';			// 상
	else if (y + 1 == r) return 's';	// 하
	else if (x - 1 == r) return 'a';	// 좌
	else return 'd';					// 우
}

/* A* 알고리즘 */
Pair Monster::aStarSearch(int grid[MAX_MAP_SIZE][MAX_MAP_SIZE], Pair src, Pair dest) {
	
	// 어떤 cell이 포함되었는지를 보기 위한 2중배열 & 초기화
	bool closedList[MAX_MAP_SIZE][MAX_MAP_SIZE];
	for (int i = 0; i < MAX_MAP_SIZE; i++)
		for (int j = 0; j < MAX_MAP_SIZE; j++)
			closedList[i][j] = false;
	
	// 모든 칸에 cell할당 & 초기화
	cell cellDetails[MAX_MAP_SIZE][MAX_MAP_SIZE];
	for(int i = 0; i<MAX_MAP_SIZE;i++)
		for (int j = 0; j < MAX_MAP_SIZE; j++) {
			cellDetails[i][j].f = INF;
			cellDetails[i][j].g = INF;
			cellDetails[i][j].h = INF;
			cellDetails[i][j].parent_i = -1;
			cellDetails[i][j].parent_j = -1;
		}
	// 출발할 곳의 cell 초기값 설정
	cellDetails[src.first][src.second].f = 0.0;
	cellDetails[src.first][src.second].g = 0.0;
	cellDetails[src.first][src.second].h = 0.0;
	cellDetails[src.first][src.second].parent_i = src.first;
	cellDetails[src.first][src.second].parent_j = src.second;

	// <f, <i, j>>꼴로 정보를 담는 openList
	set<pPair> openList;
	openList.insert(make_pair(0.0, make_pair(src.first, src.second)));	// 가장 첫 칸을 openList에 넣고 f를 0으로 설정

	// 목적지를 찾았는지 확인
	bool isDestFound = false;

	while (!openList.empty()) {
		pPair p = *openList.begin();
		openList.erase(openList.begin());

		int i = p.second.first, j = p.second.second;
		closedList[i][j] = true;


		/* 현재 set에서 뺀 셀로부터 위아래, 좌우, 대각선 4방향, 총 8방향에 대해 연산
		* 1. 위쪽 (i-1. j)
		* 2. 아래쪽 (i+1, j)
		* 3. 왼쪽 (i, j-1)
		* 4. 오른쪽 (i, j+1)
		* 5. 왼쪽 위 (i-1, j-1)
		* 6. 오른쪽 위 (i-1, j+1)
		* 7. 왼쪽 아래 (i+1, j-1)
		* 8. 오른쪽 아래 (i+1, j+1) */
		double gNew, hNew, fNew;
		Pair possibleMove[8];
		possibleMove[0] = make_pair(i - 1, j);
		possibleMove[1] = make_pair(i + 1, j);
		possibleMove[2] = make_pair(i, j - 1);
		possibleMove[3] = make_pair(i, j + 1);
		possibleMove[4] = make_pair(i - 1, j - 1);
		possibleMove[5] = make_pair(i - 1, j + 1);
		possibleMove[6] = make_pair(i + 1, j - 1);
		possibleMove[7] = make_pair(i + 1, j + 1);


		for (int dir = 0; dir < 8; dir++) {
			int new_i = possibleMove[dir].first, new_j = possibleMove[dir].second;

			// 유효한 범위가 아니면, continue
			if (!isValid(new_i, new_j))
				continue;
			// 목적지를 찾았다면 (가본 cell이 도착지 cell 과 같음)
			if (isDest(new_i, new_j, dest)) {
				// 부모 cell 수정 후 return
				cellDetails[new_i][new_j].parent_i = i;
				cellDetails[new_i][new_j].parent_j = j;
				isDestFound = true;
				return findNextMove(cellDetails, dest);
			}
			// 아직 방문을 안했고, 산(T)이 아닌 곳에서만 진행
			else if (closedList[new_i][new_j] == false && grid[new_i][new_j] == 1) {

				// 상하좌우와 대각선의 경우, g의 연산이 다르다.
				// 상하좌우의 경우, <new_i, new_j>와 <i, j>의 거리는 1
				// 대각선의 경우, <new_i, new_j>와 <i, j>의 거리는 √2 ≈ 1.41
				gNew = (dir < 4) ? cellDetails[i][j].g + 1.0 : cellDetails[i][j].g + 1.41;
				hNew = calcHValue(new_i, new_j, dest);
				fNew = gNew + hNew;

				// 만약 오류나면 여기확인~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				// 만약 현재 cell에 저장된 f가 연산한 f보다 크면
				if (cellDetails[new_i][new_j].f > fNew) {
					// openList에 추가
					openList.insert(make_pair(fNew, make_pair(i - 1, j)));

					// 이번에 연산한 셀 업데이트
					cellDetails[new_i][new_j].f = fNew;
					cellDetails[new_i][new_j].g = gNew;
					cellDetails[new_i][new_j].h = hNew;
					cellDetails[new_i][new_j].parent_i = i;
					cellDetails[new_i][new_j].parent_j = j;
				}
			}
		}
	}
	// 만약 while종료후에도 return된 것이 없다면, 주변이 막혀있어서 player에게 접근할 수 없는 경우
	return make_pair(INF, INF);
}

/* 해당 칸이 유효범위 안인지 검사하는 함수
* true -> 유효범위 안
* false -> 유효범위 안X */
bool Monster::isValid(int r, int c) {
	return ((r >= 0) && (r < MAX_MAP_SIZE) && (c >= 0) && (c < MAX_MAP_SIZE));
}

/* 해당 칸이 목적지와 동일한지 확인
* true -> 칸과 목적지 동일
* false -> 칸과 목적지 동일X */
bool Monster::isDest(int r, int c, Pair dest) {
	return (r == dest.first && c == dest.second);
}

// 몬스터가 다음 갈 곳을 반환해주는 함수
// Pair형식으로 반환되며, 다음으로 움직일 곳의 좌표 <row, col>형식으로 반환
Pair Monster::findNextMove(cell cellDetails[MAX_MAP_SIZE][MAX_MAP_SIZE], Pair dest) {
	int r = dest.first, c = dest.second;

	stack<Pair> path;

	// 도착지부터 cell의 부모cell들을 찾아가면서 stack에 push
	while (cellDetails[r][c].parent_i != r || cellDetails[r][c].parent_j != c) {
		path.push(make_pair(r, c));
		r = cellDetails[r][c].parent_i;
		c = cellDetails[r][c].parent_j;
	}
	// stack의 마지막 요소는 출발지로 저장되어있으므로 pop
	path.pop();
	// 출발지 다음 좌표 return
	return path.top();
}

/* h값을 계산하는 함수
* 현재 좌표와 도착지 좌표의 거리 계산 후 반환 */
double Monster::calcHValue(int r, int c, Pair dest) {
	return ((double)sqrt((r - dest.first) * (r - dest.first) + (c - dest.second) * (c - dest.second)));
}

/* Monster의 M 반환 */
char Monster::getChar() { return 'M'; }