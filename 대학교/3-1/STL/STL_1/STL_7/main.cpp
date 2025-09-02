//-------------------------------------------------
// 2025. STL 3.27                           4w 2d
//-------------------------------------------------
// 
//-------------------------------------------------
// callable types - ȣ�� ������ Ÿ��
// 1. �Լ�
// 2. �Լ� ������
// 3. ���� - �̸����� �Լ�
//-------------------------------------------------
// 2 ���� 1�ʷ� ������, 3���� 7�ʳ� �ɸ��鼭 ����
// ���ٴ� 1000���̸� 1000�� ȣ���� �����.
//


// [����] ���� int 1000������ �޸𸮿� �����϶�.
// qsort�� �̿��Ͽ� ������������ �����϶�.
// ���� ����� �տ��� ���� 1000���� ȭ�� ����϶�.

//#include <iostream>
//#include <random>
//#include <algorithm>
//#include <array>
//#include <print>
//#include <ranges> // views����ϱ�����
//
//std::default_random_engine dre;
//std::uniform_int_distribution<int> uid{ 1, 9999999 };
//
//const int NUM{ 10000000 };
//
//std::array<int, 10000000> a;
//
//int ��������(const void* a, const void* b) {
//	int* p = (int*)a;
//	int* q = (int*)b;
//	
//	if (*p > *q) {
//		return 1;
//	}
//	else if (*p < *q) {
//		return -1;
//	}
//
//	return 0;
//}
//
//int ��������(const void* a, const void* b) {
//	int* p = (int*)a;
//	int* q = (int*)b;
//
//	if (*p > *q) {
//		return -1;
//	}
//	else if (*p < *q) {
//		return 1;
//	}
//
//	return 0;
//}
//
//int main() {
//	// ������ �ڵ� --------------------------------------------------
//
//	for (int& num : a) {
//		num = uid(dre);
//	}
//
//	//auto ���ı��� = ��������; // ���� ������ Ÿ���� �Լ� �������̴�.
//	int(*���ı���)(const void*, const void*) = ��������;
//	���ı��� = ��������;
//
//	qsort((void*)a.data(), NUM, sizeof(std::array<int, NUM>::value_type), ���ı���);
//
//	for (int num : a | std::views::take(100)) {
//		std::print("{:8}", num);
//	}
//}
//
// ������ c�� �ڵ��̴� .�Ʒ��� c++�� �ٽ���

#include <random>
#include <algorithm>
#include <array>
#include <print>
#include <chrono>
#include <iostream>

std::default_random_engine dre;
std::uniform_int_distribution<int> uid{ 1, 9999999 };

const int NUM{ 10000000 };
std::array<int, 10000000> a;

// [����] ���� int 1000������ �޸𸮿� �����϶�.
// STL�� sort�� �̿��Ͽ� ������������ �����϶�.
// ���� ����� �տ��� ���� 1000���� ȭ�� ����϶�.

bool ��������(int a, int b) {
	return a < b;
}

//bool ��������(int a, int b) {
//	return a > b;
//}

int main() {


	//bool(*���ı���)(int, int) = ��������;

	{
		for (int& num : a)
			num = uid(dre);

		auto b = std::chrono::high_resolution_clock::now(); // �����ġ ����
		std::sort(a.begin(), a.end(), ��������); // �����̷�
		auto e = std::chrono::high_resolution_clock::now(); // �����ġ ��
		std::cout << "�ɸ� �ð� - " << e - b << std::endl;
		std::cout << "�ɸ� �ð�(��) - " << std::chrono::duration_cast<std::chrono::seconds>(e - b) << std::endl;
	}

	{
		for (int& num : a)
			num = uid(dre);

		auto b = std::chrono::high_resolution_clock::now(); // �����ġ ����
		std::sort(a.begin(), a.end(), [](int a, int b) {
			return a < b;
			});
		auto e = std::chrono::high_resolution_clock::now(); // �����ġ ��
		std::cout << "�ɸ� �ð� - " << e - b << std::endl;
		std::cout << "�ɸ� �ð�(��) - " << std::chrono::duration_cast<std::chrono::seconds>(e - b) << std::endl;
	}


	//std::ranges::sort(a, ���ı���); // �ֽ��̷�

	/*for (int num : a)
		std::print("{:8}", num);*/

	auto ���� = []() {
		std::cout << "����" << std::endl;
		};

	std::cout << "������ ��ü" << std::endl;
	std::cout << "������ ũ�� - " << sizeof(����) << std::endl;
	std::cout << "������ ��ġ - " << std::addressof(����) << std::endl;
	std::cout << "������ Ÿ�� - " << typeid(����).name() << std::endl;
	std::cout << std::endl;
	std::cout << "main�� ��ġ - " << std::addressof(main) << std::endl;


}