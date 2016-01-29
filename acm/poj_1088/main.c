/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年12月 1日 星期二 09时18分39秒 CST 
 *
 * 1. dp
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN (128)
typedef struct node_st{
	int x,y;
} node_st;

int n_nodes;
node_st nodes[10004];
node_st dir[4] = {{0,1},{0,-1}, {1,0}, {-1, 0}};
int high[MAXN][MAXN];
int len[MAXN][MAXN];
int R, C;

int cmp(const void* a, const void*b)
{
	node_st *pa = (node_st*)a;
	node_st *pb = (node_st*)b;

	if (high[pa->x][pa->y] > high[pb->x][pb->y]) {
		return 1;
	} else {
		return -1;
	}
}

void init()
{
	int i,j;

	n_nodes = 0;
	scanf("%d %d", &R, &C);
	for (i = 0; i < R; i++) {
		for (j = 0; j < C; j++) {
			scanf("%d", &high[i][j]);
			nodes[n_nodes].x = i;
			nodes[n_nodes].y = j;
			n_nodes++;

			len[i][j] = 0;
		}
	}
}

void solve()
{
	int i, j;
	int tpx, tpy;
	int max = 0 ;
	qsort(nodes, n_nodes, sizeof(nodes[0]), cmp);

	for (i = 0; i < n_nodes; i++) {
		for (j = 0; j < 4; j++) {
			tpx = nodes[i].x + dir[j].x;
			tpy = nodes[i].y + dir[j].y;

			if (tpx < 0 || tpx >= R ||
			    tpy < 0 || tpy >= C)
				continue;

			if (high[nodes[i].x][nodes[i].y] < high[tpx][tpy] &&
			    len[nodes[i].x][nodes[i].y] >= len[tpx][tpy]) {
				len[tpx][tpy] = len[nodes[i].x][nodes[i].y]+1;
			}
		}
	}

	for (i = 0; i < R; i++) {
		for (j = 0; j < C; j++) {
			if (len[i][j] > max) {
				max = len[i][j];
			}
		}
	}

	printf("%d\n", max+1);
}

int main(int argc, char* argv[])
{
	init();
	solve();

	return 0;
}


