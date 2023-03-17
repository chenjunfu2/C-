#pragma once

#ifndef _read_map
#define _read_map

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "error.h"
#include "linked_list.h"

typedef unsigned long long ULL;

//��ͼ����������ṹ��
typedef struct map_a
{
	//��ͼ��С��ָ��
	unsigned int mapx = 0;
	unsigned int mapy = 0;
	unsigned int** map = NULL;
	unsigned int** lmap = NULL;
	//��Ӧ��ͼ����
	char map_f[7][3] = { {0} };
	//�ؿ���
	unsigned int checkpoint = 0;
	//���ߵĲ���������
	unsigned int nodeRnum = 0;
	NODE nodeR;
	//�����Ĳ���
	unsigned int nodeFnum = 0;
	NODE nodeF;
	//�Ƿ���󼰱�����
	ERR error;
}MAPA;

//�ؿ�ѡ��ṹ��
typedef struct map_j
{
	//�ؿ�����
	ULL map_num = 0;
	//�ؿ��ļ�λ��
	std::vector<std::streamoff> map_checkpoint;
	//�Ƿ���󼰱�����
	ERR error;
}MAPJ;

//�򿪵�ͼ
extern inline ERR open_map_r(std::fstream& fin_a);
//�رյ�ͼ
extern inline void close_map_fin(std::fstream& fin_a);
//���ò��ֵ�ͼ����
extern inline void init_map_data(map_a& mpa);
//�����ͼ
bool delete_map(map_a& mpa);
//���濽���ɵ�ͼ���µ�ͼ
extern inline void copy_lmapTOmap(map_a& mpa);



//�ؿ�ת��
bool jump_map(std::fstream& fin_a, map_j& mpj, map_a& mpa, int map_num);
//������
extern inline bool jump_line(std::fstream& fin_a, map_a& mpa, int num);
//������һ����ͼ
extern inline bool next_map(std::fstream& fin_a, map_a& mpa);



//��ȡ�ؿ���
bool read_checkpoint(std::fstream& fin_a, map_a& mpa, map_j& mpj, int mpn);
//��ȡ��ͼ����
bool read_symbol(std::fstream& fin_a, map_a& mpa);
//��ȡ��ͼ��С(x,y)
bool read_size(std::fstream& fin_a, map_a& mpa);
//�����ͼ�ڴ�
bool new_map(map_a& mpa);
//��ȡ��ͼ����
bool read_map(std::fstream& fin_a, map_a& mpa);
//�ؿ�������ȡ����ÿһ�ؿ����ļ��������λ�ô���
map_j read_map_all(std::fstream& fin_a);
//�ؿ�ѡ��˵�
int map_jump_menu(map_j& mp_jump);



//��ȡ�ؿ�
map_a read_mapCp(map_j& mpj, std::fstream& fin_a, int mpn);

#endif