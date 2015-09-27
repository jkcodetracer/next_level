/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年 8月19日 星期三 22时30分12秒 CST 
 *
 * 1. bfs, 
 * 2. 余数剪枝
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXN	(5000)

typedef struct tree_node{
	int fa;
	int value;
	int rest;
}tree_st;

typedef struct queue_st{
	int head, tail;
	int len;
	int ring[MAXN];
}queue_st;

char rest_flag[MAXN] = {0};
tree_st node[MAXN];
int cur_node = 0;

int m_arr[MAXN] = {0};
int m_n = 0;

int target = 0;

void q_init(queue_st *que)
{
	que->len = 512;
	que->head = que->tail = 0;
}

int q_push(queue_st *que, int idx)
{
	int tmp = (que->tail+1)%que->len;

	if (tmp == que->head) {
		return -1;
	}

	que->ring[que->tail] = idx;
	que->tail = tmp;
	return 0;
}

int q_empty(queue_st *que)
{
	return (que->head == que->tail);
}

int q_pop(queue_st *que)
{
	int tmp = que->ring[que->head];

	que->head = (que->head+1)%(que->len);

	return tmp;
}

void output(int idx)
{
	if (node[idx].fa == -1)
		return;
	output(node[idx].fa);
	printf("%d", node[idx].value);
}

int cmp(const void * a, const void * b)
{
	return *(int*)a-*(int*)b;
}

int bfs()
{
	int i = 0;
	int act_idx = 0;
	tree_st tmp;
	queue_st que;

	q_init(&que);

	node[cur_node].fa = -1;
	node[cur_node].value = 0;
	node[cur_node].rest = 0;
	q_push(&que, cur_node);
	cur_node++;
	while(!q_empty(&que)){
		act_idx = q_pop(&que);

		for(i = 0; i < m_n;i++) {
			tmp.rest = (node[act_idx].rest*10 + m_arr[i])%target;
			if (node[act_idx].fa == -1 && m_arr[i] <=0)
				continue;

			if(tmp.rest == 0) {
				node[cur_node].fa = act_idx;
				node[cur_node].value = m_arr[i];
				node[cur_node].rest = tmp.rest;
				return 0;
			}

			if(rest_flag[tmp.rest]==0) {
				node[cur_node].fa = act_idx;
				node[cur_node].value = m_arr[i];
				node[cur_node].rest = tmp.rest;
				rest_flag[tmp.rest] = 1;
				q_push(&que, cur_node);

				cur_node++;
			}
		}
	}

	return -1;
}

int main(int argc, char* argv[])
{
	int i = 0;
	int ret = 0;

	while (1) {
		scanf("%d %d", &target, &m_n);
		for(i = 0; i < m_n;i++) {
			scanf("%d", &m_arr[i]);
		}

		qsort(m_arr, m_n, sizeof(int), cmp);
		memset(rest_flag, 0, MAXN);
		cur_node = 0;
		ret = bfs();
		if (ret != 0) {
			printf("0\n");
		} else {
			output(cur_node);
			printf("\n");
		}
	}

	return 0;
}



