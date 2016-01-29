/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年10月29日 星期四 22时38分16秒 CST  
 *
 * dp + short path
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN (32)
#define MAXK (16)
#define INF  (999999)

int n_vetex;
int dis[MAXN][MAXN];
int map[MAXN][MAXN];
int fly[MAXN][MAXN];
int dp[MAXN][MAXK];
int maxk;
int maxl;
int a,b;

void init()
{
	int m,i,j;
	int u,v,w;

	for (i = 0; i < MAXN; i++) {
		for (j = 0; j < MAXN; j++) {
			dis[i][j] = INF;
			fly[i][j] = 0;
			map[i][j] = INF;
		}
	}

	scanf("%d %d %d %d %d", &a, &b, &m, &maxl, &maxk);
	n_vetex = a + b;
	for (i = 0; i < m; i++){
		scanf("%d %d %d", &u, &v, &w);
		dis[u][v] = w;
		dis[v][u] = w;
		map[u][v] = w;
		map[v][u] = w;
	}
}

void floyd()
{
	int i,j,n;

	for (n = 1; n <= n_vetex; n++) {
		for (i = 1; i <= n_vetex; i++) {
			for (j = 1; j <= n_vetex; j++) {
				if (i == n || j == n)
					continue;

				if (dis[i][n] == INF)
					continue;

				if (dis[i][n] + dis[n][j] < dis[i][j]) {
					dis[i][j] = dis[i][n] + dis[n][j];
					if (n <= a && dis[i][j] <= maxl) {
						fly[i][j] = fly[i][j]= 1;
					}
				}
			}
		}
	}
}

int mini(int a, int b)
{
	return (a>b)?b:a;
}

#if 0
void dyp()
{
	int i,j,n, k;

	for(n = 1; n <= n_vetex; n++) {
		for (k = 0; k <= maxk; k++) {
			for (i = 1; i < n_vetex; i++) {
				for (j = 1; j < n_vetex; j++) {
					if (map[i][j] == INF)
						continue;
				}
			}
		}
	}
}
#endif

#if 1
void dyp()
{
	int i,j,k;
	int min;

	for (i = 0; i <= n_vetex; i++) {
		for (j = 0; j <= maxk; j++) {
			dp[i][j] = INF;
		}
	}
	for (i = 2; i <= n_vetex; i++) {
		dp[i][0] = dis[1][i];
		printf("--%d %d\n", i, dp[i][0]);
	}

	for (i = 0; i <= maxk; i++) {
		dp[1][i] = 0;
	}

	for (i = 2; i <= n_vetex; i++) {
		for (k = 1; k <= maxk; k++) {
			min = INF;
			for (j = 1; j <= n_vetex; j++) {
				if (fly[j][i]) {
					min = mini(min, dp[j][k-1]);
				}
				min = mini(min, dp[j][k] + dis[j][i]);
			}
			dp[i][k] = min;
			printf("--%d %d %d\n", i, k, min);
		}
	}
}
#endif


int main(int argc, char* argv[])
{
	int total;

	scanf("%d", &total);
	while(total--) {
		init();
		floyd();
		dyp();
		printf("%d\n", dp[n_vetex][maxk]);
	}

	return 0;
}

