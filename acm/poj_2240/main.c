/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年10月18日 星期日 16时57分40秒 CST  
 *
 * find the hightest rate consumption with the bellman alg
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN	(32)
#define MAXE	(256)

typedef struct exchange_st{
	int from;
	int to;
	float rate;
}exchange_st;

char name[MAXN][16];
int n_vetex;
exchange_st edges[MAXE];
int n_edges;
float rates[MAXN];

int find_name(char *nm)
{
	int i;
	for (i = 0; i < n_vetex; i++) {
		if (!strcmp(name[i], nm))
			break;
	}

	return i;
}

void init()
{
	int i;
	char a[32],b[32];
	float rate;

	scanf("%d", &n_vetex);
	if (n_vetex == 0) 
		exit(0);

	for (i = 0; i < n_vetex; i++) {
		scanf("%s", name[i]);
	}

	scanf("%d", &n_edges);
	for (i =0; i < n_edges; i++) {
		scanf("%s %f %s", a, &rate, b);

		edges[i].from = find_name(a);
		edges[i].to = find_name(b);
		edges[i].rate = rate;
	}
}

int bellmanford(int begin)
{
	int i,j;
	exchange_st *pe;

	memset(rates, 0, sizeof(rates[0])*MAXN);
	rates[begin] = 1.0;
	for(i = 0; i < n_vetex-1; i++) {
		for (j = 0; j < n_edges; j++) {
			pe = &edges[j];
			if (rates[pe->from]*pe->rate > rates[pe->to]) {
				rates[pe->to] = rates[pe->from]*pe->rate;
			}
		}
	}

	if (rates[begin] > 1.0) {
		return 1;
	} else {
		return 0;
	}
}

int main(int argc, char* argv[])
{
	int i;

	while(1){
		init();
		for(i = 0; i < n_vetex; i++) {
			if (bellmanford(i)) {
				printf("Yes\n");
				break;
			}
		}

		if (i >= n_vetex) {
			printf("No\n");
		}
	}

	return 0;
}



