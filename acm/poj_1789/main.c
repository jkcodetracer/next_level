/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年10月10日 星期六 17时25分28秒 CST  
 *
 * find a MST by the prime alg
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXN (2048)
#define INF (999999)

int map[MAXN][MAXN];
char truck[MAXN][16];
int lowcost[MAXN] = {0};
int n_vetex;

int dis(int i, int j)
{
	int n;
	int sum = 0;

	for (n = 0; n < 7; n++) {
		sum += abs(truck[i][n]-truck[j][n]);
	}

	return sum;
}

void init(int n)
{
	int i, j;

	n_vetex = n;
	memset(lowcost, 0, sizeof(lowcost[0])*MAXN);

	for (i = 0; i < n_vetex; i++) {
		scanf("%s", truck[i]);
	}

	for (i = 0; i < n_vetex; i++) {
		map[i][i] = INF;
		for (j = i+1; j < n_vetex; j++) {
			map[i][j] = dis(i,j);
			map[j][i] = map[i][j];
		}
	}
}

int prime(int start)
{
	int i, j;
	int min_idx, min_weight, sum = 0;

	for(i = 0;i < n_vetex; i++) {
		lowcost[i] = map[start][i];
	}
	lowcost[start] = -1;

	for (i = 0; i < n_vetex -1; i++) {
		min_weight = INF;
		min_idx = -1;

		for (j = 0; j < n_vetex; j++) {
			if (lowcost[j]!= -1 && lowcost[j] < min_weight) {
				min_idx = j;
				min_weight = lowcost[j];
			}
		}

		if (min_idx == -1) {
			printf("no result\n");
			return -1;
		}

		sum += min_weight;
		lowcost[min_idx] = -1;
		for (j = 0; j < n_vetex; j++) {
			if (lowcost[j]!=-1 && map[min_idx][j] < lowcost[j]) {
				lowcost[j] = map[min_idx][j];
			}
		}
	}

	printf("The highest possible quality is 1/%d\n", sum);
	return 0;
}


int main(int argc, char* argv[])
{
	int n;

	while(1) {
		scanf("%d", &n);
		if (n == 0) 
			break;
		init(n);
		prime(0);
	}

	return 0;
}

