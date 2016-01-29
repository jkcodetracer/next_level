/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年10月12日 星期一 12时04分49秒 CST  
 *
 * 1. use the prime alg to find MST
 * 2. sort the MST edges in descend order, get the n-st edges.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXN (512)
#define INF (99999999)

typedef struct node_st{
	int x,y;
}node_st;

int n_vetex;
int satlites;
node_st nodes[MAXN];
float map[MAXN][MAXN];
float lowcost[MAXN];
float selected[MAXN];

float distance(int a, int b)
{
	int dx, dy;

	dx = nodes[a].x - nodes[b].x;
	dy = nodes[a].y - nodes[b].y;

	return sqrt(dx*dx + dy*dy);
}

void init()
{
	int i, j;
	node_st *pn;

	scanf("%d %d", &satlites, &n_vetex);
	for(i =0; i < n_vetex ;i++) {
		pn = &nodes[i];
		scanf("%d %d", &pn->x, &pn->y);
	}

	for(i = 0; i < n_vetex; i++) {
		for(j = i+1; j < n_vetex; j++) {
			map[i][j] = distance(i,j);
			map[j][i] = map[i][j];
		}
		map[i][i] = 0.0;
	}
}

int cmp(const void *a, const void *b)
{
	float *pa = (float *)a;
	float *pb = (float *)b;

	if (*pa > *pb) {
		return -1;
	} else {
		return 1;
	}
}

void prime(int source)
{
	int i,j;
	int n_sel = 0;
	int min_idx;
	float min_weight;

	for (i = 0; i < n_vetex; i++) {
		lowcost[i] = map[source][i];
	}

	lowcost[source] = -1;
	for (i = 0; i < n_vetex-1; i++) {
		min_idx = -1;
		min_weight = INF;

		for (j = 0; j < n_vetex; j++) {
			if (lowcost[j] != -1 && lowcost[j] < min_weight) {
				min_idx = j;
				min_weight = lowcost[j];
			}
		}

		if (min_idx == -1) {
			printf("no result\n");
			return ;
		}

		selected[n_sel++] = min_weight;
		lowcost[min_idx] = -1;
		for (j = 0; j < n_vetex;j++) {
			if (lowcost[j] != -1 && map[min_idx][j] < lowcost[j]) {
				lowcost[j] = map[min_idx][j];
			}
		}
	}

	qsort(selected, n_sel, sizeof(selected[0]), cmp);
	printf("%.2f\n", selected[satlites-1]);
}

int main(int argc, char* argv[])
{
	int total;

	scanf("%d", &total);
	while(total--) {
		init();
		prime(0);
	}

	return 0;
}




