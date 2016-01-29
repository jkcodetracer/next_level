/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年10月12日 星期一 10时47分17秒 CST  
 *
 * find the shortest path between two sentenses. use the dijkstra algorithm.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN (1024)
#define INF (9999999)

#define STR2INT(str) (((str)[0]<<24)|((str)[1]<<16)|((str)[2]<<8)|((str)[3]))

typedef struct vac_st{
	int head;
	int end;
	int time;
}vac_st;

int n_nodes;
vac_st nodes[MAXN];
int dis[MAXN][MAXN];
int used[MAXN];
int min_dis[MAXN];

void init()
{
	int i, j, len;
	char str[32];
	vac_st *pn;

	for (i = 0; i < n_nodes; i++) {
		pn = &nodes[i];
		scanf("%d %s", &pn->time, str);
		len = strlen(str);
		pn->head = STR2INT(str);
		pn->end = STR2INT((str+len-4));
	}

	for (i = 0;i < n_nodes; i++) {
		for (j = 0; j < n_nodes; j++) {
			dis[i][j] = INF;
			if (i == j) 
				continue;
			if (nodes[i].end == nodes[j].head) {
				dis[i][j] = nodes[i].time;
			}
		}
	}
}

void dijkstra(int source)
{
	int i,j;
	int min_idx, min_time;

	for (i = 0; i < n_nodes; i++) {
		min_dis[i] = dis[source][i];
		used[i] = 0;
	}

	used[source] = 1;
	min_dis[source] = -1;
	for (i = 0; i < n_nodes - 1; i++) {
		min_idx = -1;
		min_time = INF;
		for(j = 0; j < n_nodes; j++) {
			if (!used[j] && min_dis[j] < min_time) {
				min_idx = j;
				min_time = min_dis[j];
			}
		}

		if (min_idx == -1) {
			printf("-1\n");
			return ;
		}

		used[min_idx] = 1;
		for (j = 0; j < n_nodes;j++) {
			if (!used[j]&&dis[min_idx][j]<INF
			&& dis[min_idx][j]+min_time< min_dis[j]) {
				min_dis[j] = dis[min_idx][j] + min_time;
			}
		}
	}

	if (min_dis[n_nodes-1] == INF) {
		printf("-1\n");
	} else {
		printf("%d\n", min_dis[n_nodes-1]);
	}
}

int main(int argc, char* argv[])
{
	while(1) {
		scanf("%d",&n_nodes);
		if (n_nodes == 0) {
			break;
		}

		init();
		dijkstra(0);
	}

	return 0;
}


