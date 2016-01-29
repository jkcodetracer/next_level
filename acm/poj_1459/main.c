/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年11月26日 星期四 16时31分59秒 CST  
 *
 * net flow
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN (1024)
#define INF (9999999)

#define MIN(a, b) ((a)>(b))?(b):(a)

typedef struct node_st{
	int f,c;
} node_st;

node_st map[MAXN][MAXN];
int minflow[MAXN];
int sign[MAXN];
int n, np, nc, m;
int n_vetex;
int s, t;

int init()
{
	int i,j;
	int u,v,w;

	scanf("%d %d %d %d", &n, &np, &nc, &m);
	if (n == 0)
		return 0;

	s = n;
	t = n+1;
	n_vetex = n+2;
	for (i = 0; i < n_vetex; i++) {
		for (j = 0; j < n_vetex; j++) {
			map[i][j].f = 0;
			map[i][j].c = INF;
		}
	}

	for (i = 0; i < m; i++) {
		while(getchar()!='(');
		scanf("%d,%d)%d", &u, &v, &w);
		map[u][v].c = w;
	}

	for (i = 0; i < np; i++) {
		while(getchar()!='(');
		scanf("%d)%d", &u, &w);
		map[s][u].c = w;
	}

	for (i = 0; i < nc; i++) {
		while(getchar()!='(');
		scanf("%d)%d", &u, &w);
		map[u][t].c = w;
	}

	return 1;
}

void ford_flow()
{
	int i;
	int head, tail;
	int flag[MAXN];
	int queue[MAXN];
	int cur, prev;
	int sum = 0;

	while(1) {
		head = tail = 0;
		queue[head++] = s;
		memset(flag, -1, sizeof(flag));
		memset(sign, 0, sizeof(sign));
		for (i = 0; i < MAXN ; i++) {
			minflow[i] = INF;
			sign[i] = -1;
		}

		flag[s] = 0;
		while(head != tail) {
			for (i = 0; i < n_vetex; i++) {
				if (flag[i] != -1)
					continue;

				if (map[queue[tail]][i].c != INF &&
				    map[queue[tail]][i].c > map[queue[tail]][i].f) {
					flag[i] = 0;
					minflow[i] = MIN(minflow[queue[tail]], map[queue[tail]][i].c - map[queue[tail]][i].f);
					sign[i] = queue[tail];
					queue[head++] = i;
				} else if (map[i][queue[tail]].c != INF &&
					map[i][queue[tail]].f) {
					flag[i] = 0;
					minflow[i] = MIN(minflow[queue[tail]], map[i][queue[tail]].f);
					sign[i] = queue[tail];
					queue[head++] = i;
				}
			}

			tail++;
		}

		if (minflow[t] == INF ||
		    sign[t] == -1)
			break;

		cur = t;
		prev = sign[cur];
		while (prev != -1) {
			if (map[prev][cur].c != INF) {
				map[prev][cur].f += minflow[t];
			} else if (map[cur][prev].c != INF) {
				map[cur][prev].f -= minflow[t];
			}
			cur = prev;
			prev = sign[prev];
		}
	}

	for (i = 0; i < n_vetex; i++) {
		if (map[s][i].c != INF) {
			sum += map[s][i].f;
		}
	}

	printf("%d\n", sum);
}

int main(int argc, char *argv[])
{
	while(init()) {
		ford_flow();
	}

	return 0;
}


