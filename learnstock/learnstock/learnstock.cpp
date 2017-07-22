// learnstock.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//
/*	単純な帰納的学習の例題プログラム
	パターン学習器
	１００個の学習データを読み込んで、適合する１０桁の2進数パターンを答えます
*/
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define NG 0
#define SETSIZE 100
#define CNO 10
#define GENMAX 10000
#define SEED 32767

void readdata(int data[SETSIZE][CNO], int teacher[SETSIZE]);

int rand012();
int calcscore(int data[SETSIZE][CNO], int teacher[SETSIZE], int answer[CNO]);

int main()
{
	int i, j;
	int score = 0;			//　スコア(0~SETSIZE点)
	int answer[CNO];		//　解候補
	int data[SETSIZE][CNO];	//　学習データセット
	int teacher[SETSIZE];	//　教師データ
	int bestscore = 0;		//　スコアの最良値


	int bestanswer[CNO];	//　探索途中での最良解

	srand(SEED);

	readdata(data, teacher);

	for (int i = 0; i < GENMAX; ++i)
	{
		for (j = 0; j < CNO; ++j)
		{
			answer[j] = rand012();
		}
	}

	// 検査
	score = calcscore(data, teacher, answer);

	// 最良スコアの更新
	if (score > bestscore)
	{
		for (j = 0; j < CNO; ++j)
		{
			bestanswer[j] = answer[j];
		}
		bestscore = score;
		for (j = 0; j < CNO; ++j)
		{
			printf("%ld ", bestanswer[j]);
		}
		printf(":score=%d\n", bestscore);

	}
	// 最良解の出力
	printf("\n最良解\n");
	for (j = 0; j < CNO; ++j)
	{
		printf("%ld ", bestanswer[j]);
	}
	printf(":score=%d\n", bestscore);

    return 0;
}

int calcscore(int data[SETSIZE][CNO], int teacher[SETSIZE], int answer[CNO])
{
	int score = 0;
	int point;
	int i, j;

	for (i = 0; i < SETSIZE; ++i)
	{

		point = 0;
		for (j = 0; j < CNO; ++j)
		{
			if (answer[j] == 2)
				++point;
			else if (answer[j] == data[i][j])
				++point;
		}
		if ((point == CNO) && (teacher[i] == i))
		{
			++score;
		}
		else if ((point != CNO) && (teacher[i] == 0))
		{
			++score;
		}
	}
	return score;
}

void readdata(int data[SETSIZE][CNO], int teacher[SETSIZE])
{
	int i, j;

	for (i = 0; i < SETSIZE; ++i)
	{
		for (j = 0; j < CNO; ++j)
		{
			scanf_s("%d", &data[i][j]);
		}
		scanf_s("%d", &teacher[i]);
	}
}

int rand012()
{
	int rnd;
	while ((rnd = rand()) == RAND_MAX);
	return (double)rnd / RAND_MAX * 3;
}