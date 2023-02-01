// base.h �Լ���

#include "base.h"
#include <climits>
#include <float.h>
// ������ stat�� buff�� �ִ� ���� ���� �� ������ �ʹ� ��������... �ӽù������� ���������� �����Ѵ�...
extern double �ݺ�bonus = 0.0;
extern double ����bonus = 0.0;
extern double ��ȭbonus = 0.0;

double Stat::return_EM_effect(int n) const
{
	switch (n)
	{
	case 1:
		return 16.0 * elementalMastery / (elementalMastery + 2000) + �ݺ�bonus;		// �ݺ�
	case 2:
		return 2.78 * elementalMastery / (elementalMastery + 1400) + ����bonus;		// ����
	case 3:
		return 5.0 * elementalMastery / (elementalMastery + 1200) + ��ȭbonus;		// ��ȭ
	default:
		return 0;
	}
}// ���Ҹ����͸��� ���� ���ʽ��� ����, 1: �ݺ� 2: ���� 3: ��ȭ
void Stat::set_stat(COORD in, int range)
{
	using std::cout;
	using std::endl;
	using std::cin;
	int i;		// for �� ��
	CursorView(1);
	gotoxy(in.X, in.Y);
	cout << "����ü��: ";
	cin >> baseHP;
	gotoxy(in.X, in.Y);
	for (i = 0; i < range; i++)
		cout << "  ";		// �����
	gotoxy(in.X, in.Y);
	cout << "�߰�ü��: ";
	cin >> additionalHP;
	gotoxy(in.X, in.Y);
	for (i = 0; i < range; i++)
		cout << "  ";		// �����
	gotoxy(in.X, in.Y);
	cout << "���ʰ��ݷ�: ";
	cin >> baseATK;
	gotoxy(in.X, in.Y);
	for (i = 0; i < range; i++)
		cout << "  ";		// �����
	gotoxy(in.X, in.Y);
	cout << "�߰����ݷ�: ";
	cin >> additionalATK;
	gotoxy(in.X, in.Y);
	for (i = 0; i < range; i++)
		cout << "  ";		// �����
	gotoxy(in.X, in.Y);
	cout << "���ʹ���: ";
	cin >> baseDEF;
	gotoxy(in.X, in.Y);
	for (i = 0; i < range; i++)
		cout << "  ";		// �����
	gotoxy(in.X, in.Y);
	cout << "�߰�����: ";
	cin >> additionalDEF;
	gotoxy(in.X, in.Y);
	for (i = 0; i < range; i++)
		cout << "  ";		// �����
	gotoxy(in.X, in.Y);
	cout << "���Ҹ����͸�: ";
	cin >> elementalMastery;
	gotoxy(in.X, in.Y);
	for (i = 0; i < range; i++)
		cout << "  ";		// �����
	gotoxy(in.X, in.Y);
	cout << "ġ��Ÿ Ȯ��: ";
	cin >> criticalRate;
	gotoxy(in.X, in.Y);
	for (i = 0; i < range; i++)
		cout << "  ";		// �����
	gotoxy(in.X, in.Y);
	cout << "ġ��Ÿ ����: ";
	cin >> criticalDMG;
	gotoxy(in.X, in.Y);
	for (i = 0; i < range; i++)
		cout << "  ";		// �����
	gotoxy(in.X, in.Y);
	cout << "��������ȿ��: ";
	cin >> energyRecharge;
	gotoxy(in.X, in.Y);
	for (i = 0; i < range; i++)
		cout << "  ";		// �����
	gotoxy(in.X, in.Y);
	for (int j = 0; j < int(ELEMENT::NUMBER); j++)
	{
		cout << ELEMENT_NAME[j] << " ���غ��ʽ�: ";
		cin >> damageBonus[j];
		gotoxy(in.X, in.Y);
		for (i = 0; i < range; i++)
			cout << "  ";		// �����
		gotoxy(in.X, in.Y);
	}
	eatline();
	return;
}// ������ ��ȭ������ �����ϴ� �Լ�
void Stat::show_stat(COORD out) const
{
	using std::cout;
	using std::endl;
	gotoxy(out.X, out.Y++);
	cout << "ü��: " << baseHP << " + " << additionalHP;
	gotoxy(out.X, out.Y++);
	cout << "���ݷ�: " << baseATK << " + " << additionalATK;
	gotoxy(out.X, out.Y++);
	cout << "����: " << baseDEF << " + " << additionalDEF;
	gotoxy(out.X, out.Y++);
	cout << "����: " << elementalMastery << ", ����: " << energyRecharge;
	gotoxy(out.X, out.Y++);
	cout << "ġȮ: " << criticalRate << ", ġ��: " << criticalDMG;
	gotoxy(out.X, out.Y++);
	cout << "���غ��ʽ�";
	for (int i = 0; i < int(ELEMENT::NUMBER); i++)		// 0�� �ƴ� ���غ��ʽ��� ����ϱ��
	{
		if (damageBonus[i] - 0.0 > DBL_EPSILON)		// ���غ��ʽ� 0�� �ƴϸ�
		{
			gotoxy(out.X, out.Y++);
			cout << ELEMENT_NAME[i] << ": " << damageBonus[i];
		}
	}
}// ������ ����ϴ� �Լ�
void Stat::show_stat(COORD out, const Buff& buff) const		// ������ ����ϴ� �Լ�(�����ε� ����)
{
	Stat buffStat = *this + buff;
	buffStat.show_stat(out);
	return;
}
std::ofstream& operator<<(std::ofstream& fout, const Stat& stat)
{
	fout << stat.baseHP << " " << stat.baseATK << " " << stat.baseDEF << " " << stat.additionalHP << " " << stat.additionalATK << " " << stat.additionalDEF << " " << stat.elementalMastery << " " << stat.criticalRate << " " << stat.criticalDMG << " " << stat.energyRecharge << " ";		// ���ǵ� ������� ����
	for (int i = 0; i < int(ELEMENT::NUMBER); i++)
		fout << stat.damageBonus[i] << " ";
	return fout;
}// ���Ͽ� ����ϴ� �Լ�
std::ifstream& operator>>(std::ifstream& fin, Stat& stat)
{
	fin >> stat.baseHP >> stat.baseATK >> stat.baseDEF >> stat.additionalHP >> stat.additionalATK >> stat.additionalDEF >> stat.elementalMastery >> stat.criticalRate >> stat.criticalDMG >> stat.energyRecharge;		// ��ĭ�� ���̻��̿� �־� �����Ͽ��� ������ ȭ��Ʈ�����̽� ���÷� �ٷ� ���� �� �ִ�
	for (int i = 0; i < int(ELEMENT::NUMBER); i++)
		fin >> stat.damageBonus[i];
	return fin;
}// ���Ͽ��� �Է¹޴� �Լ�
void Buff::add_buff()		// ������ ��ȭ������ ���ϴ� �Լ�
{
	using std::cout;
	using std::endl;
	using std::cin;
	int intValue;
	double doubleValue;

	cout << "��ü: ";
	cin >> intValue;
	hp += intValue;
	cout << "ü��: ";
	cin >> doubleValue;
	hpPer += doubleValue;
	cout << "����: ";
	cin >> intValue;
	atk += intValue;
	cout << "����: ";
	cin >> doubleValue;
	atkPer += doubleValue;
	cout << "����: ";
	cin >> intValue;
	def += intValue;
	cout << "����: ";
	cin >> doubleValue;
	defPer += doubleValue;
	cout << "���Ҹ����͸�: ";
	cin >> intValue;
	elementalMastery += intValue;
	cout << "ġ��Ÿ Ȯ��: ";
	cin >> doubleValue;
	critRate += doubleValue;
	cout << "ġ��Ÿ ����: ";
	cin >> doubleValue;
	critDamage += doubleValue;
	cout << "��������ȿ��: ";
	cin >> doubleValue;
	energyRecharge += doubleValue;
	for (int i = 0; i < int(ELEMENT::NUMBER); i++)
	{
		cout << ELEMENT_NAME[i] << " ���غ��ʽ�: ";
		cin >> doubleValue;
		damageBonus[i] += doubleValue;
	}
	cout << "���� �߰� �Ϸ�.\n";
	eatline();
	return;
}
void Buff::show_buff(COORD out, int menu) const
{
	using std::cout;
	using std::endl;
	gotoxy(out.X, out.Y++);
	cout << "���� ����";

	gotoxy(out.X, out.Y++);
	if (menu == 0)
		color(B_COLOR, H_COLOR);
	cout << "��ü: " << hp;
	if (menu == 0)
		color(B_COLOR, N_COLOR);

	gotoxy(out.X, out.Y++);
	if (menu == 1)
		color(B_COLOR, H_COLOR);
	cout << "ü��: " << hpPer;
	if (menu == 1)
		color(B_COLOR, N_COLOR);

	gotoxy(out.X, out.Y++);
	if (menu == 2)
		color(B_COLOR, H_COLOR);
	cout << "����: " << atk;
	if (menu == 2)
		color(B_COLOR, N_COLOR);

	gotoxy(out.X, out.Y++);
	if (menu == 3)
		color(B_COLOR, H_COLOR);
	cout << "����: " << atkPer;
	if (menu == 3)
		color(B_COLOR, N_COLOR);

	gotoxy(out.X, out.Y++);
	if (menu == 4)
		color(B_COLOR, H_COLOR);
	cout << "����: " << def;
	if (menu == 4)
		color(B_COLOR, N_COLOR);

	gotoxy(out.X, out.Y++);
	if (menu == 5)
		color(B_COLOR, H_COLOR);
	cout << "����: " << defPer;
	if (menu == 5)
		color(B_COLOR, N_COLOR);

	gotoxy(out.X, out.Y++);
	if (menu == 6)
		color(B_COLOR, H_COLOR);
	cout << "����: " << elementalMastery;
	if (menu == 6)
		color(B_COLOR, N_COLOR);

	gotoxy(out.X, out.Y++);
	if (menu == 7)
		color(B_COLOR, H_COLOR);
	cout << "����: " << energyRecharge;
	if (menu == 7)
		color(B_COLOR, N_COLOR);

	gotoxy(out.X, out.Y++);
	if (menu == 8)
		color(B_COLOR, H_COLOR);
	cout << "ġȮ: " << critRate;
	if (menu == 8)
		color(B_COLOR, N_COLOR);

	gotoxy(out.X, out.Y++);
	if (menu == 9)
		color(B_COLOR, H_COLOR);
	cout << "ġ��: " << critDamage;
	if (menu == 9)
		color(B_COLOR, N_COLOR);

	gotoxy(out.X, out.Y++);
	cout << "���غ��ʽ�";
	for (int i = 0; i < int(ELEMENT::NUMBER); i++)
	{
		gotoxy(out.X, out.Y++);
		if (menu == i + 10)
			color(B_COLOR, H_COLOR);
		cout << ELEMENT_NAME[i] << ": " << damageBonus[i];
		if (menu == i + 10)
			color(B_COLOR, N_COLOR);
	}
	
	gotoxy(out.X, out.Y++);
	if (menu == 18)
		color(B_COLOR, H_COLOR);
	cout << "���� ����";
	if (menu == 18)
		color(B_COLOR, N_COLOR);

	gotoxy(out.X, out.Y++);
	if (menu == 19)
		color(B_COLOR, H_COLOR);
	cout << "���� �Ϸ�";
	if (menu == 19)
		color(B_COLOR, N_COLOR);
	return;
}// ������ ����ϴ� �Լ�, �޴���� ��� ��(20�� �޴�(18�� �ɼ� + ���� + Ȯ��))
void Buff::reset_buff()		// ������ �ʱ� ���·� ������ �Լ�
{
	hp = 0;		// ��ü
	atk = 0;		// ����
	def = 0;		// ����
	hpPer = 0.0;		// ü��
	atkPer = 0.0;		// ����
	defPer = 0.0;		// ����
	elementalMastery = 0;		// ����
	energyRecharge = 0.0;		// ����
	critRate = 0.0;		// ġȮ
	critDamage = 0.0;		// ġ��
	for (int i = 0; i < int(ELEMENT::NUMBER); i++)
		damageBonus[i] = 0.0;
	return;
}
Stat operator+(Stat s, const Buff& b)
{
	s.additionalHP += s.baseHP * b.hpPer + b.hp;		// �߰�ü�� ����ü*ü�� + ��ü ����
	s.additionalATK += s.baseATK * b.atkPer + b.atk;		// �߰����� ���ʰ�*���� + ���� ����
	s.additionalDEF += s.baseDEF * b.defPer + b.def;		// �߰��濡 ���ʹ�*���� + ���� ����
	s.elementalMastery += b.elementalMastery;
	s.criticalRate += b.critRate;
	s.criticalDMG += b.critDamage;
	s.energyRecharge += b.energyRecharge;
	for (int i = 0; i < int(ELEMENT::NUMBER); i++)
		s.damageBonus[i] += b.damageBonus[i];
	return s;
}// stat + buff -> ���� ����� ���� ��ȯ.. 

