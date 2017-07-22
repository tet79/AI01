// qlearning.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

#define GENMAX	100
#define NODENO	15
#define ALPHA	0.1
#define GAMMA	0.9
#define EPSILON	0.3
#define SEED	32767

int rand100();
int rand01();
double rand1();
void printqvalue(int qvalue[NODENO]);
int selecta(int s, int qvalue[NODENO]);
int updateq(int s, int qvalue[NODENO]);

int main()
{
	int i;
	int s;	//状態
	int t;
	int qvalue[NODENO];

	srand(SEED);

	for (i = 0; i < NODENO; ++i)
	{
		qvalue[i] = rand100();
	}
	printqvalue(qvalue);

	for (i = 0; i < GENMAX; ++i)
	{
		s = 0;
		for (t = 0; t < 3; ++t)
		{
			s = selecta(s, qvalue);
			qvalue[s] = updateq(s, qvalue);
		}
		printqvalue(qvalue);
	}
    return 0;
}

/*
//	updateq()関数
//	Q値を更新する
*/
int updateq(int s, int qvalue[NODENO])
{
	int qv;		//更新されるQ値
	int qmax;	//Q値の最大値

	//最下段の場合
	if (s > 6)
	{
		if (s == 14)	
		{
			//報酬の付与
			qv = qvalue[s] + ALPHA * (1000 - qvalue[s]);
		}
		else
		{
			//報酬なし
			qv = qvalue[s];
		}
	}
	else
	{
		if ((qvalue[2 * s + 1]) > (qvalue[2 * s + 2]))
		{
			qmax = qvalue[2 * s + 1];
		}
		else
		{
			qmax = qvalue[2 * s + 2];
		}
		qv = qvalue[s] + ALPHA * (GAMMA * qmax - qvalue[s]);
	}
	return qv;
}

/*
//	selecta()関数
//	行動を選択する
*/
int selecta(int olds, int qvalue[NODENO])
{
	int s;

	if (rand1() < EPSILON)
	{
		if (rand01() == 0)
		{
			s = 2 * olds + 1;
		}
		else
		{
			s = 2 * olds + 2;
		}
	}
	else
	{
		if ((qvalue[2 * olds + 1]) > (qvalue[2 * olds + 2]))
		{
			s = 2 * olds + 1;
		}
		else
		{
			s = 2 * olds + 2;
		}
	}
	return s;
}

/*
//	printqvalue()関数
//	Q値を出力する
*/
void printqvalue(int qvalue[NODENO])
{
	int i;

	for (i = 1; i < NODENO; ++i)
	{
		printf("%d\t", qvalue[i]);
	}
	printf("\n");
}

/*
//	rand1()関数
//	０～１の実数を返す乱数関数
*/
double rand1()
{
	return (double)rand() / RAND_MAX;
}

/*
//	rand01()関数
//	０または１を返す乱数関数
*/
int rand01()
{
	int rnd;

	while ((rnd = rand()) == RAND_MAX);
	return (int)((double)rnd / RAND_MAX * 2);
}

/*
//	rand100()関数
//	０～１００を返す乱数関数
*/
int rand100()
{
	int rnd;

	while ((rnd = rand()) == RAND_MAX);
	return (int)((double)rnd / RAND_MAX * 101);
}