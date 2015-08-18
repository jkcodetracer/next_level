/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年 8月16日 星期日 23时39分38秒 CST 
 *
 * segment tree, update, discrete
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN	10001


int tree[MAXN << 2] = {0};
char hash[MAXN] = {0};

int discrete[MAXN * 3] = {0};
int li[MAXN] = {0};
int ri[MAXN] = {0};

int cnt = 0;

int cmp(const void *a, const void *b)
{
	return *(int*)a - *(int*)b;
}

void build(int l, int r, int rt)
{
	int mid = 0;

	tree[rt] = -1;

	if (l == r) {
		return ;
	}

	mid = l + ((r-l)>>1);
	build(l, mid, rt<<1);
	build(mid+1, r, rt<<1|1);
}

void push_down(int rt)
{
	if (tree[rt]!=-1) {
		tree[rt<<1] = tree[rt<<1|1] = tree[rt];
		tree[rt] = -1;
	}
}

void update(int L, int R, int v, int l, int r, int rt)
{
	int mid;
	if (L <= l && R >= r) {
		tree[rt] = v;
		return;
	}

	push_down(rt);
	mid = l + ((r-l)>>1);
	if (L <= mid)
		update(L, R, v, l, mid, rt <<1);
	if (R > mid)
		update(L, R, v, mid+1, r, rt<<1|1);
}

void query(int l, int r, int rt)
{
	int mid ;

	if (tree[rt] != -1) {
		if (!hash[tree[rt]])
			cnt++;
		hash[tree[rt]] = 1;
		return ;
	}

	if (l == r)
		return;

	mid = l + ((r-l)>>1);
	query(l, mid, rt<<1);
	query(mid+1, r, rt<<1|1);
}

int bin(int target, int *arr, int len)
{
	int mid;
	int l = 0, r = len-1;

	while (l <= r) {
		mid = l + ((r-l)>>1);
		if (target == arr[mid])
			return mid;
		else if (target > arr[mid])
			l = mid + 1;
		else
			r = mid - 1;
	}

	return -1;
}

int main(int argc, char* argv[])
{
	int n_case, N;
	int i, n_x, m;
	int l, r;

	scanf("%d", &n_case);
	while (n_case--) {
		cnt = 0;
		n_x = 0;
		scanf("%d", &N);
		for(i = 0; i < N; i++) {
			scanf("%d %d", &li[i], &ri[i]);
			discrete[n_x++] = li[i];
			discrete[n_x++] = ri[i];
		}
		qsort(discrete, n_x, sizeof(int), cmp);
		m = 1;
		//重复
		for (i = 1; i < n_x; i++) {
			if (discrete[i] != discrete[i-1])
				discrete[m++] = discrete[i];
		}

		//如果原始区间不是连续的，插入一些节点。
		for (i = m-1; i > 0; i--) {
			if (discrete[i] != discrete[i-1]+1)
				discrete[m++] = discrete[i-1] + 1;
		}
		qsort(discrete, m, sizeof(int), cmp);
		build(0, m, 1);
		//将区间更新进去
		for(i = 0; i < N; i++) {
			l = bin(li[i], discrete, m);
			r = bin(ri[i], discrete, m);
			update(l, r, i, 0, m, 1);
		}

		memset(hash, 0, sizeof(char)*MAXN);
		query(0, m, 1);
		printf ("%d\n", cnt);
	}

	return 0;
}


