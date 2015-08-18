/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年 8月 1日 星期六 20时25分54秒 CST
 *
 * 1. take all the string into an direction graph, the first alf is out deg, the
 * last alf is in deg.
 * 2. judge where the graph is an eura graph, 
 *	a. check the union state.
 *	b. check the in|out deg for every node.
 * 3. find the eura path.
 *	we should sort each string, and make sure they are in lexical order.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 26
#define SLEN 32
#define SMAX 1024
#define STACK_LEN 1024

#define SWAP(a, b) {	\
		int tmp_n ;\
		tmp_n = a;\
		a = b;\
		b = tmp_n;\
	}

struct edge{
	int str_idx;
	int next_edge;
	int next_node;
};

char str[SMAX][SLEN] = {{0}};
struct edge edges[SMAX];
int node[N] = {0};

int father[N] = {0};
int in[N] = {0};
int out[N] = {0};

int start_node = 0;
int stack[STACK_LEN] = {0};
int edge_flag[SMAX] = {0};

int n_edge = 0;
int stack_top = 0;

int get_anc(int n)
{
	if (n == father[n]) {
		return n;
	}
	return father[n] = get_anc(father[n]);
}

void merge(int a, int b)
{
	father[get_anc(a)] = get_anc(b);
}

void init()
{
	int i = 0;

	memset (in, 0, sizeof(int) * N);
	memset (out, 0, sizeof(int) * N);
	memset (edge_flag, 0, sizeof(int) * N);
	memset (node, -1, sizeof(int) * N);

	for (i = 0; i < N; i++) 
		father[i] = i;

	stack_top = 0;
	n_edge = 0;
}

void add_edge(int s_out, int s_in, int idx)
{
	int tmp = 0, str_a, str_b;

	edges[n_edge].str_idx = idx;
	edges[n_edge].next_edge = node[s_out];
	edges[n_edge].next_node = s_in;
	node[s_out] = n_edge++;

	tmp = node[s_out];
	while (edges[tmp].next_edge != -1) {
		str_a = edges[tmp].str_idx;
		str_b = edges[edges[tmp].next_edge].str_idx;

		if (strcmp(str[str_a], str[str_b]) > 0) {
			SWAP(edges[tmp].str_idx, edges[edges[tmp].next_edge].str_idx);
			SWAP(edges[tmp].next_node, edges[edges[tmp].next_edge].next_node);
		}
		tmp = edges[tmp].next_edge;
	}
}

void input()
{
	int i = 0;
	int s_in, s_out;
	int total_edge = 0;

	scanf ("%d", &total_edge);
	for (i = 0; i < total_edge; i++) {
		scanf("%s", str[i]);
		s_out = str[i][0] - 'a';
		s_in = str[i][strlen(str[i]) - 1] - 'a';

		add_edge(s_out, s_in, i);
		merge(s_out, s_in);
		in[s_in]++;
		out[s_out]++;
	}

}

void dfs(int cur_node, int used_edge)
{
	int i = 0;
	//edge_flag[used_edge] = 1;

	for (i = node[cur_node]; i != -1; i = edges[i].next_edge) {
		if (!edge_flag[i]) {
		edge_flag[used_edge] = 1;

			dfs(edges[i].next_node, i);
		}
	}

	stack[stack_top++] = used_edge;
}

void get_eura_path()
{
	dfs(start_node, n_edge);
}

void output()
{
	stack_top--;
	printf("%s", str[edges[stack[--stack_top]].str_idx]);

	while (stack_top > 0) {
		printf(".%s", str[edges[stack[--stack_top]].str_idx]);
	}

	printf ("\n");
}

int exist()
{
	int i = 0;
	int count = 0, count2 = 0;

	//1. all node are unioned
	for (i = 0; i < N; i++) {
		if (father[i] == i && (in[i]|out[i]))
			count++;
	}

	if (count > 1) {
		return 0;
	}

	//2. there is an erua path
	start_node = -1;
	count = 0;
	for (i = 0; i < N; i++) {
		if (abs(in[i] - out[i]) > 1)
			return 0;

		if (in[i] - out[i] == 1)
			count++;

		if (out[i] - in[i] == 1) {
			start_node = i;
			count2++;
		}
	}

	if (count > 1 || count2 > 1 || count != count2)
		return 0;

	if (count == 0 && count2 == 0)
		start_node = -1;

	//3. select the start node
	if (start_node == -1) {
		for (i = 0; i < N; i++) {
			if (node[i] != -1 && 
				(start_node == -1 ||
				 (strcmp(str[edges[node[start_node]].str_idx], str[edges[node[i]].str_idx]) > 0))) {
				start_node = i;
			}
		}
	}

	return 1;
}

int main (int argc, char *argv[])
{
	int total;

	scanf("%d", &total);
	while (total--) {
		init();
		input();
		if (exist()) {
			get_eura_path();
			output();
		} else {
			printf ("***\n");
		}
	}

	return 0;
}




