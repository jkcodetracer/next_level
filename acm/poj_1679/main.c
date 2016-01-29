/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年10月10日 星期六 18时58分54秒 CST  
 *
 * judge a map have the unique MST, use the kruskal alg
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN (32)
#define MAXE (1024)

typedef struct edge_st{
	int u;
	int v;
	int weight;
	char used;
	char del;
	char equal;
}edge_st;

int unions[MAXN];
edge_st edges[MAXE];
int n_edges;
int n_vetex;

int cmp(const void *a, const void *b)
{
	edge_st *pa = (edge_st*)a;
	edge_st *pb = (edge_st*)b;

	if (pa->weight > pb->weight) {
		return 1;
	} else {
		return -1;
	}
}

void union_init(int n)
{
	int i;
	for(i=0;i < n; i++) 
		unions[i] = -1;
}

void set_equal(int n)
{
	int i, last_weight, last_idx;

	last_idx = 0;
	last_weight = edges[0].weight;
	for(i = 1; i < n; i++) {
		if (edges[i].weight == last_weight) {
			edges[i].equal = 1;
			edges[last_idx].equal = 1;
		} else {
			last_weight = edges[i].weight;
			last_idx = i;
		}
	}
}

void init()
{
	int i;
	edge_st *pe;

	scanf("%d %d", &n_vetex, &n_edges);
	for (i=0; i < n_edges; i++) {
		pe = &edges[i];
		scanf("%d %d %d", &pe->u, &pe->v, &pe->weight);
		pe->del = 0;
		pe->used = 0;
		pe->equal = 0;
	}

	qsort(edges, n_edges, sizeof(edges[0]), cmp);
	set_equal(n_edges);
}

int union_find(int n)
{
	int tmp;
	int s = n;

	while(unions[s] >= 0) {
		s = unions[s];
	}

	while(n != s) {
		tmp = unions[n];
		unions[n] = s;
		n = tmp;
	}

	return s;
}

void union_set(int u, int v)
{
	int s1, s2;
	int tmp;

	s1 = union_find(u);
	s2 = union_find(v);
	tmp = unions[s1] + unions[s2];

	if (unions[s1] > unions[s2]) {
		unions[s1] = s2;
		unions[s2] = tmp;
	} else {
		unions[s2] = s1;
		unions[s1] = tmp;
	}
}

int kruskal(int reuse)
{
	int i;
	int sum = 0, total = 0;
	edge_st *pe;

	union_init(n_vetex+1);
	for (i = 0; i < n_edges; i++) {
		pe = &edges[i];
		if (pe->del)
			continue;

		if (union_find(pe->u) != union_find(pe->v)) {
			union_set(pe->u, pe->v);
			sum += pe->weight;
			if (!reuse)
				pe->used = 1;
			total++;
		}

		if (total == n_vetex-1) {
			return sum;
		}
	}

	return -1;
}

int main(int argc, char* argv[])
{
	int i;
	int total;
	int mst1, mst2;

	scanf("%d", &total);
	while(total--) {
		init();
		mst1 = kruskal(0);
		mst2 = -1;

		for(i = 0; i < n_edges; i++) {
			if (edges[i].used && edges[i].equal) {
				edges[i].del = 1;
				mst2 = kruskal(1);
				if (mst2 == mst1)
					break;
				edges[i].del = 0;
			}
		}

		if (mst2 == mst1) {
			printf("Not Unique!\n");
		} else {
			printf("%d\n", mst1);
		}
	}

	return 0;
}


