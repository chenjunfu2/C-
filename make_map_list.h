#pragma once

#ifndef _make_map_list
#define _make_map_list

#include <Windows.h>
#include <stdio.h>
#include <fstream>
#include <time.h>

#include "linked_list.h"
#include "read_map.h"
#include "error.h"

typedef unsigned long long ULL;
typedef unsigned int UI;
typedef unsigned char BYT;

#define STU(S,N) ((ULL)(((ULL)(S))<<((N-1)*8)))//str to unsigned long long
#define BTC(B,C) ((BYT)(((BYT)(B))<<(C-1)))//bin to char
#define OPB(B,N) ((B)|=((decltype(B))(1)<<(N-1))//open bin bit
#define CLB(B,N) ((B)&=(~((decltype(B))(1)<<(N-1))))//close bin bit
#define ISB(B,N) ((bool)(((B)>>(N-1))&(decltype(B)(1))))//is bin bit open

#define MAPBIN ((ULL)(STU('M', 1) | STU('A', 2) | STU('P', 3) | STU(' ', 4) | STU('B', 5) | STU('I', 6) | STU('N', 7) | STU('\0', 8)))
#define FLAG(F8,F7,F6,F5,F4,F3,F2,F1) ((BYT)(BTC(F8, 8) | BTC(F7, 7) | BTC(F6, 6) | BTC(F5, 5) | BTC(F4, 4) | BTC(F3, 3) | BTC(F2, 2) | BTC(F1, 1)))//flag

struct LinkData
{
	int list_x : 2;//�ƶ�����x
	int list_y : 2;//�ƶ�����y
	int list_n : 4;//�ƶ�����n
};

//�������ļ�ͷ�ṹ��
struct BinFileHead
{
	ULL STRULL = 0;		//�ļ�����MAPBIN
	ULL size = 0;		//�ļ���С���sizeof(BinFileHead)

	BYT flags = 0;		//�ļ����ͱ�� 1�ֽ�8λ
	/*
	��08λ	1��ʾ���޸Ĺ��ĵ�ͼ����	0��ʾ������
	��07λ	1��ʾû���޸ĵĵ�ͼ����	0��ʾ������
	��06λ	1��ʾ���߲����������ݿ���	0��ʾ������
	��05λ	1��ʾ���������������ݿ���	0��ʾ������
	��04λ	��������	��0
	��03λ	��������	��0
	��02λ	��������	��0
	��01λ	1��ʾ�ǻط��ļ�	0��ʾ�ǲо��ļ�
	*/

	UI mapX = 0;		//��ͼ��
	UI mapY = 0;		//��ͼ��
	UI nodeRN = 0;		//���߲���
	UI nodeFN = 0;		//��������

	std::streamoff mapF = 0;	//��ͼ����
	std::streamoff map = 0;		//���޸Ĺ��ĵ�ͼ
	std::streamoff lmap = 0;	//û���޸ĵĵ�ͼ
	std::streamoff nodeR = 0;	//���߲�����������
	std::streamoff nodeF = 0;	//����������������
};

extern inline void Get_Time(char lctime[]);//sizeof (lctime��ʵ��)Ӧ����Ϊ28
bool Make_Mapf_BinFile(map_a& mpa, std::fstream& fout, std::streamoff& MapfPos);
bool Make_Map_BinFile(map_a& mpa, std::fstream& fout, std::streamoff& MapPos, std::streamoff& LMapPos, bool M, bool L);
bool Make_Link_BinFile(map_a& mpa, std::fstream& fout, std::streamoff& RLinkPos, std::streamoff& FLinkPos, bool R, bool F);



ERR Make_MLD(map_a& mpa, bool playback);

#endif