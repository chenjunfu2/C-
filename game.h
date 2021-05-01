#pragma once

#ifndef _Game
#define _Game
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>
#include "linked_list.h"
#include "error.h"
using namespace std;

//玩家坐标结构体
typedef struct peo {
	int x = 0;
	int y = 0;
	ERR error;
}PEO;

//获取玩家坐标
template <typename T>
static inline PEO find_peo(const T map, int mx, int my)
{
	PEO peo;
	int pen = 0;
	for (int i = 0; i < my; ++i)
	{
		for (int j = 0; j < mx; ++j)
		{
			if (map[i][j] == 2 || map[i][j] == 6)
			{
				peo.x = j;
				peo.y = i;
				++pen;
			}
		}
	}

	if (pen == 0)
		no_good(peo.error, map_PeopleNull, find_peo_F);
	else if (pen > 1)
		no_good(peo.error, map_PeopleOverFlow, find_peo_F);
	//pen == 1
	return peo;
}

//移动人
template <typename T>
static inline void move_p(const peo& pe, T map)
{
	if (map[pe.y][pe.x] == 6)
		map[pe.y][pe.x] = 4;
	else
		map[pe.y][pe.x] = 0;

	return;
}

//全局移动（用户操作）
template <typename T>
static inline bool move_user(T map, int mx, int my, int x, int y, peo& pe, NODE& nodeR, NODE& nodeF)//move_a
{
	bool mov = false;
	if (nodeF.hpQueue != NULL)
		Del_AllQueue(nodeF);

	if (pe.x + x < 0 || pe.x + x >= mx || pe.y + y < 0 || pe.y + y >= my)//越界判断
		return mov;
	{
		if (map[pe.y + y][pe.x + x] == 0)//人前面是空地
		{
			map[pe.y + y][pe.x + x] = 2;
			move_p(pe, map);
			mov = true;//移动标记
			Add_CpQueue(nodeR, x, y, 0);
		}
		else if (map[pe.y + y][pe.x + x] == 4)//人前面是目的地
		{
			map[pe.y + y][pe.x + x] = 6;
			move_p(pe, map);
			mov = true;//移动标记
			Add_CpQueue(nodeR, x, y, 1);
		}
	}
	if (mov == true)
	{
		pe.x += x;
		pe.y += y;
		return mov;
	}


	if (pe.x + (x * 2) < 0 || pe.x + (x * 2) >= mx || pe.y + (y * 2) < 0 || pe.y + (y * 2) >= my)//越界判断
		return mov;
	{
		if (map[pe.y + y][pe.x + x] == 3)//人前面是箱子
		{
			if (map[pe.y + (y * 2)][pe.x + (x * 2)] == 0)//箱子前面是空地
			{
				map[pe.y + (y * 2)][pe.x + (x * 2)] = 3;
				map[pe.y + y][pe.x + x] = 2;
				move_p(pe, map);
				mov = true;//移动标记
				Add_CpQueue(nodeR, x, y, 2);
			}
			else if (map[pe.y + (y * 2)][pe.x + (x * 2)] == 4)//箱子前面是目的地
			{
				map[pe.y + (y * 2)][pe.x + (x * 2)] = 5;
				map[pe.y + y][pe.x + x] = 2;
				move_p(pe, map);
				mov = true;//移动标记
				Add_CpQueue(nodeR, x, y, 3);
			}
		}
		else if (map[pe.y + y][pe.x + x] == 5)//人的前面是箱子
		{
			if (map[pe.y + (y * 2)][pe.x + (x * 2)] == 0)//箱子在目的地
			{
				map[pe.y + (y * 2)][pe.x + (x * 2)] = 3;
				map[pe.y + y][pe.x + x] = 6;
				move_p(pe, map);
				mov = true;//移动标记
				Add_CpQueue(nodeR, x, y, 4);
			}
			else if (map[pe.y + (y * 2)][pe.x + (x * 2)] == 4)//箱子在目的地的前面是目的地
			{
				map[pe.y + (y * 2)][pe.x + (x * 2)] = 5;
				map[pe.y + y][pe.x + x] = 6;
				move_p(pe, map);
				mov = true;//移动标记
				Add_CpQueue(nodeR, x, y, 5);
			}
		}
	}
	if (mov == true)
	{
		pe.x += x;
		pe.y += y;
		return mov;
	}
	
	return mov;
}

