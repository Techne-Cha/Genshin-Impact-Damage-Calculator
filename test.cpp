// �׽�Ʈ ����

#include <iostream>
#include <fstream>


int main(void)
{
	using std::cout;
	using std::cin;
	using std::endl;
	char buffer[50];
	std::fstream file("�׽�Ʈ��.txt", std::ios::in | std::ios::out);
	file << "�׽�Ʈ ���Դϴ�.\n";
	file << "���� �׽�Ʈ ���Դϴ�\n";
	file.close();
	std::fstream wow("�׽�Ʈ��.txt", std::ios::in);
	while (wow >> buffer)
	{
		cout << buffer << endl;
	}
	cout << "���⼭ ������ �������ϴ�.\n";
	wow.close();
	file.open("�׽�Ʈ��.txt", std::ios::in | std::ios::out);
	for (int i = 0; i < 5; i++)
	{
		file >> buffer;
		cout << buffer << endl;
	}
	
	file.close();

	wow.open("�׽�Ʈ��.txt", std::ios::in);
	while (wow >> buffer)
	{
		cout << buffer << endl;
	}
	cout << "���⼭ ������ �������ϴ�.\n";
	wow.close();
	
	cin.get();
	return 0;
}