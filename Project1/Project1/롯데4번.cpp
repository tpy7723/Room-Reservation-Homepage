#include <iostream>

#define endl "\n"

using namespace std;

int N, M, x, y, K, order;
int map[20][20]; // ����
int r, c; // �ֻ��� ��ǥ
int cube[6] = { 0,0,0,0,0,0 }; // �ֻ��� 6�� ��
			// 0 1  2 3  4 5
			// ���� �յ� �¿� 

bool isindoor(int r, int c) {
	return (0 <= r && r < N) && (0 <= c && c < M);
}

// �ֻ����� d �������� ������ �Լ�
void solution(int d) {
	int temp;
	bool possible = true;

	switch (d){

	case 1: // ��
		// �� => ���� �� �찡 �� �ϰ� �� �°� ��
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

	case 2: // ��
		// �� => ���� �� �°� �� �ϰ� �� �찡 ��
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

	case 3: // ��
		// �� => ���� �� �ڰ� �� �ϰ� �� ���� ��
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

	case 4: // ��
		if (!isindoor(r + 1, c)) {
			possible = false;
			break;
		}
		r++;
		// �� => ���� �� ���� �� �ϰ� �� �ڰ� ��
		temp = cube[0];
		cube[0] = cube[3];
		cube[3] = cube[1];
		cube[1] = cube[2];
		cube[2] = temp;
		break;

	default:
		break;
	}

	if (!possible) return; // ������ ����� ��� ��� ����

	if (map[r][c] == 0) { // �̵��� ĭ�� ���� �ִ� ���� 0�̸�
		map[r][c] = cube[1]; // �ֻ����� �ٴڸ鿡 ���� �ִ� ���� ĭ�� ����ȴ�.
	}
	else { // �̵��� ĭ�� ���� �ִ� ���� 0�� �ƴϸ�
		cube[1] = map[r][c]; // ĭ�� ���� �ִ� ���� �ֻ����� �ٴڸ����� ����
		map[r][c] = 0; // ĭ�� ���� �ִ� ���� 0�� �ȴ�.
	}

	cout << cube[0] << endl; // ���� ���
}

int main() {
	cin >> N >> M >> r >> c >> K; // ����, ����, �ֻ��� r, �ֻ��� c, ��� ���� �Է�

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j]; // ���� �Է�
		}
	}

	for (int i = 0; i < K; i++) {
		cin >> order; // ��� �Է�
		solution(order); // �ֻ��� �̵�
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
