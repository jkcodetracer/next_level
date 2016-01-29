/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年11月25日 星期三 23时20分27秒 CST  
 *	...dp 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN	(1100)
#define INF	(999999)
#define MIN(a,b) ((a)>(b))?(b):(a)

int dp[MAXN][MAXN];

void solve()
{
	int n,m;
	int i, j;
	int B, P;
	double ans = 0, k;

	scanf("%d", &n);
	for (i = 0; i <= n; i++) {
		for (j = 0; j < MAXN; j++) {
			dp[i][j] = INF;
		}
	}


	for (i = 1; i <= n;i++) {
		scanf("%d", &m);
		while(m--) {
			scanf("%d %d", &B, &P);
			if (i == 1) {
				dp[i][B] = MIN(dp[i][B], P);
				continue;
			}
			for (j = 0; j <= MAXN;j++) {
				if (j <= B) {
					dp[i][j] = MIN(dp[i][j], dp[i-1][j]+P);
				} else {
					dp[i][B] = MIN(dp[i][B], dp[i-1][j]+P);
				}
			}
		}
	}

	for (i = 0; i < MAXN; i++) {
		if (dp[n][i] == INF)
			continue;

		k = (double)i/dp[n][i];
		if (k > ans)
			ans = k;
	}

	printf("%.3f\n", ans);
}

int main(int argc, char *argv[])
{
	int n_case;

	scanf("%d", &n_case);
	while(n_case--) {
		solve();
	}

	return 0;
}


