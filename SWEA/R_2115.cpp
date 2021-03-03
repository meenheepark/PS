#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>

using namespace std;

int N, M, C;
int answer = -1;
int map[11][11];
int visited[11][11];

int ans = 0;

void hoice(int x, int y, int cnt, int sum_c, int sum_pro) {
	if (sum_c > C) {
		return;
	}

	ans = max(ans, sum_pro);
	if (cnt == M) { return; }

	hoice(x, y + 1, cnt + 1, sum_c + map[x][y], sum_pro + pow(map[x][y], 2));
	hoice(x, y + 1, cnt + 1, sum_c, sum_pro);
}

int solution(int x, int y) {
	for (int i = 0; i < M; i++) {
		visited[x][y + i] = 1;
	}
	ans = 0;
	hoice(x, y, 0, 0, 0);
	int ans1 = ans;
	int ans2 = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N - M + 1; j++) {
			if (visited[i][j] == 0) {
				ans = 0;
				hoice(i, j, 0, 0, 0);
				ans2 = max(ans2, ans);
			}
		}
	}
	return (ans1 + ans2);
}

int main(int argc, char** argv)
{
	ios::sync_with_stdio(NULL);
	cin.tie(false);

	int test_case;
	int T;
	freopen("input.txt", "r", stdin);
	cin >> T;


	for (test_case = 1; test_case <= T; ++test_case)
	{
		answer = -1;
		memset(map, 0, sizeof(map));
		memset(visited, 0, sizeof(visited));
		cin >> N >> M >> C;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> map[i][j];
			}
		}
		
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N - M + 1; j++) {
				answer = max(answer, solution(i, j)); // 시작
			}
		}


		cout << "#" << test_case << " " << answer << '\n';
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
