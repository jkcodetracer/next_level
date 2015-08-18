/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年 8月18日 星期二 14时29分39秒 CST 
 *
 * bfs..
 */
#include <stdio.h>
#include <string.h>

#define MAXN	20

int map[MAXN * MAXN] = {0};
int back_map[MAXN*MAXN] = {0};
int route[MAXN * MAXN] = {0};

int path[MAXN * MAXN] = {0};

int main(int argc, char *argv[])
{
	int N, S, L;
	int n_case;
	int from, to;
	int i, j;
	int step, min_pos;

	scanf("%d", &n_case);
	while(n_case--) {
		memset(path, 0, sizeof(int)*MAXN*MAXN);
		scanf("%d %d %d", &N, &S, &L);
		for (i = 0; i < S+L;i++) {
			scanf("%d %d", &from, &to);
			path[from] = to;
		}

		memset(map, 0, sizeof(int)*MAXN*MAXN);
		memset(back_map, 0, sizeof(int)*MAXN*MAXN);

		step = 0;
		min_pos = 1;
		map[1] = 1;
		N*=N;
		while(map[N] == 0) {
			memcpy(back_map, map, sizeof(int)*N);
			memset(map, 0, sizeof(int)*N);
			for(i = min_pos; i < N;i++) {
				if (!back_map[i])
					continue;
				for (j = 1; j <= 6;j++) {
					if (back_map[i+j])
						continue;

					if (path[i+j]) {
						map[path[i+j]] = 1;
						route[i+j] = i;
						route[path[i+j]] = i+j;
					} else if (i+j <= N){
						map[i+j] = 1;
						route[i+j] = i;
					}
				}
			}

			step++;
		}
#if 0
		//因为bfs只是记录了这一层到下一层的可能性
		//这里的答案会在遍历的时候互相覆盖，导致
		//结果错误。不能这样记录最佳路径。
		//暂时可以使用dfs
		i = N;
		while(i>= 1){
			printf ("%d ", route[i]);
			i = route[i];
		}
#endif

		printf ("\n %d\n", step);
	}

	return 0;
}

