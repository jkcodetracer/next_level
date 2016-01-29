/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年10月15日 星期四 08时41分33秒 CST  
 *
 * 1. find shortest path with dijkstra alg
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN	(32)
#define INF	(9999999)

typedef struct min_st{
	int min_dis;
	int src_idx;
	int path[MAXN];
}min_st;

int map[MAXN][MAXN];
int n_vetex;
int min_dis[MAXN];
min_st dis[MAXN];
int path[MAXN];
int used[MAXN];
int target;
int n_source = 0;
int source[MAXN];

int getint()
{
	int result = 0;
	char chr = 0;

	chr = getchar_unlocked();
	while(chr < '0' || chr > '9') {
		chr = getchar_unlocked();
	}

	while(chr >= '0' && chr <= '9') {
		result = (result << 3) + (result << 1) + chr - '0';
		chr = getchar_unlocked();
	}

	return result;
}

void init()
{
	int i, j;
	int dst;

	scanf("%d", &n_vetex);
	for(i = 1; i <= n_vetex; i++) {
		for(j = 1; j <= n_vetex; j++) {
			scanf("%d", &map[i][j]);
		}
	}

	memset(source, 0, sizeof(source[0])*MAXN);
	target = getint();
	while(1) {
		dst = getint();
		if (dst == 0)
			break;
		n_source++;
		source[dst] = 1;
	}
}

int cmp(const void *a, const void *b)
{
	min_st *pa = (min_st*)a;
	min_st *pb = (min_st*)b;

	return pa->min_dis - pb->min_dis;
}

void dijkstra(int s)
{
	int i, j;
	int min_idx, min_len;

	for (i = 1; i <= n_vetex; i++) {
		used[i] = 0;
		if (map[s][i] >= 0) {
			min_dis[i] = map[s][i];
			path[i] = s;
		} else {
			min_dis[i] = INF;
			path[i] = -1;
		}
	}

	used[s] = 1;
	min_dis[s] = 0;
	for (i = 1; i < n_vetex; i++) {
		min_idx = -1;
		min_len = INF;
		for (j = 1; j <= n_vetex; j++) {
			if (!used[j] && min_dis[j] < min_len) {
				min_idx = j;
				min_len = min_dis[j];
			}
		}

		if (min_idx == -1) {
			printf("no result\n");
			return ;
		}

		used[min_idx] = 1;
		for (j = 1; j <= n_vetex; j++) {
			if (!used[j] && map[min_idx][j]!=-1 &&
			map[min_idx][j]+min_len < min_dis[j]) {
				min_dis[j] = map[min_idx][j] + min_len;
				path[j] = min_idx;
			}
		}
	}
}

void dump(int idx, int src, int *pt)
{
	if (idx != src) {
		dump(pt[idx], src, pt);
	}
	if (idx == src) {
		printf("%d\t", idx);
	} else {
		printf("%d\t", idx);
	}
}



int main(int argc, char* argv[])
{
	int cases;
	int i,j;

	scanf("%d", &cases);
	while(cases--) {
		init();
		j = 0;
		for (i=1; i <= n_vetex; i++) {
			if (!source[i])
				continue;

			j++;
			if (i == target) {
				dis[j].min_dis = 0;
				dis[j].src_idx = i;
				continue;
			}
			dijkstra(i);
			dis[j].min_dis = min_dis[target];
			dis[j].src_idx = i;
			memcpy(dis[j].path, path, MAXN*sizeof(int));
		}

		qsort(dis+1, n_source, sizeof(dis[0]), cmp);

		for (i = 1; i <= n_source; i++){
			printf("%d\t%d\t%d\t", dis[i].src_idx, 
				target, dis[i].min_dis);

			dump(target, dis[i].src_idx, dis[i].path);
			printf("\n");
		}
	}
	return 0;
}



