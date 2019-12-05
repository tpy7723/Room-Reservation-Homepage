#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

#define endl "\n"

using namespace std;

string solution(vector<string> phone) {
	sort(phone.begin(), phone.end()); // ������ ����

	for (int i = 0; i < phone.size() - 1; i++)
	{
		if (phone[i] == phone[i + 1].substr(0, phone[i].size())) // �κ� ���ڿ��� ���� ���
		{
			return "NO";
		}
	}

	return "YES";
}

int main() {
	int t; // �׽�Ʈ ���̽��� ����
	
	cin >> t;

	while (t--) { // �׽�Ʈ ���̽�
		int n; // ��ȭ��ȣ�� ��
		vector<string> phone; // ��ȭ��ȣ��
		string phonenum; // ��ȭ��ȣ
		cin >> n;

		for (int i = 0; i < n; i++) {
			cin >> phonenum;
			phone.push_back(phonenum);
		}

		cout << solution(phone) << endl; // ��� ���
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