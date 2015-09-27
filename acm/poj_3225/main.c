/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年 8月21日 星期五 10时14分06秒 CST 
 *
 * 1. segment tree session update
 */

#include <stdio.h>

#define MAXN	(65535<<1)
#define RANGE	(MAXN +1)

int cover[RANGE<<2] = {0};
int xor[RANGE<<2] = {0};
char hash[RANGE] = {0};

void fxor(int rt)
{
	if (cover[rt] != -1) {
		cover[rt] ^= 1;
	} else {
		xor[rt] ^=1;
	}
}

void push_down(int rt)
{
	if(cover[rt]!=-1) {
		cover[rt<<1] = cover[rt<<1|1] = cover[rt];
		xor[rt<<1] = xor[rt<<1|1] = 0;
		cover[rt] = -1;
	}

	if(xor[rt]) {
		fxor(rt<<1);
		fxor(rt<<1|1);
		xor[rt] = 0;
	}
}

void query(int l , int r, int rt)
{
	int mid, i;

	if (cover[rt] == 1) {
		for(i = l; i <=r; i++) {
			hash[i] = 1;
		}
		return ;
	} else if (cover[rt] == 0) {
		return;
	}

	if (l == r) {
		return;
	}

	mid = l+((r-l)>>1);
	push_down(rt);
	query(l, mid, rt<<1);
	query(mid+1, r, rt<<1|1);
}

void update(int L, int R, char cmd, int l, int r, int rt)
{
	int mid;

	if (L <= l && R >= r) {
		if (cmd == 'U') {
			cover[rt] = 1;
			xor[rt] = 0;
		} else if(cmd == 'D') {
			cover[rt] = 0;
			xor[rt] = 0;
		} else if (cmd == 'C' || cmd == 'S') {
			xor[rt] = 1;
			fxor(rt);
		}
		return ;
	}

	push_down(rt);

	mid = l + ((r-l)>>1);
	if (L <= mid) {
		update(L, R, cmd, l, mid, rt<<1);
	} else if(cmd == 'I' || cmd == 'C') {
		//这里只是对分支区间做清空，这里是左半部分
		cover[rt<<1] = xor[rt<<1] = 0;
	}

	if (R > mid) {
		update(L, R, cmd, mid+1, r, rt<<1|1);
	} else if(cmd == 'I' || cmd == 'C') {
		//与前面相同，这里是右半部分
		cover[rt<<1|1] = xor[rt<<1|1] = 0;
	}
}

int main(int argc, char *argv[])
{
	int i;
	int l, r;
	int s, e;
	char cmd, a, b, flag;

	cover[1] = xor[1] = 0;

	while(scanf("%c %c%d,%d%c\n", &cmd, &a, &l, &r, &b) != EOF) {
		l <<= 1;
		r <<= 1;
		//这里为什么不作统一处理，对于开区间的情况都做++或者--?
		//看一下线段树的区间:[0,1,2,3,4,5,6,7],
		//其中0, 2，4，6代表的是闭区间的0,1，2，3
		// 1，3，5, 7代表的是开区间的0,1，2，3.
		//给定的区间(1,3), 那样应该是[3, 7]
		//按照处理原则，偶数为开区间，奇数为闭区间，因此会有这样的映射
		//为什么这里是[3,5]
		//假设情况为[1,2)和(2,3]的U输入
		//映射为[2,3]和[5,6]
		//如果左右区间使用相同的映射方法，结果应该是[2,5]和[5,6]
		//很明显，两边使用相同的映射方法时，显然不能保证正确性的...
		//因此实际映射到线段树之后，统一使用左闭右开的方法来保存，
		//而最后输出的时候，右半部分由于做了开放的让步，因此需要+1来保证正确性。
		if (a == '(')
			l++;
		if (b == ')')
			r--;

		if (l > r) {
			if (cmd == 'C' || cmd == 'I')
				cover[1] = xor[1] = 0;
		} else {
			update(l, r, cmd, 0, MAXN, 1);
		}
	}

	query(0, MAXN, 1);
	flag = 0;
	s = -1, e = 0;

	for (i = 0; i <= MAXN;i++) {
		if (hash[i]) {
			if (s == -1) {
				s = i;
			}
			e = i;
		} else {
			if (s != -1) {
				if (flag)
					printf(" ");
				flag = 1;
				//区间的右半部分在加入的时候，是两倍(闭区间)或者是2*r-1(开区间）
				//为了保证映射前后一致，右半部分区间做还原的时候都做+1处理
				//左半部分区间不作这样的处理，是因为转换的时候使用了2*r或者2*r+1,
				//映射回来时，直接/2没有任何影响。
				printf("%c%d,%d%c", s&1?'(':'[', s>>1, 
					(e+1)>>1, e&1?')':']');
			}

			s = -1;
		}
	}

	if (!flag) {
		printf("empty set\n");
	}

	return 0;
}



