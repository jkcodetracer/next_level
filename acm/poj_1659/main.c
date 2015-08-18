/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年 8月 2日 星期日 00时07分12秒 CST
 *
 * discript your detail info.
 */

#include <stdio.h>
#include <string.h>

#define N 1024

int deg[N] = {0};

int get_int()
{
	int n = 0;
	char c = 0;

	while (c < 33)
		c = getchar_unlocked();

	while (c <= '9' && c >= '0') {
		n = (n << 3) + (n << 1) + c - '0';
		c = getchar_unlocked();
	}

	return n;
}

int cmp(const void *a, const void *b)
{
	return *(int*)b - *(int*)a;
}

int hh_func(int n)
{
	int i = 0, j = 0;

	for (i = 0; i< n; i++) {
		qsort(deg+i, n-i, sizeof(int), cmp);

		if (deg[i] + i >= n) {
			return 0;
		}

		for (j = i+1; j <= deg[i] + i; j++) {
			deg[j]--;
			if (deg[j] < 0) {
				return 0;
			}
		}
	}

	return 1;
}

int main(int argc, char *argv[])
{
	int total = 0, i = 0, n = 0;

	total = get_int();
	while (total--) {
		memset (deg, 0, sizeof(int) * N);

		n = get_int();
		for (i = 0; i < n; i++) {
			deg[i] = get_int();
		}

		if(hh_func(n)) {
			printf ("YES\n");
		} else {
			printf ("NO\n");
		}
	}

	return 0;
}
