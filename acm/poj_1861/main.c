/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年 9月23日 星期三 17时04分15秒 CST 
 *
 * find the MST
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN	(1024)

typedef struct edge_st{
	int u;
	int v;
	int weight;
}edge_st;

edge_st edges[MAXN];
int n_vetex, n_edge;
int unions[MAXN] = {0};

int cmp(const void *a, const void *b)
{
	edge_st *pa = (edge_st *)a;
	edge_st *pb = (edge_st *)b;

	return pa->weight - pb->weight;
}

void union_init(int max)
{
	int i;
	for(i = 0;i <max ;i++) {
		unions[i] = -1;
	}
}

int union_find(int n)
{
	int s, tmp;
	s = n;
	while(unions[s] >= 0) {
		s = unions[s];
	}

	while(s!=n) {
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
	tmp = unions[s1]+unions[s2];

	if (unions[s1]>unions[s2]) {
		unions[s1] = s2;
		unions[s2] = tmp;
	} else {
		unions[s2] = s1;
		unions[s1] = tmp;
	}
}

void kruskal()
{
	int i, j;
	int que[MAXN] = {0};
	int n_que = 0;
	edge_st *pe;

	union_init(n_vetex);

	for(i = 0; i < n_edge; i++) {
		pe = &edges[i];
		if (union_find(pe->u) != union_find(pe->v)) {
			union_set(pe->u, pe->v);
			que[n_que++] = i;
		}

		if (n_que == n_vetex - 1) {
			printf("%d\n%d\n", edges[que[n_que-1]].weight, n_que);
			for(j = 0; j < n_que; j++){
				pe = &edges[que[j]];
				printf("%d %d\n", pe->u, pe->v);
			}

			return;
		}
	}
	
	printf("no result\n");
}

int main(int argc, char* argv[])
{
	int i;
	edge_st *pe;

	scanf("%d %d", &n_vetex, &n_edge);
	for(i = 0; i < n_edge; i++) {
		pe = &edges[i];
		scanf("%d %d %d", &pe->u, &pe->v, &pe->weight);
	}

	qsort(edges, n_edge, sizeof(edges[0]), cmp);
	kruskal();

	return 0;
}


