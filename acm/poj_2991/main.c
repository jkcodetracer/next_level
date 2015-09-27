/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年 8月22日 星期六 23时53分00秒 CST 

 * segment tree, session update, math
 */
#include <stdio.h>
#include <math.h>

#define MAXN	(100001)

typedef struct node{
	double x, y;
	int deg;
	int flag;
}node_st;

node_st tree[MAXN <<2];
int angle[MAXN] = {0};

double pi;

double set(int x)
{
	return x*pi/180;
}

void work(int rt, int deg)
{
	double r = set(deg);
	double x, y;

	x = tree[rt].x;
	y = tree[rt].y;
	//只是做了逆时针旋转，
	tree[rt].x = x * cos(r) - y * sin(r);
	tree[rt].y = x * sin(r) + y * cos(r);
	tree[rt].deg = (tree[rt].deg + deg)%360;
}

void push_up(int rt)
{
	tree[rt].x = tree[rt<<1].x + tree[rt<<1|1].x;
	tree[rt].y = tree[rt<<1].y + tree[rt<<1|1].y;
}

void push_down(int rt)
{
	if (tree[rt].flag) {
		work(rt<<1, tree[rt].flag);
		work(rt<<1|1, tree[rt].flag);
		tree[rt<<1].flag += tree[rt].flag;
		tree[rt<<1|1].flag += tree[rt].flag;
		tree[rt].flag = 0;
	}
}

void update(int L, int R, int deg, int l, int r, int rt)
{
	int mid;

	if (L <= l && R >= r) {
		work(rt, deg);
		tree[rt].deg += deg;
		return;
	}

	push_down(rt);
	mid = l + ((r-l)>>1);
	if (L <= mid) {
		update(L, R, deg, l, mid, rt<<1);
	}

	if (R > mid) {
		update(L, R, deg, mid+1, r, rt<<1|1);
	}

	push_up(rt);
}

int query(int v, int l, int r, int rt)
{
	int mid;

	if (l == r)
		return tree[rt].deg;

	push_down(rt);
	mid = l + ((r-l)>>1);
	if (v <= mid)
		return query(v, l, mid, rt<<1);
	else
		return query(v, mid+1, r, rt<<1|1);
}

void init(int l, int r, int rt)
{
	int mid;

	tree[rt].x = tree[rt].y = 0;
	tree[rt].deg = tree[rt].flag = 0;
	if (l == r) {
		//tree[rt].deg = 180;
		scanf("%lf", &tree[rt].y);
		return ;
	}

	mid = l + ((r-l)>1);
	init(l, mid, rt<<1);
	init(mid+1, r, rt<<1|1);

	push_up(rt);
}

int main(int argc, char *argv[])
{
	int m, n, x, y;
	int deg;
	int i;

	pi = acos(-1.0);
	while(~scanf("%d %d", &n, &m)) {
		init(0, n-1, 1);

		for (i = 0; i < MAXN;i++)
			angle[i] = 180;

		while (m--) {
			scanf("%d %d", &x, &y);

			//deg = query(x-1, 0, n-1, 1) + 180 + y - query(x, 0, n-1, 1);
			//deg = y-query(x, 0, n-1, 1);
			deg = y - angle[x];
			angle[x] = y;
			update(x, n-1, deg, 0, n-1, 1);
			printf("%.2f %.2f\n", tree[1].x, tree[1].y);
		}
	}

	return 0;
}


