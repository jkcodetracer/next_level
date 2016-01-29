/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年10月27日 星期二 14时58分18秒 CST  
 *
 * 1. 找到所有路径中，最长距离的最小值
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXN	(256)
#define MAXE	(1024)
#define INF	(9999999)

int n_vetex;
double map[MAXN][MAXN];
double dis[MAXN][MAXN];
int nx[MAXN], ny[MAXN];

double distance(int x1, int y1, int x2, int y2)
{
	int dx,dy;

	dx = x1 - x2;
	dy = y1 - y2;

	return sqrt(dx*dx + dy*dy);
}

int init()
{
	int i, j;

	scanf("%d", &n_vetex);
	if (n_vetex == 0)
		return 0;

	for (i = 0; i < n_vetex; i++) {
		scanf("%d %d", &nx[i], &ny[i]);
	}

	for (i = 0; i < n_vetex; i++) {
		for (j = i+1; j < n_vetex; j++) {
			map[i][j] = distance(nx[i], ny[i], nx[j], ny[j]);
			map[j][i] = map[i][j];
		}

		map[i][i] = INF;
	}

	return 1;
}

void floyd()
{
	int i, j, n;
	double max;

	for (i = 0; i < n_vetex; i++){
		for (j = 0; j < n_vetex; j++) {
			dis[i][j] = map[i][j];
		}
	}

	for (n = 0; n < n_vetex; n++) {
		for (i = 0; i < n_vetex; i++) {
			for (j = 0; j < n_vetex; j++) {
				if (dis[i][n] == INF || dis[n][j] == INF)
					continue;
				if (dis[i][n] > dis[n][j]) {
					max = dis[i][n];
				} else {
					max = dis[n][j];
				}

				if (dis[i][j] > max) {
					dis[i][j] = max;
				}
			}
		}
	}

}

void print(int total)
{
	printf("Scenario #%d\n", total);
	printf("Frog Distance = %.3f\n\n", dis[0][1]);
}

int main(int argc, char* argv[])
{
	int total = 0;

	while(init()){
		total++;
		floyd();
		print(total);
	}

	return 0;
}


