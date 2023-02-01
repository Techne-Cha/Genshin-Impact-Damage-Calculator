// ���� ������ ���
// ������ : ����ȣ
// ���� �Ⱓ : 2022.11.01. ~ 2023.1.30.
// 
// <Version 1.35>
// - Character Ŭ���� �ۼ�
// - ��û, Ŭ��, ����, �뿤 �Ļ� Ŭ���� �ۼ�
// - ������ ���̽� �ۼ�
// - �������̽� ����

#ifndef BASE_H_
#define BASE_H_

#include "interface.h"		// �ܼ� �ڽ� �������̽� ���
#include <fstream>

inline void eatline() { while (std::cin.get() != '\n'); }		// ���� �����Լ�
enum class OPTION { HP, HP_PER, ATK, ATK_PER, DEF, DEF_PER, ELEMENTAL_MASTERY, ENERGE_RECHARGE, CRIT_RATE, CRIT_DMG, NUMBER };
const char* const OPTION_NAME[int(OPTION::NUMBER)] = { "ü��", "ü��", "���ݷ�", "����", "����", "����", "����", "����", "ġȮ", "ġ��" };
enum class ELEMENT { PYRO, HYDRO, DENDRO, ELECTRO, AMENO, CRYO, GEO, PHYSICAL, NUMBER };		// ������ NUMBER�� ���� ������ ����
const char* const ELEMENT_NAME[int(ELEMENT::NUMBER)] = { "��", "��", "Ǯ", "����", "�ٶ�", "����", "����", "����" };		// ���� �̸���
enum class CRIT_OPTION { NON_CRITICAL, CRITICAL, EXPECTED };
enum class REACTION { NONE, VAPORIZE_P, VAPORIZE_H, MELT_P, MELT_C, AGGRAVATE, SPREAD, OVERLOADED, SUPERCONDUCT, ELECTRO_CHARGED, BURNING, SHATTER, SWIRL, BLOOM, HYPERBLOOM, BURGEON, NUMBER };		// ���� ����(����, ����(��->��), ����(��->��), ����(��->����), ����(����->��), ����, �߻�, ������, ������, ����, ����, ���, Ȯ��, ��ȭ, ����, ��ȭ)
const char* const REACTION_NAME[int(REACTION::NUMBER)] = { "����", "����(��->��)", "����(��->��)", "����(��->����)", "����(����->��)", "����", "�߻�", "������", "������", "����", "����", "���", "Ȯ��", "��ȭ", "����", "��ȭ" };		// ���� �̸�
const double REACTION_FACTOR[int(REACTION::NUMBER)] = { 1.0, 1.5, 2.0, 2.0, 1.5, 1.15, 1.25, 2.0, 0.5, 1.2, 0.25, 1.5, 0.6, 2.0, 3.0, 3.0 };		// ���� �����
const double BASE_DAMAGE[91] = {
	0,		// BASE_DAMAGE[level] �ϸ� �ٷ� ����� ���� �� �ֵ���
	12.2, 0, 0, 0, 0, 0, 0, 0, 0, 0,			// 1~10
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,				// 11~20
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,				// 21~30
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,				// 31~40
	0, 0, 0, 0, 0, 0, 0, 0, 0, 233.3,			// 41~50
	0, 0, 0, 0, 0, 0, 0, 0, 0, 492.3,			// 51~60
	0, 0, 0, 0, 0, 0, 0, 0, 0, 765.6,			// 61~70
	0, 0, 0, 0, 915.3, 0, 0, 0, 1044.4, 1077.8,	// 71~80
	1110, 1142.9, 1180.55, 1216.63, 1253.9, 1290.89, 1329.11, 1368.08, 1407.83, 1448.38		// 81~90
};		// ���� �� �ݺ� ���̽� ������
const int ENEMY_NAME_LENGTH = 40;

struct Buff;		// ��������..(show_stat �����ε� ���� ������)

