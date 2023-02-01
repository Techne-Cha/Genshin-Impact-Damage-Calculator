// 원신 데미지 계산
// 만든이 : 차민호
// 제작 기간 : 2022.11.01. ~ 2023.1.30.
// 
// <Version 1.35>
// - Character 클래스 작성
// - 각청, 클레, 행추, 노엘 파생 클래스 작성
// - 데이터 베이스 작성
// - 인터페이스 구현

#ifndef BASE_H_
#define BASE_H_

#include "interface.h"		// 콘솔 박스 인터페이스 사용
#include <fstream>

inline void eatline() { while (std::cin.get() != '\n'); }		// 버퍼 제거함수
enum class OPTION { HP, HP_PER, ATK, ATK_PER, DEF, DEF_PER, ELEMENTAL_MASTERY, ENERGE_RECHARGE, CRIT_RATE, CRIT_DMG, NUMBER };
const char* const OPTION_NAME[int(OPTION::NUMBER)] = { "체력", "체퍼", "공격력", "공퍼", "방어력", "방퍼", "원마", "원충", "치확", "치피" };
enum class ELEMENT { PYRO, HYDRO, DENDRO, ELECTRO, AMENO, CRYO, GEO, PHYSICAL, NUMBER };		// 마지막 NUMBER는 원소 종류의 개수
const char* const ELEMENT_NAME[int(ELEMENT::NUMBER)] = { "불", "물", "풀", "번개", "바람", "얼음", "바위", "물리" };		// 원소 이름들
enum class CRIT_OPTION { NON_CRITICAL, CRITICAL, EXPECTED };
enum class REACTION { NONE, VAPORIZE_P, VAPORIZE_H, MELT_P, MELT_C, AGGRAVATE, SPREAD, OVERLOADED, SUPERCONDUCT, ELECTRO_CHARGED, BURNING, SHATTER, SWIRL, BLOOM, HYPERBLOOM, BURGEON, NUMBER };		// 반응 종류(없음, 증발(불->물), 증발(물->불), 융해(불->얼음), 융해(얼음->불), 촉진, 발산, 과부하, 초전도, 감전, 연소, 쇄빙, 확산, 개화, 만개, 발화)
const char* const REACTION_NAME[int(REACTION::NUMBER)] = { "없음", "증발(불->물)", "증발(물->불)", "융해(불->얼음)", "융해(얼음->불)", "촉진", "발산", "과부하", "초전도", "감전", "연소", "쇄빙", "확산", "개화", "만개", "발화" };		// 반응 이름
const double REACTION_FACTOR[int(REACTION::NUMBER)] = { 1.0, 1.5, 2.0, 2.0, 1.5, 1.15, 1.25, 2.0, 0.5, 1.2, 0.25, 1.5, 0.6, 2.0, 3.0, 3.0 };		// 반응 계수들
const double BASE_DAMAGE[91] = {
	0,		// BASE_DAMAGE[level] 하면 바로 결과를 얻을 수 있도록
	12.2, 0, 0, 0, 0, 0, 0, 0, 0, 0,			// 1~10
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,				// 11~20
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,				// 21~30
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,				// 31~40
	0, 0, 0, 0, 0, 0, 0, 0, 0, 233.3,			// 41~50
	0, 0, 0, 0, 0, 0, 0, 0, 0, 492.3,			// 51~60
	0, 0, 0, 0, 0, 0, 0, 0, 0, 765.6,			// 61~70
	0, 0, 0, 0, 915.3, 0, 0, 0, 1044.4, 1077.8,	// 71~80
	1110, 1142.9, 1180.55, 1216.63, 1253.9, 1290.89, 1329.11, 1368.08, 1407.83, 1448.38		// 81~90
};		// 레벨 별 격변 베이스 데미지
const int ENEMY_NAME_LENGTH = 40;

struct Buff;		// 사전선언..(show_stat 오버로딩 버전 때문임)

