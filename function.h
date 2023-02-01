// 중요 함수 작성

#ifndef FUNCTION_H_
#define FUNCTION_H_

#include "characters.h"

void revise_database();		// 데이터 베이스 추가/수정/검색
void damage_calculation();		// 데미지 계산
void set_charinfo(Character& c, COORD in, int range);		// 캐릭터 정보 설정/재설정 하여 파일에 저장.. 캐릭터 정보도 같이 설정됨
Enemy ememy_identification();		// 적 검색 후 특정
void buff_setting(Buff& buff);		// 버프 재설정

#endif