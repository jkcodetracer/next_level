/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年11月 5日 星期四 08时43分57秒 CST 
 *
 * 1. 判断是否联通
 * 2. 判断是否存在欧拉通路
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN (32)
#define INV (-1)
#define ALF2IDX(al) ((al)-'a')

int indeg[MAXN];
int outdeg[MAXN];
int set[MAXN];
int flag[MAXN];
int n_edge;

void set_init()
{
	int i;

	for (i = 0; i < MAXN; i++) {
		set[i] = -1;
	}
}

int check_set(int n)
{
	int s, tmp;

	s = n;
	while (set[s] >= 0) {
		s = set[s];
	}

	while(s != n) {
		tmp = set[n];
		set[n] = s;
		n = tmp;
	}

	return s;
}

void set_set(int u, int v)
{
	int s1, s2;
	int tmp;

	if (u == v)
		return ;

	s1 = check_set(u);
	s2 = check_set(v);
	tmp = set[s1]+set[s2];

	if (set[s1] > set[s2]) {
		set[s2] = tmp;
		set[s1] = s2;
	} else {
		set[s1] = tmp;
		set[s2] = s1;
	}
}

void init()
{
	int i, len;
	int u,v;
	char str[32];

	memset(indeg, 0, sizeof(indeg));
	memset(outdeg, 0, sizeof(outdeg));
	memset(flag, 0, sizeof(flag));

	set_init();
	scanf("%d", &n_edge);
	for (i = 0; i < n_edge; i++) {
		scanf("%s", str);
		len = strlen(str);
		u = ALF2IDX(str[0]);
		v = ALF2IDX(str[len-1]);
		indeg[u]++;
		outdeg[v]++;
		flag[u] = 1;
		flag[v] = 1;
		set_set(u, v);
	}
}

void judge()
{
	int i;
	int begin, cur;
	int desc = 0;
	int odd_neg = 0, odd_pos = 0;
	//check set;
	for (i = 0; i < MAXN; i++) {
		if (flag[i]) {
			begin = check_set(i);
			break;
		}
	}

	for (i = 0; i < MAXN; i++) {
		if (flag[i]) {
			desc = indeg[i] - outdeg[i];
			if (desc == -1) {
				odd_neg++;
				continue;
			}

			if (desc == 1) {
				odd_pos++;
				continue;
			}

			cur = check_set(i);
			if (desc != 0 || begin != cur) {
				printf("The door cannot be opened.\n");
				return;
			}
		}
	}

	if (odd_neg == odd_pos &&
	(odd_neg == 1||odd_neg==0)) {
		printf("Ordering is possible.\n");
	} else {
		printf("The door cannot be opened.\n");
	}
}

int main(int argc, char* argv[])
{
	int total;

	scanf("%d", &total);
	while(total--) {
		init();
		judge();
	}

	return 0;
}



