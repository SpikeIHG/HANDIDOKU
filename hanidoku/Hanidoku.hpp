#ifndef HANIDOKU_H_
#define HANIDOKU_H_
#define _CRT_SECURE_NO_WARNINGS
//#define DEBUG
#include<stdio.h>
#include<stdlib.h>
#define SODUSIZE	200
#define WIDTH		10

typedef char Hanidoku[SODUSIZE];		// 作为输入的数独文件
typedef int Map[WIDTH][WIDTH];			// 作为将数独变元转换为连续数的映射表
typedef struct pair {
	int x, y;
}axis;
/* 砖换坐标的函数 */
inline void mapping(Map& map)
{
	int row, line ;
	int orig_size{ 5 };
	int dist{ 0 };
	for (row = 1; row <= 5; ++row,++orig_size)
	{
		for (line = 1; line <= orig_size; ++line)
		{
			map[row][line] = dist + (line - 1) * 9;
		}
		dist = map[row][line - 1] + 9;
	}
	orig_size=8;
	for (; row <= 9; ++row,--orig_size)
	{
		for (line = 1; line <= orig_size; ++line)
		{
			map[row][line] = dist + (line - 1) * 9;
		}
		dist = map[row][line - 1] + 9;
	}
}
/* 坐标砖换逆变换*/
inline axis remapping(const Map map, int var)
{
	for (int i = 1; i <= 5; ++i)
		for (int j = 1; j <= 4 + i; ++j)
			if (map[i][j] == var)
				return { i,j };
	for (int i = 6; i <= 9; ++i)
		for (int j = 1; j <= 14 - i; ++j)
			if (map[i][j] == var)
				return { i,j };
	exit(EXIT_FAILURE);
}
/* 将斜向的角度砖换*/
inline  void axis_traverse_l(Map &axis_map,const Map& map)
{
	
	for (int i = 1; i <= 5; ++i) {
		int count{ 0 };
		for (int j = 1; j <= 4 + i; ++j)
		{
#ifdef DEBUG
			printf("(%d, %d)-> ", i, j);
#endif // DEBUG


			if (j > 5) {

				axis_map[i][j] = map[j][i - (++count)];
#ifdef DEBUG
				printf("(%d,%d)\n", j, i - (count));
#endif // DEBUG

			}
			else {
				axis_map[i][j] = map[j][i];
#ifdef DEBUG
				printf("(%d,%d)\n", j, i);
#endif // DEBUG
			}
		}
	}

	for (int i = 6; i <= 9; ++i) {
		int count{ 0 };
		for (int j = 1; j <= 14 - i; ++j)
		{
#ifdef DEBUG
			printf("(%d, %d)-> ", i, j);
#endif // DEBUG
			if (14 - i - j < 4) {
				axis_map[i][j] = map[i - 5 + j][i - (++count)];
#ifdef DEBUG
				printf("(%d,%d)\n", i - 5 + j, i - count);
#endif // DEBUG
			}
			else {
				axis_map[i][j] = map[j + i-5][i];
#ifdef DEBUG
				printf("(%d,%d)\n", j +i-5, i);
#endif // DEBUG
			}
		}
	}
}
/*右斜向砖换*/
inline void axis_traverse_r(Map& axis_map, const Map& map)
{

	for (int i = 1; i <= 5; ++i) {
		int count{ 0 };
		for (int j = 1; j <= 4 + i; ++j)
		{
#ifdef DEBUG
			printf("(%d, %d)-> ", i, j);
#endif // DEBUG
			if (j > 5) {

				axis_map[i][j] = map[j][15 - j - i + (++count)];
#ifdef DEBUG
				printf("(%d,%d)\n", j, 15 - j - i + (count));
#endif // DEBUG
			}
			else{
				axis_map[i][j] = map[j][j - i + 5];
#ifdef DEBUG
			printf("(%d,%d)\n", j , j-i+5);
#endif // DEBUG
			}
		}
	}
	for (int i = 6; i <= 9; ++i) {
		int count{ 0 };
		for (int j = 1; j <= 14 - i; ++j)
		{
#ifdef DEBUG
			printf("(%d, %d)-> ", i, j);
#endif // DEBUG
			if (14 - i - j < 4) {
				axis_map[i][j] = map[i - 5 + j][10 - i];
#ifdef DEBUG
				printf("(%d,%d)\n", i - 5 + j, 10 - i);
#endif // DEBUG
			}
			else {
				axis_map[i][j] = map[j + i-5][   j];
#ifdef DEBUG
				printf("(%d,%d)\n", j+i-5, j);
#endif // DEBUG
			}
		}
	}
}
/* 解决数独的函数 Solver */
/* 将数独格局转化为dpll算法所需的cnf并保存文件 */
void TranstoCNF(Hanidoku hanidoku,char filename[],const Map&);

#endif // !HANIDOKU_H_
