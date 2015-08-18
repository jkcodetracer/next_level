/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年 8月 9日 星期日 11时46分45秒 CST
 *
 * 1. segment tree, to find the orig idx
 */
#include <stdio.h>

#define MAXN 500000

int tree[MAXN << 2] = {0};
char kid[MAXN][10] = {{0}};
int card[MAXN] = {0};
//反素数打表
int s[40] = {1,2,4,6,12,24,36,48,60,
	120,180,240,360,720,840,1260,1680,2520,5040,7560,
	10080,15120,20160,25200,27720,45360,50400,55440,83160,
	110880,166320,221760,277200,332640,498960,500001};
int b[40] = {1,2,3,4,6,8,9,10,12,16,
	18,20,24,30,32,36,40,48,60,
	64,72,80,84,90,96,100,108,120,
	128,144,160,168,180,192,200,1314521}; 

void push_up(int rt)
{
	tree[rt] = tree[rt<<1] + tree[rt<<1|1];
}

int query(int k, int l, int r, int rt)
{
	int m, n = 0;

	if(l == r) {
		tree[rt] = 0;
		return l;
	}

	m = l + ((r-l)>>1);
	if (tree[rt << 1] >= k) {
		n = query(k, l, m, rt << 1);
	} else {
		n = query(k - tree[rt<<1], m+1, r, rt<<1|1);
	}

	push_up(rt);

	return n;
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

int main(int argc, char *argv[])
{
	int i = 0;
	int total, begin, key, n;
	int maxn, p;

	scanf("%d %d", &total, &begin);

	for (i = 0; i < total;i++) {
		scanf("%s %d", kid[i], &card[i]);
	}

	i = 0;
	while (s[i] <= total) i++;
	maxn = b[i-1];//对应的因子数
	p = s[i-1];  //第p个出队的是糖果最多的， 因子数最多
	build(0, total - 1, 1);

	n = total;
	while(p--) {
		n--;
		key = query(begin, 0, total-1, 1);
		if(!n)
			break;

		if (card[key] >= 0) {
			//模运算从0开始， 减1用于修正下标，
			//移动card[key]的话，实际上是从删除的这个元素的
			//前一个元素开始算的，因此再减1，
			//最后加1表示修正坐标从1开始。也代表需要的
			//空闲的元素的个数
			begin = (begin - 1 + card[key] - 1)%n + 1;
		} else {
			begin = ((begin - 1 + card[key])%n + n)%n + 1;
		}
	}

	printf ("%s %d\n", kid[key],maxn);

	return 0;
}

