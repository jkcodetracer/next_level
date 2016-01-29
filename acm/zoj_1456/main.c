/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年10月22日 星期四 18时01分58秒 CST  
 *
 * 1. find the shortest path, should consider the node's costs.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN	(128)
#define INF	(999999)

int map[MAXN][MAXN];
int n_vetex;
int costs[MAXN];
int weight[MAXN];
int path[MAXN];

void init()
{
	int i,j;

	scanf("%d", &n_vetex);
	for(i = 0; i < n_vetex; i++){
		for (j = 0; j < n_vetex; j++) {
			scanf("%d", &map[i][j]);
		}
	}

	for (i = 0; i < n_vetex; i++) {
		scanf("%d", &costs[i]);
	}
}

void bellman_ford(int begin)
{
	int i, j, n;

	for (i = 0; i < n_vetex; i++) {
		weight[i] = INF;
		path[i] = -1;
	}

	weight[begin] = 0;
	for (n = 0; n < n_vetex -1;n++) {
		for (i = 0; i < n_vetex; i++) {
			for (j = 0; j < n_vetex; j++) {
				if (map[i][j] == -1)
					continue;
				if (weight[i]+map[i][j]+costs[j] < weight[j]) {
					weight[j] = weight[i]+map[i][j]+costs[j];
					path[j] = i;
				}
			}
		}
	}
}

void recap(int end, int idx)
{
	if (path[idx] != -1) {
		recap(end, path[idx]);
	}

	if (end == idx) {
		printf("%d", idx+1);
	} else {
		printf("%d-->", idx+1);
	}
}

void dump(int begin, int end)
{
	printf("From %d to %d:\n", begin, end);
	printf("Path:");
	recap(end-1, end-1);
	printf("\nTotal cost:%d\n", weight[end-1]-costs[end-1]);
}

int main(int argc, char* argv[])
{
	int begin, end;

	init();
	while(1) {
		scanf("%d %d", &begin, &end);
		if (begin == -1)
			break;
		bellman_ford(begin-1);
		dump(begin, end);
	}

	return 0;
}




