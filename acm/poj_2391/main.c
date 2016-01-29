/**
 * \file main.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: 2015年12月 3日 星期四 20时32分33秒 CST 
 * 1. 使用floyd算法计算最短距离
 * 2. 二分法筛选最短时间，并依次尝试进行最大网络流的推算， 使用dinic算法优化
 *
 */
#include <stdio.h>
#include <stlib.h>
#include <string.h>

#define MAXN (256)

int resi[MAXN][MAXN];
int dis[MAXN][MAXN];
int sign[MAXN][MAXN];
int F, P;
int n_vetex;
int s, t;

void init()
{
	int i,j;

	scanf("%d %d", &F, &P);
	n_vetex = F + 2;
	s = 0;
	t = F+1;
	for (i = 0; i < F; i++) {

	}
}

int main(int argc, char* argv[])
{
	init();

	return 0;
}

