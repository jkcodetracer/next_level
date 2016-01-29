/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年 9月28日 星期一 23时06分01秒 CST 
 *
 * use kruskal alg to find the MST
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN	(1024)
#define MAXW	(32)

typedef struct edge_st{
	int from;
	int to;
	int weight;
}edge_st;

edge_st edges[MAXN];
int n_vetex = 0;
int n_edge = 0;
int unions[MAXW];

int cmp(const void *a, const void *b)
{
	edge_st *pa = (edge_st *)a;
	edge_st *pb = (edge_st *)b;

	if (pa->weight > pb->weight) {
		return 1;
	} else {
		return -1;
	}
}

void union_init(int max)
{
	int i;

	for(i = 0; i < max ;i++) {
		unions[i] = -1;
	}
}

int union_find(int n)
{
	int s, tmp;
	s = n;
	while(unions[s] >= 0)
		s = unions[s];
	while(s != n) {
		tmp = unions[n];
		unions[n] = s;
		n = tmp;
	}

	return s;
}

void union_set(int a, int b)
{
	int s1, s2;
	int tmp;

	s1 = union_find(a);
	s2 = union_find(b);
	tmp = unions[s1] + unions[s2];

	if (unions[s1] > unions[s2]) {
		unions[s1] = s2;
		unions[s2] = tmp;
	} else {
		unions[s2] = s1;
		unions[s1] = tmp;
	}
}

void kruskal()
{
	int i, count = 0;
	int total = 0;
	edge_st *pe;

	union_init(n_vetex);

	for(i = 0; i < n_edge; i++) {
		pe = &edges[i];
		if (union_find(pe->from) != union_find(pe->to)) {
			union_set(pe->from, pe->to);
			total += pe->weight;
			count++;
			if(count == n_vetex - 1) {
				printf("%d\n", total);
				return ;
			}
		}
	}
}

int main(int argc, char* argv[])
{
	int i,j;
	char from[5],to[5];
	int total, weight;
	edge_st *pe;

	while(1) {
		scanf("%d", &n_vetex);
		if(n_vetex == 0)
			break;

		n_edge = 0;
		for(i = 0; i < n_vetex-1; i++) {
			scanf("%s%d", from, &total);
			for(j = 0; j < total; j++) {
				pe = &edges[n_edge++];
				scanf("%s%d", to, &weight);
				pe->from = from[0] - 'A';
				pe->to = to[0] - 'A';
				pe->weight = weight;
			}
		}
		qsort(edges, n_edge, sizeof(edges[0]), cmp);
		kruskal();
	}

	return 0;
}

