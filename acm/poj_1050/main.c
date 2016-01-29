/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年11月29日 星期日 18时32分43秒 CST  
 *
 * 1. 类似于在一个串中找到和最小的子串的问题，这里
 * 上升了一维而已。
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXN (128)
#define INF 1000

int matrix[MAXN][MAXN];
int sum[MAXN];
int n;

void init()
{
	int i,j;
	scanf("%d", &n);
	for (i = 0; i < n; i++){
		for (j = 0; j< n; j++) {
			scanf("%d", &matrix[i][j]);
		}
	}
}

int getmax(int *arr, int total)
{
	int i;
	int max = -INF;
	int tmp = 0;

	for (i = 0;i < total; i++) {
		tmp += arr[i];
		if (tmp > max) {
			max = tmp;
		} else if(tmp < 0) {
			tmp = 0;
		}
	}

	return max;
}

void solve()
{
	int i, j, k; 
	int tmp_sum, max; 

	max = -INF;
	for (i = 0; i < n; i++) {
		for (k = 0; k < n; k++) {
			sum[k] = 0;
		}

		for (j = i; j < n; j++) {
			for (k = 0; k < n; k++) {
				sum[k] += matrix[j][k];
			}
			tmp_sum = getmax(sum, n);
			if (tmp_sum > max) {
				max = tmp_sum;
			}
		}
	}

	printf("%d\n", max);
}

int main(int argc, char* argv[])
{
	init();
	solve();

	return 0;
}


