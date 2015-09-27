/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年 9月12日 星期六 00时42分51秒 CST 
 *
 * discript your detail info.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXM	(512)
#define MAXN	(10)
#define MAP_SZ	(4)

typedef struct node_st{
	int to;
	int next;
}node_st;

int node_used = 0;
node_st node_list[MAXM];
node_st node_table[MAXN];
char fixed_map[MAP_SZ][MAP_SZ][MAXN];
int cur_map[MAP_SZ][MAP_SZ];

int count[MAXN] = {0};
char items[MAXN] = {0};
int n_items = 0;

void top_sort_detect()
{
	int i, idx;

	while(n_items--) {
		for(i = 1; i < MAXN; i++) {
			if (!count[i]) {
				break;
			}
		}
		
		if (i >= MAXN) {
			printf ("THESE WINDOWS ARE BROKEN\n");
			return;
		}

		idx = node_table[i].next;
		while(idx != -1) {
			count[node_list[idx].to]--;
			idx = node_list[idx].next;
		}
		count[i] = -1;
	}

	printf("THESE WINDOWS ARE CLEAN\n");
}

void init_graph()
{
	int i,j,k;

	n_items = 0;
	node_used = 0;
	memset(items, 0, MAXN);
	memset(count, -1, sizeof(int)*MAXN);

	for (i = 1; i < MAXN;i++) {
		node_table[i].next = -1;
	}

	for (i = 0; i < MAP_SZ;i++) {
		for (j = 0; j < MAP_SZ;j++) {
			if(!items[cur_map[i][j]]) {
				n_items++;
				count[cur_map[i][j]] = 0;
				items[cur_map[i][j]] = 1;
			}

			for (k = 1; k < MAXN; k++) {
				if (cur_map[i][j] == k ||
				    !fixed_map[i][j][k]) {
					continue;
				}

				if(!items[k]) {
					n_items++;
					count[k] = 0;
					items[k] = 1;
				}

				node_list[node_used].next = node_table[cur_map[i][j]].next;
				node_table[cur_map[i][j]].next = node_used;
				node_list[node_used].to = k;
				node_used++;
				count[k]++;
			}
		}
	}
}

void map_init()
{
	int i, j;
	int k;

	for (i = 0; i < MAP_SZ; i++) {
		for (j = 0; j < MAP_SZ; j++) {
			memset(fixed_map[i][j], 0, MAXN);
		}
	}

	for (k = 1; k < MAXN; k++) {
		i = (k-1)/3;
		j = (k-1)%3;
		fixed_map[i][j][k] = 1;
		fixed_map[i][j+1][k] = 1;
		fixed_map[i+1][j][k] = 1;
		fixed_map[i+1][j+1][k]= 1;
	}
}

int main(int argc, char* argv[])
{
	int i, j;
	char str[32];

	map_init();
	while (1) {
		scanf("%s", str);
		if (str[0] == 'E') {
			if (str[3] == 'O') {
				break;
			} else {
				continue;
			}
		}

		for (i = 0; i < MAP_SZ;i++){
			for (j = 0; j < MAP_SZ;j++) {
				scanf("%d", &cur_map[i][j]);
			}
		}

		init_graph();
		top_sort_detect();
	}

	return 0;
}

