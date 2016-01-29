/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年10月 7日 星期三 11时27分21秒 CST 
 *
 * use the prime alg to find the lowest weight
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN	(1024)
#define INF	(1000000)

int map[MAXN][MAXN];
int lowcost[MAXN] = {0};
int adapter[MAXN] = {0};
int n_vetex = 0;

void init()
{
	int i,j;

	scanf("%d", &n_vetex);
	for(i = 0; i < n_vetex; i++) {
		scanf("%d", &adapter[i]);
	}

	for(i = 0; i < n_vetex; i++) {
		for(j = 0; j < n_vetex; j++) {
			scanf("%d", &map[i][j]);
			if(i == j) {
				map[i][j] = INF;
			}
			map[i][j] += adapter[i]+adapter[j];
		}
	}

	memset(lowcost, 0, sizeof(lowcost[0])*MAXN);
}

void prime(int begin)
{
	int i, j;
	int min_v, min_w;
	int weight = 0;

	for(i = 0; i < n_vetex; i++) {
		lowcost[i] = map[begin][i];
	}
	lowcost[begin] = -1;

	for(i = 0; i < n_vetex-1; i++) {
		min_v = -1;
		min_w = 2*INF;
		for(j = 0; j < n_vetex; j++) {
			if (lowcost[j] != -1 && lowcost[j] < min_w) {
				min_w = lowcost[j];
				min_v = j;
			}
		}

		if (min_v == -1) {
			printf("no result!\n");
			return ;
		}

		weight += lowcost[min_v];
		lowcost[min_v] = -1;
		for (j = 0; j < n_vetex; j++) {
			if (lowcost[j] != -1 && map[min_v][j] < lowcost[j]) {
				lowcost[j] = map[min_v][j];
			}
		}
	}
	printf("%d\n", weight);
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


