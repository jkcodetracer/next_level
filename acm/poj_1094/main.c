/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年 9月 9日 星期三 07时55分06秒 CST
 *
 * use the topological sort to determine the fixed order
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN	(512)
#define MAXP	(26)

typedef struct node_st{
	int next;
	int to;
}node_st;

node_st node_list[MAXN];
node_st node_table[MAXP];

char alpha[MAXP] = {0};
int count[MAXP] = {0};
char seq[MAXP+1] = {0};
int used_node = 0;

int topsort(int n)
{
	int i;
	int pos = 0;
	int tmp_count[MAXP] = {0};
	int cnt = 0;
	int cur_node = 0;
	int pnode = 0;

	for(i = 0; i < MAXP;i++) {
		tmp_count[i] = count[i];
	}

	while(n--) {
		cnt = 0;
		for (i = 0; i < MAXP; i++) {
			if (tmp_count[i] == 0) {
				cnt++;
				cur_node = i;
			}
		}

		if (cnt > 1) {
			return 0;
		}

		if (cnt == 0) {
			return -1;
		}

		pnode = node_table[cur_node].next;
		while(pnode!=-1) {
			tmp_count[node_list[pnode].to]--;
			pnode = node_list[pnode].next;
		}
		seq[pos++] = cur_node + 'A';
		tmp_count[cur_node] = -1;
		seq[pos] = '\0';
	}

	return pos;
}

int main(int argc, char* argv[])
{
	int i;
	int n, m, from, to;
	char rel[16] = {0};
	int v_num = 0;
	int determined, used_rel;
	int ret = 0;

	while(1) {
		scanf("%d %d", &n, &m);
		if (n == 0 && m == 0)
			break;
		memset(count, -1, sizeof(int)*MAXP);
		memset(seq, 0, MAXP +1);
		memset(alpha, 0, MAXP);
		v_num = 0;
		used_node = 0;
		determined = 0;
		used_rel = 0;

		for(i = 0; i < MAXP; i++) {
			node_table[i].next = -1;
		}

		for(i = 0; i < m; i++) {
			scanf("%s", rel);
			from = rel[0]-'A';
			to = rel[2]-'A';
			if (!alpha[from]) {
				v_num++;
				alpha[from] = 1;
				if (count[from] == -1)
					count[from] = 0;
			}

			if (!alpha[to]) {
				v_num++;
				alpha[to] = 1;
				if (count[to] == -1)
					count[to] = 0;
			}

			node_list[used_node].to = to;
			node_list[used_node].next = node_table[from].next;
			node_table[from].next = used_node;
			used_node++;

			count[to]++;
			if (determined == 0) {
				ret = topsort(v_num);
				if (ret == n) {
					determined = 1;
					used_rel = i+1;
				} else if (ret == -1) {
					determined = -1;
					used_rel = i+1;
				}
			}

		}

		if (determined == 1) {
			printf ("%d is determined, sequence:%s\n", used_rel, seq);
		} else if (determined == 0) {
			printf ("can't determined!\n");
		} else if (determined == -1) {
			printf ("there is a circle, %d is determined!\n", used_rel);
		}
	}

	return 0;
}






