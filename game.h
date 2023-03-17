#pragma once

#ifndef _game
#define _game

#include <iostream>
#include <conio.h>
#include <stdlib.h>

#include "ConsoleAPI.h"
#include "linked_list.h"
#include "read_map.h"
#include "menu.h"
#include "error.h"

//ֱ�Ӵ���
#define REDO		0//����
#define MOVE		1//�ƶ�
#define UNDO		2//����
#define NODO		3//�ػ�
#define REGAME		4//����

//���ش���
#undef ERROR
#define ERROR		-1//�ɻָ�����
#define EXITERROR	-2//���ɻָ�����
#define LASTCHECK	5//��һ��
#define NEXTCHECK	6//��һ��
#define SWITCH		7//ѡ��
#define SAVE		8//����о�
#define QUIT		9//�˳�
#define END			10//����




//�������ṹ��
typedef struct peo
{
	int x = 0;
	int y = 0;
	ERR error;
}PEO;


//��ȡ������
extern inline PEO find_peo(unsigned int** map, int mx, int my);
//�ƶ���
extern inline void move_p(const peo& pe, unsigned int** map);
//�����ƶ���
extern inline void reverse_move_p(const peo& pe, unsigned int** map, int list_x, int list_y);



//ȫ���ƶ����û�������
bool move_user(unsigned int** map, int mx, int my, int x, int y, peo& pe, NODE& nodeR, NODE& nodeF);
//ȫ���ƶ���������
bool move_f(unsigned int** map, int mx, int my, peo& pe, NODE& nodeR, NODE& nodeF);
//����ȫ���ƶ���������
bool move_r(unsigned int** map, int mx, int my, peo& pe, NODE& nodeR, NODE& nodeF);



//���Ƶ�ͼ
template <typename T>
extern inline ERR init_map(unsigned int** map, int mx, int my, const T map_f);
//�����˸�������
template <typename T>
ERR init_peo(unsigned int** map, int mx, int my, const T map_f, const peo& pe);



//ǰ�����ҷ�ת
extern inline void reverse_num(int& list_x, int& list_y);
//�Ƿ�Ӯ
extern inline bool win_g(unsigned int** map, int mx, int my);
//��ȡ��������
int get_keyb(unsigned int** map, int mx, int my, peo& pe, NODE& nodeR, NODE& nodeF);
//������Ϸ
int game(map_a& mpa);

#endif