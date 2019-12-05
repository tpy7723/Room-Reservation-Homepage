#include <iostream>
#include <algorithm>
#include <vector>

#define endl "\n"

using namespace std;

int main() {
	int N, t;
	long long cnt = 0;
	long long factorial[21] = { 0, };
	int visit[21] = { 0, };
	vector<int> result;

	cin >> N >> t;

	// ���丮�� dp
	factorial[0] = 1;
	for (int i = 1; i < 21; i++) {
		factorial[i] = factorial[i - 1] * i;
	}

	if (t == 1) {
		cin >> cnt;
		for (int i = 0; i < N; i++) {
			for (int j = 1; j <= N; j++) {
				if (visit[j] == 1) continue; // �ش� ���ڸ� ����ߴٸ� �н�
					
				// ���Ϸ��� cnt���� ���丮���� ���� ���
				if (factorial[N - i - 1] < cnt) {
					cnt -= factorial[N - i - 1];
				}
				else {
					result.push_back(j);
					visit[j] = 1; // ���� ��� ���� üũ
					break;
				}
			}
		}

		// ��� ���
		for (int i = 0; i < N; i++) {
			cout << result[i] << " ";
		}
	}
	else if (t == 2) {
		long long ans = 0;

		for (int i = 0; i < N; i++) { // ���ϴ� ���� ������ ã�� ������ ���� �Է�
			int t;
			cin >> t;
			result.push_back(t);
		}

		for (int i = 0; i < N; i++) {
			for (int j = 1; j < result[i]; j++) {
				if (visit[j] == 0) {
					ans += factorial[N - i - 1];
				}
			}
			visit[result[i]] = 1;
		}
		cout << ans + 1 << endl;
	}

	return 0;
}

