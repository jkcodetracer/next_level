/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年 8月 2日 星期日 10时26分06秒 CST
 *
 * 1. the dfs ...
 */

#include <stdio.h>
#include <stdlib.h>


#define N 16

int m_len = 0;
int m_wid = 0;
char map[N][N] = {{0}};

int pos_step[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

int s_x = 0;
int s_y = 0;
int t_x = 0;
int t_y = 0;
int step = 0;
int finish = 0;

int dfs(int x, int y, int c_step)
{
	int i, new_x, new_y;

	if ( x <= 0 || y <= 0 ||
	     x > m_wid || y > m_len ||
	     c_step > step)
		return 0;

	if (x == t_x && y == t_y && c_step == step) {
		finish = 1;
		return 1;
	}

	for (i = 0; i < 4; i++) {
		new_x = x + pos_step[i][0];
		new_y = y + pos_step[i][1];
		if (map[new_x][new_y] != 'X') {
			map[new_x][new_y] = 'X';
			dfs(new_x, new_y, c_step+1);
			if (finish)
				return 1;
			map[new_x][new_y] = '.';
		}
	}

	return 0;
}

int get_int()
{
	int n = 0;
	char c = 0;

	while (c < 33)
		c = getchar_unlocked();

	while (c <= '9' && c >= '0') {
		n = (n << 3) + (n << 1) + c - '0';
		c = getchar_unlocked();
	}

	return n;
}


int main (int argc, char * argv[])
{
	int i, j, orig_wall;
	char tmp;

	for (i = 0; i < N;i++) {
		for (j = 0; j < N; j++) {
			map[i][j] = 'X';
		}
	}

	while (1) {
		orig_wall = 0;
		m_wid = get_int();
		m_len = get_int();
		step = get_int();

		if (m_wid == 0 || m_len == 0 || step == 0)
			break;

		for (i = 1; i <= m_wid; i++) {
			for (j = 1; j <= m_len; j++) {
				scanf("%c", &map[i][j]);
				if (map[i][j] == 'S') {
					s_x = i;
					s_y = j;
				} else if (map[i][j] == 'X') {
					orig_wall ++;
				} else if (map[i][j] == 'D') {
					t_x = i;
					t_y = j;
				}
			}

			scanf("%c", &tmp);
		}

		if (m_len * m_wid < step + orig_wall) {
			printf ("NO\n");
		}

		map[s_x][s_y] = 'X';
		finish = 0;
		dfs(s_x, s_y, 0);
		if (finish)
			printf ("YES\n");
		else
			printf ("NO\n");
	}

	return 0;
}

