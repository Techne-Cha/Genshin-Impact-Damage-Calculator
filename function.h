// �߿� �Լ� �ۼ�

#ifndef FUNCTION_H_
#define FUNCTION_H_

#include "characters.h"

void revise_database();		// ������ ���̽� �߰�/����/�˻�
void damage_calculation();		// ������ ���
void set_charinfo(Character& c, COORD in, int range);		// ĳ���� ���� ����/�缳�� �Ͽ� ���Ͽ� ����.. ĳ���� ������ ���� ������
Enemy ememy_identification();		// �� �˻� �� Ư��
void buff_setting(Buff& buff);		// ���� �缳��

#endif