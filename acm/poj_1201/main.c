/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年10月27日 星期二 23时47分27秒 CST  
 *
 * 差分约束系统
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN	(50012)
#define INF	(999999)

typedef struct edge_st{
	int u,v,weight;
}edge_st;

int dis[MAXN];
edge_st edges[MAXN];
int n_edge;
int min, max;

void add_edge(int u, int v, int w)
{
	edge_st *pe;

	pe = &edges[n_edge++];
	pe->u = u;
	pe->v = v;
	pe->weight = w;
}

void init()
{
	int i,n;
	int u,v,w;

	n_edge = 0;
	min = INF;
	max = 1;
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d %d %d", &u, &v, &w);
		if (u < min) {
			min = u;
		}

		if (v > max) {
			max = v;
		}
		add_edge(v, u-1, -w);
	}
}

void bellman_ford(int begin)
{
	int i;
	int instable = 1;
	edge_st *pe;

	for (i = 0; i <= max; i++) {
		dis[i] = INF;
	}

	dis[begin] = 0;
	while(instable) {
		instable = 0;
		for (i = 0; i < n_edge; i++) {
			pe = &edges[i];
			if(dis[pe->u] == INF)
				continue;
			if (dis[pe->u] + pe->weight < dis[pe->v]) {
				dis[pe->v] = dis[pe->u] + pe->weight;
				instable = 1;
			}
		}

		for (i = min; i <= max; i++) {
			if (dis[i-1] + 1 < dis[i]) {
				dis[i] = dis[i-1] + 1;
				instable = 1;
			}
		}

		for (i = max; i >= min; i--) {
			if (dis[i-1]>dis[i]) {
				dis[i-1] = dis[i];
				instable = 1;
			}
		}
	}
}

int main(int argc, char* argv[])
{
	init();
	bellman_ford(max);
	printf("%d\n", dis[max]-dis[min-1]);

	return 0;
}

