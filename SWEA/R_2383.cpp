#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;

int N;
int answer = 987654321;
int map[11][11];

struct person {
	int x;
	int y;
	int start_time;
	int move_time;
	int end_time;
	bool finish;
};

struct stair {
	int x;
	int y;
	int s_len;
	int num;
};

int Select[10]; // 사라마다 선택하는 계단 번호 저장 0또는 1
person p[10];
stair s[2];
int p_cnt = 0; // 사람수
int s_cnt = 0;

int cal(int p_idx, int s_idx) { // 계단과 사람 사이의 거리 + 도착하면 1초 기다려야함
	int dx = abs(p[p_idx].x - s[s_idx].x);
	int dy = abs(p[p_idx].y - s[s_idx].y);
	return dx + dy + 1;
}

void solution() {
	int time[2] = { 0,0 };
	vector <int> v[2]; // 계단 대기열

	for (int i = 0; i < p_cnt; i++) {
		int idx = Select[i]; //사람별로 계단 정하기
		p[i].move_time = cal(i, idx); // 계단까지 얼마나걸리는지
		v[idx].push_back(p[i].move_time); // 계단에 추가함
	}

	for (int i = 0; i < 2; i++) {
		if (v[i].size() == 0) continue;

		sort(v[i].begin(), v[i].end()); // 계단까지 도착한 순으로
		time[i] = v[i][v[i].size() - 1]; // 마지막 원소가 가장 긴 시간

		if (v[i].size() > 3) {
			int idx = v[i].size() - 1;
			time[i] = max(time[i] + s[i].s_len, v[i][idx - 3] + s[i].s_len + s[i].s_len);
			/*
			//마지막 사람의 인덱스번호 - 3 의 인덱스 번호를 갖는 사람이 이용을 끝내야 한다는 것
			이것이 공식.
			1. 맨 마지막 애가 내려가는게 제일 느릴때-앞에 세명이 못내려가면 기다려야할수도 있따.
			2. 앞에 누가 내려가고 바로 내려갈때
			*/
		}
		else {
			time[i] = s[i].s_len + time[i]; // 계단 길이 더해줌
		}
	}

	int max_t = max(time[0], time[1]);
	answer = min(answer, max_t);
}

void dfs(int cnt) {
	if (cnt == p_cnt) {
		solution();
		return;
	}

	for (int i = 0; i < 2; i++) { // 두 조합으로 나눔. 중복되게
		Select[cnt] = i;
		dfs(cnt + 1);
	}
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	freopen("input.txt", "r", stdin);
	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		cin >> N;
		answer = 987654321;
		p_cnt = 0;
		s_cnt = 0;
		memset(map, 0, sizeof(map));
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> map[i][j];
				if (map[i][j] == 1) {
					p[p_cnt].x = i;
					p[p_cnt].y = j;
					p[p_cnt].start_time = p[p_cnt].move_time = p[p_cnt].end_time = -1;
					p[p_cnt].finish = false;
					p_cnt++;
				}
				else if (map[i][j] > 1) {
					s[s_cnt].x = i;
					s[s_cnt].y = j;
					s[s_cnt].s_len = map[i][j];
					s_cnt++;
				}
			}
		}

		dfs(0);

		cout << "#" << test_case << " " << answer << endl;

	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
