#include <iostream>

#define endl "\n"

using namespace std;

int N, M, x, y, K, order;
int map[20][20]; // 지도
int r, c; // 주사위 좌표
int cube[6] = { 0,0,0,0,0,0 }; // 주사위 6면 값
			// 0 1  2 3  4 5
			// 상하 앞뒤 좌우 

bool isindoor(int r, int c) {
	return (0 <= r && r < N) && (0 <= c && c < M);
}

// 주사위를 d 방향으로 굴리는 함수
void solution(int d) {
	int temp;
	bool possible = true;

	switch (d){

	case 1: // 동
		// 동 => 상이 우 우가 하 하가 좌 좌가 상
		if (!isindoor(r, c + 1)) {
			possible = false;
			break;
		}
		c++;
		temp = cube[0];
		cube[0] = cube[4];
		cube[4] = cube[1];
		cube[1] = cube[5];
		cube[5] = temp;
		break;

	case 2: // 서
		// 서 => 상이 좌 좌가 하 하가 우 우가 상
		if (!isindoor(r, c - 1)) {
			possible = false;
			break;
		}
		c--;
		temp = cube[0];
		cube[0] = cube[5];
		cube[5] = cube[1];
		cube[1] = cube[4];
		cube[4] = temp;
		break;

	case 3: // 북
		// 북 => 상이 뒤 뒤가 하 하가 앞 앞이 상
		if (!isindoor(r - 1, c)) {
			possible = false;
			break;
		}
		r--;
		temp = cube[0];
		cube[0] = cube[2];
		cube[2] = cube[1];
		cube[1] = cube[3];
		cube[3] = temp;
		break;

	case 4: // 남
		if (!isindoor(r + 1, c)) {
			possible = false;
			break;
		}
		r++;
		// 남 => 상이 앞 앞이 하 하가 뒤 뒤가 상
		temp = cube[0];
		cube[0] = cube[3];
		cube[3] = cube[1];
		cube[1] = cube[2];
		cube[2] = temp;
		break;

	default:
		break;
	}

	if (!possible) return; // 범위를 벗어나는 경우 명령 무시

	if (map[r][c] == 0) { // 이동한 칸에 쓰여 있는 수가 0이면
		map[r][c] = cube[1]; // 주사위의 바닥면에 쓰여 있는 수가 칸에 복사된다.
	}
	else { // 이동한 칸에 쓰여 있는 수가 0이 아니면
		cube[1] = map[r][c]; // 칸에 쓰여 있는 수가 주사위의 바닥면으로 복사
		map[r][c] = 0; // 칸에 쓰여 있는 수는 0이 된다.
	}

	cout << cube[0] << endl; // 윗면 출력
}

int main() {
	cin >> N >> M >> r >> c >> K; // 세로, 가로, 주사위 r, 주사위 c, 명령 개수 입력

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j]; // 지도 입력
		}
	}

	for (int i = 0; i < K; i++) {
		cin >> order; // 명령 입력
		solution(order); // 주사위 이동
	}

	return 0;
}



//20 10 10 5 9
//1 2 8 4 6 9 5 1 3 5
//5 6 1 5 9 8 7 5 6 9
//3 5 9 8 7 5 8 2 2 1
//0 0 0 0 0 5 5 9 9 9
//9 5 8 4 7 5 6 3 2 1
//5 6 4 8 2 5 6 3 2 5
//9 5 1 4 7 8 9 5 1 3
//0 2 3 6 0 2 6 0 2 5
//0 5 9 8 2 0 3 6 5 4
//9 5 1 6 5 1 2 3 1 5
//6 9 5 1 5 4 7 8 5 6
//3 2 1 4 5 6 9 8 5 5
//1 2 3 1 2 5 9 8 5 2
//9 5 8 5 2 1 2 1 4 5
//6 5 2 6 9 8 5 4 1 2
//6 2 6 2 1 5 4 7 8 9
//5 9 5 1 4 5 6 6 3 2
//1 2 5 8 9 6 5 4 1 2
//1 2 3 6 5 1 1 4 7 7
//9 5 1 5 1 5 8 0 0 2
//3 3 3 1 1 1 1 1 2
