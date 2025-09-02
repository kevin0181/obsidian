//-------------------------------------------------------------------
// 2025. STL 6�� 10��                                       (14�� 1��)
//-------------------------------------------------------------------
// 
// sequence container -> array, deque, vector, list, forward list -> ã�� �Ƿ��� �߿���  o(n)
// Associatve -> set, map -> o(log n)
// 
//-------------------------------------------------------------------
// �����̳��� ã�� �Ƿ��� ���غ���. N (1000����)
// 1. vector			o(n)
// 2. set				o(log n)
// 3. unordered_set		o(1)
// 
// 4. ������ vector		o(log n) -> �����ص� �����϶� set�̶� ����
//
//-------------------------------------------------------------------
#include <array>
#include <vector>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <chrono>
#include <random>
#include <iostream>
#include "STRING.h"

// õ������ ���� int�� �غ��Ѵ�.
// ������ ã�� ���� int�� ���� �غ��Ѵ�.
// 


std::default_random_engine dre;
std::uniform_int_distribution uid{ 1, 1000'0000 };

const int NUM{ 1000'0000 };
const int FNUM{ 1'0000 };	// F - to Find
std::array<int, NUM> a;		// �����̳��� ������
std::array<int, FNUM> fa;	// ã�ƺ� ������

//--------
int main2()
//--------
{

	for (int& num : a)
		num = uid(dre);

	for (int& num : fa)
		num = uid(dre);

	// vector
	{
		std::cout << "vector���� ã��" << std::endl;

		std::vector <int> v(a.begin(), a.end());

		std::cout << "vector�� ���� ��  - " << v.size() << std::endl;

		size_t cnt{};

		std::cout << "ã����...";

		auto ���۽ð� = std::chrono::steady_clock::now();

		for (int num : fa) {
			auto p = std::find(v.begin(), v.end(), num);

			if (p != v.end())
				++cnt;
		}
		auto �ɸ��ð� = std::chrono::steady_clock::now() - ���۽ð�;

		std::cout << std::endl;
		std::cout << "�ɸ� �ð� - " 
			<< std::chrono::duration_cast<std::chrono::milliseconds>(�ɸ��ð�) << std::endl;

		std::cout << "ã�� ���� - " << cnt << std::endl;

	}

	std::cout << std::endl;

	// ������ vector
	{
		std::cout << "������ vector���� ã��" << std::endl;

		std::vector <int> v(a.begin(), a.end());
		std::sort(v.begin(), v.end());		// o(n * log n)

		std::cout << "������ vector�� ���� ��  - " << v.size() << std::endl;

		size_t cnt{};

		std::cout << "ã����...";

		auto ���۽ð� = std::chrono::steady_clock::now();

		for (int num : fa) {
			if (std::binary_search(v.begin(), v.end(), num))
				++cnt;
		}

		auto �ɸ��ð� = std::chrono::steady_clock::now() - ���۽ð�;

		std::cout << std::endl;
		std::cout << "�ɸ� �ð� - "
			<< std::chrono::duration_cast<std::chrono::milliseconds>(�ɸ��ð�) << std::endl;

		std::cout << "ã�� ���� - " << cnt << std::endl;

	}

	std::cout << std::endl;

	// multiset
	{
		std::cout << "multiset���� ã��" << std::endl;
		std::cout << "�����͸� multiset�� �ִ� ��...";
		std::multiset <int> ms(a.begin(), a.end());
		std::cout << std::endl;

		std::cout << "multiset�� ���� ��  - " << ms.size() << std::endl;

		size_t cnt{};

		std::cout << "ã����...";

		auto ���۽ð� = std::chrono::steady_clock::now();

		for (int num : fa) {
			if (ms.contains(num)) // �����Ͱ� �ִ��� �������� �˷���
				++cnt;
		}
		auto �ɸ��ð� = std::chrono::steady_clock::now() - ���۽ð�;

		std::cout << std::endl;
		std::cout << "�ɸ� �ð� - "
			<< std::chrono::duration_cast<std::chrono::milliseconds>(�ɸ��ð�) << std::endl;
		std::cout << "ã�� ���� - " << cnt << std::endl;
	}

	std::cout << std::endl;

	// unordered_multiset
	{
		std::cout << "unordered_multiset���� ã��" << std::endl;
		std::cout << "�����͸� unordered_multiset�� �ִ� ��...";
		std::unordered_multiset <int> ums(a.begin(), a.end());
		std::cout << std::endl;

		std::cout << "unordered_multiset�� ���� ��  - " << ums.size() << std::endl;

		size_t cnt{};

		std::cout << "ã����...";

		auto ���۽ð� = std::chrono::steady_clock::now();

		for (int num : fa) {
			if (ums.contains(num))
				++cnt;
		}
		auto �ɸ��ð� = std::chrono::steady_clock::now() - ���۽ð�;

		std::cout << std::endl;
		std::cout << "�ɸ� �ð� - "
			<< std::chrono::duration_cast<std::chrono::milliseconds>(�ɸ��ð�) << std::endl;
		std::cout << "ã�� ���� - " << cnt << std::endl;
	}
}