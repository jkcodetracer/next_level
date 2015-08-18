/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年 8月12日 星期三 10时56分05秒 CST 
 *
 * find the min k which has the greatest number of divisors
 * and not exceeding n. 
 */
#include <stdio.h>

#define N 100

int p_table[N >> 1] = {0};
int n_prime = 0;

unsigned long long ans = ~(unsigned long long)0;
int ans_facts = 0;
int n = 0;

int is_prime(int n)
{
	int i;
	for (i = 2; i * i <= n; i++) {
		if (n%i == 0) {
			return -1;
		}
	}

	return n;
}

void init_p_table(int n)
{
	int i;

	n_prime = 0;
	for(i = 2; i <= n; i++) {
		if ( i == is_prime(i)) {
			p_table[n_prime++] = i;
//			printf ("%d, ", i);
		}
	}
}

void dfs(int deps, unsigned long long tmp, int n_facts)
{
	int i = 0;

	if (deps >= n_prime)
		return;

	if (n_facts > ans_facts) {
		ans_facts = n_facts;
		ans = tmp;
	}

	if (n_facts == ans_facts &&
	   ans > tmp) {
		ans = tmp;
	}

	for (i = 1; i <= 63;i++) {
		if (n / p_table[deps] < tmp)
			break;
		dfs(deps + 1,  tmp*=p_table[deps], n_facts*(i+1));
	}
}

int main(int argc, char *argv[])
{
	init_p_table(N);

	while (1) {
		scanf("%d", &n);
		ans = ~(unsigned long long)0;
		ans_facts = 0;

		dfs(0, 1, 1);
		printf ("%lld\n", ans);
	}

	return 0;
}


