/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年 8月 2日 星期日 23时16分40秒 CST
 *
 * 1. code the code and do the dfs bruteforce
 */

#include <stdio.h>
#include <string.h>

#define N 16
#define GET_IDX(x) ((x)-'A')

char map[N][N] = {{0}};
char flag[N][N] = {{0}};
int steps[4][2] = {{0, -1}, {-1,0}, {0, 1}, {1,0}};
int table[11][4] = {
		{1, 1, 0, 0},
		{0, 1, 1, 0},
		{1, 0, 0, 1},
		{0, 0, 1, 1},
		{0, 1, 0, 1},
		{1, 0, 1, 0},
		{1, 1, 1, 0},
		{1, 1, 0, 1},
		{1, 0, 1, 1},
		{0, 1, 1, 1},
		{1, 1, 1, 1}
		};
int m_wid = 0;
int m_len = 0;

void dfs(int x, int y)
{
	int i = 0;
	int new_x, new_y;

	if (x < 0 || y < 0 ||
	    x >= m_wid || y >= m_len) 
		return;

	flag[x][y] = 1;
	for (i = 0; i < 4; i++) {
		if (table[GET_IDX(map[x][y])][i] == 0) 
			continue;

		new_x = x + steps[i][0];
		new_y = y + steps[i][1];
		if (new_x < 0 || new_y < 0 ||
			new_x >= m_wid || new_y >= m_len) 
			continue;

		if (flag[new_x][new_y] == 1)
			continue;

		if (table[GET_IDX(map[new_x][new_y])][(i+2)%4] == 0)
			continue;

		dfs(new_x, new_y);
	}
}

int main(int argc, char *argv[])
{
	int i, j;
	int count;

	while (1) {
		scanf("%d %d", &m_wid, &m_len);
		if (m_wid == 0 || m_len == 0)
			break;

		for (i = 0; i < m_wid; i++) {
			memset(flag[i], 0, sizeof(char)*N);
			scanf("%s", map[i]);
		}

		count = 0;
		for (i = 0; i < m_wid; i++) {
			for (j = 0; j < m_len; j++) {
				if (flag[i][j] == 0) {
					dfs(i, j);
					count ++;
				}
			}
		}
		printf ("%d\n", count);
	}

	return 0;
}