//全局移动（重做）
template <typename T>
static inline bool move_f(T map, int mx, int my, peo& pe, NODE& nodeR, NODE& nodeF)
{
	int list_x, list_y, list_n;
	if (See_CpQueue(nodeF, list_x, list_y, list_n).no_good)
		return false;
	Move_CpQueue_To_CpQueue(nodeR, nodeF);

	switch (list_n)
	{
	case 0:
		map[pe.y + list_y][pe.x + list_x] = 2;
		move_p(pe, map);
		break;
	case 1:
		map[pe.y + list_y][pe.x + list_x] = 6;
		move_p(pe, map);
		break;
	case 2:
		map[pe.y + (list_y * 2)][pe.x + (list_x * 2)] = 3;
		map[pe.y + list_y][pe.x + list_x] = 2;
		move_p(pe, map);
		break;
	case 3:
		map[pe.y + (list_y * 2)][pe.x + (list_x * 2)] = 5;
		map[pe.y + list_y][pe.x + list_x] = 2;
		move_p(pe, map);
		break;
	case 4:
		map[pe.y + (list_y * 2)][pe.x + (list_x * 2)] = 3;
		map[pe.y + list_y][pe.x + list_x] = 6;
		move_p(pe, map);
		break;
	case 5:
		map[pe.y + (list_y * 2)][pe.x + (list_x * 2)] = 5;
		map[pe.y + list_y][pe.x + list_x] = 6;
		move_p(pe, map);
		break;
	default:
		return false;
		break;
	}

	pe.x += list_x;
	pe.y += list_y;
	return true;
}

//前后左右反转
static inline void reverse_num(int& list_x, int& list_y)
{
	list_x = -list_x;
	list_y = -list_y;
}

//反向移动人
template <typename T>
static inline void reverse_move_p(const peo& pe, T map, int list_x, int list_y)
{
	if (map[pe.y + list_y][pe.x + list_x] == 4)
		map[pe.y + list_y][pe.x + list_x] = 6;
	else
		map[pe.y + list_y][pe.x + list_x] = 2;
}

//反向全局移动（撤销）
template <typename T>
static inline bool move_r(T map, int mx, int my, peo& pe, NODE& nodeR, NODE& nodeF)//reserve_move_a
{
	int list_x, list_y, list_n;
	if (See_CpQueue(nodeR, list_x, list_y, list_n).no_good)
		return false;
	Move_CpQueue_To_CpQueue(nodeF, nodeR);


	reverse_num(list_x, list_y);

	switch (list_n)
	{
	case 0:
	case 1:
		if (map[pe.y + list_y][pe.x + list_x] == 0)
		{
			move_p(pe, map);
			map[pe.y + list_y][pe.x + list_x] = 2;
		}
		else if (map[pe.y + list_y][pe.x + list_x] == 4)
		{
			move_p(pe, map);
			map[pe.y + list_y][pe.x + list_x] = 6;
		}
		break;
	case 2:
		reverse_move_p(pe, map, list_x, list_y);
		map[pe.y - list_y][pe.x - list_x] = 0;
		map[pe.y][pe.x] = 3;
		break;
	case 3:
		reverse_move_p(pe, map, list_x, list_y);
		map[pe.y - list_y][pe.x - list_x] = 4;
		map[pe.y][pe.x] = 3;
		break;
	case 4:
		reverse_move_p(pe, map, list_x, list_y);
		map[pe.y - list_y][pe.x - list_x] = 0;
		map[pe.y][pe.x] = 5;
		break;
	case 5:
		reverse_move_p(pe, map, list_x, list_y);
		map[pe.y - list_y][pe.x - list_x] = 4;
		map[pe.y][pe.x] = 5;
		break;
	default:
		return false;
		break;
	}

	pe.x += list_x;
	pe.y += list_y;
	return true;





	/*

	if (list_n == 1 || list_n == 2)//人前面不是箱子
	{
		if (map[pe.y + list_y][pe.x + list_x] == 0)//人前面是空地
		{
			move_p(pe, map);
			map[pe.y + list_y][pe.x + list_x] = 2;
		}
		else if (map[pe.y + list_y][pe.x + list_x] == 4)//人前面是目的地
		{
			move_p(pe, map);
			map[pe.y + list_y][pe.x + list_x] = 6;
		}
	}
	else if (list_n == 3 || list_n == 4)//人前面是箱子
	{
		if (list_n == 3)//箱子前面是空地
		{
			reverse_move_p(pe, map, list_x, list_y);
			map[pe.y - list_y][pe.x - list_x] = 0;
			map[pe.y][pe.x] = 3;
		}
		else if (list_n == 4)//箱子前面是目的地
		{
			reverse_move_p(pe, map, list_x, list_y);
			map[pe.y - list_y][pe.x - list_x] = 4;
			map[pe.y][pe.x] = 3;
		}
	}
	else if (list_n == 5 || list_n == 6)//人的前面是箱子
	{
		if (list_n == 5)//箱子在目的地
		{
			reverse_move_p(pe, map, list_x, list_y);
			map[pe.y - list_y][pe.x - list_x] = 0;
			map[pe.y][pe.x] = 5;
		}
		else if (list_n == 6)//箱子在目的地的前面是目的地
		{
			reverse_move_p(pe, map, list_x, list_y);
			map[pe.y - list_y][pe.x - list_x] = 4;
			map[pe.y][pe.x] = 5;
		}
	}

	*/
}




