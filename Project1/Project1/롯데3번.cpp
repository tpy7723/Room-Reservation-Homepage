#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <set>

#define endl "\n"

using namespace std;

int map[25][25]; // ����
int cnt = 0; // ���� ��
int dir[4][2] = { {1,0},{-1,0},{0,-1},{0,1} }; // ���� �¿�
int temp[500]; // ���� ��
multiset<int> s;
int s_cnt;
int n;

// ������ ������ ������� Ȯ��
bool isindoor(int a, int b) {
	return (0 <= a && a < n) && (0 <= b && b < n);
}

void dfs(int r, int c) {
	map[r][c] = 0; // 1 -> 0
	s_cnt++; // ���� ���� �߰�

	for (int i = 0; i < 4; i++) {
		// ��ǥ �̵�
		int nr = r + dir[i][0];
		int nc = c + dir[i][1];

		// ������ ����� �ʰ� ���� �����ϸ�
		if (isindoor(nr, nc) && map[nr][nc] == 1) {
			dfs(nr, nc); // ���
		}
	}
}

void Solution(int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (map[i][j] == 1) { // �ǹ��� ������
				cnt++; // ���� ���� ����
				s_cnt = 0; // ���� ���� �ʱ�ȭ
				dfs(i, j); // DFS
				s.insert(s_cnt); // ���� ���� ����
			}
		}
	}
}

int main(void) {
	cin >> n;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j]; // ���� �Է�
		}
	}

	Solution(n);

	cout << cnt << endl; // ���� �� ���

	for (auto i = s.begin(); i != s.end(); i++) {
		cout << *i << endl;// ���� �� �������� ���
	}

	return 0;
}


//5
//1 1 1 0 1
//0 0 1 0 1
//1 1 0 1 0
//0 0 1 0 1
//1 1 0 1 0
