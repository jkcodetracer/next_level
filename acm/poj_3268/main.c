/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年10月22日 星期四 20时04分27秒 CST  
 *
 * 找到所有最短路径组合中的最大的值
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN (1024)
#define MAXE (10024)
#define INF (999999)

typedef struct queue_st{
	int head;
	int tail;
	int size;
	int ring[MAXN];
}queue_st;

typedef struct edge_st{
	int from;
	int to;
	int weight;
	int next;
}edge_st;

typedef struct node_st{
	int next;
}node_st;

int n_vetex;
node_st nodes[MAXN];
int n_edge;
edge_st edges[MAXE];
int target;
int inq[MAXN];
int weight[MAXN];
int back_weight[MAXN];

void q_init(queue_st *pq)
{
	pq->head = 0;
	pq->tail = 0;
	pq->size = MAXN;
	memset(pq->ring, 0, sizeof(int)*MAXN);
}

int q_empty(queue_st *pq)
{
	return pq->head == pq->tail;
}

int q_enque(queue_st *pq, int idx)
{
	int new = (pq->head+1)%pq->size;
	if (new == pq->tail) 
		return -1;
	pq->ring[pq->head] = idx;
	pq->head = new;

	return 0;
}

int q_deque(queue_st *pq)
{
	int value = pq->ring[pq->tail];
	pq->tail = (pq->tail+1)%pq->size;

	return value;
}

void init()
{
	int i;
	int u,v,w;
	edge_st *pe;

	scanf("%d %d %d", &n_vetex, &n_edge, &target);
	for (i = 0; i <= n_vetex; i++) {
		nodes[i].next = -1;
	}
	for (i = 0; i < n_edge; i++) {
		scanf("%d %d %d", &u, &v, &w);
		pe = &edges[i];
		pe->from = u;
		pe->to = v;
		pe->weight = w;
		pe->next = nodes[u].next;
		nodes[u].next = i;
	}
}

void SPFA(int begin)
{
	int i, cur_idx, cur_edge;
	queue_st que;
	edge_st *pe;

	q_init(&que);
	for (i = 0; i <= n_vetex; i++) {
		weight[i] = INF;
		inq[i] = 0;
	}

	weight[begin] = 0;
	q_enque(&que, begin);
	inq[begin]++;
	while(!q_empty(&que)) {
		cur_idx = q_deque(&que);
		inq[cur_idx]--;
		cur_edge = nodes[cur_idx].next;
		while(cur_edge != -1) {
			pe = &edges[cur_edge];
			if (pe->weight+weight[pe->from] < weight[pe->to]) {
				weight[pe->to] = pe->weight + weight[pe->from];
				if (!inq[pe->to]) {
					q_enque(&que, pe->to);
					inq[pe->to]++;
				}
			}
			cur_edge = pe->next;
		}
	}
}

int main(int argc, char* argv[])
{
	int i, max_weight = 0;
	int tmp_weight;

	init();
	SPFA(target);
	memcpy(back_weight, weight, sizeof(int)*MAXN);
	for (i = 1; i <= n_vetex; i++) {
		if (i != target){
			SPFA(i);
			tmp_weight = weight[target] + back_weight[i];
		} else {
			tmp_weight = 0;
		}
		if (tmp_weight > max_weight) {
			max_weight = tmp_weight;
		}
	}

	printf("%d\n", max_weight);

	return 0;
}


