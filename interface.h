// tetris 프로젝트의 인터페이스 헤더를 가져와서 C++ 형식으로 바꿈

#ifndef INTERFACE_H_
#define INTERFACE_H_

#include <Windows.h>
#include <sstream>		// ostringstream 사용 위해, 여기 헤더 안에 <string> 헤더 있다
#include <iostream>
#include <conio.h>      // getch() 함수 사용
#include <cstring>

const int B_COLOR = 0;	//배경색  /검정(0), 어두운 파랑(16), 어두운 초록(32), 어두운 하늘(48), 어두운 빨강(64), 어두운 보라(80), 어두운 노랑(96), 회색(112), 어두운 회색(128), 파랑(144), 초록(160), 하늘(176), 빨강(192), 보라 (208), 노랑(224), 하양(240) 
const int N_COLOR = 15;	    // 기본글자색   /검정(0), 어두운 파랑(1), 어두운 초록(2), 어두운 하늘(3), 어두운 빨강(4), 어두운 보라(5), 어두운 노랑(6), 회색(7), 어두운 회색(8), 파랑(9), 초록(10), 하늘(11), 빨강(12), 보라(13), 노랑(14), 하양(15) 
const int H_COLOR = 10;		// 강조글자색

enum class KEY {
    UP = 72, DOWN = 80, RIGHT = 77, LEFT = 75, ENTER = 13, EXIT = 101, SPACE = 32
};      // 아스키코드 값

enum class ALIGNMENT {
    LEFT, RIGHT, CENTER
};      // 정렬

void gotoxy(double x, int y);			// 커서 이동 함수 (가로, 세로), 한글은 1*1, 알파벳은 1*0.5, 0.5도 받아들이기 위해 x는 double
void console(int g, int s);			// 콘솔 크기 변경 함수(가로, 세로) (창 속성에 나오는 크기는 알파벳 기준임. 여기서는 한글 기준으로 함, 커서 위치는 0,0으로 옮겨감
void color(int a, int b);			// 색 변경 함수 (배경색, 글자색) 
void CursorView(char show);			// 커서 숨기는 함수 0: 숨기기, 1: 나타내기 
void box(int g, int s, int gl, int sl, const char* str = nullptr, ALIGNMENT alignment = ALIGNMENT::LEFT, int visible = 1, int erase = 0);	// x좌표, y좌표, x길이, y길이 (길이는 문자를 쓸 수 있는 길이를 말함), 박스안에 쓸 문자열, 문자열 정렬, 박스 보이면 1, 안보이게 하면 0, 원래내용 지우면 1, 아니면 0

#endif