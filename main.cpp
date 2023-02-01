// ���� ���α׷�

#include "function.h"

int main(void)
{
	using std::cout;
	using std::endl;
	using std::cin;
	using std::cerr;
	
	// ����
	console(30, 30);
	CursorView(0);
	box(0, 0, 28, 28, "���� ������ ��� ���α׷�", ALIGNMENT::CENTER);
	box(0, 1, 28, 1, "Version 1.35", ALIGNMENT::RIGHT, 0);
	box(0, 2, 28, 1, "������: ����ȣ", ALIGNMENT::RIGHT, 0);
	box(0, 3, 28, 1, "press space to start", ALIGNMENT::CENTER, 0);
	int endFlag = 1;		// �÷���
	int key;
	int menu = 0;		// ���߿��� ���� �뵵�� ���� ��
	while (endFlag)
	{
		key = _getch();		// ������ Ű�� �ٷ� �Է�
		if (int(KEY::SPACE) == key)
			endFlag = 0;
	}
	// �޴� ����
	system("cls");
	const char* startMenu[] = {
		"������ ���", "�����ͺ��̽� �߰�", "����"
	};
	box(0, 0, 28, 28);
	box(9, 5, 10, 1, "�޴�", ALIGNMENT::CENTER);
	endFlag = 1;
	while (endFlag)
	{
		for (int i = 0; i < 3; i++)
		{
			if (menu == i)
			{
				color(B_COLOR, H_COLOR);
				box(9, 9 + 4 * i, 10, 1, startMenu[i], ALIGNMENT::CENTER);
				color(B_COLOR, N_COLOR);
			}
			else
				box(9, 9 + 4 * i, 10, 1, startMenu[i], ALIGNMENT::CENTER);
		}
		key = _getch();
		switch (key)
		{
		case (int)KEY::UP:
			if (menu > 0)
				menu--;
			break;
		case (int)KEY::DOWN:
			if (menu < 2)
				menu++;
			break;
		case (int)KEY::ENTER:
			endFlag = 0;
			break;
		default:
			break;
		}
	}
	switch (menu)
	{
	case 0:
		damage_calculation();
		break;
	case 1:
		revise_database();
		break;
	case 2:
		cout << "�����մϴ�.\n";
		break;
	}

	eatline();
	return 0;
}
	
