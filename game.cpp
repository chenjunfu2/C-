#include "game.h"

using namespace std;


//��ȡ������
extern inline PEO find_peo(unsigned int** map, int mx, int my)
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

//�ƶ���
extern inline void move_p(const peo& pe, unsigned int** map)
{
	if (map[pe.y][pe.x] == 6)
		map[pe.y][pe.x] = 4;
	else
		map[pe.y][pe.x] = 0;

	return;
}

//�����ƶ���
extern inline void reverse_move_p(const peo& pe, unsigned int** map, int list_x, int list_y)
{
	if (map[pe.y + list_y][pe.x + list_x] == 4)
		map[pe.y + list_y][pe.x + list_x] = 6;
	else
		map[pe.y + list_y][pe.x + list_x] = 2;
}



//ȫ���ƶ����û�������
bool move_user(unsigned int** map, int mx, int my, int x, int y, peo& pe, NODE& nodeR, NODE& nodeF)
{
	bool mov = false;

	if (pe.x + x < 0 || pe.x + x >= mx || pe.y + y < 0 || pe.y + y >= my)//Խ���ж�
		return mov;
	{
		if (map[pe.y + y][pe.x + x] == 0)//��ǰ���ǿյ�
		{
			map[pe.y + y][pe.x + x] = 2;
			move_p(pe, map);
			mov = true;//�ƶ����
			Add_CpQueue(nodeR, x, y, 0);
		}
		else if (map[pe.y + y][pe.x + x] == 4)//��ǰ����Ŀ�ĵ�
		{
			map[pe.y + y][pe.x + x] = 6;
			move_p(pe, map);
			mov = true;//�ƶ����
			Add_CpQueue(nodeR, x, y, 1);
		}
	}
	if (mov == true)
	{
		pe.x += x;
		pe.y += y;
		return mov;
	}


	if (pe.x + (x * 2) < 0 || pe.x + (x * 2) >= mx || pe.y + (y * 2) < 0 || pe.y + (y * 2) >= my)//Խ���ж�
		return mov;
	{
		if (map[pe.y + y][pe.x + x] == 3)//��ǰ��������
		{
			if (map[pe.y + (y * 2)][pe.x + (x * 2)] == 0)//����ǰ���ǿյ�
			{
				map[pe.y + (y * 2)][pe.x + (x * 2)] = 3;
				map[pe.y + y][pe.x + x] = 2;
				move_p(pe, map);
				mov = true;//�ƶ����
				Add_CpQueue(nodeR, x, y, 2);
			}
			else if (map[pe.y + (y * 2)][pe.x + (x * 2)] == 4)//����ǰ����Ŀ�ĵ�
			{
				map[pe.y + (y * 2)][pe.x + (x * 2)] = 5;
				map[pe.y + y][pe.x + x] = 2;
				move_p(pe, map);
				mov = true;//�ƶ����
				Add_CpQueue(nodeR, x, y, 3);
			}
		}
		else if (map[pe.y + y][pe.x + x] == 5)//�˵�ǰ��������
		{
			if (map[pe.y + (y * 2)][pe.x + (x * 2)] == 0)//������Ŀ�ĵ�
			{
				map[pe.y + (y * 2)][pe.x + (x * 2)] = 3;
				map[pe.y + y][pe.x + x] = 6;
				move_p(pe, map);
				mov = true;//�ƶ����
				Add_CpQueue(nodeR, x, y, 4);
			}
			else if (map[pe.y + (y * 2)][pe.x + (x * 2)] == 4)//������Ŀ�ĵص�ǰ����Ŀ�ĵ�
			{
				map[pe.y + (y * 2)][pe.x + (x * 2)] = 5;
				map[pe.y + y][pe.x + x] = 6;
				move_p(pe, map);
				mov = true;//�ƶ����
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

//ȫ���ƶ���������
bool move_f(unsigned int** map, int mx, int my, peo& pe, NODE& nodeR, NODE& nodeF)
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

//����ȫ���ƶ���������
bool move_r(unsigned int** map, int mx, int my, peo& pe, NODE& nodeR, NODE& nodeF)//reserve_move_a
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
}



//���Ƶ�ͼ
template <typename T>
extern inline ERR init_map(unsigned int** map, int mx, int my, const T map_f)
{
	ERR error;

	move_g(0, 0);//����
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

//�����˸�������
template <typename T>
ERR init_peo(unsigned int** map, int mx, int my, const T map_f, const peo& pe)//, const NODE& nodeR, const NODE& nodeF
{
	ERR error;
	//COORD OldCur = get_g();
	//int list_xR, list_yR, list_nR;
	//int list_xF, list_yF, list_nF;

	//if ((Find_CpQueue(nodeR, list_xR, list_yR, list_nR).no_good)&&(Find_CpQueue(nodeF, list_xF, list_yF, list_nF).no_good))
		//return error;


	//����
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

	//�ử
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



//ǰ�����ҷ�ת
extern inline void reverse_num(int& list_x, int& list_y)
{
	list_x = -list_x;
	list_y = -list_y;
}

//�Ƿ�Ӯ
extern inline bool win_g(unsigned int** map, int mx, int my)
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

//��ȡ��������
int get_keyb(unsigned int** map, int mx, int my, peo& pe, NODE& nodeR, NODE& nodeF)
{
	//int ch, mov;
	int mov = NODO;

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
	case 'r'://undo
	case 'R':
		mov = UNDO;
		if (!move_r(map, mx, my, pe, nodeR, nodeF))
			goto start1;
		break;
	case 'f'://redo
	case 'F':
		mov = REDO;
		if (!move_f(map, mx, my, pe, nodeR, nodeF))
			goto start1;
		break;
	case 'e'://regame
	case 'E':
		ShowCursor(true);
		if (sure("����"))
		{
			mov = REGAME;
		}
		else
			mov = NODO;
		ShowCursor(false);
		break;
	case 'c'://choose
	case 'C':
		ShowCursor(true);
		if (sure("����ѡ��"))
		{
			mov = SWITCH;
		}
		else
			mov = NODO;
		ShowCursor(false);
		break;
	case 'z'://last checkpoint
	case 'Z':
		ShowCursor(true);
		if (sure("��һ��"))
		{
			mov = LASTCHECK;
		}
		else
			mov = NODO;
		ShowCursor(false);
		break;
	case 'x'://next checkpoint
	case 'X':
		ShowCursor(true);
		if (sure("��һ��"))
		{
			mov = NEXTCHECK;
		}
		else
			mov = NODO;
		ShowCursor(false);
		break;
	case 'v'://savegame
	case 'V':
		ShowCursor(true);
		if (sure("����о�"))
		{
			mov = SAVE;
		}
		else
			mov = NODO;
		ShowCursor(false);
		break;
	case 'q'://quit
	case 'Q':
		ShowCursor(true);
		if (sure("�˳�"))
		{
			mov = QUIT;
		}
		else
			mov = NODO;
		ShowCursor(false);
		break;
	default:
		goto start1;
		break;
	}

	return mov;
}

//������Ϸ
int game(map_a& mpa)
{
	peo pe;
	int keyb;

	if (error((pe = find_peo(mpa.map, mpa.mapx, mpa.mapy)).error))
		return ERROR;
	see_cursor_hide_show(false);
	if (error(init_map(mpa.map, mpa.mapx, mpa.mapy, mpa.map_f)))//����ȫ��ͼ
		return ERROR;
	cout << "��" << mpa.nodeRnum << "��" << "  ";

	while (true)
	{
		if (win_g(mpa.map, mpa.mapx, mpa.mapy))//win game�ж�
		{
			cout << endl << "You Win!";
			break;
		}

	con1:
		switch (keyb = get_keyb(mpa.map, mpa.mapx, mpa.mapy, pe, mpa.nodeR, mpa.nodeF))//�õ��������벢������Ϸ
		{
		case REDO:
			++mpa.nodeRnum;//��������ڵ�������
			--mpa.nodeFnum;//��������ڵ����ݼ�
			break;
		case MOVE:
			++mpa.nodeRnum;//��������ڵ�������
			if (mpa.nodeF.hpQueue != NULL)
			{
				Del_AllQueue(mpa.nodeF);
				mpa.nodeFnum = 0;//��������ڵ�������
			}
			break;
		case UNDO:
			--mpa.nodeRnum;//��������ڵ����ݼ�
			++mpa.nodeFnum;//��������ڵ�������
			break;
		case NODO:
			system("cls");
			init_map(mpa.map, mpa.mapx, mpa.mapy, mpa.map_f);//������������ػ�ȫ����ͼ
			cout << "��" << mpa.nodeRnum << "��" << "  ";
			goto con1;
			break;
		case REGAME:
			system("cls");
			if (mpa.checkpoint != 0)
			{
				cout << "��" << mpa.checkpoint << "��";
				Sleep(1100);
			}
			copy_lmapTOmap(mpa);
			init_map_data(mpa);
			if (error((pe = find_peo(mpa.map, mpa.mapx, mpa.mapy)).error)) return ERROR;
			see_cursor_hide_show(false);
			if (error(init_map(mpa.map, mpa.mapx, mpa.mapy, mpa.map_f))) return ERROR;
			cout << "��" << mpa.nodeRnum << "��" << "  ";
			goto con1;
		default:
			return keyb - 5;//56789->012345
			break;
		}

		see_cursor_hide_show(false);

		if (error(init_peo(mpa.map, mpa.mapx, mpa.mapy, mpa.map_f, pe)))//���Ƹ��º�ĵ�ͼ
		{
			return ERROR;//-1
		}
		cout << "��" << mpa.nodeRnum << "��" << "  ";
	}

	return END - 5;//8->3
}


