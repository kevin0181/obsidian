//-------------------------------------------------
// 2025. STL 3.27                           4w 2d
//-------------------------------------------------
// 
//-------------------------------------------------
// callable types - 호출 가능한 타입
// 1. 함수
// 2. 함수 포인터
// 3. 람다 - 이름없는 함수
//-------------------------------------------------
// 2 번은 1초로 빠른데, 3번은 7초나 걸리면서 느림
// 람다는 1000번이면 1000번 호출을 계속함.
//


// [문제] 랜덤 int 1000만개를 메모리에 저장하라.
// qsort를 이용하여 오름차순으로 정렬하라.
// 정렬 결과를 앞에서 부터 1000개를 화면 출력하라.

//#include <iostream>
//#include <random>
//#include <algorithm>
//#include <array>
//#include <print>
//#include <ranges> // views사용하기위해
//
//std::default_random_engine dre;
//std::uniform_int_distribution<int> uid{ 1, 9999999 };
//
//const int NUM{ 10000000 };
//
//std::array<int, 10000000> a;
//
//int 오름차순(const void* a, const void* b) {
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
//int 내림차순(const void* a, const void* b) {
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
//	// 교수님 코드 --------------------------------------------------
//
//	for (int& num : a) {
//		num = uid(dre);
//	}
//
//	//auto 정렬기준 = 오름차순; // 정렬 기준의 타입은 함수 포인터이다.
//	int(*정렬기준)(const void*, const void*) = 오름차순;
//	정렬기준 = 내림차순;
//
//	qsort((void*)a.data(), NUM, sizeof(std::array<int, NUM>::value_type), 정렬기준);
//
//	for (int num : a | std::views::take(100)) {
//		std::print("{:8}", num);
//	}
//}
//
// 위에는 c의 코드이다 .아래는 c++로 다시함

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

// [문제] 랜덤 int 1000만개를 메모리에 저장하라.
// STL의 sort를 이용하여 오름차순으로 정렬하라.
// 정렬 결과를 앞에서 부터 1000개를 화면 출력하라.

bool 오름차순(int a, int b) {
	return a < b;
}

//bool 내림차순(int a, int b) {
//	return a > b;
//}

int main() {


	//bool(*정렬기준)(int, int) = 내림차순;

	{
		for (int& num : a)
			num = uid(dre);

		auto b = std::chrono::high_resolution_clock::now(); // 스톱워치 시작
		std::sort(a.begin(), a.end(), 오름차순); // 구식이래
		auto e = std::chrono::high_resolution_clock::now(); // 스톱워치 끝
		std::cout << "걸린 시간 - " << e - b << std::endl;
		std::cout << "걸린 시간(초) - " << std::chrono::duration_cast<std::chrono::seconds>(e - b) << std::endl;
	}

	{
		for (int& num : a)
			num = uid(dre);

		auto b = std::chrono::high_resolution_clock::now(); // 스톱워치 시작
		std::sort(a.begin(), a.end(), [](int a, int b) {
			return a < b;
			});
		auto e = std::chrono::high_resolution_clock::now(); // 스톱워치 끝
		std::cout << "걸린 시간 - " << e - b << std::endl;
		std::cout << "걸린 시간(초) - " << std::chrono::duration_cast<std::chrono::seconds>(e - b) << std::endl;
	}


	//std::ranges::sort(a, 정렬기준); // 최신이래

	/*for (int num : a)
		std::print("{:8}", num);*/

	auto 람다 = []() {
		std::cout << "람다" << std::endl;
		};

	std::cout << "람다의 정체" << std::endl;
	std::cout << "람다의 크기 - " << sizeof(람다) << std::endl;
	std::cout << "람다의 위치 - " << std::addressof(람다) << std::endl;
	std::cout << "람다의 타입 - " << typeid(람다).name() << std::endl;
	std::cout << std::endl;
	std::cout << "main의 위치 - " << std::addressof(main) << std::endl;


}