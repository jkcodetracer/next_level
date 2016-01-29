/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年11月29日 星期日 17时00分09秒 CST  
 *
 * 1 找到连续子串的最大值及子串的范围
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN (100024)
#define INF (100000)

int str[MAXN];
int head, tail;
int n, k;

void init()
{
	int i;
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d", &str[i]);
	}
}

void solve()
{
	int max = -INF;
	int sum = 0;
	int i, tmphead = 0;

	head = tail = 0;
	for (i = 0; i < n; i++) {
		sum += str[i];
		if (sum > max) {
			head = tmphead;
			max = sum;
			tail = i;
		} else if (sum <= 0) {
			sum = 0;
			tmphead = i + 1;
		}
	}

	printf("Case %d:\n", k);
	printf("%d %d %d\n", max,  head+1, tail+1);
}

int main(int argc, char*argv[])
{
	int total;
	k = 0;
	scanf("%d", &total);
	while(total--) {
		k++;
		init();
		solve();
	}
	return 0;
}
