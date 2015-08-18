/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年 7月27日 星期一 00时19分50秒 CST 
 *
 *  判断一个图是否存在欧拉回路， 欧拉通路
 */

#include <stdio.h>
#include <string.h>

#define N 100

int deg[N] = {0};

int main(int argc, char *argv[])
{
	char str[200];
	int des_v, total_v;
	int eve_deg, odd_deg, door;
	int i = 0, j = 0, p = 0;
	int adj_v, off_set;

	while (scanf("%s", str) != EOF) {
		if (str[3] == 'O')
			break;

		scanf("%d %d", &des_v, &total_v);
		getchar();
		memset(deg, 0, sizeof(deg));
		door = eve_deg = odd_deg = 0;

		for (i = 0; i < total_v; i++) {
			j = 0;
			p = 0;
			gets(str);
			while (str[p] && str[p] == ' ')
				p++;
			while (sscanf(str+p, "%d%n", &adj_v, &off_set) == 1) {
				door++;
				deg[i]++;
				deg[adj_v]++;
				p += off_set;

				while(str[p] && str[p] == ' ')
					++p;
			}
		}
		scanf("%*s");

		for (i = 0; i < total_v; i++) {
			if (deg[i] & 1)
				odd_deg++;
			else
				eve_deg++;
		}

		if ((odd_deg == 0 && des_v == 0) || /* 1.存在欧拉回路 */
		    (odd_deg == 2 && (deg[des_v]&1) && (deg[0]&1) && des_v != 0)
		    /* 2. 或者存在欧拉通路，起始点为0， 终点为指定的点 */
		   ) {
			printf ("YES %d\n", door);
		} else {
			printf ("NO\n");
		}
	}

	return 0;
}


