/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年 9月22日 星期二 23时49分53秒 CST 
 *
 * find the MST
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXN	(100)

typedef struct edge_st{
	int u;
	int v;
	double weight;
} edge_st;

typedef struct vetex_st{
	double x;
	double y;
}vetex_st;

edge_st edges[MAXN*MAXN];
int n_edges = 0;
vetex_st vetex[MAXN];
int n_vetex = 0;
int union_list[MAXN];

void union_init(int max)
{
	int i;

	for(i = 0; i < max ;i++) {
		union_list[i] = -1;
	}
}

int union_find(int x)
{
	int s, tmp;

	s = x;
	while(union_list[s] >= 0) {
		s = union_list[s];
	}

	while(s != x) {
		tmp = union_list[x];
		union_list[x] = s;
		x = tmp;
	}

	return s;
}

void union_set(int a, int b)
{
	int s1, s2;
	int tmp;

	s1 = union_find(a);
	s2 = union_find(b);
	tmp = union_list[s1] + union_list[s2];

	if (union_list[s1] > union_list[s2]) {
		union_list[s1] = s2;
		union_list[s2] = tmp;
	} else {
		union_list[s2] = s1;
		union_list[s1] = tmp;
	}
}

void kruskal()
{
	int i;
	int connected = 0;
	double sum_w = 0.0;

	union_init(n_vetex);

	for(i = 0; i< n_edges; i++) {
		if(union_find(edges[i].u) != union_find(edges[i].v)) {
			sum_w += edges[i].weight;
			union_set(edges[i].u, edges[i].v);
			connected ++;
		}

		if (connected == n_vetex - 1) {
			printf("The minimal distance is:%.2f\n", sum_w);
			return ;
		}
	}

	printf("no such a route...\n");
}

int cmp(const void *a, const void *b)
{
	edge_st *pa = (edge_st*)a;
	edge_st *pb = (edge_st*)b;

	if (pa->weight > pb->weight) 
		return 1;
	else 
		return -1;
}

int main(int argc, char* argv[])
{
	int i, j;
	double d_x, d_y;

	while(1) {
		scanf("%d", &n_vetex);
		if (n_vetex == 0) {
			break;
		}

		for(i = 0; i < n_vetex; i++) {
			scanf("%lf %lf", &vetex[i].x, &vetex[i].y);
		}
		printf("%d\n", n_vetex);

		n_edges = 0;
		for(i = 0; i < n_vetex; i++) {
			for(j = i+1; j < n_vetex; j++) {
				d_x = vetex[i].x - vetex[j].x;
				d_y = vetex[i].y - vetex[j].y;
				edges[n_edges].u = i;
				edges[n_edges].v = j;
				edges[n_edges].weight = sqrt(d_x*d_x + d_y*d_y);

				n_edges++;
			}
		}

		qsort(edges, n_edges, sizeof(edges[0]), cmp);
		kruskal();
	}

	return 0;
}





