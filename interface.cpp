// interface.h �Լ���

#include "interface.h"

void gotoxy(double x, int y)
{
	COORD Cur;
	Cur.X = 2 * x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
	return;
}
void console(int g, int s)
{
	std::ostringstream outstr;
	color(B_COLOR, N_COLOR);
	outstr << "mode con cols=" << 2 * g << " lines=" << s;
	system(outstr.str().c_str());		// str() �޼���� ������ �������� �ʱ�ȭ�� string ��ü ����, c_str() �޼���� string ���ڿ��� const char* ���� ����
	return;
}
void color(int a, int b)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a | b);
	return;
}
void CursorView(char show)
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
	return;
}
void box(int g, int s, int gl, int sl, const char* str, ALIGNMENT alignment, int visible, int erase)	// x��ǥ, y��ǥ, x����, y���� (���̴� ���ڸ� �� �� �ִ� ���̸� ����), �ڽ��ȿ� �� ���ڿ�, ���ڿ� ����, �ڽ� ���̸� 1, �Ⱥ��̰� �ϸ� 0
{
	using std::cout;
	int x, y;
	if (erase)
		for (y = 1; y <= sl; y++)
		{
			gotoxy(g +1, s + y);
			for (x = 1; x <= gl; x++)
				cout << "  ";
		}
	if (visible)		// �ڽ��� ���̰� ������ ����
	{
		gotoxy(g, s);
		cout << "�� ";		// ���� ��ȣ�� ũ��� 1*1�ε� ����ϸ� Ŀ���� ���ĺ� ����� ��ó�� 0.5�� �����ִ�. �׷��� ��ĭ �ϳ� �� ������ִ� ���� ����
		for (x = 1; x <= gl; x++)
			cout << "�� ";
		cout << "�� ";
		for (y = 1; y <= sl; y++)
		{
			gotoxy(g, s + y);
			cout << "�� ";
			gotoxy(g + gl + 1, s + y);
			cout << "�� ";
		}
		gotoxy(g, s + y);
		cout << "�� ";
		for (x = 1; x <= gl; x++)
			cout << "�� ";
		cout << "�� ";
	}
	if (str)		// str�� nullptr�� �ƴϸ�
	{
		int length = (strlen(str) % 2 == 0) ? strlen(str) / 2 : strlen(str) / 2 + 1;		// ũ�� 15�� 16���� �ļ� 8����(�ѱ۱���)
		if (length> gl)		// �ڽ��� �� �� �ִ� ���̺��� ������ ���(�ѱ��� 2����Ʈ �����ϰ�, �ڽ� ���̴� �ѱ� �������� å���ϹǷ�)
		{
			cout << "������ �ʹ� ��ϴ�!";
			return;
		}
		switch (alignment)
		{
		case ALIGNMENT::LEFT:
			gotoxy(g + 1, s + 1);		// Ŀ���� �ڽ��� �� �� �ִ� ù ��ġ�� ���� �д�.
			break;
		case ALIGNMENT::RIGHT:
			gotoxy(g + gl - length + 1, s + 1);
			break;
		case ALIGNMENT::CENTER:
			gotoxy(g + (gl - length) / 2.0 + 1, s + 1);
			break;
		}
		cout << str;
	}
	return;
}
