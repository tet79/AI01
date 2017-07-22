// learnstock.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//
/*	�P���ȋA�[�I�w�K�̗��v���O����
	�p�^�[���w�K��
	�P�O�O�̊w�K�f�[�^��ǂݍ���ŁA�K������P�O����2�i���p�^�[���𓚂��܂�
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
	int score = 0;			//�@�X�R�A(0~SETSIZE�_)
	int answer[CNO];		//�@�����
	int data[SETSIZE][CNO];	//�@�w�K�f�[�^�Z�b�g
	int teacher[SETSIZE];	//�@���t�f�[�^
	int bestscore = 0;		//�@�X�R�A�̍ŗǒl


	int bestanswer[CNO];	//�@�T���r���ł̍ŗǉ�

	srand(SEED);

	readdata(data, teacher);

	for (int i = 0; i < GENMAX; ++i)
	{
		for (j = 0; j < CNO; ++j)
		{
			answer[j] = rand012();
		}
	}

	// ����
	score = calcscore(data, teacher, answer);

	// �ŗǃX�R�A�̍X�V
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
	// �ŗǉ��̏o��
	printf("\n�ŗǉ�\n");
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