void Skill::set_skill(COORD in, int range)
{
	using std::cout;
	using std::endl;
	using std::cin;
	int i;		// for �� ��
	CursorView(1);
	gotoxy(in.X, in.Y);
	cout << "��ų �̸�: ";
	getline(cin, name);
	gotoxy(in.X, in.Y);
	for (i = 0; i < range; i++)
		cout << "  ";		// �����
	gotoxy(in.X, in.Y);
	cout << "��ų ����(0: �Ϲݰ���, 1: ������, 2: ���ϰ���, 3: ���ҽ�ų, 4: ��������): ";
	int num;
	cin >> num;
	type = SKILL_TYPE(num);
	gotoxy(in.X, in.Y);
	for (i = 0; i < range; i++)
		cout << "  ";		// �����
	gotoxy(in.X, in.Y);
	cout << "��ų ����( ";
	for (int i = 0; i < int(ELEMENT::NUMBER); i++)
		cout << i << ": " << ELEMENT_NAME[i] << " ";
	cout << "): ";
	cin >> num;
	element = ELEMENT(num);
	gotoxy(in.X, in.Y);
	for (i = 0; i < range; i++)
		cout << "  ";		// �����
	gotoxy(in.X, in.Y);
	cout << "���̽�(0: ü 2: �� 4: ��): ";
	cin >> num;
	base = OPTION(num);
	gotoxy(in.X, in.Y);
	for (i = 0; i < range; i++)
		cout << "  ";		// �����
	gotoxy(in.X, in.Y);
	cout << "��ų ���: ";
	cin >> coefficient;
	gotoxy(in.X, in.Y);
	for (i = 0; i < range; i++)
		cout << "  ";		// �����
	gotoxy(in.X, in.Y);
	cout << "��ų �ݺ� Ƚ��: ";
	cin >> repetition;
	gotoxy(in.X, in.Y);
	for (i = 0; i < range; i++)
		cout << "  ";		// �����
	eatline();
}
void Skill::show_skill(COORD out) const
{
	using std::cout;
	using std::endl;

	gotoxy(out.X, out.Y);
	cout << name << "(";
	switch (type)
	{
	case SKILL_TYPE::NORMAL_ATTACK:
		cout << "�Ϲݰ���, ";
		break;
	case SKILL_TYPE::CHARGED_ATTACK:
		cout << "������, ";
		break;
	case SKILL_TYPE::PLUNGING_ATTACK:
		cout << "���ϰ���, ";
		break;
	case SKILL_TYPE::E:
		cout << "���ҽ�ų, ";
		break;
	case SKILL_TYPE::Q:
		cout << "��������, ";
		break;
	}
	cout << ELEMENT_NAME[int(element)] << ", ";
	switch (base)
	{
	case OPTION::HP:
		cout << "ü) - ";
		break;
	case OPTION::ATK:
		cout << "��) - ";
		break;
	case OPTION::DEF:
		cout << "��) - ";
		break;
	}
	cout << coefficient << " * " << repetition << "ȸ\n";
}// ��ų ������ ����ϴ� �Լ�
std::ofstream& operator<<(std::ofstream& fout, const Skill& skill)
{
	fout << skill.name << "#";		// ��ȹ���� #
	fout << int(skill.type) << " " << int(skill.element) << " " << int(skill.base) << " " << skill.coefficient << " " << skill.repetition;
	return fout;
}// ���Ͽ� ����ϴ� �Լ�
std::ifstream& operator>>(std::ifstream& fin, Skill& skill)
{
	std::getline(fin, skill.name, '#');		// ��ȹ���� #�� ���������� �а�, #�� �о� ����
	int num;
	fin >> num;
	skill.type = Skill::SKILL_TYPE(num);
	fin >> num;
	skill.element = ELEMENT(num);
	fin >> num;
	skill.base = OPTION(num);
	fin >> skill.coefficient >> skill.repetition;
	return fin;
}// ���Ͽ��� �Է¹޴� �Լ�

