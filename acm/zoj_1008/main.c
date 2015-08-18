/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年 8月 3日 星期一 09时30分24秒 CST
 *
 * bruteforce ...
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 5

int element[N*N][4] = {{0}};
int result[N*N] = {0};
int stat[N*N] = {0};

int real_n = 0;
int n_stat = 0;

int dfs(int cur_n)
{
	int i = 0;

	if (cur_n == real_n * real_n)
		return 1;

	for (i = 0; i < n_stat; i++) {
		if (stat[i] == 0)
			continue;

		if (cur_n - real_n >= 0) {
			if (element[result[cur_n - real_n]][2] !=
				element[i][0])
				continue;
		}

		if (cur_n % real_n > 0) {
			if (element[result[cur_n - 1]][1] !=
			    element[i][3]) {
				continue;
			}
		}

		result[cur_n] = i;
		stat[i]--;
		if (dfs(cur_n + 1))
			return 1;

		stat[i]++;
	}

	return 0;
}

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

int main(int argc, char *argv[])
{
	int i, j, total_n;
	int up, right, down, left;

	while (1) {
		real_n = get_int();
		if (real_n == 0)
			break;

		n_stat = 0;
		total_n = real_n * real_n;

		memset(stat, 0, sizeof(int)*(N*N));
		for (i = 0; i < total_n; i++) {
			scanf("%d %d %d %d", &up, &right, &down, &left);

			for(j = 0; j < n_stat; j++) {
				if (up == element[j][0] &&
				    right == element[j][1] &&
				    down == element[j][2] &&
				    left == element[j][3])
					break;
			}

			if(j == n_stat){
				element[j][0] = up;
				element[j][1] = right;
				element[j][2] = down;
				element[j][3] = left;

				stat[n_stat++]++;
			} else {
				stat[j]++;
			}
		}

		if (dfs(0))
			printf ("YES\n");
		else
			printf ("NO\n");
	}

	return 0;
}

