// 파생클래스(캐릭터) 모음

#ifndef CHARACTERS_H_
#define CHARACTERS_H_

#include "base.h"

const int CHARACTERS = 4;		// 작성된 캐릭터 클래스 수

class Keqing : public Character
{
public:
	Keqing() : Character("각청") { }		// 이름만 고정
	virtual ~Keqing() { }
	virtual void reflect_passive(int& sknum, Enemy& e, Buff& b, COORD in, int range);		// 패시브 적용하여 적 정보, 버프 설정, 캐릭터마다 달라짐
};

class Klee : public Character
{
public:
	Klee() : Character("클레") { }		// 이름만 고정
	virtual ~Klee() { }
	virtual void reflect_passive(int& sknum, Enemy& e, Buff& b, COORD in, int range);		// 패시브 적용하여 적 정보, 버프 설정, 캐릭터마다 달라짐
};

class Xingqiu : public Character
{
public:
	Xingqiu() : Character("행추") { }		// 이름만 고정
	virtual ~Xingqiu() { }
	virtual void reflect_passive(int& sknum, Enemy& e, Buff& b, COORD in, int range);		// 패시브 적용하여 적 정보, 버프 설정, 캐릭터마다 달라짐
};

class Noelle : public Character
{
public:
	Noelle() : Character("노엘") { }		// 이름만 고정
	virtual ~Noelle() { }
	virtual void reflect_passive(int& sknum, Enemy& e, Buff& b, COORD in, int range);		// 패시브 적용하여 적 정보, 버프 설정, 캐릭터마다 달라짐
};

#endif