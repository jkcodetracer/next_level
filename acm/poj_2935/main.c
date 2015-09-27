/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年 9月 7日 星期一 00时13分35秒 CST
 *
 * bfs
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXN	(8)
#define MAXDIR	(4)
#define DIR_HOZ (0)
#define DIR_VER	(1)

typedef struct ring_st{
	int head, tail;
	int size;
	int idx[512];
}ring_st;

typedef struct node_st{
	int x;
	int y;
	int fa;
	int dir;
}node_st;

node_st nodes[512];
int node_used = 0;

char matrix[MAXN][MAXN][MAXDIR];
char visited[MAXN][MAXN];
// 0-w 1-e 2-s 3-N
char dir_map[4] = {'W', 'E', 'S', 'N'};
int wall_set[2][2] = {{1, 0}, {2, 3}};
int dir[MAXDIR][3] = {{-1, 0, 0}, {1, 0, 1}, {0, 1, 2}, {0, -1, 3}};
int s_x, s_y;
int e_x, e_y;

void r_init(ring_st *p)
{
	p->size = 512;
	p->head = p->tail = 0;
}

int r_empty(ring_st *p)
{
	return p->head == p->tail;
}

void r_push(ring_st *p, int idx)
{
	int tmp_head = (p->head + 1)%p->size;

	if (tmp_head == p->tail)
		return;

	p->idx[p->head] = idx;
	p->head = tmp_head;
}

int r_pop(ring_st *p)
{
	int tmp_idx = p->idx[p->tail];

	p->tail++;
	p->tail %= p->size;

	return tmp_idx;
}

void set_wall(int x, int y, int len, int dir)
{
	int i = 0;
	int t_x, t_y;

	for (i = 0; i < len; i++) {
		t_x = x;
		t_y = y;

		if (dir == DIR_HOZ) {
			t_y += i;
		} else {
			t_x += i;
		}

		if (dir == DIR_HOZ){
			matrix[t_x-1][t_y][wall_set[DIR_HOZ][0]] = 1;
			matrix[t_x][t_y][wall_set[DIR_HOZ][0]] = 1;
		} else {
			matrix[t_x][t_y-1][wall_set[DIR_VER][0]] = 1;
			matrix[t_x][t_y][wall_set[DIR_VER][0]] = 1;
		}
	}
}

void output(int cur_node)
{
	if (nodes[cur_node].fa != -1)
		output(nodes[cur_node].fa);
	else
		return ;

	printf("%c", dir_map[nodes[cur_node].dir]);
}

void bfs()
{
	int i;
	int tmp_x, tmp_y;
	int tar_x, tar_y;
	int cur_node;
	ring_st *cur_que, *bac_que, *tmp_que;
	ring_st que1, que2;

	r_init(&que1);
	r_init(&que2);
	cur_que = &que2;
	bac_que = &que1;

	nodes[0].fa = -1;
	nodes[0].x = s_x;
	nodes[0].y = s_y;

	r_push(bac_que, 0);
	node_used++;

	while(!r_empty(bac_que)){
		tmp_que = bac_que;
		bac_que = cur_que;
		cur_que = tmp_que;

		while(!r_empty(cur_que)) {
			cur_node = r_pop(cur_que);
			tmp_x = nodes[cur_node].x;
			tmp_y = nodes[cur_node].y;
			for (i = 0; i < 4; i++) {
				if (matrix[tmp_x][tmp_y][i])
					continue;
				tar_x = tmp_x + dir[i][0];
				tar_y = tmp_y + dir[i][1];

				if (tar_x < 1 || tar_x > 6 ||
				    tar_y < 1 || tar_y > 6)
					continue;

				if (visited[tar_x][tar_y])
					continue;
				visited[tar_x][tar_y] = 1;
				nodes[node_used].x = tar_x;
				nodes[node_used].y = tar_y;
				nodes[node_used].dir = dir[i][2];
				nodes[node_used].fa = cur_node;

				r_push(bac_que, node_used);
				node_used++;

				if (tar_x == e_x && tar_y == e_y) {
					output(node_used-1);
					return ;
				}
			}
		}
	}

}

int main(int argc, char * argv[])
{
	int i = 0;
	int bs_x, bs_y;
	int be_x, be_y;
	int len, dir;

	scanf("%d %d", &s_x, &s_y);
	scanf("%d %d", &e_x, &e_y);

	for (i = 0; i < 3;i++) {
		scanf("%d %d %d %d", &bs_x, &bs_y, &be_x, &be_y);
		if (bs_x == be_x) {
			dir = DIR_HOZ;
			len = be_y - bs_y;
		} else {
			dir = DIR_VER;
			len = be_x - bs_x;
		}

		bs_x++;
		bs_y++;
		set_wall(bs_x, bs_y, len, dir);
	}

	bfs();

	return 0;
}





