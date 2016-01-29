/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年11月 5日 星期四 12时43分31秒 CST 
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN (2000)

typedef struct name_st{
	char str[16];
}name_st;

int inde[MAXN];
int outde[MAXN];
int set[MAXN];
int n_name;
name_st names[MAXN];

int find_set(int n)
{
	int s,tmp;
	s = n;
	while (set[s] >= 0) {
		s = set[s];
	}

	while(s!=n) {
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
		return;

	s1 = find_set(u);
	s2 = find_set(v);
	if (s1 == s2) 
		return ;

	tmp = set[s1] + set[s2];
	if (set[s1] > set[s2]) {
		set[s2] = tmp;
		set[s1] = s2;
	} else {
		set[s1] = tmp;
		set[s2] = s1;
	}
}

void init_set()
{
	int i;
	for (i = 0; i < MAXN ;i++) {
		set[i] = -1;
	}
}

int find_name(char *str)
{
	int i;
	name_st *pn;

	for (i = 0; i< n_name; i++) {
		pn = &names[i];
		if (!strcmp(pn->str, str)) {
			return i;
		}
	}

	pn = &names[n_name++];
	strcpy(pn->str, str);

	return n_name-1;
}

void init()
{
	int ret;
	int u,v, i,n;
	char str1[16], str2[16];

	memset(inde, 0, sizeof(inde));
	memset(outde, 0, sizeof(outde));
	
	init_set();
	n_name = 0;
	scanf("%d", &n);
	for (i = 0;i < n; i++){
		ret = scanf("%s %s", str1, str2);
		if (ret != 2)
			break;
		u = find_name(str1);
		v = find_name(str2);
		inde[u]++;
		outde[v]++;

		set_set(u,v);
	}
}

void judge()
{
	int i, begin;
	int min = 0, max = 0;
	int de;

	begin = find_set(0);
	for (i = 0; i < n_name; i++) {
		if (begin != find_set(i)) {
			printf("Impossible\n");
			return;
		}
	}

	for (i = 0; i < n_name; i++) {
		de = inde[i] - outde[i];
		if (de == 0) {
			continue;
		}

		if (de == 1) {
			max++;
			continue;
		}

		if (de == -1) {
			min++;
			continue;
		}

		printf("Impossible\n");
		return ;
	}

	if (max == min &&
	(max == 1 || max == 0)) {
		printf("Possible\n");
	} else {
		printf("Impossible\n");
	}

	return ;
}

int main(int argc, char* argv[])
{
	init();
	judge();
	return 0;
}


