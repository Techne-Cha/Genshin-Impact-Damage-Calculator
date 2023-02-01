// 테스트 파일

#include <iostream>
#include <fstream>


int main(void)
{
	using std::cout;
	using std::cin;
	using std::endl;
	char buffer[50];
	std::fstream file("테스트용.txt", std::ios::in | std::ios::out);
	file << "테스트 중입니댜.\n";
	file << "정말 테스트 중입니다\n";
	file.close();
	std::fstream wow("테스트용.txt", std::ios::in);
	while (wow >> buffer)
	{
		cout << buffer << endl;
	}
	cout << "여기서 파일이 끝났습니다.\n";
	wow.close();
	file.open("테스트용.txt", std::ios::in | std::ios::out);
	for (int i = 0; i < 5; i++)
	{
		file >> buffer;
		cout << buffer << endl;
	}
	
	file.close();

	wow.open("테스트용.txt", std::ios::in);
	while (wow >> buffer)
	{
		cout << buffer << endl;
	}
	cout << "여기서 파일이 끝났습니다.\n";
	wow.close();
	
	cin.get();
	return 0;
}