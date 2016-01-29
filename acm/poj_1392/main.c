/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年11月12日 星期四 16时19分03秒 CST  
 *
 * 使用fluery算法发现一条欧拉路径，然后输出第n条边
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXN (1024)

typedef struct edge_st{
	int u,v;
	int weight;
	int idx;
	int valid;
	int next;
	int renext;
}edge_st;

typedef struct stack_st{
	int top;
	int ring[MAXN];
}stack_st;

int table[MAXN];
int retable[MAXN];
int n_vetex;
int n_edge;
edge_st edges[MAXN];
int n, k;

void s_init(stack_st *ps)
{
	ps->top = -1;
	memset(ps->ring, 0, sizeof(int)*MAXN);
}

void s_push(stack_st *ps, int idx)
{
	ps->ring[++ps->top] = idx;
}

int s_pop(stack_st *ps)
{
	return ps->ring[ps->top--];
}

int s_empty(stack_st *ps)
{
	return ps->top < 0;
}

void add_edge(int u, int v, int weight)
{
	edge_st *pe;

	pe = &edges[n_edge++];
	pe->u = u;
	pe->v = v;
	pe->weight = weight;
	pe->valid = 1;
	pe->idx = n_edge - 1;

	pe->next = table[u];
	table[u] = n_edge - 1;

	pe->renext = retable[v];
	retable[v] = n_edge - 1;
}

void init()
{
	int i, max;
	int u,v;

	for (i = 0;i < MAXN; i++) {
		table[i] = -1;
		retable[i] = -1;
	}

	max = powf(2, n);
	n_vetex = powf(2, n-1);

	for (i = 0;i < max; i++) {
		u = i >> 1;
		v = i & ((1 << (n-1)) - 1);
		add_edge(u, v, i);
	}

	for (i = 0; i<n_vetex; i++) {
		u = retable[i];
		edge_st *pe;
		while(1) {
			pe = &edges[u];
			u = pe->renext;
			if (u == -1)
				break;
		}
	}
}

void dfs(stack_st *ps, int cur, int cur_vetex)
{
	int reidx;
	edge_st *pe;

	s_push(ps, cur);
	pe = &edges[cur];
	reidx = retable[cur_vetex];
	if (reidx == -1)
		return ;

	while(1) {
		pe = &edges[reidx];
		if (pe->valid) {
			pe->valid = 0;
			dfs(ps, pe->idx, pe->u);
			break;
		}

		reidx = pe->renext;
		if (reidx == -1)
			break;
	}
}

void fluery()
{
	int path;
	int cur, idx, total = 0;
	edge_st *pe;
	stack_st pst;

	total = 0;
	s_init(&pst);
	s_push(&pst, 0);
	while(!s_empty(&pst)) {
		path = 0;
		cur = s_pop(&pst);
		pe = &edges[cur];
		idx = table[pe->v];
		if (idx == -1) {
			path = 0;
		} else {
			while(1) {
				pe = &edges[idx];
				if (pe->valid){
					path = 1;
					break;
				}

				if (pe->next == -1) {
					path = 0;
					break;
				}

				idx = pe->next;
			}
		}

		if (path == 0) {
			if (total == k) {
				printf("%d\n", edges[cur].weight);
				break;
			}
			total++;
		} else {
			dfs(&pst, cur, edges[cur].v);
		}
	}
}

int main(int argc, char* argv[])
{
	while(1) {
		scanf("%d %d", &n, &k);
		if (n == 0 && k == 0)
			break;
		init();
		fluery();
	}

	return 0;
}




