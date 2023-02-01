// characters.h �Լ���

#include "characters.h"

extern double �ݺ�bonus;
extern double ����bonus;
extern double ��ȭbonus;

void Klee::reflect_passive(int& sknum, Enemy& e, Buff& b, COORD in, int range)		// �нú� �����Ͽ� �� ����, ���� ����, ĳ���͸��� �޶���
{
	char ch;
	int n;
	if (10 == sknum && return_constellation() < CONSTELLATION::LV1)		// 10����ų - 1�� �������� : ����Ҳ��� 120% ����
	{
		sknum = -1;		// ������ �ʴ� ��ų�� �ٲ۴�
		return;
	}
	if (11 == sknum && return_constellation() < CONSTELLATION::LV4)		// 11�� ��ų - 4�� ������� : �� ���ӽð� �� ���� �� 555% �ҿ��� ��������
	{
		sknum = -1;		// ������ �ʴ� ��ų�� �ٲ۴�
		return;
	}
	CursorView(1);
	switch (return_constellation())
	{
	case CONSTELLATION::LV6:
		box(in.X - 1, in.Y - 1, range, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// �Է�â �����
		gotoxy(in.X, in.Y);
		std::cout << "�������� �ߵ� �� 25�� �̳��ΰ���?(y/n): ";
		std::cin >> ch;
		if ('y' == ch)
			b.damageBonus[int(ELEMENT::PYRO)] += 0.10;		// ���� �ߵ��� 25�ʵ��� ��Ƽ �ҿ������� 10% ����
		eatline();
	case CONSTELLATION::LV5:
	case CONSTELLATION::LV4:
	case CONSTELLATION::LV3:
	case CONSTELLATION::LV2:
		box(in.X - 1, in.Y - 1, range, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// �Է�â �����
		gotoxy(in.X, in.Y);
		std::cout << "���� �κ�Ʈ���� ������ 10�� �̳��ΰ���?(y/n): ";
		std::cin >> ch;
		if ('y' == ch)
			e.defense -= 0.23;		// �κ�Ʈ�� ��� 10�ʵ��� �� ���� 23% ����
		eatline();
	case CONSTELLATION::LV1:
	case CONSTELLATION::LV0:
		if (same_kind(sknum, Skill::SKILL_TYPE::CHARGED_ATTACK))		// �������̸�
		{
			box(in.X - 1, in.Y - 1, range, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// �Է�â �����
			gotoxy(in.X, in.Y);
			std::cout << "���ĺҲ��� �Ҹ��߳���?(y/n): ";
			std::cin >> ch;
			if ('y' == ch)
				b.damageBonus[int(ELEMENT::PYRO)] += 0.50;		// Ư�� - ���ĺҲ� �Ҹ��� ������ ������ 50%
			eatline();
		}
		break;
	}
	// ���� - ��ǳ����
	box(in.X - 1, in.Y - 1, range, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// �Է�â �����
	gotoxy(in.X, in.Y);
	std::cout << "��ǳ���� �� �����ΰ���?(0~4): ";
	std::cin >> n;
	if (0 <= n && n <= 4)
		for (int i = 0; i < int(ELEMENT::NUMBER) - 1; i++)		// ���� �� ���� ����(7)
			b.damageBonus[i] += (n * 0.08);		// ���ô� �������غ��ʽ� 8%
	eatline();
	// ������ - ����4��
	�ݺ�bonus = 0.40;		// ������, ����, ��ȭ ���غ��ʽ� 40%
	����bonus = 0.15;		// ����, ���� ���غ��ʽ� 15%
	box(in.X - 1, in.Y - 1, range, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// �Է�â �����
	gotoxy(in.X, in.Y);
	std::cout << "E��ų �� �� �ߵ��߳���?(0~3): ";
	std::cin >> n;
	if (0 <= n && n <= 3)
		b.damageBonus[int(ELEMENT::PYRO)] += (n * 0.075);		// ���ô� �ҿ���7.5% ����
	eatline();

	box(in.X - 1, in.Y - 1, range, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// �Է�â �����
	CursorView(0);
	return;
}

void Xingqiu::reflect_passive(int& sknum, Enemy& e, Buff& b, COORD in, int range)		// �нú� �����Ͽ� �� ����, ���� ����, ĳ���͸��� �޶���
{
	char ch;
	CursorView(1);
	switch (return_constellation())
	{
	case CONSTELLATION::LV6:
	case CONSTELLATION::LV5:
	case CONSTELLATION::LV4:
		if (same_kind(sknum, Skill::SKILL_TYPE::E))		// ���ҽ�ų�̸�
		{
			box(in.X - 1, in.Y - 1, range, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// �Է�â �����
			gotoxy(in.X, in.Y);
			std::cout << "���������� �������ΰ���?(y/n): ";
			std::cin >> ch;
			if ('y' == ch)
				b.damageBonus[int(ELEMENT::HYDRO)] += 0.50;		// ���� ���ӽð� �� ���ҽ�ų ���ط� 50% ����
			eatline();
		}
	case CONSTELLATION::LV3:
	case CONSTELLATION::LV2:
		box(in.X - 1, in.Y - 1, range, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// �Է�â �����
		gotoxy(in.X, in.Y);
		std::cout << "���� �������߿� ���� �� 4�� ���ΰ���?(y/n): ";
		std::cin >> ch;
		if ('y' == ch)
			e.resistance[int(ELEMENT::HYDRO)] -= 0.15;		// ���� �� ���� ���� �� 4�ʰ� ������ ���� 15% ����
		eatline();
	case CONSTELLATION::LV1:
	case CONSTELLATION::LV0:
		break;
	}
	box(in.X - 1, in.Y - 1, range, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// �Է�â �����
	CursorView(0);
	return;
}

void Noelle::reflect_passive(int& sknum, Enemy& e, Buff& b, COORD in, int range)
{
	char ch;
	int n;
	double coefficient = 0.76;		// ��û�� ���ݷ� ������Ű�� ���� ����
	Stat buffStat;
	if (12 == sknum && return_constellation() < CONSTELLATION::LV4)		// 12����ų - 4�� ���߿� û���ҰԿ� : ȣ�ɰ� �ı��� 400% ����� �ٿ���
	{
		sknum = -1;		// ������ �ʴ� ��ų�� �ٲ۴�
		return;
	}
	CursorView(1);
	switch (return_constellation())
	{
	case CONSTELLATION::LV6:
		coefficient += 0.50;		// �߰��� ������ 50%��ŭ ���ݷ� ����
	case CONSTELLATION::LV5:
	case CONSTELLATION::LV4:
	case CONSTELLATION::LV3:
	case CONSTELLATION::LV2:
		if (same_kind(sknum, Skill::SKILL_TYPE::CHARGED_ATTACK))
		{
			for (int i = 0; i < int(ELEMENT::NUMBER); i++)		// �Ϲ����� �������� �׳� ��� ���� �������� �����...
				b.damageBonus[i] += 0.15;		// ������ ���� 15%
		}
	case CONSTELLATION::LV1:
	case CONSTELLATION::LV0:
		break;
	}
	// ���� - �鿵��
	box(in.X - 1, in.Y - 1, range, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// �Է�â �����
	gotoxy(in.X, in.Y);
	std::cout << "�鿵�� �� �����ΰ���?(0~4): ";
	std::cin >> n;
	if (0 <= n && n <= 4)
	{
		b.atkPer += (n * 0.075);		// ���ݷ� ���ô� 7.5% ����
		b.defPer += (n * 0.075);		// ���� ���ô� 7.5% ����
	}
	eatline();
	// ������ - ���� 4��
	if (same_kind(sknum, Skill::SKILL_TYPE::NORMAL_ATTACK) || same_kind(sknum, Skill::SKILL_TYPE::CHARGED_ATTACK))		// �Ϲݰ����̳� �������̸�
	{
		box(in.X - 1, in.Y - 1, range, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// �Է�â �����
		gotoxy(in.X, in.Y);
		std::cout << "��ȣ���� �ֳ���?(y/n): ";
		std::cin >> ch;
		if ('y' == ch)
			for (int i = 0; i < int(ELEMENT::NUMBER); i++)		// �Ϲ����� �������� �׳� ��� ���� �������� �����...
				b.damageBonus[i] += 0.40;		// �Ϲ�, ������ ���� 40%
		eatline();
	}
	// �������Ǵ� ��û�� �������� ��� ���� ��� �� ���⼭ �Ѵ�
	box(in.X - 1, in.Y - 1, range, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// �Է�â �����
	gotoxy(in.X, in.Y);
	std::cout << "��û�� �ߵ� ���ΰ���?(y/n): ";
	std::cin >> ch;
	if ('y' == ch)
	{
		buffStat = return_stat() + b;
		b.atk += (buffStat.baseDEF + buffStat.additionalDEF) * coefficient;		// ��û�� ȿ�� : ���ݷ��� ������ 76%��ŭ ���(������ ����ؾ� �ϴµ�....)
		enchant(ELEMENT::GEO);		// ��Ÿ ���� ��æƮ
	}
	else
		enchant(ELEMENT::PHYSICAL);		// �ƴϸ� �ٽ� ������
	eatline();

	box(in.X - 1, in.Y - 1, range, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// �Է�â �����
	CursorView(0);
	return;
}

void Keqing::reflect_passive(int& sknum, Enemy& e, Buff& b, COORD in, int range)
{
	char ch;
	int n;
	if (17 == sknum && return_constellation() < CONSTELLATION::LV1)		// 17����ų - 1�� ��� : ����ȸ�� 2��° �ߵ� �� ��û�� ������� ��Ÿ���� ��ġ�� 50% �������� ��������
	{
		sknum = -1;		// ������ �ʴ� ��ų�� �ٲ۴�
		return;
	}
	CursorView(1);
	switch (return_constellation())
	{
	case CONSTELLATION::LV6:
		box(in.X - 1, in.Y - 1, range, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// �Է�â �����
		gotoxy(in.X, in.Y);
		std::cout << "�Ϲݰ���, ������, E, Q ����(0~4): ";
		std::cin >> n;
		if (0 <= n && n <= 4)
			b.damageBonus[int(ELEMENT::ELECTRO)] += (n * 0.06);		// 4������ ���� ����� 8�ʰ� ������ 6% ����(���� ���ӽð� 8��)
		eatline();
	case CONSTELLATION::LV5:
	case CONSTELLATION::LV4:
		box(in.X - 1, in.Y - 1, range, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// �Է�â �����
		gotoxy(in.X, in.Y);
		std::cout << "�������� ���� ���� �ߵ� �� 10�� �̳��ΰ���?(y/n): ";
		std::cin >> ch;
		if ('y' == ch)
			b.atkPer += 0.25;		// ���ݷ� 25% ����
		eatline();
	case CONSTELLATION::LV3:
	case CONSTELLATION::LV2:
	case CONSTELLATION::LV1:
	case CONSTELLATION::LV0:
		if (same_kind(sknum, Skill::SKILL_TYPE::NORMAL_ATTACK) || same_kind(sknum, Skill::SKILL_TYPE::CHARGED_ATTACK) || same_kind(sknum, Skill::SKILL_TYPE::PLUNGING_ATTACK))
		{
			box(in.X - 1, in.Y - 1, range, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// �Է�â �����
			gotoxy(in.X, in.Y);
			std::cout << "����ȸ�� ���� �ߵ� �� 5�� �̳��ΰ���?(y/n): ";
			std::cin >> ch;
			if ('y' == ch)
				enchant(ELEMENT::ELECTRO);		// ��Ÿ ���� ��æƮ
			else
				enchant(ELEMENT::PHYSICAL);		// �ƴ� �ٽ� ������
			eatline();
		}
		box(in.X - 1, in.Y - 1, range, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// �Է�â �����
		gotoxy(in.X, in.Y);
		std::cout << "õ������ �ߵ� �� 8�� �̳��ΰ���?(y/n): ";
		std::cin >> ch;
		if ('y' == ch)
		{
			b.critRate += 0.15;		// ġȮ 15% ����
			b.energyRecharge += 0.15;		// ���� 15% ����
		}
		eatline();
		break;
	}
	// ���� - ĥ���
	if (same_kind(sknum, Skill::SKILL_TYPE::NORMAL_ATTACK) || same_kind(sknum, Skill::SKILL_TYPE::CHARGED_ATTACK))		// �Ϲݰ����̳� �������̸�
	{
		for (int i = 0; i < int(ELEMENT::NUMBER); i++)		// �Ϲ����� �������� �׳� ��� ���� �������� �����...
			b.damageBonus[i] += 0.20;		// �Ϲ�, ������ ���� 20%
	}
	// ������ - ���� 4��
	�ݺ�bonus = 0.40;		// ������, ����, ������, ���� ���غ��ʽ� 40%
	��ȭbonus = 0.20;		// ���� ���غ��ʽ� 15%

	box(in.X - 1, in.Y - 1, range, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// �Է�â �����
	CursorView(0);
	return;
}