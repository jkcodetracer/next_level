/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年11月21日 星期六 12时46分53秒 CST  
 *
 * 1. net flow 
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN (1024)
#define INF (99999)

#define MINV(a,b) ((a)<(b))?(a):(b)

typedef struct node_st{
	int f,c;
}node_st;

node_st map[MAXN][MAXN];
int n_vetex;
int n_edges;
int minflow[MAXN];
int flag[MAXN];
int prev[MAXN];

void init()
{
	int i,j;
	int u,v,c;

	scanf("%d %d", &n_edges, &n_vetex);
	for (i = 1; i <= n_vetex; i++) {
		for (j = 1; j <= n_vetex; j++) {
			map[i][j].f = 0;
			map[i][j].c = INF;
		}
	}

	for (i = 0; i < n_edges; i++) {
		scanf("%d %d %d", &u, &v, &c);
		map[u][v].c = c;
	}
}

void ford()
{
	int i, cur;
	int qh,qt;
	int queue[MAXN];

	while(1) {
		qh = qt = 0;
		queue[qh++] = 1;
		memset(flag, 0, sizeof(flag));
		flag[1] = -1;
		memset(prev, 0, sizeof(prev));
		prev[1] = -1;
		memset(minflow, 0, sizeof(minflow));
		minflow[1] = INF;

		while(qh > qt && minflow[n_vetex] == 0) {
			cur = queue[qt++];
			for (i = 1; i <= n_vetex; i++) {
				if (flag[i] != 0)
					continue;

				if (map[cur][i].c < INF && 
				    map[cur][i].f < map[cur][i].c) {
					flag[i] = -1;
					minflow[i] = MINV(minflow[cur], map[cur][i].c - map[cur][i].f);
					prev[i] = cur;
					queue[qh++] = i;
				} else if (map[i][cur].c < INF &&
				    map[i][cur].f > 0){
					flag[i] = -1;
					minflow[i] = MINV(minflow[cur], map[i][cur].f);
					prev[i] = cur;
					queue[qh++] = i;
				}
			}
			flag[cur] = 1;
		}

		if (minflow[n_vetex] == 0 ||
		    prev[n_vetex] == 0)
			break;

		int next;
		cur = n_vetex;
		next = prev[n_vetex];
		while(1) {
			if (map[next][cur].c < INF) {
				map[next][cur].f += minflow[n_vetex];
			} else if (map[cur][next].c < INF) {
				map[cur][next].f -= minflow[n_vetex];
			}

			cur = next;
			next = prev[cur];
			if (next == -1)
				break;
		}
	}

	cur = 0;
	for (i = 1; i < n_vetex; i++) {
		if (map[i][n_vetex].c < INF) {
			cur += map[i][n_vetex].f;
		}
	}

	printf("%d\n", cur);
}

int main(int argc, char *argv[])
{
	init();
	ford();

	return 0;
}

