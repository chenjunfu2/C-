#pragma once

#ifndef _linked_list
#define _linked_list

#include <cstddef>
#include <new>

#include "error.h"


//���ݽṹ��
typedef struct Queue
{
	Queue* uQueue = NULL;//��һ�ڵ�
	int list_x = 0;//�ƶ�����x
	int list_y = 0;//�ƶ�����y
	int list_n = 0;//�ƶ�����n
	Queue* nQueue = NULL;//��һ�ڵ�
}QUEUE;

//����ָ��ṹ��
typedef struct Node
{
	QUEUE* hpQueue = NULL;//ͷ�ڵ�ָ��
	QUEUE* cpQueue = NULL;//β�ڵ�ָ��
	//int numQueue;//�������
}NODE;


//��ͷ�����һ��
extern inline ERR Add_HpQueue(NODE& node, int list_x, int list_y, int list_n);
//��β�����һ��
extern inline ERR Add_CpQueue(NODE& node, int list_x, int list_y, int list_n);



//�鿴β��һ��
extern inline ERR See_CpQueue(const NODE& node, int& list_x, int& list_y, int& list_n);
//�鿴ͷ��һ��
extern inline ERR See_HpQueue(const NODE& node, int& list_x, int& list_y, int& list_n);



//�ƶ�β��һ�����һ������β��
extern inline ERR Move_CpQueue_To_CpQueue(NODE& nodeI, NODE& nodeO);
//�ƶ�ͷ��һ�����һ������ͷ��
extern inline ERR Move_HpQueue_To_HpQueue(NODE& nodeI, NODE& nodeO);



//������ȡ������
template <typename T>
extern inline ERR See_All_G(const NODE& node, T fSee_P);
//������ȡ������
template <typename T>
extern inline ERR See_All_B(const NODE& node, T fSee_P);
//������ӣ�����
template <typename T>
extern inline ERR Add_All_G(NODE& node, T fAdd_P);
//������ӣ�����
template <typename T>
extern inline ERR Add_All_B(NODE& node, T fAdd_P);



//��β��ɾ��һ��
extern inline ERR Del_CpQueue(NODE& node, int& list_x, int& list_y, int& list_n);
//ɾ������
extern inline ERR Del_AllQueue(NODE& node);

#endif