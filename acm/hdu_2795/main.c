/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年 8月 8日 星期六 13时12分29秒 CST
 *
 * 1. segment tree the bigest value.
 */
#include <stdio.h>

#define MAXN 10000

int tree[MAXN << 2] = {0};

void push_up(int rt)
{
	tree[rt] = (tree[rt<<1] > tree[rt<<1|1])?
			tree[rt<<1]:tree[rt<<1|1];
}

int query(int value, int l, int r, int rt)
{
	int m = 0;
	int a = -1, b = -1;
	if (l == r) {
		if (tree[rt] < value) {
			return -1;
		} else {
			tree[rt] -= value;
			return l;
		}
	}

	m = l + ((r-l) >> 1);

	if(tree[rt] < value) {
		return -1;
	}

	a = query(value, l, m, rt<<1);
	if (a == -1)
		b = query(value, m+1, r, rt << 1 | 1);

	push_up(rt);

	return a>b?a:b;
}

void build(int l, int r, int rt, int value)
{
	int m = 0;
	if (l == r){
		tree[rt] = value;
		return;
	}

	m = l + ((r-l) >>1);
	build(l, m, rt<<1, value);
	build(m+1, r, rt<<1|1, value);

	push_up(rt);
}

int main(int argc, char* argv[])
{
	int maxn, case_n, value;
	int tmp;

	scanf("%d %d %d", &maxn, &value, &case_n);

	build(1, maxn, 1, value);
	while(case_n--) {
		scanf("%d", &tmp);
		printf("%d\n", query(tmp, 1, maxn, 1));
	}

	return 0;
}