// 캐릭터 스탯 구조체
// 초깃값을 가지고 있다
struct Stat
{
	int baseHP = 0;		// 기초체
	int baseATK = 0;		// 기초공
	int baseDEF = 0;		// 기초방
	int additionalHP = 0;		// 추가체
	int additionalATK = 0;		// 추가공
	int additionalDEF = 0;		// 추가방
	int elementalMastery = 0;		// 원소마스터리
	double criticalRate = 0.0;		// 치확
	double criticalDMG = 0.0;		// 치피
	double energyRecharge = 0.0;		// 원충
	double damageBonus[int(ELEMENT::NUMBER)] = { 0.0 };		// 피해량 배열
	int return_HP() const { return baseHP + additionalHP; }		// 최대 체력 리턴
	int return_ATK() const { return baseATK + additionalATK; }		// 공격력 리턴
	int return_DEF() const { return baseDEF + additionalDEF; }		// 방어력 리턴
	double return_EM_effect(int n) const;		// 원소마스터리에 의한 보너스를 리턴, 1: 격변 2: 증폭 3: 격화
	void set_stat(COORD in, int range);		// 스탯을 대화형으로 설정하는 함수
	void show_stat(COORD out) const;		// 스탯을 출력하는 함수
	void show_stat(COORD out, const Buff& buff) const;		// 스탯을 출력하는 함수(오버로딩 버전)
};
std::ofstream& operator<<(std::ofstream& fout, const Stat& stat);		// 스탯을 파일에 출력하는 함수, 출력후 개행 없음
std::ifstream& operator>>(std::ifstream& fin, Stat& stat);		// 스탯을 파일에서 입력받는 함수

// 스탯버프(캐릭 자체 능력치를 제외한)
// 초깃값을 가지고 있다
// 모두 같은 형으로(예를 들어 float 형) 맞추는게 프로그래밍 상 이점이 큰 것 같다
struct Buff
{
	int hp = 0;		// 깡체
	int atk = 0;		// 깡공
	int def = 0;		// 깡방
	double hpPer = 0.0;		// 체퍼
	double atkPer = 0.0;		// 공퍼
	double defPer = 0.0;		// 방퍼
	int elementalMastery = 0;		// 원마
	double energyRecharge = 0.0;		// 원충
	double critRate = 0.0;		// 치확
	double critDamage = 0.0;		// 치피
	double damageBonus[int(ELEMENT::NUMBER)] = { 0.0 };		// 피해량 배열
	void add_buff();		// 버프를 대화형으로 더하는 함수
	void show_buff(COORD out, int menu) const;		// 버프를 출력하는 함수
	void reset_buff();		// 버프를 초기 상태로 돌리는 함수
};

Stat operator+(Stat s, const Buff& b);		// stat + buff -> 버프 적용된 스탯 반환.. 버프는 변동하지만 스탯은 계산 중 변하지 않으므로 값으로 반환한다

// 캐릭터 스킬 정보 구조체
// 
struct Skill
{
	enum class SKILL_TYPE { NORMAL_ATTACK, CHARGED_ATTACK, PLUNGING_ATTACK, E, Q, NUMBER};		// 스킬 종류(일반공격, 강공격, 낙하공격, 원소스킬, 원소폭발)
	std::string name;		// 스킬 이름
	SKILL_TYPE type;		// 스킬 종류
	ELEMENT element;		// 스킬 원소
	OPTION base;		// 무엇을 기반으로 하는지(ex.. 공격력계수, 방어력계수..)
	double coefficient;		// 스킬 계수
	int repetition;		// 스킬 반복 횟수
	void set_skill(COORD in, int range);		// 스킬정보를 대화형으로 설정하는 함수
	void show_skill(COORD out) const;		// 스킬 정보를 출력하는 함수
};
std::ofstream& operator<<(std::ofstream& fout, const Skill& skill);		// 스킬정보 파일에 출력하는 함수, 출력후 개행 없음
std::ifstream& operator>>(std::ifstream& fin, Skill& skill);		// 스킬정보를 파일에서 입력받는 함수

// 적 정보 구조체
// 데이터 베이스에 읽어 사용할 예정
struct Enemy
{
	char name[ENEMY_NAME_LENGTH];		// 적 이름
	int level = 0;		// 적 레벨
	double resistance[int(ELEMENT::NUMBER)];		// 적 내성, 무한대는 INT_MAX로 저장
	double defense = 1.0;		// 적 방어력 비율(ex.. 20% 방깎 -> defense = 0.8)
	double resist_factor(double r) const;		// 내성 효과 계산
	void show_info1(COORD out) const;		// 적 이름, 내성 출력(원래 자리에 있던 내용 지우지 않는다)
	void show_info2(COORD out) const;		// 레벨, 방어력 비율 출력(원래 자리에 있던 내용 지우지 않는다)
	void change_info(COORD in, int range);		// 적 레벨, 내성배열, 방어력 비율 설정
};

