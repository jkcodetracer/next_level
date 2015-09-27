/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年 9月14日 星期一 16时41分22秒 CST 
 *
 * 0. build the map
 * 1. topsort: find one order
 * 2. dfs: find all possible ordier
 */
#include <stdio.h>
#include <string.h>

#define MAXN	(32)

#define MAX(a, b) ((a)>(b))?(a):(b)
#define MIN(a, b) ((a)<(b))?(a):(b)

typedef struct pat{
	int lx;
	int ly;
	int rx;
	int ry;
}pat_st;

char map[MAXN][MAXN];
char rel_graph[MAXN][MAXN];
int pat_num;
pat_st pat_table[MAXN];
int count[MAXN] = {0};
int flag[MAXN] = {0};
int h, w;
char ans[MAXN] = {0};

void get_map()
{
	int i;
	for (i = 0; i < h; i++) {
		scanf("%s", map[i]);
	}
}

void add_edge(int target, int k)
{
	if (target != k && !rel_graph[k][target]) {
		rel_graph[k][target] = 1;
		count[target]++;
	}
}

void init_rel(int k)
{
	int i;

	for (i = pat_table[k].lx; i <= pat_table[k].rx; i++) {
		add_edge(map[i][pat_table[k].ly] - 'A', k);
		add_edge(map[i][pat_table[k].ry] - 'A', k);
	}

	for (i = pat_table[k].ly; i <= pat_table[k].ry; i++) {
		add_edge(map[pat_table[k].lx][i] - 'A', k);
		add_edge(map[pat_table[k].rx][i] - 'A', k);
	}
}

void init_graph()
{
	int i, j;
	int target;

	pat_num = 0;
	memset(flag, 0, sizeof(int)*MAXN);
	memset(count, 0, sizeof(int)*MAXN);

	for(i = 0; i < MAXN; i++) {
		pat_table[i].lx = MAXN;
		pat_table[i].ly = MAXN;
		pat_table[i].rx = 0;
		pat_table[i].ry = 0;
	}

	for (i = 0; i < h; i++) {
		for (j = 0;j < w; j++) {
			if(map[i][j] == '.') 
				continue;

			target = map[i][j] - 'A';
			if (!flag[target]) {
				pat_num++;
				flag[target] = 1;
			}
			pat_table[target].lx = MIN(i, pat_table[target].lx);
			pat_table[target].ly = MIN(j, pat_table[target].ly);
			pat_table[target].rx = MAX(i, pat_table[target].rx);
			pat_table[target].ry = MAX(i, pat_table[target].ry);
		}
	}

	for (i = 0; i < pat_num;i++) {
		init_rel(i);
	}
}

void dfs(int depth, int total)
{
	int i,j;

	if (depth == total) {
		ans[total] = '\0';
		printf("%s\n", ans);
		return;
	}

	for (i = 0; i < total; i++) {
		if (count[i] != 0)
			continue;

		for(j=0; j < total;j++){
			if (j == i) 
				continue;
			if (rel_graph[i][j])
				count[j]--;
		}

		ans[depth] = i+'A';
		count[i] = -1;
		dfs(depth+1, total);
		//revive
		count[i] = 0;
		for (j=0; j < total; j++) {
			if (j == i) 
				continue;
			if (rel_graph[i][j]) 
				count[j]++;
		}
	}
}

int main(int argc, char *argv[])
{
	scanf("%d %d", &h, &w);
	get_map();
	init_graph();
	dfs(0, pat_num);

	return 0;
}


