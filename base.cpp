// base.h 함수들

#include "base.h"
#include <climits>
#include <float.h>
// 원래는 stat과 buff에 넣는 것이 맞을 듯 하지만 너무 복잡해져... 임시방편으로 전역변수로 설정한다...
extern double 격변bonus = 0.0;
extern double 증폭bonus = 0.0;
extern double 격화bonus = 0.0;

double Stat::return_EM_effect(int n) const
{
	switch (n)
	{
	case 1:
		return 16.0 * elementalMastery / (elementalMastery + 2000) + 격변bonus;		// 격변
	case 2:
		return 2.78 * elementalMastery / (elementalMastery + 1400) + 증폭bonus;		// 증폭
	case 3:
		return 5.0 * elementalMastery / (elementalMastery + 1200) + 격화bonus;		// 격화
	default:
		return 0;
	}
}// 원소마스터리에 의한 보너스를 리턴, 1: 격변 2: 증폭 3: 격화
void Stat::set_stat(COORD in, int range)
{
	using std::cout;
	using std::endl;
	using std::cin;
	int i;		// for 문 용
	CursorView(1);
	gotoxy(in.X, in.Y);
	cout << "기초체력: ";
	cin >> baseHP;
	gotoxy(in.X, in.Y);
	for (i = 0; i < range; i++)
		cout << "  ";		// 지우기
	gotoxy(in.X, in.Y);
	cout << "추가체력: ";
	cin >> additionalHP;
	gotoxy(in.X, in.Y);
	for (i = 0; i < range; i++)
		cout << "  ";		// 지우기
	gotoxy(in.X, in.Y);
	cout << "기초공격력: ";
	cin >> baseATK;
	gotoxy(in.X, in.Y);
	for (i = 0; i < range; i++)
		cout << "  ";		// 지우기
	gotoxy(in.X, in.Y);
	cout << "추가공격력: ";
	cin >> additionalATK;
	gotoxy(in.X, in.Y);
	for (i = 0; i < range; i++)
		cout << "  ";		// 지우기
	gotoxy(in.X, in.Y);
	cout << "기초방어력: ";
	cin >> baseDEF;
	gotoxy(in.X, in.Y);
	for (i = 0; i < range; i++)
		cout << "  ";		// 지우기
	gotoxy(in.X, in.Y);
	cout << "추가방어력: ";
	cin >> additionalDEF;
	gotoxy(in.X, in.Y);
	for (i = 0; i < range; i++)
		cout << "  ";		// 지우기
	gotoxy(in.X, in.Y);
	cout << "원소마스터리: ";
	cin >> elementalMastery;
	gotoxy(in.X, in.Y);
	for (i = 0; i < range; i++)
		cout << "  ";		// 지우기
	gotoxy(in.X, in.Y);
	cout << "치명타 확률: ";
	cin >> criticalRate;
	gotoxy(in.X, in.Y);
	for (i = 0; i < range; i++)
		cout << "  ";		// 지우기
	gotoxy(in.X, in.Y);
	cout << "치명타 피해: ";
	cin >> criticalDMG;
	gotoxy(in.X, in.Y);
	for (i = 0; i < range; i++)
		cout << "  ";		// 지우기
	gotoxy(in.X, in.Y);
	cout << "원소충전효율: ";
	cin >> energyRecharge;
	gotoxy(in.X, in.Y);
	for (i = 0; i < range; i++)
		cout << "  ";		// 지우기
	gotoxy(in.X, in.Y);
	for (int j = 0; j < int(ELEMENT::NUMBER); j++)
	{
		cout << ELEMENT_NAME[j] << " 피해보너스: ";
		cin >> damageBonus[j];
		gotoxy(in.X, in.Y);
		for (i = 0; i < range; i++)
			cout << "  ";		// 지우기
		gotoxy(in.X, in.Y);
	}
	eatline();
	return;
}// 스탯을 대화형으로 설정하는 함수
void Stat::show_stat(COORD out) const
{
	using std::cout;
	using std::endl;
	gotoxy(out.X, out.Y++);
	cout << "체력: " << baseHP << " + " << additionalHP;
	gotoxy(out.X, out.Y++);
	cout << "공격력: " << baseATK << " + " << additionalATK;
	gotoxy(out.X, out.Y++);
	cout << "방어력: " << baseDEF << " + " << additionalDEF;
	gotoxy(out.X, out.Y++);
	cout << "원마: " << elementalMastery << ", 원충: " << energyRecharge;
	gotoxy(out.X, out.Y++);
	cout << "치확: " << criticalRate << ", 치피: " << criticalDMG;
	gotoxy(out.X, out.Y++);
	cout << "피해보너스";
	for (int i = 0; i < int(ELEMENT::NUMBER); i++)		// 0이 아닌 피해보너스만 출력하기로
	{
		if (damageBonus[i] - 0.0 > DBL_EPSILON)		// 피해보너스 0이 아니면
		{
			gotoxy(out.X, out.Y++);
			cout << ELEMENT_NAME[i] << ": " << damageBonus[i];
		}
	}
}// 스탯을 출력하는 함수
void Stat::show_stat(COORD out, const Buff& buff) const		// 스탯을 출력하는 함수(오버로딩 버전)
{
	Stat buffStat = *this + buff;
	buffStat.show_stat(out);
	return;
}
std::ofstream& operator<<(std::ofstream& fout, const Stat& stat)
{
	fout << stat.baseHP << " " << stat.baseATK << " " << stat.baseDEF << " " << stat.additionalHP << " " << stat.additionalATK << " " << stat.additionalDEF << " " << stat.elementalMastery << " " << stat.criticalRate << " " << stat.criticalDMG << " " << stat.energyRecharge << " ";		// 정의된 순서대로 저장
	for (int i = 0; i < int(ELEMENT::NUMBER); i++)
		fout << stat.damageBonus[i] << " ";
	return fout;
}// 파일에 출력하는 함수
std::ifstream& operator>>(std::ifstream& fin, Stat& stat)
{
	fin >> stat.baseHP >> stat.baseATK >> stat.baseDEF >> stat.additionalHP >> stat.additionalATK >> stat.additionalDEF >> stat.elementalMastery >> stat.criticalRate >> stat.criticalDMG >> stat.energyRecharge;		// 빈칸을 사이사이에 넣어 저장하였기 때문에 화이트스페이스 무시로 바로 읽을 수 있다
	for (int i = 0; i < int(ELEMENT::NUMBER); i++)
		fin >> stat.damageBonus[i];
	return fin;
}// 파일에서 입력받는 함수
void Buff::add_buff()		// 버프를 대화형으로 더하는 함수
{
	using std::cout;
	using std::endl;
	using std::cin;
	int intValue;
	double doubleValue;

	cout << "깡체: ";
	cin >> intValue;
	hp += intValue;
	cout << "체퍼: ";
	cin >> doubleValue;
	hpPer += doubleValue;
	cout << "깡공: ";
	cin >> intValue;
	atk += intValue;
	cout << "공퍼: ";
	cin >> doubleValue;
	atkPer += doubleValue;
	cout << "깡방: ";
	cin >> intValue;
	def += intValue;
	cout << "방퍼: ";
	cin >> doubleValue;
	defPer += doubleValue;
	cout << "원소마스터리: ";
	cin >> intValue;
	elementalMastery += intValue;
	cout << "치명타 확률: ";
	cin >> doubleValue;
	critRate += doubleValue;
	cout << "치명타 피해: ";
	cin >> doubleValue;
	critDamage += doubleValue;
	cout << "원소충전효율: ";
	cin >> doubleValue;
	energyRecharge += doubleValue;
	for (int i = 0; i < int(ELEMENT::NUMBER); i++)
	{
		cout << ELEMENT_NAME[i] << " 피해보너스: ";
		cin >> doubleValue;
		damageBonus[i] += doubleValue;
	}
	cout << "버프 추가 완료.\n";
	eatline();
	return;
}
void Buff::show_buff(COORD out, int menu) const
{
	using std::cout;
	using std::endl;
	gotoxy(out.X, out.Y++);
	cout << "현재 버프";

	gotoxy(out.X, out.Y++);
	if (menu == 0)
		color(B_COLOR, H_COLOR);
	cout << "깡체: " << hp;
	if (menu == 0)
		color(B_COLOR, N_COLOR);

	gotoxy(out.X, out.Y++);
	if (menu == 1)
		color(B_COLOR, H_COLOR);
	cout << "체퍼: " << hpPer;
	if (menu == 1)
		color(B_COLOR, N_COLOR);

	gotoxy(out.X, out.Y++);
	if (menu == 2)
		color(B_COLOR, H_COLOR);
	cout << "깡공: " << atk;
	if (menu == 2)
		color(B_COLOR, N_COLOR);

	gotoxy(out.X, out.Y++);
	if (menu == 3)
		color(B_COLOR, H_COLOR);
	cout << "공퍼: " << atkPer;
	if (menu == 3)
		color(B_COLOR, N_COLOR);

	gotoxy(out.X, out.Y++);
	if (menu == 4)
		color(B_COLOR, H_COLOR);
	cout << "깡방: " << def;
	if (menu == 4)
		color(B_COLOR, N_COLOR);

	gotoxy(out.X, out.Y++);
	if (menu == 5)
		color(B_COLOR, H_COLOR);
	cout << "방퍼: " << defPer;
	if (menu == 5)
		color(B_COLOR, N_COLOR);

	gotoxy(out.X, out.Y++);
	if (menu == 6)
		color(B_COLOR, H_COLOR);
	cout << "원마: " << elementalMastery;
	if (menu == 6)
		color(B_COLOR, N_COLOR);

	gotoxy(out.X, out.Y++);
	if (menu == 7)
		color(B_COLOR, H_COLOR);
	cout << "원충: " << energyRecharge;
	if (menu == 7)
		color(B_COLOR, N_COLOR);

	gotoxy(out.X, out.Y++);
	if (menu == 8)
		color(B_COLOR, H_COLOR);
	cout << "치확: " << critRate;
	if (menu == 8)
		color(B_COLOR, N_COLOR);

	gotoxy(out.X, out.Y++);
	if (menu == 9)
		color(B_COLOR, H_COLOR);
	cout << "치피: " << critDamage;
	if (menu == 9)
		color(B_COLOR, N_COLOR);

	gotoxy(out.X, out.Y++);
	cout << "피해보너스";
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
	cout << "버프 리셋";
	if (menu == 18)
		color(B_COLOR, N_COLOR);

	gotoxy(out.X, out.Y++);
	if (menu == 19)
		color(B_COLOR, H_COLOR);
	cout << "설정 완료";
	if (menu == 19)
		color(B_COLOR, N_COLOR);
	return;
}// 버프를 출력하는 함수, 메뉴출력 제어도 함(20개 메뉴(18개 옵션 + 리셋 + 확정))
void Buff::reset_buff()		// 버프를 초기 상태로 돌리는 함수
{
	hp = 0;		// 깡체
	atk = 0;		// 깡공
	def = 0;		// 깡방
	hpPer = 0.0;		// 체퍼
	atkPer = 0.0;		// 공퍼
	defPer = 0.0;		// 방퍼
	elementalMastery = 0;		// 원마
	energyRecharge = 0.0;		// 원충
	critRate = 0.0;		// 치확
	critDamage = 0.0;		// 치피
	for (int i = 0; i < int(ELEMENT::NUMBER); i++)
		damageBonus[i] = 0.0;
	return;
}
Stat operator+(Stat s, const Buff& b)
{
	s.additionalHP += s.baseHP * b.hpPer + b.hp;		// 추가체에 기초체*체퍼 + 깡체 더함
	s.additionalATK += s.baseATK * b.atkPer + b.atk;		// 추가공에 기초공*공퍼 + 깡공 더함
	s.additionalDEF += s.baseDEF * b.defPer + b.def;		// 추가방에 기초방*방퍼 + 깡방 더함
	s.elementalMastery += b.elementalMastery;
	s.criticalRate += b.critRate;
	s.criticalDMG += b.critDamage;
	s.energyRecharge += b.energyRecharge;
	for (int i = 0; i < int(ELEMENT::NUMBER); i++)
		s.damageBonus[i] += b.damageBonus[i];
	return s;
}// stat + buff -> 버프 적용된 스탯 반환.. 

