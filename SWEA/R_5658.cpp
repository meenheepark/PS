#include <string>
#include<iostream>
#include <algorithm>
#include<vector>

using namespace std;

int N, K;
int answer = 0; 
vector <string> v;
vector <int> num;

void change() {
	//16진수 10진수로 바꿔줌.
	for (int i = 0; i < v.size(); i++) {
		int cnt = 1;
		int sum = 0;
		for (int j = N/4 -1; j >= 0 ; j--) {
			if (v[i][j] == 'A') {
				sum += cnt * 10;
			}
			else if (v[i][j] == 'B') {
				sum += cnt * 11;
			}
			else if (v[i][j] == 'C') {
				sum += cnt * 12;
			}
			else if (v[i][j] == 'D') {
				sum += cnt * 13;

			}
			else if (v[i][j] == 'E') {
				sum += cnt * 14;
			}
			else if (v[i][j] == 'F') {
				sum += cnt * 15;
			}
			else { // 숫자일때.
				int t = v[i][j] - '0'; // 숫자로 바뀜
				sum += cnt * t;
			}
			cnt *= 16; // 자릿수 높아지는것.
		}
		num.push_back(sum);

	}
	sort(num.begin(), num.end(), greater<int>());
	answer = num[K - 1];
	return;

}

string turn(string s) {
	int size = s.size();
	string tmp = "";
	tmp += s[size - 1];
	for (int i = 0; i < size - 1; i++) {
		tmp += s[i];
	}
	return tmp;
}

void add(string s) {
	for (int i = 0; i < N ; i += N / 4) {
		string p ="";
		for (int j = 0; j < N / 4; j++) {
			p += s[i + j];
		}
		bool check = true;
		for (int j = 0; j < v.size(); j++) {
			if (p == v[j]) {
				check = false;
				break;
			}
		}
		if (check == true) {
			v.push_back(p);
		}
	}
	return;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	freopen("input.txt", "r", stdin);
	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		answer = 0;
		cin >> N >> K;
		string s;
		cin >> s;
		for (int i = 0; i < N / 4; i++) { // 회전
			s = turn(s);
			add(s);
		}
		change();

		cout << "#" << test_case << " " << answer << endl;
		v.clear();
		num.clear();
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
