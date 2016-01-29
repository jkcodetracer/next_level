/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年10月23日 星期五 17时55分19秒 CST  
 *
 * 1. 确认图中是否存在负权值回路
 * 2. 其实就是寻找一条回路， 并且这条回路中存在负权值的边。
 * 3. 这里使用SPFA算法来寻找，如果一个节点反复入队N，认为存在
 * 回路，N为图中的节点总数。
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN (512)
#define MAXE (8192)
#define INF	(999999)

typedef struct node_st{
	int next;
}node_st;

typedef struct edge_st{
	int from;
	int to;
	int weight;
	int next;
}edge_st;

typedef struct queue_st{
	int head;
	int tail;
	int size;
	int ring[MAXN];
}queue_st;

int n_vetex;
node_st nodes[MAXN];
int n_edge;
edge_st edges[MAXE];
int weight[MAXN];
int inq[MAXN];
int count[MAXN];

void q_init(queue_st *pq)
{
	pq->head = 0;
	pq->tail = 0;
	pq->size = MAXN;
	memset(pq->ring, 0, sizeof(int)*MAXN);
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
	int cur = pq->ring[pq->tail];

	pq->tail = (pq->tail+1)%pq->size;

	return cur;
}

int q_empty(queue_st *pq)
{
	return pq->head == pq->tail;
}

void add_edge(int from, int to, int weight)
{
	edge_st *pe;
	node_st *pn;

	pn = &nodes[from];
	pe = &edges[n_edge++];
	pe->from = from;
	pe->to = to;
	pe->weight = weight;
	pe->next = pn->next;
	pn->next = n_edge - 1;
}

void init()
{
	int i,u,v,w;
	int n_way, n_hole;

	n_edge = 0;
	scanf("%d %d %d", &n_vetex, &n_way, &n_hole);

	for (i = 0; i <= n_vetex; i++) {
		nodes[i].next = -1;
	}

	for(i = 0; i < n_way; i++) {
		scanf("%d %d %d", &u, &v, &w);
		add_edge(u,v,w);
		add_edge(v,u,w);
	}

	for (i = 0; i < n_hole; i++) {
		scanf("%d %d %d", &u, &v, &w);
		add_edge(u,v,-w);
	}
}

int SPFA(int begin)
{
	int i;
	int cur_idx, cur_edge;
	queue_st que;
	edge_st *pe;

	q_init(&que);
	for (i = 0; i<= n_vetex; i++) {
		weight[i] = INF;
		count[i] = 0;
		inq[i] = 0;
	}

	weight[begin] = 0;
	q_enque(&que, begin);
	inq[begin]++;
	count[begin]++;
	while(!q_empty(&que)) {
		cur_idx = q_deque(&que);
		if (count[cur_idx] > n_vetex) 
			return -1;
		inq[cur_idx]--;
		cur_edge = nodes[cur_idx].next;
		while(cur_edge != -1) {
			pe = &edges[cur_edge];
			if (weight[pe->from] + pe->weight < weight[pe->to]) {
				weight[pe->to] = weight[pe->from]+pe->weight;
				if (!inq[pe->to]) {
					q_enque(&que, pe->to);
					inq[pe->to]++;
					count[pe->to]++;
				}
			}

			cur_edge = pe->next;
		}
	}

	return 0;
}

int main(int argc, char* argv[])
{
	int total;

	scanf("%d", &total);
	while(total--){
		init();
		if (SPFA(1)) {
			printf("YES\n");
		} else {
			printf("NO\n");
		}
	}

	return 0;
}


