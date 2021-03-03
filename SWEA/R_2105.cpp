#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>

using namespace std;

int N;
int answer = -1;
int map[21][21];
int road[21][21];
int check[101];
int s_x, s_y;

int dx[] = { 1,1,-1,-1 };
int dy[] = { 1,-1,-1,1 };


void dfs(int x, int y, int dir, int cnt) {
	if (x == s_x && y == s_y && cnt > 1) {
		if (cnt > answer) answer = cnt;
		return;
	}
		for (int i = 0; i < 2; i++) {
			int rx = x + dx[dir + i];
			int ry = y + dy[dir + i];
			if (rx >=0 && rx <N && ry >=0 && ry < N && check[map[rx][ry]] == 0 && road[rx][ry] == 0) {
				check[map[rx][ry]] = 1;
				road[rx][ry] = 1;
				dfs(rx, ry, dir+i, cnt+1); // 시작
				check[map[rx][ry]] = 0;
				road[rx][ry] = 0;
			}
			else if (rx == s_x && ry == s_y) {
				dfs(rx, ry, dir + i, cnt + 1);
			}
		}
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
		memset(check, 0, sizeof(check));
		memset(road, 0, sizeof(road));
		cin >> N;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> map[i][j];
			}
		}

		for (int i = 0; i < N-1; i++) {
			for (int j = 1; j < N-1; j++) {
				s_x = i;
				s_y = j;
				check[map[i][j]] = 1;
				road[i][j] = 1;
				dfs(i, j, 0, 0); // 시작
				memset(check, 0, sizeof(check));
				memset(road, 0, sizeof(road));
			}
		}


		cout << "#" << test_case << " " << answer << '\n';
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
