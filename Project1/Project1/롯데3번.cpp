#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <set>

#define endl "\n"

using namespace std;

int map[25][25]; // 지도
int cnt = 0; // 단지 수
int dir[4][2] = { {1,0},{-1,0},{0,-1},{0,1} }; // 상하 좌우
int temp[500]; // 동의 수
multiset<int> s;
int s_cnt;
int n;

// 지도의 범위를 벗어나는지 확인
bool isindoor(int a, int b) {
	return (0 <= a && a < n) && (0 <= b && b < n);
}

void dfs(int r, int c) {
	map[r][c] = 0; // 1 -> 0
	s_cnt++; // 동의 개수 추가

	for (int i = 0; i < 4; i++) {
		// 좌표 이동
		int nr = r + dir[i][0];
		int nc = c + dir[i][1];

		// 범위를 벗어나지 않고 동이 존재하면
		if (isindoor(nr, nc) && map[nr][nc] == 1) {
			dfs(nr, nc); // 재귀
		}
	}
}

void Solution(int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (map[i][j] == 1) { // 건물이 있으면
				cnt++; // 단지 종류 개수
				s_cnt = 0; // 동의 개수 초기화
				dfs(i, j); // DFS
				s.insert(s_cnt); // 동의 개수 삽입
			}
		}
	}
}

int main(void) {
	cin >> n;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j]; // 지도 입력
		}
	}

	Solution(n);

	cout << cnt << endl; // 단지 수 출력

	for (auto i = s.begin(); i != s.end(); i++) {
		cout << *i << endl;// 동의 수 오름차순 출력
	}

	return 0;
}


//5
//1 1 1 0 1
//0 0 1 0 1
//1 1 0 1 0
//0 0 1 0 1
//1 1 0 1 0
