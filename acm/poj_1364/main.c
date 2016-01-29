/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年10月28日 星期三 10时51分06秒 CST  
 *
 * 差分约束系统
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN (128)
#define MAXE (1024)
#define INF	(9999999)

typedef struct edge_st{
	int u,v;
	int weight;
}edge_st;

int n_edge;
edge_st edges[MAXE];
int n_vetex;
int dis[MAXN];

void add_edge(int u, int v, int weight)
{
	edge_st *pe;
	pe = &edges[n_edge++];
	pe->u = u;
	pe->v = v;
	pe->weight = weight;
}

int init()
{
	int i,n;
	int u,v,w;
	char str[32];

	scanf("%d", &n_vetex);
	if (n_vetex == 0)
		return 0;

	n_edge = 0;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%d %d", &u, &v);
		scanf("%s %d", str, &w);
		v+=u;
		if (!strcmp(str, "gt")) {
			add_edge(v, u-1, (w*-1-1));
		} else {
			add_edge(u-1, v, w-1);
		}
	}

	return 1;
}

int bellman_ford(int begin)
{
	int i, j;
	edge_st *pe;

	for (i = 0; i < n_vetex; i++) {
		dis[i] = INF;
	}

	dis[begin] = 0;
	for (i = 0; i < n_vetex - 1; i++) {
		for (j = 0;j < n_edge; j++) {
			pe = &edges[j];
			if (dis[pe->u] == INF)
				continue;
			if (dis[pe->u] + pe->weight < dis[pe->v]) {
				dis[pe->v] = dis[pe->u] + pe->weight;
			}
		}
	}

	for (i = 0; i < n_edge; i++) {
		pe = &edges[i];
		if (dis[pe->u] == INF)
			continue;
		if (dis[pe->u]+pe->weight < dis[pe->v])
			return -1;
	}

	return 0;
}

int main(int argc, char* argv[])
{
	while(init()) {
		if (bellman_ford(0)) {
			printf("successful conspiracy\n");
		} else {
			printf("lamentable kingdom\n");
		}
	}

	return 0;
}


