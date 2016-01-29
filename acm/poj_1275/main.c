/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年10月29日 星期四 17时09分45秒 CST  
 *
 *	差分约束系统
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN	(32)
#define MAXE	(2048)
#define INF	(999999)

typedef struct edge_st{
	int u,v,w;
}edge_st;

int n_edge;
edge_st edges[MAXE];
int r[MAXN];
int t[MAXN];
int dis[MAXN];
int ans;
int maxp;

void add_edge(int u, int v, int w)
{
	edge_st *pe;

	pe = &edges[n_edge++];
	pe->u = u;
	pe->v = v;
	pe->w = w;
}

void init()
{
	int i, num;

	for (i = 1; i <= 24; i++) {
		scanf("%d", &num);
		r[i] = num;
	}

	n_edge = 0;
	memset(t, 0, sizeof(int)*MAXN);
	scanf("%d", &maxp);
	for (i = 0; i < maxp; i++) {
		scanf("%d", &num);
		t[num+1]++;
	}
	//一共48条边
	for(i = 1; i <= 24; i++) {
		add_edge(i, i-1, 0); //s[i-1] <= s[i] + 0
		add_edge(i-1, i, t[i]); //s[i] <= s[i-1] + t[i]
	}
}

void init_graph(int sum)
{
	int i;

	n_edge  = 48;	//最初加入的有效边，重置之后确保后面这种情况的正确性,这个过程是尝试枚举解的过程，
			//只有后面两个不等式生成的边会不同。
	for (i = 1; i <= 8; i++) {
		add_edge(i, i+16, sum-r[i]); //s[i+16] <= s[i] + s[24] - r[i];
	}
	for (i = 9; i <= 24; i++) {
		add_edge(i, i-8, -r[i]); //s[i-8] <= s[i] - r[i];
	}

	add_edge(0, 24, sum); //s[24]-s[0] >= sum;
}

int bellman_ford(int begin)
{
	int i,j;
	edge_st *pe;

	for (i = 0; i < 25; i++) {
		dis[i] = INF;
	}

	dis[0] = 0;
	for (i = 0; i < 24; i++) {
		for (j = 0; j < n_edge; j++) {
			pe = &edges[j];
			if (dis[pe->u] == INF)
				continue;
			if (dis[pe->u] + pe->w < dis[pe->v]) {
				dis[pe->v] = dis[pe->u] + pe->w;
			}
		}
	}

	for (i = 0; i < n_edge; i++) {
		pe = &edges[i];
		if (dis[pe->u] + pe->w < dis[pe->v]) 
			return 0;
	}

	return 1;
}

void binary_enum(int low, int high)
{
	int mid;

	if (low > high)
		return ;

	mid = low + ((high-low) >>1);
	init_graph(mid);

	if (bellman_ford(0)) {
		ans = mid;
		binary_enum(low, mid-1);
	} else {
		binary_enum(mid+1, high);
	}
}

int main(int argc, char* argv[])
{
	int total;

	scanf("%d", &total);
	while(total--) {
		init();
		ans = -1;

		binary_enum(0, maxp);
		if (ans == -1){
			printf("No Solution\n");
		} else {
			printf("%d\n", ans);
		}
	}

	return 0;
}

