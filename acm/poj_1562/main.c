/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年 8月 2日 星期日 20时54分58秒 CST
 *
 * broutforce ... go on
 */

#include <stdio.h>

#define N 16

char map[N][N] = {{0}};
int m_wid = 0;
int m_len = 0;

int steps[8][2] = {{0,-1}, {0,1}, {-1, 0}, {-1, 1},
		   {-1, -1}, {1, 1}, {1, -1}, {1, 0}};

void dfs(int x, int y)
{
	int i = 0, new_x, new_y;

	if (x <= 0 || y <= 0 ||
	    x > m_wid || y > m_len)
		return;

	map[x][y] = '*';
	for (i = 0; i < 8; i++) {
		new_x = x + steps[i][0];
		new_y = y + steps[i][1];
		if (map[new_x][new_y] == '@') {
			dfs(new_x, new_y);
		}
	}
}

int main (int argc, char *argv[])
{
	int i = 0, j = 0;
	int count;
	char str[16];

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			map[i][j] = '*';
		}
	}

	while (1) {
		scanf("%d %d", &m_wid, &m_len);
		if (m_wid == 0 || m_len == 0)
			break;

		for(i = 1; i <= m_wid; i++){
			scanf("%s", str);
			for (j = 1; j <= m_len; j++) {
				map[i][j] = str[j-1];
			}
		}

		for(i = 1; i <= m_wid; i++){
			for (j = 1; j <= m_len; j++) {
				printf("%c", map[i][j]);
			}
			printf ("\n");
		}


		count = 0;
		for (i = 1; i <= m_wid; i++) {
			for (j = 1; j <= m_len; j++) {
				if (map[i][j] == '@') {
					dfs(i, j);
					count++;
				}
			}
		}

		printf ("%d\n", count);
	}

	return 0;
}

