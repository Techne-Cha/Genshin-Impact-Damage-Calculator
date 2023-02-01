// 중요 함수 작성

#include "function.h"

void revise_database()		// 데이터 베이스 추가/수정/검색
{
	using std::cout;
	using std::endl;
	using std::cin;
	using std::cerr;
	std::fstream finout;
	std::ofstream fout;		// 항목 삭제시 사용할 쓰기스트림
	Enemy enemy;
	int count = 0;		// 적 수
	int key;		// 키 입력값
	int selectFlag = 0;		// 메뉴 선택 플래그, 선택하면 1
	int endFlag = 1;		// 반복 종료 플래그, 종료하려면 0
	int menu = 21;		// 메뉴 설정값 <0~19 : 적 내성 정보 차례대로, 20 : 페이지 정보, 21 : 추가, 22 : 검색, 23 : 종료>
	int page = 1;		// 한 페이지에 20개 정보
	int maxPage = 1;		// 최대 페이지
	int remainder;		// 남은 나머지(52개 -> 12개가 나머지), 20도 나머지가 될 수 있다
	int pageChanged = 0;		// 방금 페이지 바뀌면 1
	const char* menus[] = { "추가", "검색", "종료" };
	int i;		// for 문 용

	// 인터페이스
	console(60, 30);
	box(0, 0, 58, 28);		// 전체 창
	box(0, 0, 47, 24);		// 파일 내용 출력창
	box(0, 0, 47, 1);		// 파일 내용 제목
	box(0, 0, 23, 1, "적 내성 정보", ALIGNMENT::CENTER, 0);
	for (i = 0; i < int(ELEMENT::NUMBER); i++)
		box(24 + i * 3, 0, 2, 1, ELEMENT_NAME[i], ALIGNMENT::LEFT, 0);
	box(0, 23, 47, 1);		// 페이지 정보창
	box(0, 25, 58, 3);		// 입출력창

	finout.open("적내성.dat", std::ios_base::in | std::ios_base::out | std::ios_base::binary);		// 읽기쓰기 겸용
	if (!finout.is_open())
	{
		gotoxy(1, 26);
		cerr << "파일을 열 수 없습니다.\n";
		exit(EXIT_FAILURE);
	}
	while (finout.read((char*)&enemy, sizeof enemy))		// 처음 읽을때는 끝까지 읽어서 적 수를 파악함
		count++;
	if (0 == count % 20)		// 20으로 나누어떨어지면(ex.. 40)
	{
		maxPage = count / 20;
		remainder = 20;
	}
	else
	{
		maxPage = count / 20 + 1;
		remainder = count % 20;
	}
	finout.clear();
	finout.seekg(0);		// 입력포인터 처음으로

	while (endFlag)
	{
		while (!selectFlag)
		{
			// 왼쪽메뉴 출력
			finout.seekg((page - 1) * 20 * sizeof enemy);		// 페이지의 시작점에 입력포인터 위치
			if (pageChanged)		// 페이지 바뀌었으면
			{
				box(0, 2, 47, 20, nullptr, ALIGNMENT::LEFT, 0, 1);		// 페이지 모두 지우기
				pageChanged = 0;
			}
			if (page == maxPage)		// 마지막 페이지이면
				for (i = 0; i < remainder; i++)
				{
					if (menu == i)
						color(B_COLOR, H_COLOR);
					gotoxy(1, i + 3);
					cout << "#" << i + 1 + 20 * (page - 1);
					finout.read((char*)&enemy, sizeof enemy);
					enemy.show_info1({ 4, short(i + 3) });
					if (menu == i)
						color(B_COLOR, N_COLOR);
				}
			else		// 마지막 페이지 아니면
			{
				for (i = 0; i < 20; i++)
				{
					if (menu == i)
						color(B_COLOR, H_COLOR);
					gotoxy(1, i + 3);
					cout << "#" << i + 1 + 20 * (page - 1);
					finout.read((char*)&enemy, sizeof enemy);
					enemy.show_info1({ 4, short(i + 3) });
					if (menu == i)
						color(B_COLOR, N_COLOR);
				}
			}
			// 페이지 정보 출력
			if (menu == 20)
				color(B_COLOR, H_COLOR);
			gotoxy(21, 24);
			cout << "◀";
			gotoxy(23, 24);
			cout << "  ";		// 지우기
			gotoxy(23, 24);
			cout << page;
			gotoxy(24, 24);
			cout << "/";
			gotoxy(25, 24);
			cout << maxPage;
			gotoxy(27, 24);
			cout << "▶";
			if (menu == 20)
				color(B_COLOR, N_COLOR);
			// 오른쪽 메뉴 출력
			for (i = 0; i < 3; i++)
			{
				if (menu == i + 21)		// 21,22,23 즉 오른쪽 메뉴가 menu일때
				{
					color(B_COLOR, H_COLOR);
					box(52, 8 + i * 4, 2, 1, menus[i]);
					color(B_COLOR, N_COLOR);
				}
				else
					box(52, 8 + i * 4, 2, 1, menus[i]);
			}

			key = _getch();
			switch (key)
			{
			case (int)KEY::UP:
				if (21 <= menu && menu <= 23)		// 오른쪽 메뉴
				{
					if (menu != 21)		// '추가'에서만 안올라가면 됨
						menu--;
				}
				else		//  왼쪽 메뉴
				{
					if (page != maxPage)		// 왼쪽 메뉴에서는 마지막 페이지 아니면
					{
						if (menu != 0)		// 맨 위에서만 안올라가면 된다
							menu--;
					}
					else		// 마지막 페이지면
					{
						if (menu == 20)			// 페이지 정보이면
							menu = remainder - 1;		// 해당 페이지의 마지막 메뉴로 올라간다
						else if (menu != 0)		// 아니면 맨 위에서만 안올라가면 된다
							menu--;
					}
				}
				break;
			case (int)KEY::DOWN:
				if (21 <= menu && menu <= 23)		// 오른쪽 메뉴
				{
					if (menu != 23)		// '종료'에서만 안내려가면 됨
						menu++;
				}
				else		//  왼쪽 메뉴
				{
					if (page != maxPage)		// 왼쪽 메뉴에서는 마지막 페이지 아니면
					{
						if (menu != 20)		// 페이지 정보에서만 안내려가면 된다
							menu++;
					}
					else		// 마지막 페이지면
					{
						if (menu <= remainder - 2)		// 해당 페이지의 마지막 메뉴가 아니면
							menu++;
						else if (menu == remainder - 1)		// 해당 페이지의 마지막 메뉴이면
							menu = 20;		// 페이지 정보로 내려간다
					}
				}
				break;
			case (int)KEY::LEFT:
				if (21 <= menu)		// 오른쪽 메뉴일때
					menu = 0;		// 왼쪽 메뉴 제일 위로
				else if (20 == menu)		// 페이지 정보일때
					if (2 <= page)		// 2페이지 이상이면
					{
						page--;
						pageChanged = 1;
					}
				break;
			case (int)KEY::RIGHT:
				if (menu <= 19)		// 왼쪽 메뉴일때
					menu = 21;		// 오른쪽 메뉴 제일 위로
				else if (20 == menu)		// 페이지 정보일때
					if (page < maxPage)		// 최대페이지보다 작으면
					{
						page++;
						pageChanged = 1;
					}
				break;
			case (int)KEY::ENTER:
				selectFlag = 1;
				break;
			default:
				break;
			}
		}

		// 메뉴가 결정되었다
		selectFlag = 0;
		if (!(0 <= menu && menu <= 23))
		{
			gotoxy(1, 26);
			cerr << "오류입니다. 종료합니다.";
			exit(EXIT_FAILURE);
		}
		// 수정/삭제
		if (0 <= menu && menu <= 19)
		{
			CursorView(1);
			box(0, 25, 58, 3, nullptr, ALIGNMENT::LEFT, 0, 1);		// 입출력창 지우기
			gotoxy(1, 26);
			cout << "해당 정보를 수정합니다. 해당 정보를 완전히 삭제하려면 '삭제'를 입력해주세요.";
			gotoxy(1, 27);
			cout << "적이름: ";
			cin.getline(enemy.name, ENEMY_NAME_LENGTH);
			
			if (!strcmp("삭제", enemy.name))		// 두 문자열이 같으면
			{
				gotoxy(1, 28);
				cout << "정말 삭제하시겠습니까?(y/n) : ";
				if ('y' == cin.get())
				{
					fout.open("temp.dat", std::ios_base::binary);
					finout.seekg(0);
					for (i = 0; i < count; i++)
					{
						finout.read((char*)&enemy, sizeof enemy);
						if (i == ((page - 1) * 20 + menu))		// 삭제하려는 번호는 새 파일에 쓰지 않는다
							continue;
						fout.write((char*)&enemy, sizeof enemy);
					}
					fout.close();
					finout.close();
					remove("적내성.dat");
					rename("temp.dat", "적내성.dat");
					box(0, 25, 58, 3, nullptr, ALIGNMENT::LEFT, 0, 1);		// 입출력창 지우기
					gotoxy(1, 26);
					cout << "삭제 완료했습니다.";
					// 스트림을 다시 설정하고 count도 바꾸어주어야 한다
					finout.open("적내성.dat", std::ios_base::in | std::ios_base::out | std::ios_base::binary);		// 읽기쓰기 겸용
					count--;
					if (0 == count % 20)		// 20으로 나누어떨어지면(ex.. 40)
					{
						maxPage = count / 20;
						remainder = 20;
					}
					else
					{
						maxPage = count / 20 + 1;
						remainder = count % 20;
					}
					page = 1;
					pageChanged = 1;
				}
				else
				{
					box(0, 25, 58, 3, nullptr, ALIGNMENT::LEFT, 0, 1);		// 입출력창 지우기
					gotoxy(1, 26);
					cout << "삭제하지 않았습니다.";
				}
			}
			else		// 수정
			{
				gotoxy(1, 28);
				for (int i = 0; i < (int)ELEMENT::NUMBER; i++)
					cout << ELEMENT_NAME[i] << " ";
				cout << "내성(무한대는 # 입력): ";
				for (int i = 0; i < (int)ELEMENT::NUMBER; i++)
				{
					if (!(cin >> enemy.resistance[i]))		// 문자 입력되면
					{
						cin.clear();
						if ('#' == cin.get())		// 무한대 입력을 위해 #을 입력했으면
							enemy.resistance[i] = INT_MAX;
						else
							enemy.resistance[i] = 0;
					}
				}
				eatline();
				box(0, 25, 58, 3, nullptr, ALIGNMENT::LEFT, 0, 1);		// 입출력창 지우기
				gotoxy(1, 26);
				cout << "다음과 같이 입력하셨습니다";
				enemy.show_info1({ 4, 27 });
				gotoxy(1, 28);
				cout << "수정하려면 y를 눌러주세요: ";
				if ('y' == cin.get())
				{
					finout.seekp(((page - 1) * 20 + menu) * sizeof enemy);		// 해당 적 내용이 있는 곳에 출력포인터 위치
					finout.write((char*)&enemy, sizeof enemy);
					box(0, 25, 58, 3, nullptr, ALIGNMENT::LEFT, 0, 1);		// 입출력창 지우기
					gotoxy(1, 26);
					cout << "수정되었습니다.";
					pageChanged = 1;		// 위에 덧씌우는거 방지
				}
				else
				{
					box(0, 25, 58, 3, nullptr, ALIGNMENT::LEFT, 0, 1);		// 입출력창 지우기
					gotoxy(1, 26);
					cout << "수정하지 않았습니다.";
				}
			}
			eatline();
			CursorView(0);
		}
		// 추가
		if (21 == menu)
		{
			box(0, 25, 58, 3, nullptr, ALIGNMENT::LEFT, 0, 1);		// 입출력창 지우기
			gotoxy(1, 26);
			cout << "데이터베이스에 추가합니다. 종료하려면 q를 입력해주세요";
			gotoxy(1, 27);
			CursorView(1);
			cout << "적이름: ";
			while (cin.getline(enemy.name, ENEMY_NAME_LENGTH))
			{
				if (!strcmp("q", enemy.name))		// 두 문자열이 같으면
					break;
				gotoxy(1, 28);
				for (int i = 0; i < (int)ELEMENT::NUMBER; i++)
					cout << ELEMENT_NAME[i] << " ";
				cout << "내성(무한대는 # 입력): ";
				for (int i = 0; i < (int)ELEMENT::NUMBER; i++)
				{
					if (!(cin >> enemy.resistance[i]))		// 문자 입력되면
					{
						cin.clear();
						if ('#' == cin.get())		// 무한대 입력을 위해 #을 입력했으면
							enemy.resistance[i] = INT_MAX;
						else
							enemy.resistance[i] = 0;
					}
				}
				eatline();
				box(0, 25, 58, 3, nullptr, ALIGNMENT::LEFT, 0, 1);		// 입출력창 지우기
				gotoxy(1, 26);
				cout << "다음과 같이 입력하셨습니다";
				enemy.show_info1({ 4, 27 });
				gotoxy(1, 28);
				cout << "저장하려면 y를 눌러주세요: ";
				if ('y' == cin.get())
				{
					finout.seekp(0, std::ios::end);		// 출력포인터 마지막에 위치
					finout.write((char*)&enemy, sizeof enemy);
					box(0, 25, 58, 3, nullptr, ALIGNMENT::LEFT, 0, 1);		// 입출력창 지우기
					gotoxy(1, 26);
					cout << "저장되었습니다. 종료하려면 q를 입력해주세요";
					count++;
				}
				else
				{
					box(0, 25, 58, 3, nullptr, ALIGNMENT::LEFT, 0, 1);		// 입출력창 지우기
					gotoxy(1, 26);
					cout << "저장하지 않았습니다. 종료하려면 q를 입력해주세요";
				}
				eatline();
				gotoxy(1, 27);
				cout << "적이름: ";
			}
			// count가 바뀌었으므로 다시 maxPage와 remainder를 설정한다
			if (0 == count % 20)		// 20으로 나누어떨어지면(ex.. 40)
			{
				maxPage = count / 20;
				remainder = 20;
			}
			else
			{
				maxPage = count / 20 + 1;
				remainder = count % 20;
			}
			CursorView(0);
		}
		// 검색
		if (22 == menu)
		{
			char enemyName[ENEMY_NAME_LENGTH];		// 검색할 적 이름
			CursorView(1);
			box(0, 25, 58, 3, nullptr, ALIGNMENT::LEFT, 0, 1);		// 입출력창 지우기
			gotoxy(1, 26);
			cout << "검색할 적 이름을 입력해주세요: ";
			while (cin.getline(enemyName, ENEMY_NAME_LENGTH))
			{
				if (!strcmp("그만", enemyName))
					break;
				finout.seekg(0);		// 파일 포인터를 파일 시작위치에 위치시킴
				box(0, 2, 47, 20, nullptr, ALIGNMENT::LEFT, 0, 1);		// 페이지 모두 지우기
				int j = 0;		// 최대 20개까지만 출력하려고
				for (i = 0; i < count; i++)		// 적 수만큼 반복한다
				{
					finout.read((char*)&enemy, sizeof enemy);
					if (strstr(enemy.name, enemyName))		// 찾으려는 이름이 포함되면
					{
						gotoxy(1, j + 3);
						cout << "#" << i + 1;
						enemy.show_info1({ 4, short(j + 3) });
						if (++j >= 20)
							break;		// for문 종료
					}
				}
				box(0, 25, 58, 3, nullptr, ALIGNMENT::LEFT, 0, 1);		// 입출력창 지우기
				gotoxy(1, 26);
				if (!j)		// 검색결과 없으면
					cout << "검색하신 적 이름을 포함하는 적이 없습니다.";
				else
					cout << "검색하신 적 이름을 포함하는 적들은 위와 같습니다.";		// 최대 20개 출력
				gotoxy(1, 27);
				cout << "검색할 적 이름을 입력해주세요, 그만하려면 '그만' 입력하세요: ";
			}
			if (!cin)		// 너무 많은 글자를 입력하면
			{
				cin.clear();
				eatline();
			}
			pageChanged = 1;		// 페이지 썼으므로 다시 파일 내용 출력하게 하기 위해 설정
			CursorView(0);
		}
		// 종료
		if (23 == menu)
			endFlag = 0;
	}
	finout.close();
	return;
}
void damage_calculation()		// 데미지 계산
{
	using std::cout;
	using std::endl;
	using std::cin;
	using std::cerr;

	Keqing 각청;
	Klee 클레;
	Xingqiu 행추;
	Noelle 노엘;
	Character* p_characters[CHARACTERS] = { &각청, &클레, &행추, &노엘 };
	Character* p_main = nullptr;		// 선택된 캐릭터 객체를 가리키는 포인터
	Enemy enemy;
	Buff buff;
	std::ofstream fout;
	std::ifstream fin;
	int selectFlag = 0;		// 선택되면 1
	int endFlag = 1;		// 끝내고 싶으면 0
	int menu = 0;		// 메뉴 설정값
	int buffmenu;		// 버프 설정시 사용할 메뉴
	int backstep = 0;		// '이전'이 눌리면 1
	int key;		// 입력 키
	const char* menu2[] = {
		"재설정", "계산", "이전"
	};
	const char* menu3[] = {
		"버프", "디버프", "적교체", "이전"
	};
	char enemyName[ENEMY_NAME_LENGTH];		// 적 이름(검색에 쓰임)
	int count;		// 출력 제어에 쓰임
	int sknum;		// 스킬번호
	console(60, 30);
	while (1)
	{
		// 캐릭터 선택
		box(0, 0, 58, 26, nullptr, ALIGNMENT::LEFT, 1, 1);
		box(0, 0, 13, 26);		// 스탯창
		box(14, 16, 13, 1);		// 적 부가정보 창
		box(14, 18, 44, 1);		// 적 정보 창
		box(14, 20, 44, 6);		// 출력창
		box(0, 27, 58, 1);		// 입력창
		box(0, 0, 13, 1, "현재 계산 가능한 캐릭터", ALIGNMENT::CENTER, 1, 1);
		selectFlag = 0;
		while (!selectFlag)
		{
			for (int i = 0; i < CHARACTERS; i++)
			{
				if (menu == i)
				{
					color(B_COLOR, H_COLOR);
					box(0, 3 + 3 * i, 13, 1, p_characters[i]->return_name().c_str(), ALIGNMENT::RIGHT, 0);
					color(B_COLOR, N_COLOR);
				}
				else
					box(0, 3 + 3 * i, 13, 1, p_characters[i]->return_name().c_str(), ALIGNMENT::RIGHT, 0);
			}
			key = _getch();
			switch (key)
			{
			case (int)KEY::UP:
				if (menu > 0)
					menu--;
				break;
			case (int)KEY::DOWN:
				if (menu < CHARACTERS - 1)
					menu++;
				break;
			case (int)KEY::ENTER:
				selectFlag = 1;
				break;
			default:
				break;
			}
		}
		p_main = p_characters[menu];		// 캐릭터 선택 완료

		// 캐릭 정보 파일에서 읽어 디스플레이
		box(0, 0, 13, 1, p_main->return_name().c_str(), ALIGNMENT::CENTER, 0, 1);
		box(0, 2, 13, 24, nullptr, ALIGNMENT::LEFT, 0, 1);		// 스탯창 지우기
		std::string filename = p_main->return_name() + ".txt";		// 파일 이름 만들기
		fin.open(filename);
		if (!fin.is_open())
		{
			gotoxy(1, 3);
			cerr << filename << " 파일을 열 수 없습니다.";
			gotoxy(1, 4);
			cerr << "새로운 파일을 만듭니다.";
			set_charinfo(*p_main, { 1, 28 }, 58);
			fin.open(filename);		// 다시 열기 시도
			if (!fin.is_open())
			{
				gotoxy(1, 5);
				cerr << filename << " 파일을 열 수 없습니다";
				gotoxy(1, 6);
				cerr << "종료합니다.";
				exit(EXIT_FAILURE);
			}
		}
		// 파일이 제대로 열어져야 여기까지 올 수 있다
		box(0, 2, 13, 24, nullptr, ALIGNMENT::LEFT, 0, 1);		// 스탯창 지우기
		if (!(fin >> *p_main))		// 입력 불량이면
		{
			gotoxy(1, 3);
			cerr << "파일 내용에 문제가 있습니다.\n종료합니다.\n";
			fin.close();
			exit(EXIT_FAILURE);
		}
		fin.close();

		// 정보 출력
		p_main->show_stat({ 1, 3 });		// 스탯 출력
		p_main->show_skills({ 17, 1 });		// 스킬 출력
		
		
		backstep = 0;
		// 분기점(재설정, 계산, 이전이동)
		while (!backstep)
		{
			menu = 0;		// 나중에도 같은 용도로 쓰일 것
			selectFlag = 0;
			while (!selectFlag)
			{
				for (int i = 0; i < 3; i++)
				{
					if (menu == i)
					{
						color(B_COLOR, H_COLOR);
						box(1 + 4 * i, 24, 3, 1, menu2[i], ALIGNMENT::CENTER, 0);
						color(B_COLOR, N_COLOR);
					}
					else
						box(1 + 4 * i, 24, 3, 1, menu2[i], ALIGNMENT::CENTER, 0);
				}
				key = _getch();
				switch (key)
				{
				case (int)KEY::LEFT:
					if (menu > 0)
						menu--;
					break;
				case (int)KEY::RIGHT:
					if (menu < 2)
						menu++;
					break;
				case (int)KEY::ENTER:
					selectFlag = 1;		// 선택됨
					break;
				default:
					break;
				}
			}
			switch (menu)
			{
			case 0:		// 정보 재설정
				set_charinfo(*p_main, { 1, 28 }, 58);
				continue;		// 분기점으로 다시 간다
			case 1:		// 계산 진행
				break;
			case 2:
				backstep = 1;		// 캐릭터 선택창으로 다시 넘어감
				continue;
			default:
				break;
			}

			// 적 검색 후 특정
			enemy = ememy_identification();
			enemy.show_info1({ 15, 19 });
			enemy.change_info({ 1, 28 }, 58);
			enemy.show_info1({ 15, 19 });
			enemy.show_info2({ 15, 17 });
			
			// 버프 초기화
			buff.reset_buff();
			
			// 스킬 선택
			box(14, 20, 44, 6, nullptr, ALIGNMENT::LEFT, 0, 1);		// 출력창 지우기
			gotoxy(15, 21);
			cout << "스킬을 선택하세요";
			menu = 0;		// 나중에도 같은 용도로 쓰일 것
			selectFlag = 0;
			while (!selectFlag)
			{
				p_main->show_skills({ 17,1 }, & menu);
				key = _getch();
				switch (key)
				{
				case (int)KEY::UP:
					if (0 < menu)		// 1 이상이면 (맨 첫 스킬에서는 올라가면 안됨)
						menu--;
					break;
				case (int)KEY::DOWN:
					menu++;		// 마음껏 올려도 show_skills에서 보정해줌
					break;
				case (int)KEY::ENTER:
					selectFlag = 1;		// 선택됨
					break;
				default:
					break;
				}
			}
			box(14, 20, 44, 6, nullptr, ALIGNMENT::LEFT, 0, 1);		// 출력창 지우기
			gotoxy(15, 21);
			sknum = menu;		// 스킬 선택 완료
			cout << "선택된 스킬은 " << menu << "번입니다.";
			p_main->reflect_passive(sknum, enemy, buff, { 1, 28 }, 58);		// 캐릭터 패시브 적용
			box(0, 2, 13, 24, nullptr, ALIGNMENT::LEFT, 0, 1);		// 스탯창 지우기
			p_main->show_stat({ 1, 3 }, buff);		// 스탯 출력
			enemy.show_info1({ 15, 19 });
			enemy.show_info2({ 15, 17 });
			p_main->show_all_damage(sknum, enemy, buff, { 15, 21 });		// 데미지 계산
			// 한 번 계산 후는 여러 메뉴가 나옴
			menu = 0;		// 여기 메뉴는 스킬들은 show_skills 함수가 관리하고, 버프, 디버프, 적교체, 이전 메뉴는 -1, -2, -3, -4 번 으로 설정
			endFlag = 1;
			while (endFlag)
			{
				selectFlag = 0;
				while (!selectFlag)
				{
					// 버프, 디버프, 적교체, 이전 메뉴 표시
					for (int i = 1; i <= 4; i++)
					{
						if (menu == -i)
							color(B_COLOR, H_COLOR);
						box(54, i * 4 - 3, 3, 1, menu3[i - 1], ALIGNMENT::CENTER, 1);
						if (menu == -i)
							color(B_COLOR, N_COLOR);
					}
					// 스킬 메뉴 표시
					p_main->show_skills({ 17,1 }, &menu);

					key = _getch();
					switch (key)
					{
					case (int)KEY::UP:
						if (0 < menu)		// 1 이상이면 (맨 첫 스킬에서는 올라가면 안됨)
							menu--;
						else if (menu <= -2)		// -2 이하이면(-1에서는 올라가면 안됨)
							menu++;
						break;
					case (int)KEY::DOWN:
						if (0 <= menu)		// 스킬메뉴라면
							menu++;		// 마음껏 올려도 show_skills에서 보정해줌
						else if (-3 <= menu)		// 스킬 메뉴 아니고 -3 이상이면 (- 4에서만 안내려가면 됨)
							menu--;
						break;
					case (int)KEY::LEFT:
						if (menu < 0)		// 스킬 메뉴 아니면
							menu = 0;		// 맨 첫 스킬로
						break;
					case (int)KEY::RIGHT:
						if (0 <= menu)		// 스킬 메뉴라면
							menu = -1;		// 버프로 이동
						break;
					case (int)KEY::ENTER:
						selectFlag = 1;		// 선택됨
						break;
					default:
						break;
					}
				}
				switch (menu)
				{
				case -1:		// 버프
					buff_setting(buff);
					// 버프 후 스탯 다시 출력
					box(0, 2, 13, 24, nullptr, ALIGNMENT::LEFT, 0, 1);		// 스탯창 지우기
					p_main->show_stat({ 1, 3 }, buff);		// 스탯 출력
					break;
				case -2:		// 디버프 (레벨(좀 이상하지만..), 내성깎, 방깎)
					enemy.change_info({ 1, 28 }, 58);
					box(14, 18, 44, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// 이름, 내성 정보 창 지우기
					enemy.show_info1({ 15, 19 });
					box(14, 16, 13, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// 레벨, 방어력 비율 창 지우기
					enemy.show_info2({ 15, 17 });
					break;
				case -3:		// 적교체
					enemy = ememy_identification();
					box(14, 18, 44, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// 이름, 내성 정보 창 지우기
					box(14, 16, 13, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// 레벨, 방어력 비율 창 지우기
					enemy.show_info1({ 15, 19 });
					enemy.change_info({ 1, 28 }, 58);
					box(14, 18, 44, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// 이름, 내성 정보 창 지우기
					enemy.show_info1({ 15, 19 });
					enemy.show_info2({ 15, 17 });
					break;
				case -4:		// 이전
					endFlag = 0;		// 이전(재설정, 계산, 이전 메뉴 있는 곳)으로 돌아감
					continue;
				default:		// 스킬메뉴
					box(14, 20, 44, 6, nullptr, ALIGNMENT::LEFT, 0, 1);		// 출력창 지우기
					gotoxy(15, 21);
					sknum = menu;		// 스킬 선택 완료
					cout << "선택된 스킬은 " << menu << "번입니다.";
					break;
				}
				// 메뉴의 행동을 한 후에는 다시 계산하여 계산결과 출력('이전' 제외)
				p_main->reflect_passive(sknum, enemy, buff, { 1, 28 }, 58);		// 캐릭터 패시브 적용
				box(0, 2, 13, 24, nullptr, ALIGNMENT::LEFT, 0, 1);		// 스탯창 지우기
				p_main->show_stat({ 1, 3 }, buff);		// 스탯 출력
				box(14, 18, 44, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// 이름, 내성 정보 창 지우기
				box(14, 16, 13, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// 레벨, 방어력 비율 창 지우기
				enemy.show_info1({ 15, 19 });
				enemy.show_info2({ 15, 17 });
				box(14, 20, 44, 6, nullptr, ALIGNMENT::LEFT, 0, 1);		// 출력창 지우기
				p_main->show_all_damage(sknum, enemy, buff, { 15, 21 });		// 데미지 계산
			}
		}
	}
	return;
}

void set_charinfo(Character& c, COORD in, int range)
{
	CursorView(1);
	c.set_info(in, range);
	std::ofstream fout(c.return_name() + ".txt");
	if (!fout.is_open())
	{
		gotoxy(in.X, in.Y);
		std::cerr << c.return_name() + ".txt" << " 파일을  쓰기모드로 열 수 없습니다. 종료합니다.";
		exit(EXIT_FAILURE);
	}
	fout << c;
	fout.close();
	CursorView(0);
	return;
}

Enemy ememy_identification()		// 적 검색 후 특정
{
	using std::cout;
	using std::endl;
	using std::cin;
	using std::cerr;
	std::ifstream fin;
	int selectFlag = 0;		// 선택되면 1
	Enemy enemy;
	char enemyName[ENEMY_NAME_LENGTH];		// 적 이름(검색에 쓰임)
	int count;		// 출력 제어에 쓰임
	box(14, 20, 44, 6, nullptr, ALIGNMENT::LEFT, 0, 1);		// 출력창 지우기
	box(14, 18, 44, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// 적 정보 창 지우기
	CursorView(1);
	fin.open("적내성.dat", std::ios_base::in | std::ios_base::binary);
	if (!fin.is_open())
	{
		gotoxy(15, 21);		// 출력창으로 감
		cerr << "적내성.dat 파일을 열 수 없습니다. 종료합니다.";
		exit(EXIT_FAILURE);
	}
	gotoxy(15, 21);		// 출력창으로 감
	cout << "검색할 적 이름을 입력해주세요(그만하려면 '그만' 입력해주세요)";
	selectFlag = 0;		// 찾으면 1
	count = 0;		// 몇 명 출력했는지
	gotoxy(1, 28);		// 입력창으로 감
	while (cin.getline(enemyName, ENEMY_NAME_LENGTH))
	{
		if (!strcmp("그만", enemyName))
			break;
		while (fin.read((char*)&enemy, sizeof enemy))
		{
			if (!strcmp(enemy.name, enemyName))		// 찾으려는 이름이 나오면
			{
				selectFlag = 1;
				break;
			}
		}
		if (selectFlag)
			break;
		box(14, 20, 44, 6, nullptr, ALIGNMENT::LEFT, 0, 1);		// 출력창 지우기
		gotoxy(15, 21);
		cout << "검색하신 적 이름을 찾지 못하였습니다.";
		gotoxy(15, 22);
		cout << "검색하신 적 이름을 포함하는 적들은 다음과 같습니다.";
		fin.clear();
		fin.seekg(0);		// 파일 포인터를 파일 시작위치에 위치시킴
		count = 0;
		while (fin.read((char*)&enemy, sizeof enemy))
		{
			if (strstr(enemy.name, enemyName))		// 찾으려는 이름이 포함되면
			{
				enemy.show_info1({ 15, short(23 + count) });
				count++;
			}
			if (count >= 4)		// 4개 까지 출력가능
				break;
		}
		fin.clear();
		fin.seekg(0);		// 파일 포인터를 파일 시작위치에 위치시킴
		box(0, 27, 58, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// 입력창 지우기
		gotoxy(1, 28);
	}
	fin.close();
	box(14, 20, 44, 6, nullptr, ALIGNMENT::LEFT, 0, 1);		// 출력창 지우기
	gotoxy(15, 21);
	CursorView(0);
	if (!selectFlag)		// '그만' 입력
	{
		cout << "종료합니다.";
		exit(EXIT_FAILURE);
	}
	cout << "선택되었습니다.";
	return enemy;
}

void buff_setting(Buff& buff)		// 버프 재설정
{
	using std::cout;
	using std::cin;
	int menu = 0;
	int selectFlag = 0;
	int endFlag = 1;		// 0 되면 종료
	int key;
	double plus;		// 더해지는 값
	while (endFlag)
	{
		box(0, 2, 13, 24, nullptr, ALIGNMENT::LEFT, 0, 1);		// 스탯창 지우기
		selectFlag = 0;
		while (!selectFlag)
		{
			buff.show_buff({ 1,3 }, menu);
			key = _getch();
			switch (key)
			{
			case (int)KEY::UP:
				if (0 < menu)		// 1 이상이면 (맨 첫 메뉴에서는 올라가면 안됨)
					menu--;
				break;
			case (int)KEY::DOWN:
				if (menu < 19)		// 18 이하이면 (19, 즉 마지막 메뉴에서는 내려가면 안됨)
					menu++;
				break;
			case (int)KEY::ENTER:
				selectFlag = 1;		// 선택됨
				break;
			default:
				break;
			}
		}
		if (menu == 18)		// 버프 리셋
		{
			buff.reset_buff();
			continue;		// 다시 선택
		}
		if (menu == 19)		// 설정 완료
		{
			endFlag = 0;
			continue;		// 종료
		}
		CursorView(1);
		box(0, 27, 58, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// 입력창 지우기
		gotoxy(1, 28);
		cout << "더할 값: ";
		cin >> plus;
		switch (menu)
		{
		case 0:
			buff.hp += plus;
			break;
		case 1:
			buff.hpPer += plus;
			break;
		case 2:
			buff.atk += plus;
			break;
		case 3:
			buff.atkPer += plus;
			break;
		case 4:
			buff.def += plus;
			break;
		case 5:
			buff.defPer += plus;
			break;
		case 6:
			buff.elementalMastery += plus;
			break;
		case 7:
			buff.energyRecharge += plus;
			break;
		case 8:
			buff.critRate += plus;
			break;
		case 9:
			buff.critDamage += plus;
			break;
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
		case 17:
			buff.damageBonus[menu - 10] += plus;
			break;
		default:
			break;
		}
		box(0, 27, 58, 1, nullptr, ALIGNMENT::LEFT, 0, 1);		// 입력창 지우기
		CursorView(0);
	}
	return;
}