// ĳ���� ���� ����ü
// �ʱ갪�� ������ �ִ�
struct Stat
{
	int baseHP = 0;		// ����ü
	int baseATK = 0;		// ���ʰ�
	int baseDEF = 0;		// ���ʹ�
	int additionalHP = 0;		// �߰�ü
	int additionalATK = 0;		// �߰���
	int additionalDEF = 0;		// �߰���
	int elementalMastery = 0;		// ���Ҹ����͸�
	double criticalRate = 0.0;		// ġȮ
	double criticalDMG = 0.0;		// ġ��
	double energyRecharge = 0.0;		// ����
	double damageBonus[int(ELEMENT::NUMBER)] = { 0.0 };		// ���ط� �迭
	int return_HP() const { return baseHP + additionalHP; }		// �ִ� ü�� ����
	int return_ATK() const { return baseATK + additionalATK; }		// ���ݷ� ����
	int return_DEF() const { return baseDEF + additionalDEF; }		// ���� ����
	double return_EM_effect(int n) const;		// ���Ҹ����͸��� ���� ���ʽ��� ����, 1: �ݺ� 2: ���� 3: ��ȭ
	void set_stat(COORD in, int range);		// ������ ��ȭ������ �����ϴ� �Լ�
	void show_stat(COORD out) const;		// ������ ����ϴ� �Լ�
	void show_stat(COORD out, const Buff& buff) const;		// ������ ����ϴ� �Լ�(�����ε� ����)
};
std::ofstream& operator<<(std::ofstream& fout, const Stat& stat);		// ������ ���Ͽ� ����ϴ� �Լ�, ����� ���� ����
std::ifstream& operator>>(std::ifstream& fin, Stat& stat);		// ������ ���Ͽ��� �Է¹޴� �Լ�

// ���ȹ���(ĳ�� ��ü �ɷ�ġ�� ������)
// �ʱ갪�� ������ �ִ�
// ��� ���� ������(���� ��� float ��) ���ߴ°� ���α׷��� �� ������ ū �� ����
struct Buff
{
	int hp = 0;		// ��ü
	int atk = 0;		// ����
	int def = 0;		// ����
	double hpPer = 0.0;		// ü��
	double atkPer = 0.0;		// ����
	double defPer = 0.0;		// ����
	int elementalMastery = 0;		// ����
	double energyRecharge = 0.0;		// ����
	double critRate = 0.0;		// ġȮ
	double critDamage = 0.0;		// ġ��
	double damageBonus[int(ELEMENT::NUMBER)] = { 0.0 };		// ���ط� �迭
	void add_buff();		// ������ ��ȭ������ ���ϴ� �Լ�
	void show_buff(COORD out, int menu) const;		// ������ ����ϴ� �Լ�
	void reset_buff();		// ������ �ʱ� ���·� ������ �Լ�
};

Stat operator+(Stat s, const Buff& b);		// stat + buff -> ���� ����� ���� ��ȯ.. ������ ���������� ������ ��� �� ������ �����Ƿ� ������ ��ȯ�Ѵ�

// ĳ���� ��ų ���� ����ü
// 
struct Skill
{
	enum class SKILL_TYPE { NORMAL_ATTACK, CHARGED_ATTACK, PLUNGING_ATTACK, E, Q, NUMBER};		// ��ų ����(�Ϲݰ���, ������, ���ϰ���, ���ҽ�ų, ��������)
	std::string name;		// ��ų �̸�
	SKILL_TYPE type;		// ��ų ����
	ELEMENT element;		// ��ų ����
	OPTION base;		// ������ ������� �ϴ���(ex.. ���ݷ°��, ���°��..)
	double coefficient;		// ��ų ���
	int repetition;		// ��ų �ݺ� Ƚ��
	void set_skill(COORD in, int range);		// ��ų������ ��ȭ������ �����ϴ� �Լ�
	void show_skill(COORD out) const;		// ��ų ������ ����ϴ� �Լ�
};
std::ofstream& operator<<(std::ofstream& fout, const Skill& skill);		// ��ų���� ���Ͽ� ����ϴ� �Լ�, ����� ���� ����
std::ifstream& operator>>(std::ifstream& fin, Skill& skill);		// ��ų������ ���Ͽ��� �Է¹޴� �Լ�

// �� ���� ����ü
// ������ ���̽��� �о� ����� ����
struct Enemy
{
	char name[ENEMY_NAME_LENGTH];		// �� �̸�
	int level = 0;		// �� ����
	double resistance[int(ELEMENT::NUMBER)];		// �� ����, ���Ѵ�� INT_MAX�� ����
	double defense = 1.0;		// �� ���� ����(ex.. 20% ��� -> defense = 0.8)
	double resist_factor(double r) const;		// ���� ȿ�� ���
	void show_info1(COORD out) const;		// �� �̸�, ���� ���(���� �ڸ��� �ִ� ���� ������ �ʴ´�)
	void show_info2(COORD out) const;		// ����, ���� ���� ���(���� �ڸ��� �ִ� ���� ������ �ʴ´�)
	void change_info(COORD in, int range);		// �� ����, �����迭, ���� ���� ����
};

