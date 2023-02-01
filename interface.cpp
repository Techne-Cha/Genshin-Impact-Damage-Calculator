// interface.h 함수들

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
	system(outstr.str().c_str());		// str() 메서드는 버퍼의 내용으로 초기화된 string 객체 리턴, c_str() 메서드는 string 문자열의 const char* 버전 리턴
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
void box(int g, int s, int gl, int sl, const char* str, ALIGNMENT alignment, int visible, int erase)	// x좌표, y좌표, x길이, y길이 (길이는 문자를 쓸 수 있는 길이를 말함), 박스안에 쓸 문자열, 문자열 정렬, 박스 보이면 1, 안보이게 하면 0
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
	if (visible)		// 박스가 보이게 설정할 때만
	{
		gotoxy(g, s);
		cout << "┌ ";		// 꺾쇠 기호는 크기는 1*1인데 출력하면 커서가 알파벳 출력한 거처럼 0.5에 멈춰있다. 그래서 빈칸 하나 더 출력해주는 것이 좋다
		for (x = 1; x <= gl; x++)
			cout << "─ ";
		cout << "┐ ";
		for (y = 1; y <= sl; y++)
		{
			gotoxy(g, s + y);
			cout << "│ ";
			gotoxy(g + gl + 1, s + y);
			cout << "│ ";
		}
		gotoxy(g, s + y);
		cout << "└ ";
		for (x = 1; x <= gl; x++)
			cout << "─ ";
		cout << "┘ ";
	}
	if (str)		// str이 nullptr이 아니면
	{
		int length = (strlen(str) % 2 == 0) ? strlen(str) / 2 : strlen(str) / 2 + 1;		// 크기 15면 16으로 쳐서 8글자(한글기준)
		if (length> gl)		// 박스에 쓸 수 있는 길이보다 문장이 길면(한글이 2바이트 차지하고, 박스 길이는 한글 기준으로 책정하므로)
		{
			cout << "문장이 너무 깁니다!";
			return;
		}
		switch (alignment)
		{
		case ALIGNMENT::LEFT:
			gotoxy(g + 1, s + 1);		// 커서는 박스에 쓸 수 있는 첫 위치에 갖다 둔다.
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
