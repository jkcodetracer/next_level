/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年 8月 8日 星期六 07时46分24秒 CST
 *
 * 1. sigle point update, the segment tree
 */
#include<stdio.h>

#define MAXN 50000

int sum[MAXN << 2] = {0};

void push_up(int rt)
{
	sum[rt] = sum[rt << 1] + sum[rt << 1|1];
}

int query(int L, int R, int l, int r, int rt)
{
	int m = 0;
	int ret = 0;
	if (L <= l && R >= r) {
		return sum[rt];
	}

	m = l + ((r-l)>>1);
	if (L <= m)
		ret += query(L, R, l, m, rt << 1);
	if (R > m)
		ret += query(L, R, m+1, r, rt << 1|1);

	return ret;
}

void update(int p, int add, int l , int r, int rt)
{
	int m = 0;

	if (l == r) {
		sum[rt] += add;
		return;
	}

	m = l + ((r-l)>>1);
	if (p <= m) {
		update(p, add, l, m, rt<<1);
	} else {
		update(p, add, m+1, r, rt<<1|1);
	}
	push_up(rt);
}

void build(int l, int r, int rt)
{
	if (l == r) {
		scanf("%d", &sum[rt]);
		return;
	}

	build(l, l+((r-l)>>1), (rt << 1));
	build(l + ((r-l)>>1)+1, r, (rt << 1)|1);
	push_up(rt);
}

int main(int argc, char* argv[])
{
	int n_case, maxn;
	int a, b;
	char op[10] = {0};

	scanf("%d", &n_case);
	while (n_case--) {
		scanf("%d", &maxn);

		build(1, maxn, 1);
		while(scanf("%s", op)) {
			if (op[0] == 'E')
				break;
			scanf("%d %d", &a, &b);

			if (op[0] == 'Q')
				printf ("%d\n", query(a, b, 1, maxn,1));
			else if (op[0] == 'S')
				update (a, -b, 1, maxn, 1);
			else
				update (a, b, 1, maxn, 1);
		}
	}

	return 0;
}


