/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年11月20日 星期五 16时21分47秒 CST  
 *
 * 1. 最大网络流的问题
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN	(1024)
#define INF	(99999999)

#define MINV(a, b) ((a)<(b))?(a):(b);

typedef struct node_st{
	int f,c;
}node_st;

node_st map[MAXN][MAXN];
int n_vetex;

int init()
{
	int n_pig, i, j, keys, circle;
	int pigs[MAXN], last[MAXN];

	scanf("%d %d", &n_pig, &n_vetex);
	n_vetex += 2; // add source and dest node.

	for (i = 0; i < n_vetex; i++) {
		for (j = 0; j < n_vetex; j++) {
			map[i][j].f = 0;
			map[i][j].c = 0;
		}
	}

	for (i = 1; i <= n_pig; i++) {
		scanf("%d", &pigs[i]);
	}
	
	memset(last, 0, sizeof(last));
	for (i = 1; i <= n_vetex - 2; i++) {
		scanf("%d", &keys);
		for (j = 0; j < keys; j++) {
			scanf("%d", &circle);
			if (last[circle] == 0) {
				map[0][i].c += pigs[circle];
			} else {
				map[last[circle]][i].c = INF;
			}
			last[circle] = i;
		}
		scanf("%d", &map[i][n_vetex - 1].c);
	}

	return 1;
}

void ford()
{
	int prev[MAXN];
	int minflow[MAXN];
	int queue[MAXN];
	int qh,qt;
	int i,j, tmp;

	while(1) {
		for (i = 0; i < n_vetex; i++) {
			prev[i] = -1;
		}
		prev[0] = -2;
		minflow[0] = INF;

		qh = qt = 0;
		queue[qh++] = 0;
		while(qt < qh && prev[n_vetex-1] == -1) {
			tmp = queue[qt++];
			for (i = 0; i < n_vetex; i++) {
				if (prev[i] != -1)
					continue;

				if (map[tmp][i].f < map[tmp][i].c) {
					prev[i] = tmp;
					minflow[i] = MINV(minflow[tmp],
						map[tmp][i].c - map[tmp][i].f);
					queue[qh++] = i;
				}
			}
		}

		if (prev[n_vetex-1] == -1 || 
		    minflow[n_vetex - 1] == 0)
			break;

		for (i = prev[n_vetex-1], j = n_vetex-1; i!= -2; j = i, i = prev[i]) {
			map[i][j].f = map[i][j].f + minflow[n_vetex-1];
			map[j][i].f = - map[i][j].f;
		}
	}

	for (i = 0, tmp = 0; i < n_vetex-1; i++) 
		tmp += map[i][n_vetex-1].f;
	printf("%d\n", tmp);
}

int main(int argc, char* argv[])
{
	while(init()) {
		ford();
	}

	return 0;
}


