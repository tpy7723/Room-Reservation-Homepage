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

	// 팩토리얼 dp
	factorial[0] = 1;
	for (int i = 1; i < 21; i++) {
		factorial[i] = factorial[i - 1] * i;
	}

	if (t == 1) {
		cin >> cnt;
		for (int i = 0; i < N; i++) {
			for (int j = 1; j <= N; j++) {
				if (visit[j] == 1) continue; // 해당 숫자를 사용했다면 패스
					
				// 구하려는 cnt보다 팩토리얼이 작을 경우
				if (factorial[N - i - 1] < cnt) {
					cnt -= factorial[N - i - 1];
				}
				else {
					result.push_back(j);
					visit[j] = 1; // 숫자 사용 여부 체크
					break;
				}
			}
		}

		// 결과 출력
		for (int i = 0; i < N; i++) {
			cout << result[i] << " ";
		}
	}
	else if (t == 2) {
		long long ans = 0;

		for (int i = 0; i < N; i++) { // 원하는 연구 순서를 찾을 재료들의 순서 입력
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

