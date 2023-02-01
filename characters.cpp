// characters.h 함수들

#include "characters.h"

extern double 격변bonus;
extern double 증폭bonus;
extern double 격화bonus;

void Klee::reflect_passive(int& sknum, Enemy& e, Buff& b, COORD in, int range)		// 패시브 적용하여 적 정보, 버프 설정, 캐릭터마다 달라짐
{
	char ch;
	int n;
	if (10 == sknum && return_constellation() < CONSTELLATION::LV1)		// 10번스킬 - 1돌 연쇄폭발 : 쾅쾅불꽃의 120% 피해
	{
		sknum = -1;		// 허용되지 않는 스킬로 바꾼다
		return;
	}
	if (11 == sknum && return_constellation() < CONSTELLATION::LV4)		// 11번 스킬 - 4돌 일촉즉발 : 궁 지속시간 내 퇴장 시 555% 불원소 범위피해
	{
		sknum = -1;		// 허용되지 않는 스킬로 바꾼다
		return;
	}
	CursorView(1);
	switch (return_constellation())
	{
	case CONSTELLATION::LV6:
		box(in.X - 1, in.Y - 1, range, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// 입력창 지우기
		gotoxy(in.X, in.Y);
		std::cout << "원소폭발 발동 후 25초 이내인가요?(y/n): ";
		std::cin >> ch;
		if ('y' == ch)
			b.damageBonus[int(ELEMENT::PYRO)] += 0.10;		// 원폭 발동후 25초동안 파티 불원소피해 10% 증가
		eatline();
	case CONSTELLATION::LV5:
	case CONSTELLATION::LV4:
	case CONSTELLATION::LV3:
	case CONSTELLATION::LV2:
		box(in.X - 1, in.Y - 1, range, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// 입력창 지우기
		gotoxy(in.X, in.Y);
		std::cout << "적이 부비트랩을 밟은지 10초 이내인가요?(y/n): ";
		std::cin >> ch;
		if ('y' == ch)
			e.defense -= 0.23;		// 부비트랩 밟고 10초동안 적 방어력 23% 감소
		eatline();
	case CONSTELLATION::LV1:
	case CONSTELLATION::LV0:
		if (same_kind(sknum, Skill::SKILL_TYPE::CHARGED_ATTACK))		// 강공격이면
		{
			box(in.X - 1, in.Y - 1, range, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// 입력창 지우기
			gotoxy(in.X, in.Y);
			std::cout << "폭렬불꽃을 소모했나요?(y/n): ";
			std::cin >> ch;
			if ('y' == ch)
				b.damageBonus[int(ELEMENT::PYRO)] += 0.50;		// 특성 - 폭렬불꽃 소모한 강공격 가피증 50%
			eatline();
		}
		break;
	}
	// 무기 - 사풍원서
	box(in.X - 1, in.Y - 1, range, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// 입력창 지우기
	gotoxy(in.X, in.Y);
	std::cout << "사풍원서 몇 스택인가요?(0~4): ";
	std::cin >> n;
	if (0 <= n && n <= 4)
		for (int i = 0; i < int(ELEMENT::NUMBER) - 1; i++)		// 물리 뺀 원소 개수(7)
			b.damageBonus[i] += (n * 0.08);		// 스택당 원소피해보너스 8%
	eatline();
	// 성유물 - 마녀4셋
	격변bonus = 0.40;		// 과부하, 연소, 발화 피해보너스 40%
	증폭bonus = 0.15;		// 증발, 융해 피해보너스 15%
	box(in.X - 1, in.Y - 1, range, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// 입력창 지우기
	gotoxy(in.X, in.Y);
	std::cout << "E스킬 몇 번 발동했나요?(0~3): ";
	std::cin >> n;
	if (0 <= n && n <= 3)
		b.damageBonus[int(ELEMENT::PYRO)] += (n * 0.075);		// 스택당 불원피7.5% 증가
	eatline();

	box(in.X - 1, in.Y - 1, range, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// 입력창 지우기
	CursorView(0);
	return;
}

void Xingqiu::reflect_passive(int& sknum, Enemy& e, Buff& b, COORD in, int range)		// 패시브 적용하여 적 정보, 버프 설정, 캐릭터마다 달라짐
{
	char ch;
	CursorView(1);
	switch (return_constellation())
	{
	case CONSTELLATION::LV6:
	case CONSTELLATION::LV5:
	case CONSTELLATION::LV4:
		if (same_kind(sknum, Skill::SKILL_TYPE::E))		// 원소스킬이면
		{
			box(in.X - 1, in.Y - 1, range, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// 입력창 지우기
			gotoxy(in.X, in.Y);
			std::cout << "원소폭발이 지속중인가요?(y/n): ";
			std::cin >> ch;
			if ('y' == ch)
				b.damageBonus[int(ELEMENT::HYDRO)] += 0.50;		// 원폭 지속시간 중 원소스킬 피해량 50% 증가
			eatline();
		}
	case CONSTELLATION::LV3:
	case CONSTELLATION::LV2:
		box(in.X - 1, in.Y - 1, range, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// 입력창 지우기
		gotoxy(in.X, in.Y);
		std::cout << "적이 원소폭발에 맞은 후 4초 안인가요?(y/n): ";
		std::cin >> ch;
		if ('y' == ch)
			e.resistance[int(ELEMENT::HYDRO)] -= 0.15;		// 검의 비 공격 맞은 후 4초간 물원소 내성 15% 감소
		eatline();
	case CONSTELLATION::LV1:
	case CONSTELLATION::LV0:
		break;
	}
	box(in.X - 1, in.Y - 1, range, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// 입력창 지우기
	CursorView(0);
	return;
}

void Noelle::reflect_passive(int& sknum, Enemy& e, Buff& b, COORD in, int range)
{
	char ch;
	int n;
	double coefficient = 0.76;		// 대청소 공격력 증가시키는 방어력 비율
	Stat buffStat;
	if (12 == sknum && return_constellation() < CONSTELLATION::LV4)		// 12번스킬 - 4돌 나중에 청소할게요 : 호심경 파괴시 400% 공계수 바원피
	{
		sknum = -1;		// 허용되지 않는 스킬로 바꾼다
		return;
	}
	CursorView(1);
	switch (return_constellation())
	{
	case CONSTELLATION::LV6:
		coefficient += 0.50;		// 추가로 방어력의 50%만큼 공격력 증가
	case CONSTELLATION::LV5:
	case CONSTELLATION::LV4:
	case CONSTELLATION::LV3:
	case CONSTELLATION::LV2:
		if (same_kind(sknum, Skill::SKILL_TYPE::CHARGED_ATTACK))
		{
			for (int i = 0; i < int(ELEMENT::NUMBER); i++)		// 일반적인 가피증은 그냥 모든 원소 피증으로 만든다...
				b.damageBonus[i] += 0.15;		// 강공격 피증 15%
		}
	case CONSTELLATION::LV1:
	case CONSTELLATION::LV0:
		break;
	}
	// 무기 - 백영검
	box(in.X - 1, in.Y - 1, range, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// 입력창 지우기
	gotoxy(in.X, in.Y);
	std::cout << "백영검 몇 스택인가요?(0~4): ";
	std::cin >> n;
	if (0 <= n && n <= 4)
	{
		b.atkPer += (n * 0.075);		// 공격력 스택당 7.5% 증가
		b.defPer += (n * 0.075);		// 방어력 스택당 7.5% 증가
	}
	eatline();
	// 성유물 - 유성 4셋
	if (same_kind(sknum, Skill::SKILL_TYPE::NORMAL_ATTACK) || same_kind(sknum, Skill::SKILL_TYPE::CHARGED_ATTACK))		// 일반공격이나 강공격이면
	{
		box(in.X - 1, in.Y - 1, range, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// 입력창 지우기
		gotoxy(in.X, in.Y);
		std::cout << "보호막이 있나요?(y/n): ";
		std::cin >> ch;
		if ('y' == ch)
			for (int i = 0; i < int(ELEMENT::NUMBER); i++)		// 일반적인 가피증은 그냥 모든 원소 피증으로 만든다...
				b.damageBonus[i] += 0.40;		// 일반, 강공격 피증 40%
		eatline();
	}
	// 스냅샷되는 대청소 공버프는 모든 버프 계산 후 여기서 한다
	box(in.X - 1, in.Y - 1, range, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// 입력창 지우기
	gotoxy(in.X, in.Y);
	std::cout << "대청소 발동 중인가요?(y/n): ";
	std::cin >> ch;
	if ('y' == ch)
	{
		buffStat = return_stat() + b;
		b.atk += (buffStat.baseDEF + buffStat.additionalDEF) * coefficient;		// 대청소 효과 : 공격력이 방어력의 76%만큼 상승(스냅샷 고려해야 하는데....)
		enchant(ELEMENT::GEO);		// 평타 바위 인챈트
	}
	else
		enchant(ELEMENT::PHYSICAL);		// 아니면 다시 물리로
	eatline();

	box(in.X - 1, in.Y - 1, range, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// 입력창 지우기
	CursorView(0);
	return;
}

void Keqing::reflect_passive(int& sknum, Enemy& e, Buff& b, COORD in, int range)
{
	char ch;
	int n;
	if (17 == sknum && return_constellation() < CONSTELLATION::LV1)		// 17번스킬 - 1돌 계뢰 : 성신회귀 2번째 발동 시 각청이 사라지고 나타나는 위치게 50% 번개원소 범위피해
	{
		sknum = -1;		// 허용되지 않는 스킬로 바꾼다
		return;
	}
	CursorView(1);
	switch (return_constellation())
	{
	case CONSTELLATION::LV6:
		box(in.X - 1, in.Y - 1, range, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// 입력창 지우기
		gotoxy(in.X, in.Y);
		std::cout << "일반공격, 강공격, E, Q 스택(0~4): ";
		std::cin >> n;
		if (0 <= n && n <= 4)
			b.damageBonus[int(ELEMENT::ELECTRO)] += (n * 0.06);		// 4종류의 공격 사용후 8초간 번원피 6% 증가(각각 지속시간 8초)
		eatline();
	case CONSTELLATION::LV5:
	case CONSTELLATION::LV4:
		box(in.X - 1, in.Y - 1, range, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// 입력창 지우기
		gotoxy(in.X, in.Y);
		std::cout << "번개원소 관련 반응 발동 후 10초 이내인가요?(y/n): ";
		std::cin >> ch;
		if ('y' == ch)
			b.atkPer += 0.25;		// 공격력 25% 증가
		eatline();
	case CONSTELLATION::LV3:
	case CONSTELLATION::LV2:
	case CONSTELLATION::LV1:
	case CONSTELLATION::LV0:
		if (same_kind(sknum, Skill::SKILL_TYPE::NORMAL_ATTACK) || same_kind(sknum, Skill::SKILL_TYPE::CHARGED_ATTACK) || same_kind(sknum, Skill::SKILL_TYPE::PLUNGING_ATTACK))
		{
			box(in.X - 1, in.Y - 1, range, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// 입력창 지우기
			gotoxy(in.X, in.Y);
			std::cout << "성신회귀 참격 발동 후 5초 이내인가요?(y/n): ";
			std::cin >> ch;
			if ('y' == ch)
				enchant(ELEMENT::ELECTRO);		// 평타 번개 인챈트
			else
				enchant(ELEMENT::PHYSICAL);		// 아님 다시 물리로
			eatline();
		}
		box(in.X - 1, in.Y - 1, range, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// 입력창 지우기
		gotoxy(in.X, in.Y);
		std::cout << "천가순유 발동 후 8초 이내인가요?(y/n): ";
		std::cin >> ch;
		if ('y' == ch)
		{
			b.critRate += 0.15;		// 치확 15% 증가
			b.energyRecharge += 0.15;		// 원충 15% 증가
		}
		eatline();
		break;
	}
	// 무기 - 칠흑검
	if (same_kind(sknum, Skill::SKILL_TYPE::NORMAL_ATTACK) || same_kind(sknum, Skill::SKILL_TYPE::CHARGED_ATTACK))		// 일반공격이나 강공격이면
	{
		for (int i = 0; i < int(ELEMENT::NUMBER); i++)		// 일반적인 가피증은 그냥 모든 원소 피증으로 만든다...
			b.damageBonus[i] += 0.20;		// 일반, 강공격 피증 20%
	}
	// 성유물 - 번분 4셋
	격변bonus = 0.40;		// 과부하, 감전, 초전도, 만개 피해보너스 40%
	격화bonus = 0.20;		// 촉진 피해보너스 15%

	box(in.X - 1, in.Y - 1, range, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// 입력창 지우기
	CursorView(0);
	return;
}