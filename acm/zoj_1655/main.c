/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年10月17日 星期六 17时16分58秒 CST  
 *
 * find the shortest transform rate to N
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF	(9999999)
#define MAXN	(128)

float map[MAXN][MAXN];
int n_vetex;
float weight[MAXN];
float min_dis[MAXN];
int used[MAXN];

void init()
{
	int i,j;
	int edges, from, to;
	float rate;

	scanf("%d %d", &n_vetex, &edges);
	for(i=1; i <= n_vetex-1; i++) {
		scanf("%f", &weight[i]);
	}

	for (i = 1; i <= n_vetex; i++) {
		for (j = i; j <= n_vetex; j++) {
			map[i][j] = INF;
			map[j][i] = INF;
		}
	}

	for(i = 0; i < edges; i++) {
		scanf("%d %d %f", &from, &to, &rate);
		map[from][to] = rate;
		map[to][from] = rate;
	}
}

void dijkstra(int s)
{
	int i,j;
	int min_idx;
	float min_weight;

	for (i = 1; i <= n_vetex; i++) {
		min_dis[i] = map[s][i];
		used[i] = 0;
	}
	
	used[s] = 1;
	min_dis[s] = -1;
	for (i = 1; i < n_vetex; i++) {
		min_idx = -1;
		min_weight = INF;
		for (j = 1; j <= n_vetex; j++) {
			if (!used[j] && min_dis[j] < min_weight) {
				min_weight = min_dis[j];
				min_idx = j;
			}
		}

		if (min_idx == -1) {
			printf("no result\n");
			return ;
		}

		used[min_idx] = 1;
		for (j = 1; j <= n_vetex; j++) {
			if (!used[j] && map[min_idx][j] < INF &&
			    map[min_idx][j] + min_weight < min_dis[j]) {
				min_dis[j] = map[min_idx][j] + min_weight;
			}
		}
	}
}

int main(int argc, char* argv[])
{
	int i;
	float total = 0;

	init();
	for(i = 1; i < n_vetex; i++) {
		dijkstra(i);
		total += weight[i] - weight[i]*min_dis[n_vetex];
	}
	printf("%.2f\n", total);

	return 0;
}



