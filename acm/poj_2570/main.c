/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年10月24日 星期六 10时42分13秒 CST  
 *
 * 1. 使用floyd算法求两点之间存在哪些可用的公司。
 * 2. 通过在路径上使用与运算来求解
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN (256)
#define CHR2BIT(chr)	(1<<((chr)-'a'))

int map[MAXN][MAXN];
int n_vetex;
int weight[MAXN][MAXN];

void init()
{
	int u, v, i, j, len;
	char str[MAXN];

	for (i = 1; i <= n_vetex; i++) {
		for (j = 1; j <= n_vetex; j++) {
			map[i][j] = 0;
		}
	}

	while(1){
		scanf("%d %d", &u, &v);
		if (u == 0)
			break;

		scanf("%s", str);
		len = strlen(str);
		for (i = 0; i < len; i++) {
			map[u][v] |= CHR2BIT(str[i]);
		}
	}
}

void floyd()
{
	int i,j,n;

	for (i = 1; i <= n_vetex; i++) {
		for (j = 1; j <= n_vetex; j++) {
			weight[i][j] = map[i][j];
		}
	}

	for (n = 1; n <= n_vetex; n++) {
		for (i = 1; i <= n_vetex; i++) {
			for (j = 1; j <= n_vetex; j++) {
				//if (i == n || j == n)
				//	continue;
				weight[i][j] |= weight[i][n] & weight[n][j];
			}
		}
	}
}

void query()
{
	int i;
	int u,v;

	while(1) {
		scanf("%d %d", &u, &v);
		if (u == 0)
			break;
		if (weight[u][v] == 0) {
			printf("-\n");
		} else {
			for (i = 0; i < 26; i++) {
				if (weight[u][v] & (1<<i)) {
					printf("%c", 'a'+i);
				}
			}
			printf("\n");
		}
	}
	printf ("\n");
}

int main(int argc, char *argv[])
{
	while(1){
		scanf("%d", &n_vetex);
		if (n_vetex == 0)
			break;
		init();
		floyd();
		query();
		printf(" \n");
	}
	return 0;
}


