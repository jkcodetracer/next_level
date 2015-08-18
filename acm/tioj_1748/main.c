/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年 8月12日 星期三 17时31分36秒 CST 
 *
 * find a k which has the maxmum divisors and is not greater than the 
 * given n.
 */
#include <stdio.h>

#define N (100)

int p_table[N >> 1] = {0};
int n_prime = 0;

unsigned long long n = 0;
unsigned long long ans = 0;
int ans_factors = 0;

int is_prime(int n)
{
	int i;
	for (i = 2; i * i <= n;i++) {
		if (n%i==0) {
			return -1;
		}
	}

	return n;
}

void init_p_table(int max)
{
	int i;

	for (i = 2; i <= max;i++) {
		if (i == is_prime(i)) {
			p_table[n_prime++] = i;
		}
	}
}

void dfs(int deps, unsigned long long tmp, int n_factors)
{
	int i;

	if (deps > 16)
		return ;

	if (n_factors > ans_factors) {
		ans = tmp;
		ans_factors = n_factors;
	}

	if (n_factors == ans_factors &&
	    ans > tmp) {
		ans = tmp;
	}

	for (i = 1 ; i < 60; i++) {
		if (n < tmp*p_table[deps])
			break;
		dfs(deps + 1, tmp*=p_table[deps], n_factors*(i+1));
	}
}

int main(int argc, char * argv[])
{
	int total;

	init_p_table(N);
	scanf("%d", &total);
	while(total--) {
		scanf("%lld", &n);

		ans = -1;
		ans_factors = 0;
		dfs(0, 1, 1);
		printf ("%lld %d\n", ans, ans_factors);
	}

	return 0;
}

