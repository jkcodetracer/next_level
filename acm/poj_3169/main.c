/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年11月 4日 星期三 23时43分00秒 CST 
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN	(2000024)
#define MAXM	(10024)
#define INF	(9999999)

typedef struct edge_st{
	int u,v,w;
}edge_st;

edge_st edges[MAXN];
int n_edge;
int n_vetex;
int cost[MAXM];

void add_edge(int u, int v, int w)
{
	edge_st *pe;

	pe = &edges[n_edge++];
	pe->u = u;
	pe->v = v;
	pe->w = w;
}

void init()
{
	int i;
	int ml, md;
	int u,v,w;

	scanf("%d %d %d", &n_vetex, &ml, &md);

	n_edge = 0;
	for (i = 0; i < ml; i++) {
		scanf("%d %d %d", &u, &v, &w);
		add_edge(u, v, w);
	}

	for (i = 0; i < md; i++) {
		scanf("%d %d %d", &u, &v, &w);
		add_edge(v, u, -w);
	}
}

int bellman_ford(int begin)
{
	int i,j;
	edge_st *pe;

	for (i = 1; i <= n_vetex; i++) {
		cost[i] = INF;
	}

	cost[begin] = 0;
	for (i = 0; i < n_vetex-1;i++) {
		for (j = 0; j < n_edge; j++) {
			pe = &edges[j];
			if(cost[pe->u] != INF && 
			cost[pe->u] + pe->w < cost[pe->v]) {
				cost[pe->v] = cost[pe->u] + pe->w;
			}
		}
	}

	for (i = 0; i < n_edge; i++) {
		pe = &edges[i];
		if (cost[pe->u] != INF &&
		cost[pe->u] + pe->w < cost[pe->v]) {
			return -1;
		}
	}

	if (cost[n_vetex] == INF) {
		return -2;
	} else {
		return cost[n_vetex];
	}
}

int main(int argc, char* argv[])
{
	init();
	printf("%d\n", bellman_ford(1));

	return 0;
}