void Skill::set_skill(COORD in, int range)
{
	using std::cout;
	using std::endl;
	using std::cin;
	int i;		// for 문 용
	CursorView(1);
	gotoxy(in.X, in.Y);
	cout << "스킬 이름: ";
	getline(cin, name);
	gotoxy(in.X, in.Y);
	for (i = 0; i < range; i++)
		cout << "  ";		// 지우기
	gotoxy(in.X, in.Y);
	cout << "스킬 종류(0: 일반공격, 1: 강공격, 2: 낙하공격, 3: 원소스킬, 4: 원소폭발): ";
	int num;
	cin >> num;
	type = SKILL_TYPE(num);
	gotoxy(in.X, in.Y);
	for (i = 0; i < range; i++)
		cout << "  ";		// 지우기
	gotoxy(in.X, in.Y);
	cout << "스킬 원소( ";
	for (int i = 0; i < int(ELEMENT::NUMBER); i++)
		cout << i << ": " << ELEMENT_NAME[i] << " ";
	cout << "): ";
	cin >> num;
	element = ELEMENT(num);
	gotoxy(in.X, in.Y);
	for (i = 0; i < range; i++)
		cout << "  ";		// 지우기
	gotoxy(in.X, in.Y);
	cout << "베이스(0: 체 2: 공 4: 방): ";
	cin >> num;
	base = OPTION(num);
	gotoxy(in.X, in.Y);
	for (i = 0; i < range; i++)
		cout << "  ";		// 지우기
	gotoxy(in.X, in.Y);
	cout << "스킬 계수: ";
	cin >> coefficient;
	gotoxy(in.X, in.Y);
	for (i = 0; i < range; i++)
		cout << "  ";		// 지우기
	gotoxy(in.X, in.Y);
	cout << "스킬 반복 횟수: ";
	cin >> repetition;
	gotoxy(in.X, in.Y);
	for (i = 0; i < range; i++)
		cout << "  ";		// 지우기
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
		cout << "일반공격, ";
		break;
	case SKILL_TYPE::CHARGED_ATTACK:
		cout << "강공격, ";
		break;
	case SKILL_TYPE::PLUNGING_ATTACK:
		cout << "낙하공격, ";
		break;
	case SKILL_TYPE::E:
		cout << "원소스킬, ";
		break;
	case SKILL_TYPE::Q:
		cout << "원소폭발, ";
		break;
	}
	cout << ELEMENT_NAME[int(element)] << ", ";
	switch (base)
	{
	case OPTION::HP:
		cout << "체) - ";
		break;
	case OPTION::ATK:
		cout << "공) - ";
		break;
	case OPTION::DEF:
		cout << "방) - ";
		break;
	}
	cout << coefficient << " * " << repetition << "회\n";
}// 스킬 정보를 출력하는 함수
std::ofstream& operator<<(std::ofstream& fout, const Skill& skill)
{
	fout << skill.name << "#";		// 구획문자 #
	fout << int(skill.type) << " " << int(skill.element) << " " << int(skill.base) << " " << skill.coefficient << " " << skill.repetition;
	return fout;
}// 파일에 출력하는 함수
std::ifstream& operator>>(std::ifstream& fin, Skill& skill)
{
	std::getline(fin, skill.name, '#');		// 구획문자 #를 만날때까지 읽고, #는 읽어 버림
	int num;
	fin >> num;
	skill.type = Skill::SKILL_TYPE(num);
	fin >> num;
	skill.element = ELEMENT(num);
	fin >> num;
	skill.base = OPTION(num);
	fin >> skill.coefficient >> skill.repetition;
	return fin;
}// 파일에서 입력받는 함수