//改变光标
inline void move_g(short x, short y)
{
	//HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//找到控制台窗口
	//COORD coord = { x,y };//光标的结构体设置坐标
	//SetConsoleCursorPosition(handle, coord);//同步到控制台(Set设置)（Console控制台）（Cursor光标） （Position位置）
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ x,y });//同步到控制台(Set设置)（Console控制台）（Cursor光标） （Position位置）
}

//得到当前光标位置
//inline COORD get_g(void)
//{
	//ConsoleCursor
	//GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),)
//}

//光标隐藏||显示
//inline void HideCursor(DWORD x, bool y)//x=1，y=0代表光标不可见
inline void ShowCursor(bool Show)//Show=0代表光标不可见
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, Show };//x,y
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}




//绘制人附近方块
template <typename T, typename D>
static inline ERR init_peo(const T map, int mx, int my, const D map_f, const peo& pe)//, const NODE& nodeR, const NODE& nodeF
{
	ERR error;
	//COORD OldCur = get_g();
	//int list_xR, list_yR, list_nR;
	//int list_xF, list_yF, list_nF;

	//if ((Find_CpQueue(nodeR, list_xR, list_yR, list_nR).no_good)&&(Find_CpQueue(nodeF, list_xF, list_yF, list_nF).no_good))
		//return error;


	//竖画
	for (int i = pe.y - 2, j = pe.x; i < pe.y + 3; ++i)
	{
		if (i < 0 || i >= my) continue;
		if (map[i][j] >= 0 && map[i][j] <= 6)
		{
			move_g(j * 2, i);
			cout << map_f[map[i][j]];
			//cout << map[i][j];
		}
		else
		{
			system("cls");
			no_good(error, map_Default, init_peo_F);
			return error;
		}
	}

	//横画
	for (int i = pe.y, j = pe.x - 2; j < pe.x + 3; ++j)
	{
		if (j < 0 || j >= mx) continue;
		if (map[i][j] >= 0 && map[i][j] <= 6)
		{
			move_g(j * 2, i);
			cout << map_f[map[i][j]];
			//cout << map[i][j];
		}
		else
		{
			system("cls");
			no_good(error, map_Default, init_peo_F);
			return error;
		}
	}

	//move_g(OldCur.X, OldCur.Y);
	move_g(0, my);
	return error;
}


