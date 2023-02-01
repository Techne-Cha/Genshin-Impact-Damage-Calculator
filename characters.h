// �Ļ�Ŭ����(ĳ����) ����

#ifndef CHARACTERS_H_
#define CHARACTERS_H_

#include "base.h"

const int CHARACTERS = 4;		// �ۼ��� ĳ���� Ŭ���� ��

class Keqing : public Character
{
public:
	Keqing() : Character("��û") { }		// �̸��� ����
	virtual ~Keqing() { }
	virtual void reflect_passive(int& sknum, Enemy& e, Buff& b, COORD in, int range);		// �нú� �����Ͽ� �� ����, ���� ����, ĳ���͸��� �޶���
};

class Klee : public Character
{
public:
	Klee() : Character("Ŭ��") { }		// �̸��� ����
	virtual ~Klee() { }
	virtual void reflect_passive(int& sknum, Enemy& e, Buff& b, COORD in, int range);		// �нú� �����Ͽ� �� ����, ���� ����, ĳ���͸��� �޶���
};

class Xingqiu : public Character
{
public:
	Xingqiu() : Character("����") { }		// �̸��� ����
	virtual ~Xingqiu() { }
	virtual void reflect_passive(int& sknum, Enemy& e, Buff& b, COORD in, int range);		// �нú� �����Ͽ� �� ����, ���� ����, ĳ���͸��� �޶���
};

class Noelle : public Character
{
public:
	Noelle() : Character("�뿤") { }		// �̸��� ����
	virtual ~Noelle() { }
	virtual void reflect_passive(int& sknum, Enemy& e, Buff& b, COORD in, int range);		// �нú� �����Ͽ� �� ����, ���� ����, ĳ���͸��� �޶���
};

#endif