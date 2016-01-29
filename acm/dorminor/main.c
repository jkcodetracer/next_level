/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年11月11日 星期三 12时45分29秒 CST  
 *
 * 1. 使用dfs确定欧拉路径
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXE	(1024)
#define MAXN	(16)

#define NEG	(-1)
#define POS	(1)

typedef struct edge_st{
	int u,v, dir;
	int edge_num;
	int idx;
	int next;
}edge_st;

typedef struct vet_st{
	int valid;
	int next;
}vet_st;

int n_edge;
edge_st edges[MAXE];
int n_vetex;
vet_st vetexs[MAXN];
int used[MAXE];
int n_idx;
int deg[MAXN];
int begin;

int sets[MAXN];
int stack[MAXE];
int top;

void init_set()
{
	int i = 0;

	for (i = 0 ;i < MAXN; i++) {
		sets[i] = -1;
	}
}

int find_par(int n)
{
	int s, tmp;

	s = n;
	while(sets[s] >= 0) {
		s = sets[s];
	}

	while(s != n) {
		tmp = sets[n];
		sets[n] = s;
		n = tmp;
	}
	return s;
}

void setsets(int u, int v)
{
	int s1,s2, tmp;

	if (u == v)
		return ;

	s1 = find_par(u);
	s2 = find_par(v);
	tmp = sets[s1] + sets[s2];
	if (sets[s1] > sets[s2]) {
		sets[s1] = s2;
		sets[s2] = tmp;
	} else {
		sets[s2] = s1;
		sets[s1] = tmp;
	}
}

void add_edge(int u, int v, int dir, int idx)
{
	vet_st *pv;
	edge_st *pe;

	pe = &edges[n_edge++];
	pe->u = u;
	pe->v = v;
	pe->dir = dir;
	pe->idx = idx;
	pe->edge_num = n_edge-1;

	pv = &vetexs[u];
	pv->valid = 1;
	pe->next = pv->next;
	pv->next = n_edge-1;
}

int check_path()
{
	int i;
	int first_par;
	int odd_node = 0;
	vet_st *pv;

	first_par = find_par(begin);
	for (i = 1; i <= n_vetex; i++) {
		pv = &vetexs[i];
		if (pv->valid && first_par != find_par(i)) {
			return 1;
		}
	}

	for (i = 1; i <= n_vetex; i++) {
		pv = &vetexs[i];
		if (pv->valid && deg[i]%2 == 1) {
			begin = i;
			odd_node++;
		}
	}

	if (odd_node == 0 || odd_node == 2) {
		return 1;
	} else {
		return 0;
	}
}

int init()
{
	int i, u, v;
	int max = 0;

	for (i = 0; i < MAXN; i++) {
		vetexs[i].next = -1;
		vetexs[i].valid = 0;
	}

	n_vetex = 6;
	begin = 0;
	memset(deg, 0, sizeof(deg));
	memset(used, 0, sizeof(used));
	memset(stack, 0, sizeof(stack));
	top = 0;
	n_idx = 0;
	n_edge = 0;
	init_set();

	scanf("%d", &max);
	for(i = 1; i <= max; i++) {
		scanf("%d %d", &u, &v);
		add_edge(u, v, POS, i);
		add_edge(v, u, NEG, i);
		deg[u]++;
		deg[v]++;
		setsets(u, v);

		begin = u;
		n_idx++;
	}

	return max;
}

int dfs_path(int cur, int dep)
{
	int idx;
	edge_st *pe;

	if (dep >= n_idx)
		return 1;

	idx = vetexs[cur].next;
	pe = &edges[idx];
	while(1) {
		if (used[pe->idx]) {
			if(pe->next == -1)
				return 0;
			pe = &edges[pe->next];
			continue;
		}

		stack[dep] = pe->edge_num;
		used[pe->idx] = 1;
		if (dfs_path(pe->v, dep+1)) {
			return 1;
		}
		used[pe->idx] = 0;
		stack[dep] = 0;

		if (pe->next == -1) {
			break;
		}

		pe = &edges[pe->next];
	}

	return 0;
}

void dump_card()
{
	int i;
	edge_st *pe;

	for (i = 0; i < n_idx; i++) {
		pe = &edges[stack[i]];
		printf("%d%c\n", pe->idx, (pe->dir == POS)?'+':'-');
	}

	printf("\n");
}

int main(int argc, char * argv[])
{
	while(init()) {
		if(check_path() && 
		  dfs_path(begin, 0)) {
			dump_card();
		} else {
			printf("no solution\n");
		}
	}

	return 0;
}

