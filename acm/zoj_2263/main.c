/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年10月25日 星期日 10时06分15秒 CST  
 *
 * 1. 找到每条路径上最窄的那个通路
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN	(256)
#define MAXM	(32)
#define INF	(999999)

typedef struct name_st{
	char name[MAXM];
}name_st;

int n_vetex;
int n_name;
name_st names[MAXN];
int n_edges;
int map[MAXN][MAXN];
int weight[MAXN][MAXN];
int begin, end;

int mindex(char *name)
{
	int i, idx;

	for (i = 0; i < n_name; i++) {
		if (!strcmp(name, names[i].name)) {
			return i;
		}
	}
	idx = n_name++;
	strcpy(names[idx].name, name);

	return idx;
}

int init()
{
	int i,j;
	char n1[MAXM],n2[MAXM];
	int u,v,w;

	scanf("%d %d", &n_vetex, &n_edges);
	if (n_vetex == 0)
		return 0;

	n_name = 0;
	for (i = 0; i < n_vetex; i++) {
		for (j = 0; j < n_vetex; j++) {
			map[i][j] = INF;
		}
	}

	for (i = 0; i < n_edges; i++) {
		scanf("%s %s %d", n1, n2, &w);
		u = mindex(n1);
		v = mindex(n2);

		map[u][v] = w;
		map[v][u] = w;
	}

	scanf("%s %s", n1, n2);
	begin = mindex(n1);
	end = mindex(n2);

	return 1;
}

void floyd()
{
	int i, j, n;
	int min;

	for (i = 0; i < n_vetex; i++) {
		for (j = 0; j < n_vetex; j++) {
			weight[i][j] = map[i][j];
		}
	}

	for (n = 0; n < n_vetex; n++) {
		for (i = 0; i < n_vetex; i++) {
			for (j = 0; j < n_vetex; j++) {
				if (weight[i][n] == INF || weight[n][j] == INF)
					continue;

				if (weight[i][n] < weight[n][j]) {
					min = weight[i][n];
				} else {
					min = weight[n][j];
				}

				if (weight[i][j] < min) {
					weight[i][j] = min;
				}

				if (weight[i][j] == INF) {
					weight[i][j] = min;
				}
			}
		}
	}
}

int main(int argc, char* argv[])
{
	int k = 0;

	while(init()){
		k++;
		floyd();
		printf("Scenario #%d\n",k);
		printf("%d tons\n\n", weight[begin][end]);
	}

	return 0;
}

