/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年 9月18日 星期五 23时01分42秒 CST 
 *
 * 1. top sort 
 */
#include <stdio.h>
#include <string.h>

#define MAXN	(256)

int count[MAXN] = {0};
int node_num = 0;
char rel_table[MAXN][MAXN];
char ans[MAXN] = {0}; 

void top_sort(int max)
{
	int i, j;
	int cur = 0;

	for (i = 0; i < max; i++) {
		for(cur = 1; cur <= max; cur++) {
			if (count[cur] == 0) {
				break;
			}
		}

		if (cur > max) {
			printf("-1\n");
			return;
		}

		ans[i] = cur - 1 + '1';
		for (j = 1; j < max; j++) {
			if (rel_table[cur][j] && j != cur) {
				count[j]--;
			}
		}
		count[cur] = -1;
	}

	ans[i] = '\0';
	printf ("%s\n", ans);
}

int main(int argc, char *argv[])
{
	int total;
	int i;
	int n, m;
	int from, to;

	scanf("%d", &total);
	while(total--) {
		for (i = 0; i < MAXN; i++) {
			memset(rel_table[i], 0, MAXN);
		}
		node_num = 0;
		memset(count, -1, MAXN * sizeof(int));
		memset(ans, 0, MAXN);
		scanf("%d %d", &n, &m);
		for (i = 1; i <=n; i++) {
			count[i] = 0;
		}

		for (i = 0; i < m; i++) {
			scanf("%d %d", &from, &to);
			rel_table[from][to] = 1;

			if (count[to] == -1) {
				count[to] = 0;
			}
			count[to]++;
		}

		top_sort(n);
	}

	return 0;
}


