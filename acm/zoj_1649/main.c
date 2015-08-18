/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年 8月13日 星期四 23时52分53秒 CST 
 *
 * 1. use the bfs to find the efficient path.
 */
#include <stdio.h>

#define MAXMN	(200)
#define INF    (1000000)

struct point{
	int x, y; //the position
	int steps; //steps from start point
	int time; //the time used
};

struct point ring[MAXMN << 2]; 
int r_head = 0;
int r_tail = 0;

int N, M;
char map[MAXMN][MAXMN] = {{0}};
int mintime[MAXMN][MAXMN] = {{0}};

int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int ax, ay;

void q_push(struct point *p)
{
	if ((r_tail + 1)%(MAXMN<<2) == r_head) {
		printf ("push failed!\n");
		return;
	}

	ring[r_tail].x = p->x;
	ring[r_tail].y = p->y;
	ring[r_tail].steps = p->steps;
	ring[r_tail].time = p->time;

	r_tail = (r_tail+1)%(MAXMN<<2);
}

int q_empty()
{
	return r_tail == r_head;
}

int q_pop()
{
	int tmp = r_head;

	if (r_tail == r_head) {
		return -1;
	}

	r_head = (r_head+1)%(MAXMN<<2);
	return tmp;
}

int bfs(struct point *p)
{
	int i = 0, cur = 0;
	int x, y;
	struct point t_point;

	q_push(p);
	while (!q_empty()) {
		cur = q_pop();
		for (i = 0; i < 4; i++) {
			x = ring[cur].x + dir[i][0];
			y = ring[cur].y + dir[i][1];
			if (x >= 0 && x < N &&
			    y >= 0 && y < M &&
			    map[x][y] != '#') {
				t_point.time = ring[cur].time + 1;
				if (map[x][y] == 'x')
					t_point.time++;

				if (t_point.time >= mintime[x][y])
					continue;
				mintime[x][y] = t_point.time;
				t_point.x = x;
				t_point.y = y;
				t_point.steps = ring[cur].steps + 1;
				q_push(&t_point);
			}
		}
	}

	return mintime[ax][ay];
}

int main(int argc, char *argv[])
{
	int i, j;

	while (scanf("%d %d", &N, &M) != EOF) {
		struct point s;
		for(i = 0; i < N; i++)
			scanf("%s", map[i]);
		for(i = 0; i < N; i++) {
			for (j = 0; j < M; j++) {
				mintime[i][j] = INF;
				if (map[i][j] == 'a') {
					ax = i;
					ay = j;
				}

				if (map[i][j] == 'r') {
					s.x = i;
					s.y = j;
					s.steps = 0;
					s.time = 0;
				}
			}
		}

		mintime[s.x][s.y] = 0;

		int mint = bfs(&s);
		if (mint < INF)
			printf ("%d\n", mint);
		else 
			printf ("Poor angel has to stay in the poison.\n");

	}
	return 0;
}

