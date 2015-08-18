/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年 8月12日 星期三 23时04分10秒 CST 
 *
 * 1. 枚举反素数
 * 2. 构造表来表示含有K个非因子的最小的N
 */
#include <stdio.h>

#define N 100
#define MAXK (50000)


int p_table[N >> 1] = {0};
int n_prime = 0;
int k_table[MAXK] = {0};
unsigned long long int ans = ~(unsigned long long)0;
unsigned long long int INF = (((unsigned long long)1)<<62) + 1;
int k = 0;

int is_prime(int n)
{
	int i;

	for (i = 2; i*i <= n;i++) {
		if (n%i == 0) 
			return -1;
	}

	return n;
}

void init_table(int n)
{
	int i;

	n_prime = 0;
	for (i = 2; i <= n;i++) {
		if (i == is_prime(i)) {
			p_table[n_prime++] = i;
		}
	}
}

//calc all the possible solution Type 1
void init_k_table()
{
	int i, j;

	for (i = 1; i < MAXK; i++)
		k_table[i] = i;

	for (i = 1; i < MAXK; i++) {
		for (j = i; j < MAXK; j+=i) {
			k_table[j]--;
		}
		if(!k_table[k_table[i]])
			k_table[k_table[i]] = i;
		k_table[i] = 0;
	}
}

void dfs(int deps, unsigned long long tmp, int n_facts)
{
	int i, new_facts;

	if(deps >= 16)
		return;

	if(k == n_facts && ans > tmp) {
		ans = tmp;
	}

	for (i = 1; i <= 60; i++) {
		new_facts = n_facts * (i+1);
		tmp *= p_table[deps];

		if (ans < tmp || new_facts > k)
			break;
		//这里做个剪枝，因为k最终要与n_facts结果相等才有
		//意义,而n_facts是通过不断相乘得到的，也就是说
		//正确分支上的n_facts一定可以被k整除
		if (k%new_facts == 0)
			dfs(deps+1, tmp, new_facts);
	}
}

int main(int argc, char* argv[])
{
	int type, n_case;

	init_k_table();
	init_table(N);

	scanf("%d", &n_case);
	while (n_case--) {
		scanf("%d %d", &type, &k);
		ans = INF;

		if (type) {
			ans = k_table[k];
		} else {
			dfs(0, 1, 1);
		}

		if (ans == 0) puts("Illegal\n");
		else if (ans >= INF) puts("INF\n");
		else printf ("%lld\n", ans);
	}

	return 0;
}



