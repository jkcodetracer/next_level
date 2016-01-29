/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年10月29日 星期四 20时09分47秒 CST  
 *
 * 找到最短路径， 使用最短路径算法时，额外保留当前路径上最高权值
 * 的边，用于费用减免
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN	(1024)
#define INF	(99999)

int n_vetex;
int map[MAXN][MAXN];
int max_e[MAXN][MAXN];
int begin;
int end;
char str[MAXN][32];

int find_idx(char *p)
{
	int i;

	for (i = 0; i < n_vetex; i++) {
		if (!strcmp(str[i], p)) {
			return i;
		}
	}

	strcpy(str[i], p);
	n_vetex++;

	return i;
}

void init()
{
	int i, j, total;
	char str1[32], str2[32];
	int idx_f, idx_t, w;

	for (i = 0; i < MAXN; i++) {
		for (j = 0; j < MAXN; j++) {
			map[i][j] = INF;
			max_e[i][j] = 0;
		}
	}

	n_vetex = 0;
	scanf("%s %s", str1, str2);
	begin = find_idx(str1);
	end = find_idx(str2);

	scanf("%d", &total);
	for (i = 0; i < total; i++) {
		scanf("%s %s %d", str1, str2, &w);
		idx_f = find_idx(str1);
		idx_t = find_idx(str2);
		map[idx_f][idx_t] = w;
		max_e[idx_f][idx_t] = w;
	}
}

void floyd()
{
	int i,j,n;
	int max;

	for (n = 0; n < n_vetex; n++) {
		for (i = 0; i < n_vetex; i++) {
			for (j = 0; j < n_vetex; j++) {
				if (i == n || j == n)
					continue;

				if (max_e[i][n] < max_e[n][j]) {
					max = max_e[n][j];
				} else {
					max = max_e[i][n];
				}

				if (map[i][n] + map[n][j] - max < map[i][j] - max_e[i][j]) {
					map[i][j] = map[i][n] + map[n][j];
					if (max > max_e[i][j]) {
						max_e[i][j] = max;
					}
				}
			}
		}
	}
}

int main(int argc, char* argv[])
{
	init();
	floyd();
	printf("%d", map[begin][end] - max_e[begin][end]);

	return 0;
}

