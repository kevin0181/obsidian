//-------------------------------------------------
// 2025. STL 3.18                           3w 1d
//-------------------------------------------------
// ���� ���� �ڷ� ó���ϱ� - ���� �����
//						   - ���̳ʸ� ���� ������ �����
// 
//-------------------------------------------------
// [����] ���� �ð��� int�� 1000���� �����Ͽ���.
// ���Ͽ��� ����� ����Ʈ ���� Ȯ���غ���. - 8250 ����Ʈ�� ����ߴ�
//-------------------------------------------------
// �޸���
//
//

#include <fstream>
#include <iostream>
#include <string>
#include <array>
#include <algorithm>
#include <iterator>
#include <print>
#include <bitset> // 2������ ����ϱ� ���� ���
#include <numeric>
#include <random>

int main() {
	std::array<int, 1000>arr;
	std::cout << "a�� ����ϴ� �޸� ũ�� - " << sizeof(arr) << "����Ʈ" << std::endl; 
	// �̰� ������ 4000����Ʈ�� �����µ� �޸������� 1000�� int �����Ҷ� 8000����Ʈ�� ���Դµ� �� �׷���? ��ȿ�����ε�.


	int num{ 0x01020304 };
	std::cout << "num�� ����ϴ� �޸� ũ�� - " << sizeof(num) << "����Ʈ" << std::endl;
	
	
	/*std::cout << " 2���� - " << std::bitset<sizeof(int) * 8>(num) << std::endl;
	std::cout << "10���� - " << num << std::endl;
	std::cout << "16���� - 0x" << std::hex << num << std::endl;*/
	
	// � int ���� ���� �ʿ��� �޸𸮴� �����Ʈ�ΰ�? �������.

	// [����] int �� 1000���� ������ ����Լ��� ����Ͽ� �޸� ũ�� �״�� ���Ͽ� ����Ѵ�.
	// ���� "int õ���� �޸𸮱״�� ���"�� ����Ѵ�.
	// -> �޸𸮿� �ִ� bit�� �״�� ���Ͽ� ����Ѵ�.

	std::ofstream out{ "int õ���� �޸𸮱״�� ���", std::ios::binary }; //std::ios::binary�� ���༭ �������� ����������� (���̳ʸ� ���� �״�ξ�)
	if (not out)
		return 0;

	std::array<int, 1000>a;

	//windows���� 0x0A(line feed)�� ��� ��ȯ�ϴ°� -> 0x0D 0x0A�� ��ȯ�Ѵ�.
	a.fill(10); // -> ���� ���̳ʸ� �����ϸ�. �����쿡���� 10 ���� ��� �������� 0A�� �����. 10������ ����Ǵ°� �ƴ϶� 16������ �����.

	//std::iota(a.begin(), a.end(), 1); // 0���� 1000���� ���������� ä���ִ´�. // �̷��� �����ϸ� 4000byte�� ����
	// ������ �Լ��� ����Ѵ�.
	out.write((char*)a.data(), sizeof(int) * a.size());


	//------------------------------------------------------------------------------------

	std::ofstream out2{ "��¥ ����",std::ios::binary };
	std::random_device rd{};
	std::uniform_int_distribution<int>uid{ 0,100 };
	int num2;
	for (int i = 0; i < 100000; ++i) {
		num2 = rd();
		out2.write((char*)&num2, sizeof(int));
	}
	
	//------------------------------------------------------------------------------------
	// ����? [����] e-class���� �ٿ� ���� "��¥ ����" ���Ͽ��� int�� 10������ �ִ�.
	// ������ binary mode�� ������, write �Լ��� ����Ͽ� int ���� ����Ͽ���.
	// int �� 10���� ��ü�� �޸𸮷� �о�Ͷ�.
	// ���� ū ���� ���� ���� ã�� ȭ�鿡 ����϶�.
	// ��µ� ���� ������ �����. (10��)

	std::ifstream in2{ "��¥ ����", std::ios::binary };

	if (not in2) {
		std::cerr << "������ �� �� �����ϴ�." << std::endl;
		return 0;
	}

	std::array<int, 100000>arr2;
	in2.read((char*)arr2.data(), sizeof(int) * arr2.size());

	for (int i = 0; i < 10000; ++i) {
		in2 >> arr2[i];
	}

	int max_value = *std::max_element(arr2.begin(), arr2.end());
	int min_value = *std::min_element(arr2.begin(), arr2.end());

	std::cout << "���� ū �� : " << max_value << std::endl;
	std::cout << "���� ���� �� : " << min_value << std::endl;

	//����-------�����Բ�----------------------------------

	std::ifstream in3{ "��¥ ����", std::ios::binary };
	if (not in3)
		return 0;

	int num3;
	size_t cnt{};
	while (in3.read((char*)&num, sizeof(int))) {
		++cnt;
	}

	std::cout << "���� ������ ���� : " << cnt << std::endl;

	std::array<int, 100000>arr3;
	in3.read((char*)arr3.data(), sizeof(int) * arr3.size());

	//std::cout << "���� ū �� : " << *std::max_element(arr3.begin(), arr3.end()) << std::endl;		// o(N)
	//std::cout << "���� ���� �� : " << *std::min_element(arr3.begin(), arr3.end()) << std::endl;		// o(N)

	
	auto [min_,max_] = std::minmax_element(arr3.begin(), arr3.end());
	// structured-binding

	std::cout << "�ּڰ� - " << *min_ << std::endl;
	std::cout << "�ִ� - " << *max_ << std::endl;
	//�ȵǴ°Ű�����..?

}