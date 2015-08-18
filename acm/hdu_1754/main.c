/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年 8月 8日 星期六 08时49分23秒 CST
 *
 * 1. segment tree signle update
 */
#include <stdio.h>

#define MAXN 2000000

int tree[MAXN << 2] = {0};

void push_up(int rt)
{
	tree[rt] = (tree[rt<<1]>tree[rt<<1|1])?
			tree[rt<<1]:tree[rt<<1|1];
}

void update(int p, int v, int l , int r, int rt)
{
	int m = 0;

	if (l == r) {
		tree[rt] = v;
		return ;
	}

	m = l+((r-l)>>1);
	if(p <= m)
		update(p, v, l, m, rt<<1);
	else 
		update(p, v, m+1, r, rt<<1|1);

	push_up(rt);
}

int query(int L, int R, int l, int r, int rt)
{
	int a = 0, b = 0, m;

	if (L <= l && R >= r)
		return tree[rt];

	m = l + ((r-l)>>1);
	if (L > l) 
		a = query(L, R, m+1, r, rt << 1 | 1);
	if (R <= r)
		b = query(L, R, l, m, rt<<1);

	return (a>b)?a:b;
}

void build(int l, int r, int rt)
{
	if (l == r) {
		scanf("%d", &tree[rt]);
		return;
	}

	build(l, l+((r-l)>>1), (rt<<1));
	build(l+((r-l)>>1)+1, r, (rt<<1)|1);
	push_up(rt);
}

int main(int argc, char* argv[])
{
	int maxn, opn;
	int a, b;
	char op[10] = {0};

	scanf("%d %d", &maxn, &opn);
	build(1, maxn, 1);
	while(opn--){
		scanf("%s%d%d", op, &a, &b);
		if (op[0] == 'Q')
			printf ("%d\n", query(a, b, 1, maxn, 1));
		if (op[0] == 'U')
			update (a, b, 1, maxn, 1);
	}

	return 0;
}

