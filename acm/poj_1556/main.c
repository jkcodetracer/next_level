/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年10月20日 星期二 08时08分12秒 CST  
 *
 * 1. generate all edges.
 * 2. find the shortest path in the graph with bellman_ford alg
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXW	(128)
#define MAXN	(1024)
#define INF	(999999)

typedef struct wall_st{
	double x;
	double y[4];
}wall_st;

typedef struct point_st{
	double x,y;
}point_st;

typedef struct edge_st{
	int from;
	int to;
	double weight;
}edge_st;

int n_wall;
wall_st walls[MAXW];
int n_point;
point_st points[MAXW<<2];
int n_edge;
edge_st edges[MAXN];
int n_vetex;
double weight[MAXW];

void init()
{
	int i,j;
	wall_st *pw;
	point_st *pp;

	points[0].x = 0;
	points[0].y = 5;
	n_point = 1;
	for (i = 0; i < n_wall; i++) {
		pw = &walls[i];
		scanf("%lf %lf %lf %lf %lf", 
		    &pw->x, &pw->y[0], &pw->y[1], &pw->y[2], &pw->y[3]);
		for (j = 0; j < 4; j++) {
			pp = &points[n_point++];
			pp->x = pw->x;
			pp->y = pw->y[j];
		}
	}

	points[n_point].x = 10;
	points[n_point].y = 5;
	n_vetex = ++n_point;
}

//>0 (x3,y3) above the line,
//<0 (x3,y3) below the line;
double cross(double x1, double y1, double x2, double y2, double x3, double y3)
{
	return (x2-x1)*(y3-y1) - (x3-x1)*(y2-y1);
}

int is_valid(point_st *pa, point_st *pb)
{
	int i = 0;
	wall_st *pw;

	if (pa->x >= pb->x){
		return 0;
	}
	while(i < n_wall && walls[i].x <= pa->x)
		i++;

	while(i < n_wall && walls[i].x < pb->x) {
		pw = &walls[i];

		if (cross(pa->x, pa->y, pb->x, pb->y, pw->x, 0)*
		    cross(pa->x, pa->y, pb->x, pb->y, pw->x, pw->y[0]) < 0 ||
		    cross(pa->x, pa->y, pb->x, pb->y, pw->x, pw->y[1])*
		    cross(pa->x, pa->y, pb->x, pb->y, pw->x, pw->y[2]) < 0 ||
		    cross(pa->x, pa->y, pb->x, pb->y, pw->x, pw->y[3])*
		    cross(pa->x, pa->y, pb->x, pb->y, pw->x, 10) < 0) {
			return 0;
		}
		i++;
	}

	return 1;
}

double dist(double x1, double y1, double x2, double y2)
{
	double dy, dx;

	dx = x1-x2;
	dy = y1-y2;

	return sqrt(dx*dx + dy*dy);
}

void generate_edges()
{
	int i,j;
	point_st *pa, *pb;
	edge_st *pe;

	n_edge = 0;
	for(i = 0; i < n_point;i++) {
		pa = &points[i];
		for (j = i+1; j < n_point; j++) {
			pb = &points[j];
			if (is_valid(pa, pb)) {
				pe = &edges[n_edge++];
				pe->from = i;
				pe->to = j;
				pe->weight = dist(pa->x, pa->y, pb->x, pb->y);
			}
		}
	}
}

void bellman_ford(int begin)
{
	int i,j;
	edge_st *pe;

	for (i = 0; i < n_vetex; i++) {
		weight[i] = INF;
	}

	weight[begin] = 0;
	for (i = 0; i < n_vetex-1; i++) {
		for (j = 0; j < n_edge; j++) {
			pe = &edges[j];
			if (weight[pe->from] < INF &&
			    weight[pe->from]+pe->weight < weight[pe->to]) {
				weight[pe->to] = weight[pe->from]+pe->weight;
			}
		}
	}
}

int main(int argc, char*argv[])
{
	while(1){
		scanf("%d", &n_wall);
		if (n_wall == -1)
			break;
		init();
		generate_edges();
		bellman_ford(0);
		printf("%.2lf\n", weight[n_vetex-1]);
	}
	return 0;
}


