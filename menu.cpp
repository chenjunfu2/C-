#include "menu.h"

using namespace std;


//���˵�
extern inline int menu_page(void)
{
	cout << "------------Ŀ¼-----------\n";
	cout << " 1.��ʼ��Ϸ\t2.��Ϸ˵��\n";
	cout << " 3.����Ӧ��\t4.�˳�Ӧ��\n";
	cout << "---------------------------\n";
	cout << "\n�밴�¶�Ӧ����ѡ��\n";
	int input = _getch();
	while (input < '1' || input > '4')
		input = _getch();

	return input;
}

//��ʼ��Ϸ
extern inline int menu_game(void)
{
	cout << "------------��Ϸ-----------\n";
	cout << " 1.����ģʽ\t2.�о�ģʽ\n";
	cout << " 3.�ط�ģʽ\t4.�����ϲ�\n";
	cout << "---------------------------\n";
	cout << "\n�밴�¶�Ӧ����ѡ��\n";
	int input = _getch();
	while (input < '1' || input > '4')
		input = _getch();

	return input;
}

//��Ϸ˵��
extern inline void menu_explain(void)
{
	cout << "��Ϸ˵����\n\n";
	cout << "1.��ʹ��:\n"\
		"  W (��) A (��) S (��) D (��) ��\n"\
		"  ��(��) ��(��) ��(��) ��(��) �ٿ�����\n";
	cout << "2.����Ϸʱ:\n"\
		"  ��Q���򷵻���һ����\n"\
		"  ��R��������һ����\n"\
		"  ��F����������һ����\n"\
		"  ��E�������浱ǰ�ؿ�\n"\
		"  ��Z����ת����һ�ؿ�\n"\
		"  ��X����ת����һ�ؿ�\n"\
		"  ��C�������ѡ��ģʽ\n"\
		"  ��V���򱣴浱ǰ�о�\n";
	cout << "3.�������ִ�Сд����Ҫע�������Ҫʹ��Ӣ�����뷨�����򰴼��ᱻ���뷨����ץ�ߵ����޷���ʱ����\n";
	cout << "4.��Ϸ��ͼ�ڵ�һ�δ�ʱ�����ɣ���Ҫ������Ϸ\n";
	cout << "5.��Ϸ��ͼ�ɱ༭������ɾ�������ϸ����ص�ͼע��������ݵ�ͼ�����Ͷ�Ӧ�޸�\n\n";
	cout << "��л���������֧�֣�����BUG���뼰ʱ����Ŷ~\n";
	cout << "\n�����������...\n";
	(void)_getch();

	return;
}

//����Ӧ��
extern inline void menu_about(void)
{
	cout << "---------------����--------------\n";
	cout << " �� д �ߣ�" Cooder "\n";
	cout << " ��д���ڣ�" __DATE__ " " __TIME__ "\n";//CoodingDay
	cout << " �� �� �ţ�" VersionNumber "\n";
	cout << " ��Ȩ���У�CopyRight(C)" CopyRightYearBeg "-" CopyRightYearEnd "\n";
	cout << "---------------------------------\n";
	cout << "\n�����������...\n";
	(void)_getch();

	return;
}



//�ȴ��û���һ������
extern inline void sypose(void)
{
	cout << "�밴���������. . .";
	(void)_getch();
}

//���û�ȷ���Ƿ���ĳ��
extern inline bool sure(const char* be)
{
	cout << "\nȷ��Ҫ" << be << "��(y/n)\n";

	int input;
	while ((input = tolower(getchar())) != 'y' && input != 'n')
	{
		if (input != '\n')
			while (getchar() != '\n')continue;
	}
	if (input != '\n')
		while (getchar() != '\n')continue;

	if (input == 'y')
		return true;
	else
		return false;
}