double Enemy::resist_factor(double r) const
{
	if (r < 0)		// ������ �����϶�
		return 1 - r / 2;		// ���� ���� ȿ�� 1/2
	else if (r < 0.75)		// 0 <= ���� < 0.75 �϶�
		return 1 - r;
	else		// ������ 75% �ʰ��ϸ�
		return 1 / (1 + 4 * r);
}
void Enemy::show_info1(COORD out) const		// �� �̸�, ���� ���(���� �ڸ� ������ ����)
{
	box(out.X - 1, out.Y - 1, ENEMY_NAME_LENGTH / 2, 1, name, ALIGNMENT::CENTER, 0);		// �ڽ��� ��ǥ��ġ�� ���ϹǷ� ���ڰ� ��ǥ��ġ�� ���ϵ��� -1
	// 0.35 -> 4����, �ѱ۷δ� 2����
	for (int i = 0; i < int(ELEMENT::NUMBER); i++)
	{
		if (resist_factor(resistance[i]) < FLT_EPSILON)		// ���� ���Ѵ��(�������� ����� ���Ƿ� ���� �����̴�)
			box(out.X + ENEMY_NAME_LENGTH / 2 + i * 3, out.Y - 1, 2, 1, "��", ALIGNMENT::LEFT, 0);
		else
		{
			gotoxy(out.X + ENEMY_NAME_LENGTH / 2 + 1 + i * 3, out.Y);
			std::cout << resistance[i];
		}
	}
	return;
}
void Enemy::show_info2(COORD out) const		// ����, ���� ���� ���
{
	box(out.X - 1, out.Y - 1, 3, 1, "����: ", ALIGNMENT::LEFT, 0, 1);		// �� �ΰ����� ���
	gotoxy(out.X + 3, out.Y);
	std::cout << level;
	box(out.X + 4, out.Y - 1, 6, 1, "���º���: ", ALIGNMENT::LEFT, 0, 1);
	gotoxy(out.X + 11, out.Y);
	std::cout << defense;
	return;
}
void Enemy::change_info(COORD in, int range)		// �� ����, �����迭, ���� ���� ����
{
	using std::cout;
	using std::endl;
	using std::cin;

	CursorView(1);
	box(in.X - 1, in.Y - 1, range, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// �Է¹��� â �����
	gotoxy(in.X, in.Y);
	cout << "�� ����: ";
	cin >> level;
	double decrease;		// ���� ���� ����, ���� ���� ����
	for (int i = 0; i < int(ELEMENT::NUMBER); i++)
	{
		box(in.X - 1, in.Y - 1, range, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// �Է¹��� â �����
		gotoxy(in.X, in.Y);
		cout << ELEMENT_NAME[i] << "��������: ";
		cin >> decrease;
		if (INT_MAX != resistance[i])		// ���� ���Ѵ밡 �ƴҶ���
			resistance[i] -= decrease;
	}
	box(in.X - 1, in.Y - 1, range, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// �Է¹��� â �����
	gotoxy(in.X, in.Y);
	cout << "���: ";
	cin >> decrease;
	defense -= decrease;
	box(in.X - 1, in.Y - 1, range, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// �Է¹��� â �����
	eatline();
	CursorView(0);
	return;
}

Character::Character(const Character& c) : name(c.name)
{
	level = c.level;
	constellation = c.constellation;
	stat = c.stat;
	skills = c.skills;
	skill = new Skill[skills];
	for (int i = 0; i < skills; i++)
		skill[i] = c.skill[i];
}// ���� ������
Character::~Character()
{
	delete[] skill;
}
Character& Character::operator=(const Character& c)
{
	if (this == &c)
		return *this;
	delete[] skill;
	level = c.level;
	constellation = c.constellation;
	stat = c.stat;
	skills = c.skills;
	skill = new Skill[skills];
	for (int i = 0; i < skills; i++)
		skill[i] = c.skill[i];
	return *this;
}// ���� ������
void Character::set_info(COORD in, int range)
{
	using std::cout;
	using std::cin;
	using std::endl;
	int i;		// for �� ��
	CursorView(1);
	gotoxy(in.X, in.Y);
	cout << "�̸�: ";
	cin >> name;
	gotoxy(in.X, in.Y);
	for (i = 0; i < range; i++)
		cout << "  ";		// �����
	gotoxy(in.X, in.Y);
	cout << "����: ";
	cin >> level;
	gotoxy(in.X, in.Y);
	for (i = 0; i < range; i++)
		cout << "  ";		// �����
	gotoxy(in.X, in.Y);
	cout << "���ڸ�(0~6): ";
	int num;
	cin >> num;
	constellation = CONSTELLATION(num);
	gotoxy(in.X, in.Y);
	for (i = 0; i < range; i++)
		cout << "  ";		// �����
	eatline();
	stat.set_stat(in, range);
	gotoxy(in.X, in.Y);
	cout << "��ų ����: ";
	(cin >> skills).get();
	gotoxy(in.X, in.Y);
	for (i = 0; i < range; i++)
		cout << "  ";		// �����
	gotoxy(in.X, in.Y);
	delete[] skill;		// ���� ���� ����
	skill = new Skill[skills];
	for (int i = 0; i < skills; i++)
		skill[i].set_skill(in, range);
	CursorView(0);
}// ���� �����Լ�
void Character::show_stat(COORD out) const		// ������ �ִ� ���� ��� �Լ�
{
	using std::cout;
	using std::endl;
	gotoxy(out.X, out.Y++);
	cout << "����: " << level << endl;
	gotoxy(out.X, out.Y++);
	cout << "���ڸ�: " << int(constellation) << "����";
	stat.show_stat(out);
	return;
}
void Character::show_stat(COORD out, const Buff& buff) const		// ������ �ִ� ���� ��� �Լ�(�����ε� ����)
{
	using std::cout;
	using std::endl;
	gotoxy(out.X, out.Y++);
	cout << "����: " << level << endl;
	gotoxy(out.X, out.Y++);
	cout << "���ڸ�: " << int(constellation) << "����";
	stat.show_stat(out, buff);
	return;
}
void Character::show_skills(COORD out, int* menu) const		// ��ų ���� �����ִ� �Լ�, �޴���� ��� ��
{
	COORD temp = out;
	// �ѹ��� ��ų 15�������� ��°���
	int end = (skills < 15 ? skills : 15);
	if (menu == nullptr)		// �⺻ ���
	{
		for (int i = 0; i < end; i++)
			skill[i].show_skill({ out.X, out.Y++ });
		return;
	}
	if (*menu >= skills)
		*menu = skills - 1;		// �ۿ����� skills�� ���� �𸥴�. �𸣰� DOWN Ű ������ menu�� �÷��� ���⼭ �������ش�.
	int start = (15 <= *menu ? *menu - 14 : 0);
	if (*menu >= 14)		// ������ �ٱ��� ��ų�̸�
		box(temp.X - 1, temp.Y - 1, 37, 15, nullptr, ALIGNMENT::LEFT, 0, 1);		// ��ų ���â �����(�ʺ�� ���������� ����)
	for (int i = start; i < end + start; i++)
	{
		if (*menu == i)
			color(B_COLOR, H_COLOR);
		skill[i].show_skill({ out.X, out.Y++ });
		if (*menu == i)
			color(B_COLOR, N_COLOR);
	}
	return;
}
int Character::damage_of(int sknum, const Enemy& e, const Buff& b, REACTION react, CRIT_OPTION crit) const
{
	if (sknum > skills - 1 || sknum < 0)
		return -1;
	switch (react)		// ������ ����ų �� ���� ��ų�̸� �Ÿ���
	{
	case REACTION::OVERLOADED:
		if (skill[sknum].element != ELEMENT::PYRO && skill[sknum].element != ELEMENT::ELECTRO)		// ��ų ���Ұ� ���̳� ������ �ƴϸ� �����ϸ� ������Ŵ
			return -1;
		break;
	case REACTION::SUPERCONDUCT:
		if (skill[sknum].element != ELEMENT::CRYO && skill[sknum].element != ELEMENT::ELECTRO)
			return -1;
		break;
	case REACTION::ELECTRO_CHARGED:
		if (skill[sknum].element != ELEMENT::HYDRO && skill[sknum].element != ELEMENT::ELECTRO)
			return -1;
		break;
	case REACTION::BURNING:
		if (skill[sknum].element != ELEMENT::PYRO && skill[sknum].element != ELEMENT::DENDRO)
			return -1;
		break;
	case REACTION::SHATTER:		// ����� �ϴ� ��Ȱ��ȭ �Ѵ�... ���߼� ������ ��������� �Ѵ�
		return -1;
	case REACTION::SWIRL:		// �Ϲ������� �ٶ�ĳ������ Ȯ���� ����ų �� �ִٰ� �����Ѵ�, � ���Ҹ� Ȯ���Ű������ �����ؾ� �ϴµ�... �ϴ� �� ���� Ȯ������ ��
		if (skill[sknum].element != ELEMENT::AMENO)
			return -1;
		break;
	case REACTION::BLOOM:
		if (skill[sknum].element != ELEMENT::HYDRO && skill[sknum].element != ELEMENT::DENDRO)
			return -1;
		break;
	case REACTION::HYPERBLOOM:
	case REACTION::AGGRAVATE:
		if (skill[sknum].element != ELEMENT::ELECTRO)		// ����, ������ �������Ұ� ����Ų��
			return -1;
		break;
	case REACTION::BURGEON:
	case REACTION::VAPORIZE_P:
	case REACTION::MELT_P:
		if (skill[sknum].element != ELEMENT::PYRO)		// ��ȭ, ����(��->��), ����(��->����)�� �ҿ��Ұ� ����Ų��
			return -1;
		break;
	case REACTION::VAPORIZE_H:
		if (skill[sknum].element != ELEMENT::HYDRO)
			return -1;
		break;
	case REACTION::MELT_C:
		if (skill[sknum].element != ELEMENT::CRYO)
			return -1;
		break;
	case REACTION::SPREAD:
		if (skill[sknum].element != ELEMENT::DENDRO)
			return -1;
		break;
	case REACTION::NONE:
		break;
	default:
		break;
	}
	Stat buffStat = stat + b;		// ��� �� ���ȿ� ������ ����
	double resultDamage = 0.0;
	double baseDamage = 0.0;		// �⺻ ������(��� * ���ݷ� or)
	double critFactor = 0.0;		// ġ��Ÿ�� ��ġ�� ����
	switch (react)		// �Ÿ� �� ���
	{
	case REACTION::OVERLOADED:
		return BASE_DAMAGE[level] * (1 + buffStat.return_EM_effect(1)) * REACTION_FACTOR[(int)REACTION::OVERLOADED] * e.resist_factor(e.resistance[(int)ELEMENT::PYRO]);
	case REACTION::SUPERCONDUCT:
		return BASE_DAMAGE[level] * (1 + buffStat.return_EM_effect(1)) * REACTION_FACTOR[(int)REACTION::SUPERCONDUCT] * e.resist_factor(e.resistance[(int)ELEMENT::CRYO]);
	case REACTION::ELECTRO_CHARGED:
		return BASE_DAMAGE[level] * (1 + buffStat.return_EM_effect(1)) * REACTION_FACTOR[(int)REACTION::ELECTRO_CHARGED] * e.resist_factor(e.resistance[(int)ELEMENT::ELECTRO]);
	case REACTION::BURNING:
		return BASE_DAMAGE[level] * (1 + buffStat.return_EM_effect(1)) * REACTION_FACTOR[(int)REACTION::BURNING] * e.resist_factor(e.resistance[(int)ELEMENT::PYRO]);
	case REACTION::SHATTER:		// ����� �ϴ� ��Ȱ��ȭ �Ѵ�... ���߼� ������ ��������� �Ѵ�
		return -1;
	case REACTION::SWIRL:		// �Ϲ������� �ٶ�ĳ������ Ȯ���� ����ų �� �ִٰ� �����Ѵ�, � ���Ҹ� Ȯ���Ű������ �����ؾ� �ϴµ�... �ϴ� �� ���� Ȯ������ ��
		return BASE_DAMAGE[level] * (1 + buffStat.return_EM_effect(1)) * REACTION_FACTOR[(int)REACTION::SWIRL] * e.resist_factor(e.resistance[(int)ELEMENT::PYRO]);
	case REACTION::BLOOM:
		return BASE_DAMAGE[level] * (1 + buffStat.return_EM_effect(1)) * REACTION_FACTOR[(int)REACTION::BLOOM] * e.resist_factor(e.resistance[(int)ELEMENT::DENDRO]);
	case REACTION::HYPERBLOOM:
		return BASE_DAMAGE[level] * (1 + buffStat.return_EM_effect(1)) * REACTION_FACTOR[(int)REACTION::HYPERBLOOM] * e.resist_factor(e.resistance[(int)ELEMENT::DENDRO]);
	case REACTION::BURGEON:
		return BASE_DAMAGE[level] * (1 + buffStat.return_EM_effect(1)) * REACTION_FACTOR[(int)REACTION::BURGEON] * e.resist_factor(e.resistance[(int)ELEMENT::DENDRO]);
	case REACTION::NONE:
	case REACTION::VAPORIZE_P:
	case REACTION::VAPORIZE_H:
	case REACTION::MELT_P:
	case REACTION::MELT_C:
		switch (skill[sknum].base)		// �⺻������ ����
		{
		case OPTION::HP:
			baseDamage = buffStat.return_HP() * skill[sknum].coefficient;
			break;
		case OPTION::ATK:
			baseDamage = buffStat.return_ATK() * skill[sknum].coefficient;
			break;
		case OPTION::DEF:
			baseDamage = buffStat.return_DEF() * skill[sknum].coefficient;
			break;
		default:
			break;
		}

		switch (crit)
		{
		case CRIT_OPTION::NON_CRITICAL:
			critFactor = 1.0;
			break;
		case CRIT_OPTION::CRITICAL:
			critFactor = 1 + buffStat.criticalDMG;
			break;
		case CRIT_OPTION::EXPECTED:
			critFactor = buffStat.criticalRate * (1 + buffStat.criticalDMG) + (1 - buffStat.criticalRate) * 1.0;
			break;
		}

		// ���� �ٽ��� �Ǵ� ��
		resultDamage =  baseDamage * (1 + buffStat.damageBonus[(int)skill[sknum].element]) * ((level + 100) / (level + 100 + (e.level + 100) * e.defense)) * (e.resist_factor(e.resistance[(int)skill[sknum].element])) * critFactor;
		switch (react)		// �ѹ��� ü�� �Ÿ���
		{
		case REACTION::NONE:
			return resultDamage;
		case REACTION::VAPORIZE_P:
		case REACTION::VAPORIZE_H:
		case REACTION::MELT_P:
		case REACTION::MELT_C:
			return resultDamage * (1 + buffStat.return_EM_effect(2)) * REACTION_FACTOR[(int)react];
		}
	case REACTION::AGGRAVATE:
	case REACTION::SPREAD:
		switch (skill[sknum].base)		// �⺻������ ���� -> ������ ���� ����� �ջ�ȴ�
		{
		case OPTION::HP:
			baseDamage = buffStat.return_HP() * skill[sknum].coefficient + BASE_DAMAGE[level] * (1 + buffStat.return_EM_effect(3)) * REACTION_FACTOR[(int)react];
			break;
		case OPTION::ATK:
			baseDamage = buffStat.return_ATK() * skill[sknum].coefficient + BASE_DAMAGE[level] * (1 + buffStat.return_EM_effect(3)) * REACTION_FACTOR[(int)react];
			break;
		case OPTION::DEF:
			baseDamage = buffStat.return_DEF() * skill[sknum].coefficient + BASE_DAMAGE[level] * (1 + buffStat.return_EM_effect(3)) * REACTION_FACTOR[(int)react];
			break;
		default:
			break;
		}

		switch (crit)
		{
		case CRIT_OPTION::NON_CRITICAL:
			critFactor = 1.0;
			break;
		case CRIT_OPTION::CRITICAL:
			critFactor = 1 + buffStat.criticalDMG;
			break;
		case CRIT_OPTION::EXPECTED:
			critFactor = buffStat.criticalRate * (1 + buffStat.criticalDMG) + (1 - buffStat.criticalRate) * 1.0;
			break;
		}

		// ���� �ٽ��� �Ǵ� ��
		return baseDamage * (1 + buffStat.damageBonus[(int)skill[sknum].element]) * ((level + 100) / (level + 100 + (e.level + 100) * e.defense)) * (e.resist_factor(e.resistance[(int)skill[sknum].element])) * critFactor;
	default:
		break;
	}
	return 0;		// default�� �ɷ�����
}// ������ ����
void Character::show_all_damage(int sknum, const Enemy& e, const Buff& b, COORD out)		// ��ų�� ������ ��� ������ ���
{
	using std::cout;
	using std::endl;
	gotoxy(out.X, out.Y++);
	if (sknum > skills - 1 || sknum < 0)
	{
		cout << "��ų��ȣ�� �ùٸ� ������ �ƴմϴ�.\n";
		return;
	}
	int damage;
	int i;
	cout << "[" << skill[sknum].name << "]�� ������ �������� ������ �����ϴ�.";
	for (i = 0; i < 7; i++)		// 7�� ����, ����(��->��), ����(��->��), ����(��->����), ����(����->��), ����, �߻� ������ 7�̴�.. ����� �ϰ� �ͱ� ������.. ���������� �׳� ��
	{	
		damage = damage_of(sknum, e, b, REACTION(i), CRIT_OPTION::NON_CRITICAL);
		if (-1 == damage)		// ���� ��ų�� �ƴϸ�
			continue;
		gotoxy(out.X, out.Y++);
		cout << '<' << REACTION_NAME[i] << '>';
		cout << " ġ��X: " << damage;
		damage = damage_of(sknum, e, b, REACTION(i), CRIT_OPTION::CRITICAL);
		cout << " ġ��Ÿ: " << damage;
		damage = damage_of(sknum, e, b, REACTION(i), CRIT_OPTION::EXPECTED);
		cout << " ���: " << damage << endl;
	}
	gotoxy(out.X, out.Y++);
	for (; i < (int)REACTION::NUMBER; i++)		// ������ �ݺ�����
	{
		damage = damage_of(sknum, e, b, REACTION(i));
		if (-1 == damage)		// ���� ��ų�� �ƴϸ�
			continue;
		cout << '<' << REACTION_NAME[i] << "> : " << damage  << "  ";
	}
	return;
}
void Character::enchant(ELEMENT element)		// ��æƮ ó�� �Լ�(��� ��Ÿ ��æƮ�̹Ƿ� sknum�� ���� �ʿ������)
{
	for (int i = 0; i < skills; i++)
	{
		if (skill[i].type == Skill::SKILL_TYPE::NORMAL_ATTACK || skill[i].type == Skill::SKILL_TYPE::CHARGED_ATTACK || skill[i].type == Skill::SKILL_TYPE::PLUNGING_ATTACK)		// ��Ÿ ��æƮ
			skill[i].element = element;
	}
	return;
}
std::ofstream& operator<<(std::ofstream& fout, const Character& c)
{
	using std::endl;
	fout << c.name << '#' << c.level << ' ' << (int)c.constellation << endl;		// ��ȹ���� #
	fout << c.stat << endl;
	fout << c.skills << endl;
	for (int i = 0; i < c.skills; i++)
		fout << c.skill[i] << endl;
	return fout;
}// ĳ���� ���� ������� ������
std::ifstream& operator>>(std::ifstream& fin, Character& c)
{
	std::getline(fin, c.name, '#');
	fin >> c.level;
	int num;
	fin >> num;
	c.constellation = Character::CONSTELLATION(num);
	fin >> c.stat;
	(fin >> c.skills).get();
	delete[] c.skill;		// Ȥ�ó� ����Ű�� �ִ� ������ ����.. ��κ� nullptr�ϰ�..
	c.skill = new Skill[c.skills];		// ��ų ������ŭ �����Ҵ�
	for (int i = 0; i < c.skills; i++)
		(fin >> c.skill[i]).get();		// ������ ���� ������� ���� ��ų �̸� �Է¹��� �� ����
	return fin;
}// ĳ���� ���� ���Ͽ��� �Է¹޴� ������