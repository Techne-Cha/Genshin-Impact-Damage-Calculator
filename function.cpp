// �߿� �Լ� �ۼ�

#include "function.h"

void revise_database()		// ������ ���̽� �߰�/����/�˻�
{
	using std::cout;
	using std::endl;
	using std::cin;
	using std::cerr;
	std::fstream finout;
	std::ofstream fout;		// �׸� ������ ����� ���⽺Ʈ��
	Enemy enemy;
	int count = 0;		// �� ��
	int key;		// Ű �Է°�
	int selectFlag = 0;		// �޴� ���� �÷���, �����ϸ� 1
	int endFlag = 1;		// �ݺ� ���� �÷���, �����Ϸ��� 0
	int menu = 21;		// �޴� ������ <0~19 : �� ���� ���� ���ʴ��, 20 : ������ ����, 21 : �߰�, 22 : �˻�, 23 : ����>
	int page = 1;		// �� �������� 20�� ����
	int maxPage = 1;		// �ִ� ������
	int remainder;		// ���� ������(52�� -> 12���� ������), 20�� �������� �� �� �ִ�
	int pageChanged = 0;		// ��� ������ �ٲ�� 1
	const char* menus[] = { "�߰�", "�˻�", "����" };
	int i;		// for �� ��

	// �������̽�
	console(60, 30);
	box(0, 0, 58, 28);		// ��ü â
	box(0, 0, 47, 24);		// ���� ���� ���â
	box(0, 0, 47, 1);		// ���� ���� ����
	box(0, 0, 23, 1, "�� ���� ����", ALIGNMENT::CENTER, 0);
	for (i = 0; i < int(ELEMENT::NUMBER); i++)
		box(24 + i * 3, 0, 2, 1, ELEMENT_NAME[i], ALIGNMENT::LEFT, 0);
	box(0, 23, 47, 1);		// ������ ����â
	box(0, 25, 58, 3);		// �����â

	finout.open("������.dat", std::ios_base::in | std::ios_base::out | std::ios_base::binary);		// �б⾲�� ���
	if (!finout.is_open())
	{
		gotoxy(1, 26);
		cerr << "������ �� �� �����ϴ�.\n";
		exit(EXIT_FAILURE);
	}
	while (finout.read((char*)&enemy, sizeof enemy))		// ó�� �������� ������ �о �� ���� �ľ���
		count++;
	if (0 == count % 20)		// 20���� �����������(ex.. 40)
	{
		maxPage = count / 20;
		remainder = 20;
	}
	else
	{
		maxPage = count / 20 + 1;
		remainder = count % 20;
	}
	finout.clear();
	finout.seekg(0);		// �Է������� ó������

	while (endFlag)
	{
		while (!selectFlag)
		{
			// ���ʸ޴� ���
			finout.seekg((page - 1) * 20 * sizeof enemy);		// �������� �������� �Է������� ��ġ
			if (pageChanged)		// ������ �ٲ������
			{
				box(0, 2, 47, 20, nullptr, ALIGNMENT::LEFT, 0, 1);		// ������ ��� �����
				pageChanged = 0;
			}
			if (page == maxPage)		// ������ �������̸�
				for (i = 0; i < remainder; i++)
				{
					if (menu == i)
						color(B_COLOR, H_COLOR);
					gotoxy(1, i + 3);
					cout << "#" << i + 1 + 20 * (page - 1);
					finout.read((char*)&enemy, sizeof enemy);
					enemy.show_info1({ 4, short(i + 3) });
					if (menu == i)
						color(B_COLOR, N_COLOR);
				}
			else		// ������ ������ �ƴϸ�
			{
				for (i = 0; i < 20; i++)
				{
					if (menu == i)
						color(B_COLOR, H_COLOR);
					gotoxy(1, i + 3);
					cout << "#" << i + 1 + 20 * (page - 1);
					finout.read((char*)&enemy, sizeof enemy);
					enemy.show_info1({ 4, short(i + 3) });
					if (menu == i)
						color(B_COLOR, N_COLOR);
				}
			}
			// ������ ���� ���
			if (menu == 20)
				color(B_COLOR, H_COLOR);
			gotoxy(21, 24);
			cout << "��";
			gotoxy(23, 24);
			cout << "  ";		// �����
			gotoxy(23, 24);
			cout << page;
			gotoxy(24, 24);
			cout << "/";
			gotoxy(25, 24);
			cout << maxPage;
			gotoxy(27, 24);
			cout << "��";
			if (menu == 20)
				color(B_COLOR, N_COLOR);
			// ������ �޴� ���
			for (i = 0; i < 3; i++)
			{
				if (menu == i + 21)		// 21,22,23 �� ������ �޴��� menu�϶�
				{
					color(B_COLOR, H_COLOR);
					box(52, 8 + i * 4, 2, 1, menus[i]);
					color(B_COLOR, N_COLOR);
				}
				else
					box(52, 8 + i * 4, 2, 1, menus[i]);
			}

			key = _getch();
			switch (key)
			{
			case (int)KEY::UP:
				if (21 <= menu && menu <= 23)		// ������ �޴�
				{
					if (menu != 21)		// '�߰�'������ �ȿö󰡸� ��
						menu--;
				}
				else		//  ���� �޴�
				{
					if (page != maxPage)		// ���� �޴������� ������ ������ �ƴϸ�
					{
						if (menu != 0)		// �� �������� �ȿö󰡸� �ȴ�
							menu--;
					}
					else		// ������ ��������
					{
						if (menu == 20)			// ������ �����̸�
							menu = remainder - 1;		// �ش� �������� ������ �޴��� �ö󰣴�
						else if (menu != 0)		// �ƴϸ� �� �������� �ȿö󰡸� �ȴ�
							menu--;
					}
				}
				break;
			case (int)KEY::DOWN:
				if (21 <= menu && menu <= 23)		// ������ �޴�
				{
					if (menu != 23)		// '����'������ �ȳ������� ��
						menu++;
				}
				else		//  ���� �޴�
				{
					if (page != maxPage)		// ���� �޴������� ������ ������ �ƴϸ�
					{
						if (menu != 20)		// ������ ���������� �ȳ������� �ȴ�
							menu++;
					}
					else		// ������ ��������
					{
						if (menu <= remainder - 2)		// �ش� �������� ������ �޴��� �ƴϸ�
							menu++;
						else if (menu == remainder - 1)		// �ش� �������� ������ �޴��̸�
							menu = 20;		// ������ ������ ��������
					}
				}
				break;
			case (int)KEY::LEFT:
				if (21 <= menu)		// ������ �޴��϶�
					menu = 0;		// ���� �޴� ���� ����
				else if (20 == menu)		// ������ �����϶�
					if (2 <= page)		// 2������ �̻��̸�
					{
						page--;
						pageChanged = 1;
					}
				break;
			case (int)KEY::RIGHT:
				if (menu <= 19)		// ���� �޴��϶�
					menu = 21;		// ������ �޴� ���� ����
				else if (20 == menu)		// ������ �����϶�
					if (page < maxPage)		// �ִ����������� ������
					{
						page++;
						pageChanged = 1;
					}
				break;
			case (int)KEY::ENTER:
				selectFlag = 1;
				break;
			default:
				break;
			}
		}

		// �޴��� �����Ǿ���
		selectFlag = 0;
		if (!(0 <= menu && menu <= 23))
		{
			gotoxy(1, 26);
			cerr << "�����Դϴ�. �����մϴ�.";
			exit(EXIT_FAILURE);
		}
		// ����/����
		if (0 <= menu && menu <= 19)
		{
			CursorView(1);
			box(0, 25, 58, 3, nullptr, ALIGNMENT::LEFT, 0, 1);		// �����â �����
			gotoxy(1, 26);
			cout << "�ش� ������ �����մϴ�. �ش� ������ ������ �����Ϸ��� '����'�� �Է����ּ���.";
			gotoxy(1, 27);
			cout << "���̸�: ";
			cin.getline(enemy.name, ENEMY_NAME_LENGTH);
			
			if (!strcmp("����", enemy.name))		// �� ���ڿ��� ������
			{
				gotoxy(1, 28);
				cout << "���� �����Ͻðڽ��ϱ�?(y/n) : ";
				if ('y' == cin.get())
				{
					fout.open("temp.dat", std::ios_base::binary);
					finout.seekg(0);
					for (i = 0; i < count; i++)
					{
						finout.read((char*)&enemy, sizeof enemy);
						if (i == ((page - 1) * 20 + menu))		// �����Ϸ��� ��ȣ�� �� ���Ͽ� ���� �ʴ´�
							continue;
						fout.write((char*)&enemy, sizeof enemy);
					}
					fout.close();
					finout.close();
					remove("������.dat");
					rename("temp.dat", "������.dat");
					box(0, 25, 58, 3, nullptr, ALIGNMENT::LEFT, 0, 1);		// �����â �����
					gotoxy(1, 26);
					cout << "���� �Ϸ��߽��ϴ�.";
					// ��Ʈ���� �ٽ� �����ϰ� count�� �ٲپ��־�� �Ѵ�
					finout.open("������.dat", std::ios_base::in | std::ios_base::out | std::ios_base::binary);		// �б⾲�� ���
					count--;
					if (0 == count % 20)		// 20���� �����������(ex.. 40)
					{
						maxPage = count / 20;
						remainder = 20;
					}
					else
					{
						maxPage = count / 20 + 1;
						remainder = count % 20;
					}
					page = 1;
					pageChanged = 1;
				}
				else
				{
					box(0, 25, 58, 3, nullptr, ALIGNMENT::LEFT, 0, 1);		// �����â �����
					gotoxy(1, 26);
					cout << "�������� �ʾҽ��ϴ�.";
				}
			}
			else		// ����
			{
				gotoxy(1, 28);
				for (int i = 0; i < (int)ELEMENT::NUMBER; i++)
					cout << ELEMENT_NAME[i] << " ";
				cout << "����(���Ѵ�� # �Է�): ";
				for (int i = 0; i < (int)ELEMENT::NUMBER; i++)
				{
					if (!(cin >> enemy.resistance[i]))		// ���� �ԷµǸ�
					{
						cin.clear();
						if ('#' == cin.get())		// ���Ѵ� �Է��� ���� #�� �Է�������
							enemy.resistance[i] = INT_MAX;
						else
							enemy.resistance[i] = 0;
					}
				}
				eatline();
				box(0, 25, 58, 3, nullptr, ALIGNMENT::LEFT, 0, 1);		// �����â �����
				gotoxy(1, 26);
				cout << "������ ���� �Է��ϼ̽��ϴ�";
				enemy.show_info1({ 4, 27 });
				gotoxy(1, 28);
				cout << "�����Ϸ��� y�� �����ּ���: ";
				if ('y' == cin.get())
				{
					finout.seekp(((page - 1) * 20 + menu) * sizeof enemy);		// �ش� �� ������ �ִ� ���� ��������� ��ġ
					finout.write((char*)&enemy, sizeof enemy);
					box(0, 25, 58, 3, nullptr, ALIGNMENT::LEFT, 0, 1);		// �����â �����
					gotoxy(1, 26);
					cout << "�����Ǿ����ϴ�.";
					pageChanged = 1;		// ���� ������°� ����
				}
				else
				{
					box(0, 25, 58, 3, nullptr, ALIGNMENT::LEFT, 0, 1);		// �����â �����
					gotoxy(1, 26);
					cout << "�������� �ʾҽ��ϴ�.";
				}
			}
			eatline();
			CursorView(0);
		}
		// �߰�
		if (21 == menu)
		{
			box(0, 25, 58, 3, nullptr, ALIGNMENT::LEFT, 0, 1);		// �����â �����
			gotoxy(1, 26);
			cout << "�����ͺ��̽��� �߰��մϴ�. �����Ϸ��� q�� �Է����ּ���";
			gotoxy(1, 27);
			CursorView(1);
			cout << "���̸�: ";
			while (cin.getline(enemy.name, ENEMY_NAME_LENGTH))
			{
				if (!strcmp("q", enemy.name))		// �� ���ڿ��� ������
					break;
				gotoxy(1, 28);
				for (int i = 0; i < (int)ELEMENT::NUMBER; i++)
					cout << ELEMENT_NAME[i] << " ";
				cout << "����(���Ѵ�� # �Է�): ";
				for (int i = 0; i < (int)ELEMENT::NUMBER; i++)
				{
					if (!(cin >> enemy.resistance[i]))		// ���� �ԷµǸ�
					{
						cin.clear();
						if ('#' == cin.get())		// ���Ѵ� �Է��� ���� #�� �Է�������
							enemy.resistance[i] = INT_MAX;
						else
							enemy.resistance[i] = 0;
					}
				}
				eatline();
				box(0, 25, 58, 3, nullptr, ALIGNMENT::LEFT, 0, 1);		// �����â �����
				gotoxy(1, 26);
				cout << "������ ���� �Է��ϼ̽��ϴ�";
				enemy.show_info1({ 4, 27 });
				gotoxy(1, 28);
				cout << "�����Ϸ��� y�� �����ּ���: ";
				if ('y' == cin.get())
				{
					finout.seekp(0, std::ios::end);		// ��������� �������� ��ġ
					finout.write((char*)&enemy, sizeof enemy);
					box(0, 25, 58, 3, nullptr, ALIGNMENT::LEFT, 0, 1);		// �����â �����
					gotoxy(1, 26);
					cout << "����Ǿ����ϴ�. �����Ϸ��� q�� �Է����ּ���";
					count++;
				}
				else
				{
					box(0, 25, 58, 3, nullptr, ALIGNMENT::LEFT, 0, 1);		// �����â �����
					gotoxy(1, 26);
					cout << "�������� �ʾҽ��ϴ�. �����Ϸ��� q�� �Է����ּ���";
				}
				eatline();
				gotoxy(1, 27);
				cout << "���̸�: ";
			}
			// count�� �ٲ�����Ƿ� �ٽ� maxPage�� remainder�� �����Ѵ�
			if (0 == count % 20)		// 20���� �����������(ex.. 40)
			{
				maxPage = count / 20;
				remainder = 20;
			}
			else
			{
				maxPage = count / 20 + 1;
				remainder = count % 20;
			}
			CursorView(0);
		}
		// �˻�
		if (22 == menu)
		{
			char enemyName[ENEMY_NAME_LENGTH];		// �˻��� �� �̸�
			CursorView(1);
			box(0, 25, 58, 3, nullptr, ALIGNMENT::LEFT, 0, 1);		// �����â �����
			gotoxy(1, 26);
			cout << "�˻��� �� �̸��� �Է����ּ���: ";
			while (cin.getline(enemyName, ENEMY_NAME_LENGTH))
			{
				if (!strcmp("�׸�", enemyName))
					break;
				finout.seekg(0);		// ���� �����͸� ���� ������ġ�� ��ġ��Ŵ
				box(0, 2, 47, 20, nullptr, ALIGNMENT::LEFT, 0, 1);		// ������ ��� �����
				int j = 0;		// �ִ� 20�������� ����Ϸ���
				for (i = 0; i < count; i++)		// �� ����ŭ �ݺ��Ѵ�
				{
					finout.read((char*)&enemy, sizeof enemy);
					if (strstr(enemy.name, enemyName))		// ã������ �̸��� ���ԵǸ�
					{
						gotoxy(1, j + 3);
						cout << "#" << i + 1;
						enemy.show_info1({ 4, short(j + 3) });
						if (++j >= 20)
							break;		// for�� ����
					}
				}
				box(0, 25, 58, 3, nullptr, ALIGNMENT::LEFT, 0, 1);		// �����â �����
				gotoxy(1, 26);
				if (!j)		// �˻���� ������
					cout << "�˻��Ͻ� �� �̸��� �����ϴ� ���� �����ϴ�.";
				else
					cout << "�˻��Ͻ� �� �̸��� �����ϴ� ������ ���� �����ϴ�.";		// �ִ� 20�� ���
				gotoxy(1, 27);
				cout << "�˻��� �� �̸��� �Է����ּ���, �׸��Ϸ��� '�׸�' �Է��ϼ���: ";
			}
			if (!cin)		// �ʹ� ���� ���ڸ� �Է��ϸ�
			{
				cin.clear();
				eatline();
			}
			pageChanged = 1;		// ������ �����Ƿ� �ٽ� ���� ���� ����ϰ� �ϱ� ���� ����
			CursorView(0);
		}
		// ����
		if (23 == menu)
			endFlag = 0;
	}
	finout.close();
	return;
}
void damage_calculation()		// ������ ���
{
	using std::cout;
	using std::endl;
	using std::cin;
	using std::cerr;

	Keqing ��û;
	Klee Ŭ��;
	Xingqiu ����;
	Noelle �뿤;
	Character* p_characters[CHARACTERS] = { &��û, &Ŭ��, &����, &�뿤 };
	Character* p_main = nullptr;		// ���õ� ĳ���� ��ü�� ����Ű�� ������
	Enemy enemy;
	Buff buff;
	std::ofstream fout;
	std::ifstream fin;
	int selectFlag = 0;		// ���õǸ� 1
	int endFlag = 1;		// ������ ������ 0
	int menu = 0;		// �޴� ������
	int buffmenu;		// ���� ������ ����� �޴�
	int backstep = 0;		// '����'�� ������ 1
	int key;		// �Է� Ű
	const char* menu2[] = {
		"�缳��", "���", "����"
	};
	const char* menu3[] = {
		"����", "�����", "����ü", "����"
	};
	char enemyName[ENEMY_NAME_LENGTH];		// �� �̸�(�˻��� ����)
	int count;		// ��� ��� ����
	int sknum;		// ��ų��ȣ
	console(60, 30);
	while (1)
	{
		// ĳ���� ����
		box(0, 0, 58, 26, nullptr, ALIGNMENT::LEFT, 1, 1);
		box(0, 0, 13, 26);		// ����â
		box(14, 16, 13, 1);		// �� �ΰ����� â
		box(14, 18, 44, 1);		// �� ���� â
		box(14, 20, 44, 6);		// ���â
		box(0, 27, 58, 1);		// �Է�â
		box(0, 0, 13, 1, "���� ��� ������ ĳ����", ALIGNMENT::CENTER, 1, 1);
		selectFlag = 0;
		while (!selectFlag)
		{
			for (int i = 0; i < CHARACTERS; i++)
			{
				if (menu == i)
				{
					color(B_COLOR, H_COLOR);
					box(0, 3 + 3 * i, 13, 1, p_characters[i]->return_name().c_str(), ALIGNMENT::RIGHT, 0);
					color(B_COLOR, N_COLOR);
				}
				else
					box(0, 3 + 3 * i, 13, 1, p_characters[i]->return_name().c_str(), ALIGNMENT::RIGHT, 0);
			}
			key = _getch();
			switch (key)
			{
			case (int)KEY::UP:
				if (menu > 0)
					menu--;
				break;
			case (int)KEY::DOWN:
				if (menu < CHARACTERS - 1)
					menu++;
				break;
			case (int)KEY::ENTER:
				selectFlag = 1;
				break;
			default:
				break;
			}
		}
		p_main = p_characters[menu];		// ĳ���� ���� �Ϸ�

		// ĳ�� ���� ���Ͽ��� �о� ���÷���
		box(0, 0, 13, 1, p_main->return_name().c_str(), ALIGNMENT::CENTER, 0, 1);
		box(0, 2, 13, 24, nullptr, ALIGNMENT::LEFT, 0, 1);		// ����â �����
		std::string filename = p_main->return_name() + ".txt";		// ���� �̸� �����
		fin.open(filename);
		if (!fin.is_open())
		{
			gotoxy(1, 3);
			cerr << filename << " ������ �� �� �����ϴ�.";
			gotoxy(1, 4);
			cerr << "���ο� ������ ����ϴ�.";
			set_charinfo(*p_main, { 1, 28 }, 58);
			fin.open(filename);		// �ٽ� ���� �õ�
			if (!fin.is_open())
			{
				gotoxy(1, 5);
				cerr << filename << " ������ �� �� �����ϴ�";
				gotoxy(1, 6);
				cerr << "�����մϴ�.";
				exit(EXIT_FAILURE);
			}
		}
		// ������ ����� �������� ������� �� �� �ִ�
		box(0, 2, 13, 24, nullptr, ALIGNMENT::LEFT, 0, 1);		// ����â �����
		if (!(fin >> *p_main))		// �Է� �ҷ��̸�
		{
			gotoxy(1, 3);
			cerr << "���� ���뿡 ������ �ֽ��ϴ�.\n�����մϴ�.\n";
			fin.close();
			exit(EXIT_FAILURE);
		}
		fin.close();

		// ���� ���
		p_main->show_stat({ 1, 3 });		// ���� ���
		p_main->show_skills({ 17, 1 });		// ��ų ���
		
		
		backstep = 0;
		// �б���(�缳��, ���, �����̵�)
		while (!backstep)
		{
			menu = 0;		// ���߿��� ���� �뵵�� ���� ��
			selectFlag = 0;
			while (!selectFlag)
			{
				for (int i = 0; i < 3; i++)
				{
					if (menu == i)
					{
						color(B_COLOR, H_COLOR);
						box(1 + 4 * i, 24, 3, 1, menu2[i], ALIGNMENT::CENTER, 0);
						color(B_COLOR, N_COLOR);
					}
					else
						box(1 + 4 * i, 24, 3, 1, menu2[i], ALIGNMENT::CENTER, 0);
				}
				key = _getch();
				switch (key)
				{
				case (int)KEY::LEFT:
					if (menu > 0)
						menu--;
					break;
				case (int)KEY::RIGHT:
					if (menu < 2)
						menu++;
					break;
				case (int)KEY::ENTER:
					selectFlag = 1;		// ���õ�
					break;
				default:
					break;
				}
			}
			switch (menu)
			{
			case 0:		// ���� �缳��
				set_charinfo(*p_main, { 1, 28 }, 58);
				continue;		// �б������� �ٽ� ����
			case 1:		// ��� ����
				break;
			case 2:
				backstep = 1;		// ĳ���� ����â���� �ٽ� �Ѿ
				continue;
			default:
				break;
			}

			// �� �˻� �� Ư��
			enemy = ememy_identification();
			enemy.show_info1({ 15, 19 });
			enemy.change_info({ 1, 28 }, 58);
			enemy.show_info1({ 15, 19 });
			enemy.show_info2({ 15, 17 });
			
			// ���� �ʱ�ȭ
			buff.reset_buff();
			
			// ��ų ����
			box(14, 20, 44, 6, nullptr, ALIGNMENT::LEFT, 0, 1);		// ���â �����
			gotoxy(15, 21);
			cout << "��ų�� �����ϼ���";
			menu = 0;		// ���߿��� ���� �뵵�� ���� ��
			selectFlag = 0;
			while (!selectFlag)
			{
				p_main->show_skills({ 17,1 }, & menu);
				key = _getch();
				switch (key)
				{
				case (int)KEY::UP:
					if (0 < menu)		// 1 �̻��̸� (�� ù ��ų������ �ö󰡸� �ȵ�)
						menu--;
					break;
				case (int)KEY::DOWN:
					menu++;		// ������ �÷��� show_skills���� ��������
					break;
				case (int)KEY::ENTER:
					selectFlag = 1;		// ���õ�
					break;
				default:
					break;
				}
			}
			box(14, 20, 44, 6, nullptr, ALIGNMENT::LEFT, 0, 1);		// ���â �����
			gotoxy(15, 21);
			sknum = menu;		// ��ų ���� �Ϸ�
			cout << "���õ� ��ų�� " << menu << "���Դϴ�.";
			p_main->reflect_passive(sknum, enemy, buff, { 1, 28 }, 58);		// ĳ���� �нú� ����
			box(0, 2, 13, 24, nullptr, ALIGNMENT::LEFT, 0, 1);		// ����â �����
			p_main->show_stat({ 1, 3 }, buff);		// ���� ���
			enemy.show_info1({ 15, 19 });
			enemy.show_info2({ 15, 17 });
			p_main->show_all_damage(sknum, enemy, buff, { 15, 21 });		// ������ ���
			// �� �� ��� �Ĵ� ���� �޴��� ����
			menu = 0;		// ���� �޴��� ��ų���� show_skills �Լ��� �����ϰ�, ����, �����, ����ü, ���� �޴��� -1, -2, -3, -4 �� ���� ����
			endFlag = 1;
			while (endFlag)
			{
				selectFlag = 0;
				while (!selectFlag)
				{
					// ����, �����, ����ü, ���� �޴� ǥ��
					for (int i = 1; i <= 4; i++)
					{
						if (menu == -i)
							color(B_COLOR, H_COLOR);
						box(54, i * 4 - 3, 3, 1, menu3[i - 1], ALIGNMENT::CENTER, 1);
						if (menu == -i)
							color(B_COLOR, N_COLOR);
					}
					// ��ų �޴� ǥ��
					p_main->show_skills({ 17,1 }, &menu);

					key = _getch();
					switch (key)
					{
					case (int)KEY::UP:
						if (0 < menu)		// 1 �̻��̸� (�� ù ��ų������ �ö󰡸� �ȵ�)
							menu--;
						else if (menu <= -2)		// -2 �����̸�(-1������ �ö󰡸� �ȵ�)
							menu++;
						break;
					case (int)KEY::DOWN:
						if (0 <= menu)		// ��ų�޴����
							menu++;		// ������ �÷��� show_skills���� ��������
						else if (-3 <= menu)		// ��ų �޴� �ƴϰ� -3 �̻��̸� (- 4������ �ȳ������� ��)
							menu--;
						break;
					case (int)KEY::LEFT:
						if (menu < 0)		// ��ų �޴� �ƴϸ�
							menu = 0;		// �� ù ��ų��
						break;
					case (int)KEY::RIGHT:
						if (0 <= menu)		// ��ų �޴����
							menu = -1;		// ������ �̵�
						break;
					case (int)KEY::ENTER:
						selectFlag = 1;		// ���õ�
						break;
					default:
						break;
					}
				}
				switch (menu)
				{
				case -1:		// ����
					buff_setting(buff);
					// ���� �� ���� �ٽ� ���
					box(0, 2, 13, 24, nullptr, ALIGNMENT::LEFT, 0, 1);		// ����â �����
					p_main->show_stat({ 1, 3 }, buff);		// ���� ���
					break;
				case -2:		// ����� (����(�� �̻�������..), ������, ���)
					enemy.change_info({ 1, 28 }, 58);
					box(14, 18, 44, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// �̸�, ���� ���� â �����
					enemy.show_info1({ 15, 19 });
					box(14, 16, 13, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// ����, ���� ���� â �����
					enemy.show_info2({ 15, 17 });
					break;
				case -3:		// ����ü
					enemy = ememy_identification();
					box(14, 18, 44, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// �̸�, ���� ���� â �����
					box(14, 16, 13, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// ����, ���� ���� â �����
					enemy.show_info1({ 15, 19 });
					enemy.change_info({ 1, 28 }, 58);
					box(14, 18, 44, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// �̸�, ���� ���� â �����
					enemy.show_info1({ 15, 19 });
					enemy.show_info2({ 15, 17 });
					break;
				case -4:		// ����
					endFlag = 0;		// ����(�缳��, ���, ���� �޴� �ִ� ��)���� ���ư�
					continue;
				default:		// ��ų�޴�
					box(14, 20, 44, 6, nullptr, ALIGNMENT::LEFT, 0, 1);		// ���â �����
					gotoxy(15, 21);
					sknum = menu;		// ��ų ���� �Ϸ�
					cout << "���õ� ��ų�� " << menu << "���Դϴ�.";
					break;
				}
				// �޴��� �ൿ�� �� �Ŀ��� �ٽ� ����Ͽ� ����� ���('����' ����)
				p_main->reflect_passive(sknum, enemy, buff, { 1, 28 }, 58);		// ĳ���� �нú� ����
				box(0, 2, 13, 24, nullptr, ALIGNMENT::LEFT, 0, 1);		// ����â �����
				p_main->show_stat({ 1, 3 }, buff);		// ���� ���
				box(14, 18, 44, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// �̸�, ���� ���� â �����
				box(14, 16, 13, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// ����, ���� ���� â �����
				enemy.show_info1({ 15, 19 });
				enemy.show_info2({ 15, 17 });
				box(14, 20, 44, 6, nullptr, ALIGNMENT::LEFT, 0, 1);		// ���â �����
				p_main->show_all_damage(sknum, enemy, buff, { 15, 21 });		// ������ ���
			}
		}
	}
	return;
}

void set_charinfo(Character& c, COORD in, int range)
{
	CursorView(1);
	c.set_info(in, range);
	std::ofstream fout(c.return_name() + ".txt");
	if (!fout.is_open())
	{
		gotoxy(in.X, in.Y);
		std::cerr << c.return_name() + ".txt" << " ������  ������� �� �� �����ϴ�. �����մϴ�.";
		exit(EXIT_FAILURE);
	}
	fout << c;
	fout.close();
	CursorView(0);
	return;
}

Enemy ememy_identification()		// �� �˻� �� Ư��
{
	using std::cout;
	using std::endl;
	using std::cin;
	using std::cerr;
	std::ifstream fin;
	int selectFlag = 0;		// ���õǸ� 1
	Enemy enemy;
	char enemyName[ENEMY_NAME_LENGTH];		// �� �̸�(�˻��� ����)
	int count;		// ��� ��� ����
	box(14, 20, 44, 6, nullptr, ALIGNMENT::LEFT, 0, 1);		// ���â �����
	box(14, 18, 44, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// �� ���� â �����
	CursorView(1);
	fin.open("������.dat", std::ios_base::in | std::ios_base::binary);
	if (!fin.is_open())
	{
		gotoxy(15, 21);		// ���â���� ��
		cerr << "������.dat ������ �� �� �����ϴ�. �����մϴ�.";
		exit(EXIT_FAILURE);
	}
	gotoxy(15, 21);		// ���â���� ��
	cout << "�˻��� �� �̸��� �Է����ּ���(�׸��Ϸ��� '�׸�' �Է����ּ���)";
	selectFlag = 0;		// ã���� 1
	count = 0;		// �� �� ����ߴ���
	gotoxy(1, 28);		// �Է�â���� ��
	while (cin.getline(enemyName, ENEMY_NAME_LENGTH))
	{
		if (!strcmp("�׸�", enemyName))
			break;
		while (fin.read((char*)&enemy, sizeof enemy))
		{
			if (!strcmp(enemy.name, enemyName))		// ã������ �̸��� ������
			{
				selectFlag = 1;
				break;
			}
		}
		if (selectFlag)
			break;
		box(14, 20, 44, 6, nullptr, ALIGNMENT::LEFT, 0, 1);		// ���â �����
		gotoxy(15, 21);
		cout << "�˻��Ͻ� �� �̸��� ã�� ���Ͽ����ϴ�.";
		gotoxy(15, 22);
		cout << "�˻��Ͻ� �� �̸��� �����ϴ� ������ ������ �����ϴ�.";
		fin.clear();
		fin.seekg(0);		// ���� �����͸� ���� ������ġ�� ��ġ��Ŵ
		count = 0;
		while (fin.read((char*)&enemy, sizeof enemy))
		{
			if (strstr(enemy.name, enemyName))		// ã������ �̸��� ���ԵǸ�
			{
				enemy.show_info1({ 15, short(23 + count) });
				count++;
			}
			if (count >= 4)		// 4�� ���� ��°���
				break;
		}
		fin.clear();
		fin.seekg(0);		// ���� �����͸� ���� ������ġ�� ��ġ��Ŵ
		box(0, 27, 58, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// �Է�â �����
		gotoxy(1, 28);
	}
	fin.close();
	box(14, 20, 44, 6, nullptr, ALIGNMENT::LEFT, 0, 1);		// ���â �����
	gotoxy(15, 21);
	CursorView(0);
	if (!selectFlag)		// '�׸�' �Է�
	{
		cout << "�����մϴ�.";
		exit(EXIT_FAILURE);
	}
	cout << "���õǾ����ϴ�.";
	return enemy;
}

void buff_setting(Buff& buff)		// ���� �缳��
{
	using std::cout;
	using std::cin;
	int menu = 0;
	int selectFlag = 0;
	int endFlag = 1;		// 0 �Ǹ� ����
	int key;
	double plus;		// �������� ��
	while (endFlag)
	{
		box(0, 2, 13, 24, nullptr, ALIGNMENT::LEFT, 0, 1);		// ����â �����
		selectFlag = 0;
		while (!selectFlag)
		{
			buff.show_buff({ 1,3 }, menu);
			key = _getch();
			switch (key)
			{
			case (int)KEY::UP:
				if (0 < menu)		// 1 �̻��̸� (�� ù �޴������� �ö󰡸� �ȵ�)
					menu--;
				break;
			case (int)KEY::DOWN:
				if (menu < 19)		// 18 �����̸� (19, �� ������ �޴������� �������� �ȵ�)
					menu++;
				break;
			case (int)KEY::ENTER:
				selectFlag = 1;		// ���õ�
				break;
			default:
				break;
			}
		}
		if (menu == 18)		// ���� ����
		{
			buff.reset_buff();
			continue;		// �ٽ� ����
		}
		if (menu == 19)		// ���� �Ϸ�
		{
			endFlag = 0;
			continue;		// ����
		}
		CursorView(1);
		box(0, 27, 58, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// �Է�â �����
		gotoxy(1, 28);
		cout << "���� ��: ";
		cin >> plus;
		switch (menu)
		{
		case 0:
			buff.hp += plus;
			break;
		case 1:
			buff.hpPer += plus;
			break;
		case 2:
			buff.atk += plus;
			break;
		case 3:
			buff.atkPer += plus;
			break;
		case 4:
			buff.def += plus;
			break;
		case 5:
			buff.defPer += plus;
			break;
		case 6:
			buff.elementalMastery += plus;
			break;
		case 7:
			buff.energyRecharge += plus;
			break;
		case 8:
			buff.critRate += plus;
			break;
		case 9:
			buff.critDamage += plus;
			break;
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
		case 17:
			buff.damageBonus[menu - 10] += plus;
			break;
		default:
			break;
		}
		box(0, 27, 58, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// �Է�â �����
		CursorView(0);
	}
	return;
}