// 무기 클래스(ABC)
// 무기 효과는 무기마다 파생하여 작성하도록 해야겠다
class Weapon
{
	enum class TYPE { SWORD, CATALYST, CLAYMORE, BOW, POLEARM };		// 한손검, 법구, 대검, 활, 창
	TYPE type;		// 무기 종류
	std::string name;		// 무기 이름
	int level;		// 무기 레벨
	int refinementRank;		// 재련 단계
	int baseATK;		// 기초 공격력
	OPTION mainOption;		// 주 옵션
public:
	Weapon() { }
	virtual ~Weapon() = 0 { }
};

// 성유물 클래스(ABC)
// 
class Artifacts
{
public:
	Artifacts() { }
	virtual ~Artifacts() = 0 { }
};

// 캐릭터 클래스(ABC)
// 무기, 성유물을 컨테인해야 하지만 먼저 그냥 구현해보자
class Character		
{
public:
	enum class CONSTELLATION { LV0, LV1, LV2, LV3, LV4, LV5, LV6 };
private:
	std::string name;		// 캐릭터 이름
	int level;		// 캐릭 레벨
	CONSTELLATION constellation;		// 별자리 돌파
	Stat stat;
	int skills;		// 스킬 개수(1~)
	Skill* skill;		// 스킬들을 저장할 거임
public:
	explicit Character(const std::string& n = "noname") : name(n), level(0), constellation(CONSTELLATION::LV0), skill(nullptr), skills(0) { }		// 기본 생성자
	Character(const Character& c);		// 복사 생성자
	virtual ~Character() = 0;
	Character& operator=(const Character& c);		// 대입 연산자
	void set_info(COORD in, int range);		// 정보 설정함수, 스킬정보 동적할당도 여기서 일어남, COORD형 1개, 글자가 들어갈 수 있는 범위 전달받음
	void show_stat(COORD out) const;		// 가지고 있는 스탯 출력 함수
	void show_stat(COORD out, const Buff& buff) const;		// 가지고 있는 스탯 출력 함수(오버로딩 버전)
	void show_skills(COORD out, int* menu = nullptr) const;		// 스킬 정보 보여주는 함수, 키 입력받아 메뉴 선택시 1 반환
	std::string return_name() const { return name; }		// 이름 리턴하는 함수
	CONSTELLATION return_constellation() const { return constellation; }		// 별자리 리턴하는 함수
	Stat return_stat() const { return stat; }		// 스탯 리턴하는 함수
	bool same_kind(int s, Skill::SKILL_TYPE type) const { return type == skill[s].type; }		// 스킬번호의 스킬이 해당 스킬타입인지 true or false
	int damage_of(int sknum, const Enemy& e, const Buff& b, REACTION react = REACTION::NONE, CRIT_OPTION crit = CRIT_OPTION::EXPECTED) const;		// 데미지 리턴, 계산이 허락되지 않는 경우 -1 반환
	void show_all_damage(int sknum, const Enemy& e, const Buff& b, COORD out);		// 스킬로 가능한 모든 데미지 출력
	virtual void reflect_passive(int& sknum, Enemy& e, Buff& b, COORD in, int range) = 0;		// 패시브 적용하여 적 정보, 버프 설정, 캐릭터마다 달라짐(원래 const였으나 인챈트 처리때문에 const일 수 없게 되었다)
	void enchant(ELEMENT element);		// 인챈트 처리 함수(모두 평타 인챈트이므로 sknum은 딱히 필요없을듯)
	friend std::ofstream& operator<<(std::ofstream& fout, const Character& c);		// 캐릭터 정보 파일출력 프렌드
	friend std::ifstream& operator>>(std::ifstream& fin, Character& c);		// 캐릭터 정보 파일에서 입력받는 프렌드
};

#endif