/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年 8月15日 星期六 23时21分46秒 CST 
 *
 * segment tree, section update
 */
#include <stdio.h>

#define MAXN	100000

int tree[MAXN << 2] = {0};
int col[MAXN << 2] = {0};
int N = 0;

void push_up(int rt)
{
	tree[rt] = tree[rt << 1] + tree[rt << 1 | 1];
}

void push_down(int rt, int m)
{
	if (col[rt]) {
		col[rt << 1] = col[rt << 1|1] = col[rt];
		tree[rt << 1] = (m - (m>>1)) * col[rt];
		tree[rt << 1 |1] = (m>>1) * col[rt];
		col[rt] = 0;
	}
}

void update(int L, int R, int v, int l, int r, int rt)
{
	int mid;
	if (L <= l && R >= r) {
		col[rt] = v;
		tree[rt] = (r-l + 1)*v;
		return ;
	}

	mid = l + ((r-l)>>1);
	push_down(rt, r - l+1);

	if (L <= mid){
		update(L, R, v, l, mid, rt << 1);
	}

	if (R > mid) {
		update(L, R, v, mid+1, r, rt << 1|1);
	}
	push_up(rt);
}


void init(int l, int r, int rt)
{
	int mid = 0;

	col[rt] = 0;

	if (l == r) {
		tree[rt] = 1;
		return;
	}

	mid = l + ((r - l) >>1);
	init(l, mid, rt << 1);
	init(mid+1, r, rt << 1 |1);
	push_up(rt);
}

int main(int argc, char* argv[])
{
	int total, l, r, n_case, v;

	scanf("%d", &total);
	while(total--) {
		scanf("%d", &N);
		init(1, N, 1);

		scanf("%d", &n_case);
		while(n_case--) {
			scanf("%d %d %d", &l, &r, &v);
			update(l, r, v, 1, N, 1);
		}

		printf ("%d\n", tree[1]);
	}
	return 0;
}
