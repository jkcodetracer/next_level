/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年 8月20日 星期四 00时31分53秒 CST 
 *
 * bfs
 */
#include <stdio.h>
#include <string.h>

#define MAXN	(9)
#define SWAP(a, b) {	\
		int tmp = a;	\
		a = b;	\
		b = tmp;\
	}

char map[MAXN][MAXN] = {{0}};

int dir[8][2] = {{1, 2}, {2,1},{-2, 1}, {2,-1}, {-2, -1}, {-1, -2},
		{1, -2}, {-1, 2}};
int t_x = 0, t_y = 0;
int s_x = 0, s_y = 0;

int step = 0;

typedef struct queue_st{
	int tail, head;
	int len;
	int ring[512];
}queue_st;

void q_init(queue_st *que)
{
	que->len = 512;
	que->tail = que->head = 0;
}

int q_push(queue_st *que, int idx)
{
	int tmp = (que->tail+1)%que->len;

	if (tmp == que->head)
		return -1;

	que->ring[que->tail] = idx;
	que->tail = tmp;

	return 0;
}

int q_pop(queue_st *que)
{
	int tmp = que->ring[que->head];
	que->head = (que->head + 1)%que->len;

	return tmp;
}

int q_empty(queue_st *que)
{
	return (que->head == que->tail);
}

int bfs()
{
	int x, y;
	int a, b;
	int tr_x, tr_y;
	int i;
	queue_st que[2];

	a = 0, b = 1;
	q_init(&que[a]);
	q_init(&que[b]);

	q_push(&que[a], s_x);
	q_push(&que[a], s_y);

	while(!q_empty(&que[a])) {
		SWAP(a, b);
		step++;

		while(!q_empty(&que[b])) {
			x = q_pop(&que[b]);
			y = q_pop(&que[b]);
	
			for(i = 0; i < 8; i++) {
				tr_x = x + dir[i][0];
				tr_y = y + dir[i][1];
	
				if (tr_x <= 0 || tr_x > 8 ||
				    tr_y <= 0 || tr_y > 8) {
					continue;
				}
	
				if (tr_x == t_x && tr_y == t_y)
					return 0;
	
				if (map[tr_x][tr_y] == 0) {
					map[tr_x][tr_y] = 1;
					q_push(&que[a], tr_x);
					q_push(&que[a], tr_y);
				}
	
			}
		}
	}

	return -1;
}

int main(int argc, char* argv[])
{
	char a[3], b[3];
	int ret = 0;
	int i;

	while(1) {
		scanf("%s %s", a, b);
		s_x = a[0] - 'a'+1;
		s_y = a[1] - '1'+1;
		t_x = b[0] - 'a'+1;
		t_y = b[1] - '1'+1;

		step = 0;
		if(s_x == t_x &&
		   s_y == t_y) {
			printf ("%d\n", 0);
			continue;
		}

		for(i = 0;i < MAXN;i++) {
			memset(map[i], 0, sizeof(char)*MAXN);
		}
		ret = bfs();
		if (ret) {
			printf("-1.\n");
		} else {
			printf("%d\n", step);
		}
	}

	return 0;
}


