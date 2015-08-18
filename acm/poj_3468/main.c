/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年 8月16日 星期日 10时06分49秒 CST 
 *
 * segment tree, session update
 */
#include <stdio.h>

#define MAXN	(100000)

long long tree[MAXN << 2] = {0};
long long col[MAXN << 2] = {0};
int N = 0;

void push_up(int rt)
{
	tree[rt] = tree[rt<<1] + tree[rt<<1|1];
}

void push_down(int rt, int len)
{
	if (col[rt]) {
		col[rt<<1] += col[rt];
		col[rt<<1|1] += col[rt];
		tree[rt<<1] += (len - (len>>1))*col[rt];
		tree[rt<<1|1] += (len>>1)*col[rt];
		col[rt] = 0;
	}
}

long long query(int L, int R, int l, int r, int rt)
{
	int mid;
	long long sum = 0;

	if (L <= l && R >= r) {
		return tree[rt];
	}

	mid = l + ((r-l)>>1);
	push_down(rt, r-l+1);
	if (L <=mid) {
		sum = query(L, R, l, mid, rt<<1);
	}
	if (R > mid) {
		sum += query(L, R, mid+1, r, rt<<1|1);
	}

	return sum;
}

void update(int L, int R, int v, int l , int r, int rt)
{
	int mid;

	if (L <= l && R >=r) {
		tree[rt] += (r-l+1)*v;
		col[rt] += v;
		return;
	}

	mid = l + ((r-l)>>1);
	push_down(rt, r-l+1);

	if (L <=mid) {
		update(L, R, v, l, mid, rt<<1);
	}

	if (R >mid) {
		update(L, R, v, mid+1, r, rt<<1|1);
	}

	push_up(rt);
}

void build(int l, int r, int rt)
{
	int mid = 0;

	col[rt] = 0;
	if(l == r) {
		scanf("%lld", &tree[rt]);
		return;
	}

	mid = l + ((r-l)>>1);
	build(l, mid, rt<<1);
	build(mid+1, r, rt<<1|1);

	push_up(rt);
}

int main(int argc, char* argv[])
{
	char cmd[2];
	int a, b, v;
	int Q;

	scanf("%d %d", &N, &Q);
	build(1, N, 1);
	while(Q--) {
		scanf("%s", cmd);
		if (cmd[0] == 'Q') {
			scanf("%d %d", &a, &b);
			printf ("%lld\n", query(a, b, 1, N, 1));
		} else {
			scanf("%d %d %d", &a, &b, &v);
			update(a, b, v, 1, N, 1);
		}
	}

	return 0;
}

