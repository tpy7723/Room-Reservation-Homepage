#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

#define endl "\n"

using namespace std;

string solution(vector<string> phone) {
	sort(phone.begin(), phone.end()); // 사전순 정렬

	for (int i = 0; i < phone.size() - 1; i++)
	{
		if (phone[i] == phone[i + 1].substr(0, phone[i].size())) // 부분 문자열과 같은 경우
		{
			return "NO";
		}
	}

	return "YES";
}

int main() {
	int t; // 테스트 케이스의 개수
	
	cin >> t;

	while (t--) { // 테스트 케이스
		int n; // 전화번호의 수
		vector<string> phone; // 전화번호부
		string phonenum; // 전화번호
		cin >> n;

		for (int i = 0; i < n; i++) {
			cin >> phonenum;
			phone.push_back(phonenum);
		}

		cout << solution(phone) << endl; // 결과 출력
	}
	
	return 0;
}


//2
//3
//119
//0108374902
//1192983023
//4
//017
//0108374902
//0112983923
//0198394891