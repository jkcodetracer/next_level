/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年10月11日 星期日 23时57分12秒 CST  
 *
 * 1. to find the max-min weight
 * 2. to find the max weight to every edge
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 512
#define INF 9999999

int map[MAXN][MAXN];
int used[MAXN];
int time[MAXN];
int n_edges, n_vetex;

void init()
{
	int i, j;
	int u, v, weight;

	for (i = 1; i <= n_vetex;i++) {
		for(j = 1; j <= n_vetex;j++) {
			map[i][j] = INF;
		}
	}

	for(i = 0; i < n_edges; i++) {
		scanf("%d %d %d", &u, &v, &weight);
		map[u][v] = weight;
	}

	memset(used, 0, sizeof(used[0])*MAXN);
}

void dijkstra(int begin)
{
	int i, j;
	int min_time, min_idx;

	for(i = 1; i <= n_vetex; i++) {
		time[i] = map[begin][i];
		used[i] = 0;
	}

	used[begin] = 1;
	time[begin] = 0;
	for(i = 1; i <= n_vetex-1; i++) {
		min_time = INF;
		min_idx = -1;

		for (j=1; j <= n_vetex; j++) {
			if (!used[j] && time[j] < min_time) {
				min_time = time[j];
				min_idx = j;
			}
		}

		if (min_idx == -1) {
			printf("no result\n");
			return;
		}
		
		used[min_idx] = 1;
		for (j = 1; j <= n_vetex; j++) {
			if (!used[j] && map[min_idx][j] < INF && 
			map[min_idx][j] + time[min_idx] < time[j]) {
				time[j] = map[min_idx][j]+time[min_idx];
			}
		}
	}
}

void solve()
{
	int i,j,u,v, u1;
	double max1, max2, weight;

	max1 = 0.0;
	for (i = 1; i <= n_vetex; i++) {
		if (time[i] > max1) {
			max1 = time[i];
			u1 = i;
		}
	}

	max2 = 0.0;
	for (i = 1; i <= n_vetex; i++) {
		for (j = 1; j <= n_vetex; j++) {
			if (map[i][j] >= INF) 
				continue;
			weight = (map[i][j]+time[i]+time[j])/2.0;
			if(weight > max2) {
				max2 = weight;
				u = i;
				v = j;
			}
		}
	}

	if (max1 >= max2) {
		printf("the last domino falls after %.1f seconds, at key %d.\n", 
			max1, u1);
	} else {
		printf("the last domino falls after %.1f seconds, at key %d and %d.\n",
			max2, u, v);
	}
}

int main(int argc, char* argv[])
{
	while(1) {
		scanf("%d %d", &n_vetex, &n_edges);
		if (n_vetex == 0)
			break;
		init();
		dijkstra(1);
		solve();
	}

	return 0;
}



