#pragma once

#ifndef _menu
#define _menu

#include <iostream>
#include <string>
#include <conio.h>

#define Cooder				"С��"
#define VersionNumber		"3.6"
#define CopyRightYearBeg	"2021"
#define CopyRightYearEnd	"2023"

//���˵�
extern inline int menu_page(void);
//��ʼ��Ϸ
extern inline int menu_game(void);
//��Ϸ˵��
extern inline void menu_explain(void);
//����Ӧ��
extern inline void menu_about(void);



//�ȴ��û���һ������
extern inline void sypose(void);
//���û�ȷ���Ƿ���ĳ��
extern inline bool sure(const char* be);

#endif