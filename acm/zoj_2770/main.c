/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年10月27日 星期二 16时43分09秒 CST  
 *
 * 差分约束系统。 利用bellman_ford算法求最优解
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN (1024)
#define MAXE (102400)
#define INF (999999)

typedef struct edge_st{
	int u,v,weight;
}edge_st;

int n_edge;
edge_st edges[MAXE];
int n_vetex;
int cap[MAXN];
int consum[MAXN];
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
	int i;
	int m;
	int u,v,weight;

	n_edge = 0;
	cap[0] = 0;
	consum[0] = 0;
	scanf("%d %d", &n_vetex, &m);
	for(i = 1; i <= n_vetex; i++) {
		scanf("%d", &cap[i]);
		add_edge(i-1, i, cap[i]);
		add_edge(i, i-1, 0);
		consum[i] = consum[i-1] + cap[i];
	}

	for (i = 1; i <= m; i++) {
		scanf("%d %d %d", &u, &v, &weight);
		add_edge(v, u-1, -weight);
		add_edge(u-1, v, consum[v]-consum[u-1]);
	}

	return 1;
}

int bellman_ford(int begin)
{
	int i,k;
	int len;
	edge_st *pe;

	for (i = 0; i < n_vetex; i++) {
		dis[i] = INF;
	}

	dis[begin] = 0;
	for (i = 0; i < n_vetex; i++) {
		for (k = 0; k < n_edge; k++) {
			pe = &edges[k];
			if (dis[pe->u] == INF)
				continue;
			len = dis[pe->u] + pe->weight;
			if (len < dis[pe->v]) {
				dis[pe->v] = len;
			}
		}
	}

	//check the circle
	for (i = 0; i < n_edge; i++) {
		pe = &edges[i];
		if (dis[pe->u] == INF)
			continue;

		if (dis[pe->u] + pe->weight < dis[pe->v])
			return -1;
	}

	return 0;
}

int main(int argc, char* argv[])
{
	while(init()) {
		if (bellman_ford(n_vetex)) {
			printf("Bad Estimations\n");
		} else {
			printf("%d\n", dis[n_vetex] - dis[0]);
		}
	}

	return 0;
}





