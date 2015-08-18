/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年 8月 6日 星期四 08时32分34秒 CST
 *
 * 1. dfs bruteforce
 */
#include <stdio.h>
#include <string.h>

#define N 32

char map[N][N] = {{0}};
int m_wid = 0;
int m_len = 0;

int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

int dfs(int x, int y, int *step)
{
	int i= 0;
	int new_x, new_y ;

	if(x <= 0 || x > m_wid ||
	   y <= 0 || y > m_len)
		return *step;
	(*step)++;

	for (i = 0; i < 4; i++) {
		new_x = x + dir[i][0];
		new_y = y + dir[i][1];
		if (map[new_x][new_y] == '.') {
			map[new_x][new_y] = '#';
			dfs(new_x, new_y, step);
		}
	}

	return *step;
}

int main(int argc, char *argv[])
{
	int i, j;
	int s_x, s_y = 0;
	int count = 0;
	char str[32] = {0};

	for (i = 0; i < N; i++){
		for (j = 0; j < N; j++){
			map[i][j] = '#';
		}
	}

	while (1) {
		scanf("%d %d", &m_len, &m_wid);
		if (m_wid == 0 || m_len == 0)
			break;

		for (i = 1; i <= m_wid; i++) {
			scanf("%s", str);
			for (j = 1; j <= m_len; j++) {
				map[i][j] = str[j-1];
				if(map[i][j] == '@') {
					s_x = i;
					s_y = j;
				}
			}
		}

		for (i = 0; i <= m_wid;i++) {
			for (j = 0;j <= m_len; j++)
				printf ("%c",map[i][j]);
			printf ("\n");
		}


		count = 0;
		dfs(s_x, s_y, &count);
		printf("%d\n", count);
	}

	return 0;
}
