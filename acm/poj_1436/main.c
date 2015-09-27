/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年 9月23日 星期三 18时15分56秒 CST 
 *
 * segment tree, segment update!
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN (8096)

typedef struct edge_st{
	int y1, y2;
	int x;
}edge_st;

char map[MAXN][MAXN];
int cover[(MAXN*2) << 2];
edge_st edges[MAXN];
int n_edges;

void init(int l, int r, int rt)
{
	int mid;

	cover[rt] = 0;
	if (l == r)
		return ;

	mid = l + ((r-l)>>1);
	init(l, mid, (rt<<1));
	init(mid+1, r, (rt<<1|1));
}

void push_down(int rt)
{
	if (cover[rt]) {
		cover[rt<<1] = cover[rt<<1|1] = cover[rt];
		cover[rt] = 0;
	}
}

void update(int L, int R, int n, int l, int r, int rt)
{
	int mid = 0;
	if (L <= l && R >= r) {
		cover[rt] = n;
		return ;
	}

	mid = l + ((r-l)>>1);
	push_down(rt);
	if (L <= mid)
		update(L, R, n, l, mid, rt<<1);

	if (R > mid)
		update(L, R, n, mid+1, r, rt<<1|1);
}

void query(int L, int R, int n, int l, int r, int rt)
{
	int mid = 0;
	if (cover[rt]) {
		map[n][cover[rt]] = 1;
		return ;
	}

	if(l == r)
		return ;

	mid = l + ((r-l)>>1);
	if (L <= mid) {
		query(L, R, n, l, mid, rt<<1);
	}

	if (R > mid) {
		query(L, R, n, mid+1, r, rt<<1|1);
	}


int cmp(const void *a, const void *b)
{
	edge_st *pa = (edge_st *)a;
	edge_st *pb = (edge_st *)b;

	return pa->x - pb->x;
}

int main(int argc, char*argv[])
{
	int i, j, k, total;
	int ans;
	edge_st *pe;

	scanf("%d", &total);
	while(total--) {
		scanf("%d", &n_edges);
		for(i = 1; i<=n_edges; i++) {
			pe = &edges[i];
			scanf("%d %d %d", &pe->y1, &pe->y2, &pe->x);
		}

		qsort(edges+1, n_edges, sizeof(edges[0]), cmp);
		for(i = 0; i < MAXN ; i++){
			memset(map[i], 0, MAXN);
		}

		init(0, MAXN*2, 1);
		for(i = 1; i <= n_edges; i++) {
			pe = &edges[i];
			query(pe->y1*2, pe->y2*2, i, 0, MAXN*2, 1);
			update(pe->y1*2, pe->y2*2, i, 0, MAXN*2, 1);
		}

		ans = 0;
		for(i = 1; i <= n_edges; i++) {
			for(j = 1; j <= n_edges; j++) {
				if (map[i][j]) {
					for(k = 1; k <= n_edges;k++)  {
						if (map[i][k]&&map[j][k]) {
							ans++;
						}
					}
				}
			}
		}
		printf ("%d\n", ans);
	}

	return 0;
}


