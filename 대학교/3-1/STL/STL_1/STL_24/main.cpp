//-------------------------------------------------------------------
// 2025. STL 6월 10일                                       (14주 1일)
//-------------------------------------------------------------------
// 
// sequence container -> array, deque, vector, list, forward list -> 찾기 실력이 중요함  o(n)
// Associatve -> set, map -> o(log n)
// 
//-------------------------------------------------------------------
// 컨테이너의 찾기 실력을 비교해보자. N (1000만개)
// 1. vector			o(n)
// 2. set				o(log n)
// 3. unordered_set		o(1)
// 
// 4. 정렬한 vector		o(log n) -> 정렬해둔 상태일땐 set이랑 같음
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

// 천만개의 랜덤 int를 준비한다.
// 만개의 찾을 랜덤 int를 따로 준비한다.
// 


std::default_random_engine dre;
std::uniform_int_distribution uid{ 1, 1000'0000 };

const int NUM{ 1000'0000 };
const int FNUM{ 1'0000 };	// F - to Find
std::array<int, NUM> a;		// 컨테이너의 데이터
std::array<int, FNUM> fa;	// 찾아볼 데이터

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
		std::cout << "vector에서 찾기" << std::endl;

		std::vector <int> v(a.begin(), a.end());

		std::cout << "vector의 원소 수  - " << v.size() << std::endl;

		size_t cnt{};

		std::cout << "찾는중...";

		auto 시작시간 = std::chrono::steady_clock::now();

		for (int num : fa) {
			auto p = std::find(v.begin(), v.end(), num);

			if (p != v.end())
				++cnt;
		}
		auto 걸린시간 = std::chrono::steady_clock::now() - 시작시간;

		std::cout << std::endl;
		std::cout << "걸린 시간 - " 
			<< std::chrono::duration_cast<std::chrono::milliseconds>(걸린시간) << std::endl;

		std::cout << "찾은 개수 - " << cnt << std::endl;

	}

	std::cout << std::endl;

	// 정렬한 vector
	{
		std::cout << "정렬한 vector에서 찾기" << std::endl;

		std::vector <int> v(a.begin(), a.end());
		std::sort(v.begin(), v.end());		// o(n * log n)

		std::cout << "정렬한 vector의 원소 수  - " << v.size() << std::endl;

		size_t cnt{};

		std::cout << "찾는중...";

		auto 시작시간 = std::chrono::steady_clock::now();

		for (int num : fa) {
			if (std::binary_search(v.begin(), v.end(), num))
				++cnt;
		}

		auto 걸린시간 = std::chrono::steady_clock::now() - 시작시간;

		std::cout << std::endl;
		std::cout << "걸린 시간 - "
			<< std::chrono::duration_cast<std::chrono::milliseconds>(걸린시간) << std::endl;

		std::cout << "찾은 개수 - " << cnt << std::endl;

	}

	std::cout << std::endl;

	// multiset
	{
		std::cout << "multiset에서 찾기" << std::endl;
		std::cout << "데이터를 multiset에 넣는 중...";
		std::multiset <int> ms(a.begin(), a.end());
		std::cout << std::endl;

		std::cout << "multiset의 원소 수  - " << ms.size() << std::endl;

		size_t cnt{};

		std::cout << "찾는중...";

		auto 시작시간 = std::chrono::steady_clock::now();

		for (int num : fa) {
			if (ms.contains(num)) // 데이터가 있는지 없는지만 알려줌
				++cnt;
		}
		auto 걸린시간 = std::chrono::steady_clock::now() - 시작시간;

		std::cout << std::endl;
		std::cout << "걸린 시간 - "
			<< std::chrono::duration_cast<std::chrono::milliseconds>(걸린시간) << std::endl;
		std::cout << "찾은 개수 - " << cnt << std::endl;
	}

	std::cout << std::endl;

	// unordered_multiset
	{
		std::cout << "unordered_multiset에서 찾기" << std::endl;
		std::cout << "데이터를 unordered_multiset에 넣는 중...";
		std::unordered_multiset <int> ums(a.begin(), a.end());
		std::cout << std::endl;

		std::cout << "unordered_multiset의 원소 수  - " << ums.size() << std::endl;

		size_t cnt{};

		std::cout << "찾는중...";

		auto 시작시간 = std::chrono::steady_clock::now();

		for (int num : fa) {
			if (ums.contains(num))
				++cnt;
		}
		auto 걸린시간 = std::chrono::steady_clock::now() - 시작시간;

		std::cout << std::endl;
		std::cout << "걸린 시간 - "
			<< std::chrono::duration_cast<std::chrono::milliseconds>(걸린시간) << std::endl;
		std::cout << "찾은 개수 - " << cnt << std::endl;
	}
}