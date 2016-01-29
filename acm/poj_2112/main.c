/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年11月25日 星期三 21时37分52秒 CST  
 *
 * 1. 使用floyd算法求解每两个点之间的最短距离。
 * 2. 使用dinic算法，求解最大网络流
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN (1024)
#define INF (9999999)
#define MIN(a, b) ((a)>(b))?(b):(a)

int dis[MAXN][MAXN];
int map[MAXN][MAXN];
int sign[MAXN][MAXN];
int K, C, M;
int n_vetex, n;

void init()
{
	int i,j;


	memset(dis, 0, sizeof(dis));
	scanf("%d %d %d", &K, &C, &M);
	n_vetex = K + C + 2; // add a begin node and end node
	n = K + C;

	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			scanf("%d", &dis[i][j]);
		}
	}
}

void floyd()
{
	int i,j,k;

	for (k = 1; k <= n; k++) {
		for (i =1; i <= n; i++) {
			for (j = 1; j <= n;j++) {
				if (dis[i][k] == 0)
					continue;
				if (dis[i][k] + dis[k][j] < dis[i][j]) {
					dis[i][j] = dis[i][k] + dis[k][j];
				}
			}
		}
	}
}

//生成残余网络
void flow_init(int min_dis)
{
	int i,j;

	memset(map, 0, sizeof(map));
	for (i = K + 1; i <= n; i++) {
		map[0][i] = 1;
	}

	for (i = 1; i <= K; i++) {
		map[i][n+1] = M;
	}

	for (i = K+1; i <= n; i++) {
		for ( j = 1; j <= K; j++) {
			if (dis[i][j] <= min_dis)
				map[i][j] = 1;
		}
	}
}

int bfs()
{
	int i; 
	int queue[MAXN*MAXN];
	int used[MAXN];
	int tail, head;

	memset(used, 0, sizeof(used));
	for (i = 0; i < MAXN; i++) {
		memset(sign[i], 0, sizeof(int)*MAXN);
	}

	head = tail = 0;
	used[0] = 1;
	queue[head++] = 0;
	while(tail < head) {
		for (i = 0; i <= n+1; i++) {
			if (!used[i] && map[queue[tail]][i]) {
				sign[queue[tail]][i] = 1;
				queue[head++] = i;
				used[i] = 1;
			}
		}
		tail++;
	}

	if (used[n+1]){
		return 1;
	} else {
		return 0;
	}
}

int dfs(int cur, int sum)
{
	int tmp, i, t;

	if(cur == n+1)
		return sum;
	tmp = sum;
	for (i = 0; i <= n+1; i++) {
		if (sign[cur][i]) {
			t = dfs(i, MIN(map[cur][i], sum));
			map[cur][i] -= t;
			map[i][cur] += t;
			sum -= t;
		}
	}

	return tmp - sum;
}

int main(int argc, char* argv[])
{
	int ans = 0;
	int L, R, mid;
	init();
	floyd();

	//使用二分法尝试出所有最短路径的最大值
	L = 0;
	R = 100000;
	while(L < R) {
		mid = ((R-L)>>1) + L;

		ans = 0;
		flow_init(mid);
		while(bfs()){  //生成层次网络
			ans += dfs(0, INF); //使用dfs发现增广路
		}

		if (ans >= C) {
			R = mid;
		} else {
			L = mid + 1;
		}
	}

	printf("%d\n", R);
	return 0;
}


