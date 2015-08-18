/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年 8月17日 星期一 10时53分50秒 CST 
 *
 * bfs, compare all the minimum path
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAXN	(10000)

#define SWAP(a, b) {\
		int tmp;\
		tmp = a;\
		a = b;\
		b = tmp;\
	}

typedef struct queue_st{
	int head;
	int tail;
	int ring[MAXN >> 3];
	int len;
}queue_st;

int table[MAXN][10];//记录邻接关系
int mz[MAXN] = {0};//记录邻接关系的数量
int reach[MAXN] = {0};//记录在第几次被访问了， 给出的公交线路中所有
		//的点，都会至少访问一次。 用于区分当前这一次是否可以继续访问，
		//从而用于求最短路径
int res_max[MAXN] = {0};//记录点i到达其他点的最短路径中最大的值
int cur = 0;//访问的批次

int max(int a, int b)
{
	return (a>b)?a:b;
}

void q_init(queue_st *qu)
{
	qu->head = qu->tail = 0;
	qu->len = MAXN >> 3;
}

int q_empty(queue_st *qu)
{
	return (qu->head == qu->tail);
}

int q_push(queue_st *qu, int idx)
{
	int tmp = (qu->tail + 1)%qu->len;

	if(tmp == qu->head) {
		return -1;
	}

	qu->ring[qu->tail] = idx;
	qu->tail = tmp;

	return 0;
}

int q_pop(queue_st *qu)
{
	int idx = 0;

	idx = qu->ring[qu->head];
	qu->head = (qu->head+1)%qu->len;

	return idx;
}

void bfs(int idx)
{
	int val;
	int use, back;
	int id,i, itr_id;
	queue_st que[2];

	q_init(&que[0]);
	q_init(&que[1]);
	use = 0, back = 1, val = 0;

	if(reach[idx] < cur) {
		reach[idx] = cur;
		q_push(&que[back], idx);
		res_max[idx] = max(res_max[idx], val+1);
	}
	//这里bfs可以保证到达每一个点的距离是最小的
	//使用两个队列纯粹是为了分层，统计距离使用的
	while(!q_empty(&que[back])) {
		SWAP(use, back);
		val++;
		while(!q_empty(&que[use])) {
			id = q_pop(&que[use]);
			for (i = 0; i < mz[id]; i++) {
				itr_id = table[id][i];
				if (reach[itr_id] < cur) {
					q_push(&que[back], itr_id);
					reach[itr_id] = cur;
					//从idx到当前点是最小的，但是
					//res_max里面记录的是所有最小路径中，最大的那个
					res_max[itr_id] = max(res_max[itr_id], val+1);
				}
			}
		}
	}
}

int main(int argc, char* argv[])
{
	int n_case, n_node, n_path;
	int i,j, id;
	int p_len;

	scanf("%d", &n_case);
	while(n_case--) {
		scanf("%d %d", &n_node, &n_path);

		for(i = 0; i < n_node; i++) {
			scanf("%d", &id);
			scanf("%d", &mz[id]);

			for (j = 0; j < mz[id]; j++) {
				scanf("%d", &table[id][j]);
			}
		}

		cur = 0;
		memset(reach, -1, sizeof(int)*MAXN);
		memset(res_max, 0, sizeof(int)*MAXN);
		//从路径点开始出发做bfs，
		for (i = 0; i < n_path; i++) {
			scanf("%d", &p_len);
			for(j = 0; j < p_len; j++) {
				scanf("%d", &id);
				bfs(id);
				cur++;
			}
		}

		int min = 1111111;
		int result = -1;
		for(i = 0; i < MAXN; i++) {
			if(reach[i] == cur-1 && res_max[i] < min) {
				result = i;
				min = res_max[i];
			}
		}

		printf ("%d %d\n", min, result);
	}

	return 0;
}


