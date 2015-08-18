/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年 8月 9日 星期日 08时34分18秒 CST
 *
 * 1. segment tree singal update, to use the segment sum
 */
#include <stdio.h>

#define MAXN 200000

int tree[MAXN<<2] = {0};
int arr[MAXN] = {0};
int pos[MAXN] = {0};
int final[MAXN] = {0};

void push_up(int rt)
{
	tree[rt] = tree[rt<<1] + tree[rt<<1|1];
}

void update(int p, int value, int l, int r, int rt)
{
	int m = 0;
	if (l == r) {
		tree[rt] = 0;
		final[l] = value;
		return ;
	}

	m = l + ((r-l)>>1);
	if (tree[rt<<1] >= p) {
		update(p, value, l, m, rt << 1);
	} else {
		update(p - tree[rt<<1], value, m+1, r, rt << 1 | 1);
	}

	push_up(rt);
}

void build(int l, int r, int rt)
{
	int m = 0;
	if (l == r) {
		tree[rt] = 1;
		return;
	}

	m = l + ((r-l)>>1);
	build(l, m, rt<<1);
	build(m+1, r, rt<<1|1);

	push_up(rt);
}

int main(int argc, char* argv[])
{
	int i = 0;
	int total;

	while (1) {
		scanf("%d", &total);
		build(0, total-1, 1);

		for (i = 0; i < total; i++) {
			scanf("%d %d", &pos[i], &arr[i]);
		}

		for (i = total-1; i >= 0; i--) {
			update(pos[i]+1, arr[i], 0, total-1, 1);
		}

		for (i = 0; i < total; i++) {
			printf ("%d ", final[i]);
		}
	}

	return 0;
}

