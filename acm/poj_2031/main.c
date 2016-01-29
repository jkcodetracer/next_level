/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年 9月29日 星期二 07时34分18秒 CST 
 *
 * building a space station, an MST problem, with kruskal
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXN (128)
#define MAXV (100*100)

typedef struct edge_st{
	int u;
	int v;
	double weight;
}edge_st;

typedef struct node_st {
	float x,y,z;
	float cir;
}node_st;

edge_st edges[MAXV];
int n_edge;
node_st nodes[MAXN];
int n_vetex;
int unions[MAXN];

int cmp(const void *a, const void *b)
{
	edge_st *pa = (edge_st*)a;
	edge_st *pb = (edge_st*)b;

	if (pa->weight > pb->weight) {
		return 1;
	}else {
		return -1;
	}
}

double calc_weight(node_st *pf, node_st *pt)
{
	float dx,dy,dz;
	double dis;

	dx = pf->x - pt->x;
	dy = pf->y - pt->y;
	dz = pf->z - pt->z;

	dis = sqrt(dx*dx+dy*dy+dz*dz);
	dis = dis - pf->cir- pt->cir;
	if (dis <= 0.001) {
		return 0.0;
	}

	return dis;
}

void init_edges()
{
	int i, j;
	node_st *pf,*pt;
	edge_st *pe;

	n_edge = 0;
	for(i = 0; i < n_vetex; i++) {
		pf = &nodes[i];
		for(j = i+1; j < n_vetex; j++) {
			pt = &nodes[j];
			pe = &edges[n_edge++];
			pe->weight = calc_weight(pf, pt);
			pe->u = i;
			pe->v = j;
		}
	}

	qsort(edges, n_edge, sizeof(edges[0]), cmp);
}

void union_init(int max)
{
	int i;

	for(i = 0; i < max; i++) {
		unions[i] = -1;
	}
}

int union_find(int n)
{
	int s, tmp;

	s = n;
	while(unions[s] >= 0) 
		s = unions[s];

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
	tmp = unions[s1] + unions[s2];

	if(unions[s1] > unions[s2]) {
		unions[s1] = s2;
		unions[s2] = tmp;
	} else {
		unions[s2] = s1;
		unions[s1] = tmp;
	}
}

void kruskal()
{
	int i;
	int count = 0;
	double weight = 0.0;
	edge_st *pe = NULL;

	union_init(n_vetex);

	for(i = 0; i < n_edge; i++) {
		pe = &edges[i];
		if(union_find(pe->u) != union_find(pe->v)) {
			union_set(pe->u, pe->v);
			weight += pe->weight;
			count++;

			if(count == n_vetex -1){
				printf("%.3f\n", weight);
				return ;
			}
		}
	}
}

int main(int argc, char* argv[])
{
	int i;
	node_st *pn;

	while (1) {
		scanf("%d", &n_vetex);
		if (n_vetex == 0)
			break;

		for(i = 0; i < n_vetex; i++) {
			pn = &nodes[i];
			scanf("%f %f %f %f", &pn->x, &pn->y, &pn->z, &pn->cir);
		}

		init_edges();
		kruskal();
	}

	return 0;
}


