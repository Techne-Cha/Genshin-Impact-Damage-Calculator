// tetris ������Ʈ�� �������̽� ����� �����ͼ� C++ �������� �ٲ�

#ifndef INTERFACE_H_
#define INTERFACE_H_

#include <Windows.h>
#include <sstream>		// ostringstream ��� ����, ���� ��� �ȿ� <string> ��� �ִ�
#include <iostream>
#include <conio.h>      // getch() �Լ� ���
#include <cstring>

const int B_COLOR = 0;	//����  /����(0), ��ο� �Ķ�(16), ��ο� �ʷ�(32), ��ο� �ϴ�(48), ��ο� ����(64), ��ο� ����(80), ��ο� ���(96), ȸ��(112), ��ο� ȸ��(128), �Ķ�(144), �ʷ�(160), �ϴ�(176), ����(192), ���� (208), ���(224), �Ͼ�(240) 
const int N_COLOR = 15;	    // �⺻���ڻ�   /����(0), ��ο� �Ķ�(1), ��ο� �ʷ�(2), ��ο� �ϴ�(3), ��ο� ����(4), ��ο� ����(5), ��ο� ���(6), ȸ��(7), ��ο� ȸ��(8), �Ķ�(9), �ʷ�(10), �ϴ�(11), ����(12), ����(13), ���(14), �Ͼ�(15) 
const int H_COLOR = 10;		// �������ڻ�

enum class KEY {
    UP = 72, DOWN = 80, RIGHT = 77, LEFT = 75, ENTER = 13, EXIT = 101, SPACE = 32
};      // �ƽ�Ű�ڵ� ��

enum class ALIGNMENT {
    LEFT, RIGHT, CENTER
};      // ����

void gotoxy(double x, int y);			// Ŀ�� �̵� �Լ� (����, ����), �ѱ��� 1*1, ���ĺ��� 1*0.5, 0.5�� �޾Ƶ��̱� ���� x�� double
void console(int g, int s);			// �ܼ� ũ�� ���� �Լ�(����, ����) (â �Ӽ��� ������ ũ��� ���ĺ� ������. ���⼭�� �ѱ� �������� ��, Ŀ�� ��ġ�� 0,0���� �Űܰ�
void color(int a, int b);			// �� ���� �Լ� (����, ���ڻ�) 
void CursorView(char show);			// Ŀ�� ����� �Լ� 0: �����, 1: ��Ÿ���� 
void box(int g, int s, int gl, int sl, const char* str = nullptr, ALIGNMENT alignment = ALIGNMENT::LEFT, int visible = 1, int erase = 0);	// x��ǥ, y��ǥ, x����, y���� (���̴� ���ڸ� �� �� �ִ� ���̸� ����), �ڽ��ȿ� �� ���ڿ�, ���ڿ� ����, �ڽ� ���̸� 1, �Ⱥ��̰� �ϸ� 0, �������� ����� 1, �ƴϸ� 0

#endif