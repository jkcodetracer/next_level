/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年11月29日 星期日 19时36分33秒 CST  
 *
 * segment tree. segment update
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1024

int cover[MAXN <<2];
int tree[MAXN <<2];

void tree_init(int l, int r, int rt)
{
	int mid;

	cover[rt] = 0;
	tree[rt] = 0;
	if (l == r)
		return;

	mid = (r+l)/2;
	tree_init(l, mid, (rt<<1));
	tree_init(mid+1, r, (rt<<1)|1);
}

void push_up(int rt)
{
	if (tree[rt<<1] > tree[(rt<<1)|1]) {
		tree[rt] = tree[rt <<1];
	} else {
		tree[rt] = tree[(rt<<1)|1];
	}
}

void push_down(int rt)
{
	if (cover[rt]) {
		cover[rt<<1] += cover[rt];
		cover[(rt<<1)|1] += cover[rt];
		tree[rt<<1] += cover[rt];
		tree[rt<<1|1] += cover[rt];
		cover[rt] = 0;
	}
}

void tree_update(int L, int R, int l, int r, int rt)
{
	int mid;
	if (L <= l && R >= r) {
		cover[rt] += 10;
		tree[rt] += 10;
		return;
	}

	mid = (l + r) / 2;
	push_down(rt);
	if (L <= mid) {
		tree_update(L, R, l, mid, rt<<1);
	}

	if (R > mid){
		tree_update(L, R, mid+1, r, (rt<<1)|1);
	}

	push_up(rt);
}

void init()
{
	int i, n;
	int l, r;
	tree_init(0, 199, 1);
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d %d", &l, &r);
		l = (l-1)/2;
		r = (r-1)/2;
		tree_update(l, r, 0, 199, 1);
	}
}

int main(int argc, char*argv[])
{
	int total;

	scanf("%d", &total);
	while(total--) {
		init();
		printf("%d\n", tree[1]);
	}

	return 0;
}