double Enemy::resist_factor(double r) const
{
	if (r < 0)		// 내성이 음수일때
		return 1 - r / 2;		// 내성 감소 효과 1/2
	else if (r < 0.75)		// 0 <= 내성 < 0.75 일때
		return 1 - r;
	else		// 내성이 75% 초과하면
		return 1 / (1 + 4 * r);
}
void Enemy::show_info1(COORD out) const		// 적 이름, 내성 출력(원래 자리 지우지 않음)
{
	box(out.X - 1, out.Y - 1, ENEMY_NAME_LENGTH / 2, 1, name, ALIGNMENT::CENTER, 0);		// 박스가 좌표위치를 취하므로 글자가 좌표위치를 취하도록 -1
	// 0.35 -> 4글자, 한글로는 2글자
	for (int i = 0; i < int(ELEMENT::NUMBER); i++)
	{
		if (resist_factor(resistance[i]) < FLT_EPSILON)		// 내성 무한대면(귀찮음의 결과로 임의로 잡은 기준이다)
			box(out.X + ENEMY_NAME_LENGTH / 2 + i * 3, out.Y - 1, 2, 1, "∞", ALIGNMENT::LEFT, 0);
		else
		{
			gotoxy(out.X + ENEMY_NAME_LENGTH / 2 + 1 + i * 3, out.Y);
			std::cout << resistance[i];
		}
	}
	return;
}
void Enemy::show_info2(COORD out) const		// 레벨, 방어력 비율 출력
{
	box(out.X - 1, out.Y - 1, 3, 1, "레벨: ", ALIGNMENT::LEFT, 0, 1);		// 적 부가정보 출력
	gotoxy(out.X + 3, out.Y);
	std::cout << level;
	box(out.X + 4, out.Y - 1, 6, 1, "방어력비율: ", ALIGNMENT::LEFT, 0, 1);
	gotoxy(out.X + 11, out.Y);
	std::cout << defense;
	return;
}
void Enemy::change_info(COORD in, int range)		// 적 레벨, 내성배열, 방어력 비율 설정
{
	using std::cout;
	using std::endl;
	using std::cin;

	CursorView(1);
	box(in.X - 1, in.Y - 1, range, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// 입력받을 창 지우기
	gotoxy(in.X, in.Y);
	cout << "적 레벨: ";
	cin >> level;
	double decrease;		// 내성 감소 비율, 방어력 감소 비율
	for (int i = 0; i < int(ELEMENT::NUMBER); i++)
	{
		box(in.X - 1, in.Y - 1, range, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// 입력받을 창 지우기
		gotoxy(in.X, in.Y);
		cout << ELEMENT_NAME[i] << "내성감소: ";
		cin >> decrease;
		if (INT_MAX != resistance[i])		// 내성 무한대가 아닐때만
			resistance[i] -= decrease;
	}
	box(in.X - 1, in.Y - 1, range, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// 입력받을 창 지우기
	gotoxy(in.X, in.Y);
	cout << "방깎: ";
	cin >> decrease;
	defense -= decrease;
	box(in.X - 1, in.Y - 1, range, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// 입력받을 창 지우기
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
}// 복사 생성자
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
}// 대입 연산자
void Character::set_info(COORD in, int range)
{
	using std::cout;
	using std::cin;
	using std::endl;
	int i;		// for 문 용
	CursorView(1);
	gotoxy(in.X, in.Y);
	cout << "이름: ";
	cin >> name;
	gotoxy(in.X, in.Y);
	for (i = 0; i < range; i++)
		cout << "  ";		// 지우기
	gotoxy(in.X, in.Y);
	cout << "레벨: ";
	cin >> level;
	gotoxy(in.X, in.Y);
	for (i = 0; i < range; i++)
		cout << "  ";		// 지우기
	gotoxy(in.X, in.Y);
	cout << "별자리(0~6): ";
	int num;
	cin >> num;
	constellation = CONSTELLATION(num);
	gotoxy(in.X, in.Y);
	for (i = 0; i < range; i++)
		cout << "  ";		// 지우기
	eatline();
	stat.set_stat(in, range);
	gotoxy(in.X, in.Y);
	cout << "스킬 개수: ";
	(cin >> skills).get();
	gotoxy(in.X, in.Y);
	for (i = 0; i < range; i++)
		cout << "  ";		// 지우기
	gotoxy(in.X, in.Y);
	delete[] skill;		// 이전 정보 해제
	skill = new Skill[skills];
	for (int i = 0; i < skills; i++)
		skill[i].set_skill(in, range);
	CursorView(0);
}// 정보 설정함수
void Character::show_stat(COORD out) const		// 가지고 있는 스탯 출력 함수
{
	using std::cout;
	using std::endl;
	gotoxy(out.X, out.Y++);
	cout << "레벨: " << level << endl;
	gotoxy(out.X, out.Y++);
	cout << "별자리: " << int(constellation) << "돌파";
	stat.show_stat(out);
	return;
}
void Character::show_stat(COORD out, const Buff& buff) const		// 가지고 있는 스탯 출력 함수(오버로딩 버전)
{
	using std::cout;
	using std::endl;
	gotoxy(out.X, out.Y++);
	cout << "레벨: " << level << endl;
	gotoxy(out.X, out.Y++);
	cout << "별자리: " << int(constellation) << "돌파";
	stat.show_stat(out, buff);
	return;
}
void Character::show_skills(COORD out, int* menu) const		// 스킬 정보 보여주는 함수, 메뉴출력 제어도 함
{
	COORD temp = out;
	// 한번에 스킬 15개까지만 출력가능
	int end = (skills < 15 ? skills : 15);
	if (menu == nullptr)		// 기본 출력
	{
		for (int i = 0; i < end; i++)
			skill[i].show_skill({ out.X, out.Y++ });
		return;
	}
	if (*menu >= skills)
		*menu = skills - 1;		// 밖에서는 skills의 값을 모른다. 모르고 DOWN 키 때문에 menu를 올려도 여기서 보정해준다.
	int start = (15 <= *menu ? *menu - 14 : 0);
	if (*menu >= 14)		// 페이지 바깥의 스킬이면
		box(temp.X - 1, temp.Y - 1, 37, 15, nullptr, ALIGNMENT::LEFT, 0, 1);		// 스킬 출력창 지우기(너비는 실험적으로 정함)
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
	switch (react)		// 반응을 일으킬 수 없는 스킬이면 거른다
	{
	case REACTION::OVERLOADED:
		if (skill[sknum].element != ELEMENT::PYRO && skill[sknum].element != ELEMENT::ELECTRO)		// 스킬 원소가 불이나 번개가 아니면 과부하를 못일으킴
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
	case REACTION::SHATTER:		// 쇄빙은 일단 비활성화 한다... 폭발성 공격을 규정지어야 한다
		return -1;
	case REACTION::SWIRL:		// 일반적으로 바람캐릭만이 확산을 일으킬 수 있다고 가정한다, 어떤 원소를 확산시키는지도 규정해야 하는데... 일단 불 원소 확산으로 함
		if (skill[sknum].element != ELEMENT::AMENO)
			return -1;
		break;
	case REACTION::BLOOM:
		if (skill[sknum].element != ELEMENT::HYDRO && skill[sknum].element != ELEMENT::DENDRO)
			return -1;
		break;
	case REACTION::HYPERBLOOM:
	case REACTION::AGGRAVATE:
		if (skill[sknum].element != ELEMENT::ELECTRO)		// 만개, 촉진은 번개원소가 일으킨다
			return -1;
		break;
	case REACTION::BURGEON:
	case REACTION::VAPORIZE_P:
	case REACTION::MELT_P:
		if (skill[sknum].element != ELEMENT::PYRO)		// 발화, 증발(불->물), 융해(불->얼음)는 불원소가 일으킨다
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
	Stat buffStat = stat + b;		// 계산 전 스탯에 버프를 제공
	double resultDamage = 0.0;
	double baseDamage = 0.0;		// 기본 데미지(계수 * 공격력 or)
	double critFactor = 0.0;		// 치명타가 미치는 요인
	switch (react)		// 거른 후 계산
	{
	case REACTION::OVERLOADED:
		return BASE_DAMAGE[level] * (1 + buffStat.return_EM_effect(1)) * REACTION_FACTOR[(int)REACTION::OVERLOADED] * e.resist_factor(e.resistance[(int)ELEMENT::PYRO]);
	case REACTION::SUPERCONDUCT:
		return BASE_DAMAGE[level] * (1 + buffStat.return_EM_effect(1)) * REACTION_FACTOR[(int)REACTION::SUPERCONDUCT] * e.resist_factor(e.resistance[(int)ELEMENT::CRYO]);
	case REACTION::ELECTRO_CHARGED:
		return BASE_DAMAGE[level] * (1 + buffStat.return_EM_effect(1)) * REACTION_FACTOR[(int)REACTION::ELECTRO_CHARGED] * e.resist_factor(e.resistance[(int)ELEMENT::ELECTRO]);
	case REACTION::BURNING:
		return BASE_DAMAGE[level] * (1 + buffStat.return_EM_effect(1)) * REACTION_FACTOR[(int)REACTION::BURNING] * e.resist_factor(e.resistance[(int)ELEMENT::PYRO]);
	case REACTION::SHATTER:		// 쇄빙은 일단 비활성화 한다... 폭발성 공격을 규정지어야 한다
		return -1;
	case REACTION::SWIRL:		// 일반적으로 바람캐릭만이 확산을 일으킬 수 있다고 가정한다, 어떤 원소를 확산시키는지도 규정해야 하는데... 일단 불 원소 확산으로 함
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
		switch (skill[sknum].base)		// 기본데미지 세팅
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

		// 가장 핵심이 되는 식
		resultDamage =  baseDamage * (1 + buffStat.damageBonus[(int)skill[sknum].element]) * ((level + 100) / (level + 100 + (e.level + 100) * e.defense)) * (e.resist_factor(e.resistance[(int)skill[sknum].element])) * critFactor;
		switch (react)		// 한번더 체에 거른다
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
		switch (skill[sknum].base)		// 기본데미지 세팅 -> 원마에 의한 계수가 합산된다
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

		// 가장 핵심이 되는 식
		return baseDamage * (1 + buffStat.damageBonus[(int)skill[sknum].element]) * ((level + 100) / (level + 100 + (e.level + 100) * e.defense)) * (e.resist_factor(e.resistance[(int)skill[sknum].element])) * critFactor;
	default:
		break;
	}
	return 0;		// default에 걸렸을때
}// 데미지 리턴
void Character::show_all_damage(int sknum, const Enemy& e, const Buff& b, COORD out)		// 스킬로 가능한 모든 데미지 출력
{
	using std::cout;
	using std::endl;
	gotoxy(out.X, out.Y++);
	if (sknum > skills - 1 || sknum < 0)
	{
		cout << "스킬번호가 올바른 범위가 아닙니다.\n";
		return;
	}
	int damage;
	int i;
	cout << "[" << skill[sknum].name << "]의 가능한 데미지는 다음과 같습니다.";
	for (i = 0; i < 7; i++)		// 7은 없음, 증발(불->물), 증발(물->불), 융해(불->얼음), 융해(얼음->불), 촉진, 발산 까지의 7이다.. 상수로 하고 싶긴 하지만.. 복잡해지니 그냥 함
	{	
		damage = damage_of(sknum, e, b, REACTION(i), CRIT_OPTION::NON_CRITICAL);
		if (-1 == damage)		// 허용된 스킬이 아니면
			continue;
		gotoxy(out.X, out.Y++);
		cout << '<' << REACTION_NAME[i] << '>';
		cout << " 치명X: " << damage;
		damage = damage_of(sknum, e, b, REACTION(i), CRIT_OPTION::CRITICAL);
		cout << " 치명타: " << damage;
		damage = damage_of(sknum, e, b, REACTION(i), CRIT_OPTION::EXPECTED);
		cout << " 기댓값: " << damage << endl;
	}
	gotoxy(out.X, out.Y++);
	for (; i < (int)REACTION::NUMBER; i++)		// 나머지 격변반응
	{
		damage = damage_of(sknum, e, b, REACTION(i));
		if (-1 == damage)		// 허용된 스킬이 아니면
			continue;
		cout << '<' << REACTION_NAME[i] << "> : " << damage  << "  ";
	}
	return;
}
void Character::enchant(ELEMENT element)		// 인챈트 처리 함수(모두 평타 인챈트이므로 sknum은 딱히 필요없을듯)
{
	for (int i = 0; i < skills; i++)
	{
		if (skill[i].type == Skill::SKILL_TYPE::NORMAL_ATTACK || skill[i].type == Skill::SKILL_TYPE::CHARGED_ATTACK || skill[i].type == Skill::SKILL_TYPE::PLUNGING_ATTACK)		// 평타 인챈트
			skill[i].element = element;
	}
	return;
}
std::ofstream& operator<<(std::ofstream& fout, const Character& c)
{
	using std::endl;
	fout << c.name << '#' << c.level << ' ' << (int)c.constellation << endl;		// 구획문자 #
	fout << c.stat << endl;
	fout << c.skills << endl;
	for (int i = 0; i < c.skills; i++)
		fout << c.skill[i] << endl;
	return fout;
}// 캐릭터 정보 파일출력 프렌드
std::ifstream& operator>>(std::ifstream& fin, Character& c)
{
	std::getline(fin, c.name, '#');
	fin >> c.level;
	int num;
	fin >> num;
	c.constellation = Character::CONSTELLATION(num);
	fin >> c.stat;
	(fin >> c.skills).get();
	delete[] c.skill;		// 혹시나 가리키고 있는 포인터 해제.. 대부분 nullptr일걸..
	c.skill = new Skill[c.skills];		// 스킬 개수만큼 동적할당
	for (int i = 0; i < c.skills; i++)
		(fin >> c.skill[i]).get();		// 마지막 개행 지워줘야 다음 스킬 이름 입력받을 수 있음
	return fin;
}// 캐릭터 정보 파일에서 입력받는 프렌드