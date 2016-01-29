/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年11月29日 星期日 14时16分01秒 CST  
 *
 * 1. find the largest net flow in the map
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN (1024)
#define INF (999999)

#define ALFA2IDX(a) (((a) - 'A') + 2)

int map[MAXN][MAXN];
int hi[MAXN];
int ef[MAXN];
int flag[26];
int n_vetex;
int s, t, n, m, k; 

void init()
{
	int i,j;
	char alpha[32], bet[32];
	char str[32];

	for (i = 0; i < MAXN; i++) {
		for(j = 0; j < MAXN; j++) {
			map[i][j] = 0;
		}
	}

	memset(flag, 0, sizeof(int)*26);
	s = 0;
	t = 1;
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%s", alpha);
		map[ALFA2IDX(alpha[0])][t]++;
		flag[alpha[0] - 'A'] = 1;
	}

	scanf("%d", &m);
	for (i = 0; i < m; i++) {
		scanf("%s %s", str, alpha);
		map[s][ALFA2IDX(alpha[0])]++;
		flag[alpha[0] - 'A'] = 1;
	}

	scanf("%d", &k);
	for (i = 0; i < k; i++) {
		scanf("%s %s", alpha, bet);
		map[ALFA2IDX(alpha[0])][ALFA2IDX(bet[0])] = INF;
		flag[alpha[0] - 'A'] = 1;
		flag[bet[0] - 'A'] = 1;
	}

	n_vetex = 28;
#if 0
	for (i = 0; i < 26; i++) {
		if (flag[i]) 
			n_vetex++;
	}
#endif
}

void push_flow()
{
	int i;
	int queue[MAXN];
	int head, tail;
	int cur, tmp;
	int sum;

	head = tail = 0; 
	memset(queue, 0, sizeof(int)*MAXN);
	memset(ef, 0, sizeof(int)*MAXN);
	queue[head++] = s;
	hi[s] = n_vetex;
	ef[s] = INF;
	ef[t] = -INF;
	sum = 0;

	while(head != tail) {
		cur = queue[tail++];
		for (i = 0; i < n_vetex; i++){
			if (map[cur][i] > ef[cur]) {
				tmp = ef[cur];
			} else {
				tmp = map[cur][i];
			}

			if (tmp > 0 && 
			    (cur == s || hi[cur] == (hi[i]+1))) {
				map[cur][i] -= tmp;
				map[i][cur] += tmp;
				if (i == t)
					sum += tmp;
				ef[cur] -= tmp;
				ef[i] += tmp;

				if (i != t && i != s) {
					queue[head++] = i;
				}
			}
		}

		if (cur != s && ef[cur] > 0) {
			hi[cur]++;
			queue[head++] = cur;
		}
	}

	printf("%d\n", m - sum);
}

int main(int argc, char* argv[])
{
	int total;
	scanf("%d", &total);
	while(total--) {
		init();
		push_flow();
	}
	return 0;
}

