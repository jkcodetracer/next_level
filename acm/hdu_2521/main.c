/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年 8月15日 星期六 00时33分47秒 CST 
 *
 *  反素数， 限定了区间的
 */
#include <stdio.h>

#define MAXN	100
#define LIMIT	6000

int p_table[MAXN >> 1] = {0};
int n_prime = 0;

int ans = 0;
int ans_fact = 0;
int a,b;

void dfs(int deps, int tmp, int n_facts)
{
	int i = 0;

	if (deps >= 16)
		return;

	if (tmp >= a && tmp <= b &&
	    n_facts > ans_fact) {
		ans = tmp;
		ans_fact = n_facts;
	}

	if (n_facts == ans_fact &&
	    ans > tmp) {
		ans = tmp;
	}

	for (i = 1; i < 60; i++) {
		tmp *= p_table[deps];
		if (tmp > b)
			break;

		dfs(deps+1, tmp, n_facts*(i+1));
	}
}

int is_prime(int n)
{
	int i;

	if (n%2 == 0) {
		return -1;
	}

	for (i = 3; i * i <= n ;i+=2) {
		if (n%i == 0) {
			return -1;
		}
	}

	return n;
}

void init_table(int n)
{
	int i;

	n_prime = 0;
	p_table[n_prime++] = 2;
	for (i = 3;i <= n; i++) {
		if (i == is_prime(i)) {
			p_table[n_prime++] = i;
		}
	}
}

int main(int argc, char* argv[])
{
	int n_case;

	init_table(MAXN);
	scanf("%d", &n_case);
	while(n_case--) {
		scanf("%d %d", &a, &b);

		ans = LIMIT;
		ans_fact = 0;

		dfs(0, 1, 1);
		printf ("%d\n", ans);
	}

	return 0;
}
