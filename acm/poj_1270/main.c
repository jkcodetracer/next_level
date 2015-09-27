/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年 9月18日 星期五 20时51分14秒 CST 
 *
 * 1. list the sequence use the topologic sort and dfs
 */
#include <stdio.h>
#include <string.h>

#define MAXN	(26)
#define MAXS	(64)

char var_list[MAXN] = {0};
int total = 0;
int count[MAXN] = {0};
char rel_table[MAXN][MAXN];
char seq[MAXN+1] = {0};

void dfs(int depth, int max)
{
	int i = 0, j = 0;

	if(depth == max) {
		seq[depth] = '\0';
		printf("%s\n", seq);
		return ;
	}
	for (i = 0; i < MAXN; i++) {
		if (var_list[i] == 0)
			continue;
		if (count[i] == 0) {
			seq[depth] = i+'a';
			count[i] = -1;
			for (j = 0; j < MAXN;j++){
				if (rel_table[i][j] && i != j) {
					count[j]--;
				}
			}
			dfs(depth + 1, max);
			count[i] = 0;

			for (j = 0; j < MAXN; j++) {
				if (rel_table[i][j] && i != j) {
					count[j]++;
				}
			}
		}
	}

}

int main(int argc, char* argv[])
{
	char *ptr = NULL;
	char str[MAXS] = {0};
	char from, to;
	int i = 0;
	int flag = 0;

	while(1) {
		from = -1;
		to = -1;
		total = 0;
		flag = 0;
		memset(var_list, 0, MAXN);
		for (i = 0; i < MAXN;i++) {
			memset(rel_table[i], 0, MAXN);
		}
		memset(count, -1, sizeof(int)*MAXN);

		scanf("%s", str);
		for(ptr = str; *ptr != '\0'; ptr++){
			if (*ptr == ' ' || *ptr == '\n')
				continue;

			var_list[*ptr - 'a'] = 1;
			count[*ptr - 'a'] = 0;
			total++;
		}

		scanf("%s", str);
		for(ptr = str; *ptr != '\0'; ptr++){
			if (*ptr == ' ' || *ptr == '\n')
				continue;

			if (!flag) {
				from = *ptr;
				flag = 1;
			} else {
				to = *ptr;
				rel_table[from-'a'][to-'a'] = 1;
				count[to-'a']++;
				flag = 0;
			}
		}

		dfs(0, total);
	}

	return 0;
}