// ���� Ŭ����(ABC)
// ���� ȿ���� ���⸶�� �Ļ��Ͽ� �ۼ��ϵ��� �ؾ߰ڴ�
class Weapon
{
	enum class TYPE { SWORD, CATALYST, CLAYMORE, BOW, POLEARM };		// �Ѽհ�, ����, ���, Ȱ, â
	TYPE type;		// ���� ����
	std::string name;		// ���� �̸�
	int level;		// ���� ����
	int refinementRank;		// ��� �ܰ�
	int baseATK;		// ���� ���ݷ�
	OPTION mainOption;		// �� �ɼ�
public:
	Weapon() { }
	virtual ~Weapon() = 0 { }
};

// ������ Ŭ����(ABC)
// 
class Artifacts
{
public:
	Artifacts() { }
	virtual ~Artifacts() = 0 { }
};

// ĳ���� Ŭ����(ABC)
// ����, �������� �������ؾ� ������ ���� �׳� �����غ���
class Character		
{
public:
	enum class CONSTELLATION { LV0, LV1, LV2, LV3, LV4, LV5, LV6 };
private:
	std::string name;		// ĳ���� �̸�
	int level;		// ĳ�� ����
	CONSTELLATION constellation;		// ���ڸ� ����
	Stat stat;
	int skills;		// ��ų ����(1~)
	Skill* skill;		// ��ų���� ������ ����
public:
	explicit Character(const std::string& n = "noname") : name(n), level(0), constellation(CONSTELLATION::LV0), skill(nullptr), skills(0) { }		// �⺻ ������
	Character(const Character& c);		// ���� ������
	virtual ~Character() = 0;
	Character& operator=(const Character& c);		// ���� ������
	void set_info(COORD in, int range);		// ���� �����Լ�, ��ų���� �����Ҵ絵 ���⼭ �Ͼ, COORD�� 1��, ���ڰ� �� �� �ִ� ���� ���޹���
	void show_stat(COORD out) const;		// ������ �ִ� ���� ��� �Լ�
	void show_stat(COORD out, const Buff& buff) const;		// ������ �ִ� ���� ��� �Լ�(�����ε� ����)
	void show_skills(COORD out, int* menu = nullptr) const;		// ��ų ���� �����ִ� �Լ�, Ű �Է¹޾� �޴� ���ý� 1 ��ȯ
	std::string return_name() const { return name; }		// �̸� �����ϴ� �Լ�
	CONSTELLATION return_constellation() const { return constellation; }		// ���ڸ� �����ϴ� �Լ�
	Stat return_stat() const { return stat; }		// ���� �����ϴ� �Լ�
	bool same_kind(int s, Skill::SKILL_TYPE type) const { return type == skill[s].type; }		// ��ų��ȣ�� ��ų�� �ش� ��ųŸ������ true or false
	int damage_of(int sknum, const Enemy& e, const Buff& b, REACTION react = REACTION::NONE, CRIT_OPTION crit = CRIT_OPTION::EXPECTED) const;		// ������ ����, ����� ������� �ʴ� ��� -1 ��ȯ
	void show_all_damage(int sknum, const Enemy& e, const Buff& b, COORD out);		// ��ų�� ������ ��� ������ ���
	virtual void reflect_passive(int& sknum, Enemy& e, Buff& b, COORD in, int range) = 0;		// �нú� �����Ͽ� �� ����, ���� ����, ĳ���͸��� �޶���(���� const������ ��æƮ ó�������� const�� �� ���� �Ǿ���)
	void enchant(ELEMENT element);		// ��æƮ ó�� �Լ�(��� ��Ÿ ��æƮ�̹Ƿ� sknum�� ���� �ʿ������)
	friend std::ofstream& operator<<(std::ofstream& fout, const Character& c);		// ĳ���� ���� ������� ������
	friend std::ifstream& operator>>(std::ifstream& fin, Character& c);		// ĳ���� ���� ���Ͽ��� �Է¹޴� ������
};

#endif