//绘制地图
template <typename T , typename D>
static inline ERR init_map(const T map, int mx, int my, const D map_f)
{
	ERR error;

	move_g(0, 0);//清屏
	for (int i = 0; i < my; ++i)
	{
		for (int j = 0; j < mx; ++j)
		{
			if (map[i][j] >= 0 && map[i][j] <= 6)
			cout << map_f[map[i][j]];
			//cout << map[i][j];
			else
			{
				system("cls");
				no_good(error, map_Default, init_map_F);
				return error;
			}
		}
		cout << endl;
	}
	return error;
}

//获取键盘输入，并进行游戏
template <typename T>
static inline int get_keyb(T map, int mx, int my, peo& pe, NODE& nodeR, NODE& nodeF)
{
	//int ch, mov;
	int mov = -1;

	start1:
	//{
		//ch = tolower(_getch());
		//if (ch != 'w' && ch != 'a' && ch != 's' && ch != 'd' && ch != 'q' && ch != 'r')
			//ch = _getch();
	//}
	
	switch (_getch())
	{
	case 72://up
	case 'w':
	case 'W':
		if ((mov = move_user(map, mx, my, 0, -1, pe, nodeR, nodeF)) == false)goto start1;
		break;
	case 75://left
	case 'a':
	case 'A':
		if ((mov = move_user(map, mx, my, -1, 0, pe, nodeR, nodeF)) == false)goto start1;
		break;
	case 77://right
	case 'd':
	case 'D':
		if ((mov = move_user(map, mx, my, +1, 0, pe, nodeR, nodeF)) == false)goto start1;
		break;
	case 80://down
	case 's':
	case 'S':
		if ((mov = move_user(map, mx, my, 0, +1, pe, nodeR, nodeF)) == false)goto start1;
		break;
	case 'r'://revoke
	case 'R':
		mov = 2;
		if (!move_r(map, mx, my, pe, nodeR, nodeF))
			goto start1;
		break;
	case 'f'://redo
	case 'F':
		mov = 0;
		if (!move_f(map, mx, my, pe, nodeR, nodeF))
			goto start1;
		break;
	case 'q'://quit
	case 'Q':
		ShowCursor(true);
		if (sure("退出"))
		{
			mov = 3;
			Del_AllQueue(nodeR);
			Del_AllQueue(nodeF);
		}
		else
			mov = 4;
		ShowCursor(false);
		break;
	default:
		goto start1;
		break;
	}

	return mov;
}

//是否赢
template <typename T>
static inline bool win_g(const T map,int mx,int my)
{
	for (int i = 0; i < my; ++i)
	{
		for (int j = 0; j < mx; ++j)
		{
			if (map[i][j] == 3)
			{
				return false;
			}
		}
	}
	return true;
}





//进行游戏
template <typename T, typename D>
inline int game(T map, int mx, int my, D map_f)
{
	peo pe = find_peo(map, mx, my);
	if (error(pe.error))
		return false;
	int num = 0;//, keyb = 0;
	NODE nodeR, nodeF;

	if (error(init_map(map, mx, my, map_f)))//绘制全地图
		return 0;
	cout << "第" << num << "步" << "  ";
	
	while (true)
	{
		if (win_g(map, mx, my))//win game判断
		{
			cout << endl << "You Win!";
			Del_AllQueue(nodeR);
			Del_AllQueue(nodeF);
			break;
		}

	con1:
		switch (get_keyb(map, mx, my, pe, nodeR, nodeF))//得到键盘输入并进行游戏
		{
		case 0:
		case 1:
			++num;//如果有移动或重做步数递增
			break;
		case 2:
			--num;//如果撤销步数递减
			break;
		case 3:
			return -1;//退出游戏并返回上层
			break;
		case 4:
			system("cls");
			init_map(map, mx, my, map_f);//如果不退出则重绘全部地图
			cout << "第" << num << "步" << "  ";
			goto con1;
			break;
		default:
			break;
		}

		if (error(init_peo(map, mx, my, map_f, pe)))//绘制更新后的地图
		{
			Del_AllQueue(nodeR);
			Del_AllQueue(nodeF);
			return 0;
		}
		cout << "第" << num << "步" << "  ";
	}

	return 1;
}


#endif