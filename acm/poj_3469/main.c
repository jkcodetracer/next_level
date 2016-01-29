/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年11月17日 星期二 23时25分56秒 CST  
 *
 *  使用增广路的思想来求解网络流的最大值
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN	(2048)
#define INF	(999999)

#define MINV(a,b) (((a)>(b))?(b):(a))

typedef struct arch_st{
	int f;
	int c;
}arch_st;

typedef struct queue_st{
	int head, tail;
	int size;
	int ring[MAXN];
}queue_st;

arch_st map[MAXN][MAXN];
int n_vetex;
int ex_edge;
int flag[MAXN]; //标记节点处于的状态， -1 -- 未标记未检查,  0 -- 已标记未检查，  1 -- 已标记已检查
int prev[MAXN]; //标记从哪个节点访问到当前节点，用于回溯并使求出的alpha生效
int alpha[MAXN]; //标记本次检查得到的修正量alpha的值

void q_init(queue_st *que)
{
	que->head = que->tail = 0;
	que->size = MAXN;
	memset(que->ring, 0, sizeof(que->ring));
}

int q_empty(queue_st *que)
{
	return (que->head == que->tail);
}

void q_enque(queue_st *que, int idx)
{
	int tmp = (que->tail + 1)%(que->size);
	que->ring[que->tail] = idx;
	que->tail = tmp;
}

int q_deque(queue_st *que)
{
	int idx = que->ring[que->head];
	que->head = (que->head + 1)%(que->size);
	return idx;
}

void init()
{
	int i, j, a, b, w;

	scanf("%d %d", &n_vetex, &ex_edge);
	for (i = 0; i < n_vetex+2; i++) {
		for (j = 0; j < n_vetex+2; j++) {
			map[i][j].f = INF;
			map[i][j].c = INF;
		}
	}

	for (i = 1; i <= n_vetex; i++) {
		scanf("%d %d", &a, &b);
		map[0][i].c = a;
		map[0][i].f = 0;
		map[i][n_vetex + 1].c = b;
		map[i][n_vetex + 1].f = 0;
	}

	for (i = 1; i <= ex_edge; i++) {
		scanf("%d %d %d", &a, &b, &w);
		map[a][b].c = w;
		map[a][b].f = 0;
		map[b][a].c = w;
		map[b][a].f = 0;
	}

	n_vetex += 2;
}

void ford_init()
{
	memset(flag, -1, sizeof(flag));
	memset(alpha, -1, sizeof(alpha));
	memset(prev, -1, sizeof(prev));
	flag[0] = 0;
	prev[0] = 0;
	alpha[0] = INF;
}

void ford_fulkerson()
{
	int i,j;
	int cur, tmp, value, prev_n;
	queue_st que;

	while(1) {
		//1. 这是一种收缩的求解手段，直到不能收缩为止
		ford_init();
		q_init(&que);

		//2.使用bfs的思想来进行收缩
		q_enque(&que, 0);
		while(!q_empty(&que)) {
			cur = q_deque(&que);
			for (i = 0; i < n_vetex; i++) {
				//只与未标记的邻接点做延伸
				if (flag[i] != -1)
					continue;
				//3.1
				//处理正向邻接节点，或者反向临街节点，求出的alpha值为当前弧的剩余流量，
				//正向节点和反向节点求解方式不同。
				if (map[cur][i].c < INF &&
				    map[cur][i].f < map[cur][i].c) {
					flag[i] = 0;
					prev[i] = cur;
					tmp = map[cur][i].c - map[cur][i].f;
					alpha[i] = MINV(tmp, alpha[cur]);
					q_enque(&que, i);
				} else if (map[i][cur].c < INF &&
				    map[i][cur].f > 0) {
					flag[i] = 0;
					prev[i] = cur;
					alpha[i] = MINV(map[i][cur].f, alpha[cur]);
					q_enque(&que, i);
				}
			}
			//标记当前节点被检查完毕
			flag[cur] = 1;
		}

		//没有收缩的余地, 就此结束，输出结果
		if (flag[n_vetex - 1] == -1 ||
		    alpha[n_vetex - 1] <= 0)
			break;

		//将收缩的结果应用到这条路径上去
		//set new alpha
		cur = n_vetex - 1;
		prev_n = prev[n_vetex - 1];
		value = alpha[n_vetex - 1];
		while(1) {
			if (map[prev_n][cur].c < INF) {
				map[prev_n][cur].f += value;
			} else if (map[cur][prev_n].c < INF) {
				map[cur][prev_n].f -= value;
			}

			cur = prev_n;
			if (cur == 0)
				break;
			prev_n = prev[cur];
		}
	}

	value = 0;
	for (i = 0;i < n_vetex; i++) {
		for (j = 0; j < n_vetex; j++) {
			if (i == 0 && map[i][j].f < INF)
				value += map[i][j].f;
			if (map[i][j].f < INF) {
				//printf("%d->%d:%d\n", i,j,map[i][j].f);
			}
		}
	}

	printf("%d\n", value);
}

int main(int argc, char* argv[])
{
	init();
	ford_fulkerson();

	return 0;
}

