//-------------------------------------------------------------------
// 2025. STL 6월 12일                                       (14주 2일)
//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
// Algorithm
// 정렬관련 알고리즘 비교 - 복잡도 순으로
// 1. partition 
// 2. nth_element
// 3. partial_sort
// 4. sort
// 5. stable_sort
// 
// distance
//-------------------------------------------------------------------

// a~b까지 정렬하지 않을 경우 partition이 가장 좋음.

#include<iostream>
#include<random>
#include<vector>
#include<algorithm>
#include <numeric>
#include <print>
#include <ranges>
#include <list>

std::default_random_engine dre{ std::random_device{}() };
std::uniform_int_distribution<int> uidC{ 'a', 'z' };
std::uniform_int_distribution<int> uid{ 1, 100 };

template <class Iter>
std::iterator_traits<Iter>::difference_type my_distance(Iter b, Iter e) { // vector가 사망한다.
	// 랜덤이라면
	//return e - b;
	// 그 외
	typename std::iterator_traits<Iter>::difference_type d{};
	while (b != e) {
		++d;
		++b;
	}
	return d;
}

struct Dog {
	char c = static_cast<int>(uidC(dre));
	int n{ uid(dre) };
	friend std::ostream& operator<<(std::ostream& os, const Dog& dog) {
		std::print(os,"{} - {:3}", dog.c, dog.n);
		return os;
	}
};

int main() {

	std::vector<int> v(100);
	std::iota(v.begin(), v.end(), 1);

	// 1. partition
	{
		std::shuffle(v.begin(), v.end(), dre);
		std::cout << "partition 하기 전" << std::endl;
		for (int num : v) {
			std::print("{:8}", num);
		}
		std::cout << std::endl;

		auto p = std::partition(v.begin(), v.end(), [](int num) { return num & 1; });

		std::cout << "홀수와 짝수로 partition 한 후" << std::endl;
		std::cout << "홀수" << std::endl;
		for (auto i = v.begin(); i < p; ++i) {
			std::print("{:8}", *i);
		}
		std::cout << std::endl;

		std::cout << "짝수" << std::endl;
		for (auto i = p; i < v.end(); ++i) {
			std::print("{:8}", *i);
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;

	// 2. nth_element -> 이거 시험문제 낸다그럼.
	{
		std::shuffle(v.begin(), v.end(), dre);
		std::cout << "nth_element 실행 전" << std::endl;
		for (int num : v) {
			std::print("{:8}", num);
		}
		std::cout << std::endl;

		/*std::nth_element(v.begin(), v.begin() + 10, v.end(), [](int num) {
			return num & 1;
			});*/

		/*std::nth_element(v.begin(), v.begin() + 10, v.end(), [](int a, int b) {
			return a < b;
			});*/ // 11번째 값이 전체 숫자 중에서 11번째로 작은 값이 되고, 1~10번까지는 11번째보다 작은 값이 되고, 12번째에서 100번째까지는 11번째 값보다 큰 값들로 배치됨.

		std::nth_element(v.begin(), v.begin() + 40, v.end()); // 일케쓰면댐 -> 11번째 위치에 있는 값이 전체 숫자 중에서 11번째로 작은 값이 됨.

		std::cout << "40등 이내까지는 정렬" << std::endl;
		std::cout << "40등까지" << std::endl;
		for (auto i = v.begin(); i < v.begin() + 40; ++i) {
			std::print("{:8}", *i);
		}
		std::cout << std::endl;

		std::cout << "나머지" << std::endl;
		for (auto i = v.begin() + 40; i < v.end(); ++i) {
			std::print("{:8}", *i);
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;

	// 3. partial_sort
	{
		std::shuffle(v.begin(), v.end(), dre);
		std::cout << "partial_sort 실행 전" << std::endl;
		for (int num : v) {
			std::print("{:8}", num);
		}
		std::cout << std::endl;

		std::partial_sort(v.begin(), v.begin() + 40, v.end());

		std::cout << "40등까지 부분 정렬" << std::endl;
		std::cout << "40등까지" << std::endl;
		for (auto i = v.begin(); i < v.begin() + 40; ++i) {
			std::print("{:8}", *i);
		}
		std::cout << std::endl;

		std::cout << "나머지" << std::endl;
		for (auto i = v.begin() + 40; i < v.end(); ++i) {
			std::print("{:8}", *i);
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;

	// 3. sort
	{
		std::shuffle(v.begin(), v.end(), dre);
		std::cout << "sort 실행 전" << std::endl;
		for (int num : v) {
			std::print("{:8}", num);
		}
		std::cout << std::endl;

		std::sort(v.begin(), v.end());

		std::cout << "정렬 후" << std::endl;
		for (auto i = v.begin(); i < v.end(); ++i) {
			std::print("{:8}", *i);
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;

	// class 사용
	std::vector<Dog> dogs(100);

	std::ranges::sort(dogs, {}, &Dog::c);

	std::cout << "글자 순서로 정렬" << std::endl;
	for (const Dog& dog : dogs) {
		std::cout << dog << std::endl;
	}

	std::cout << std::endl;

	std::cout << "숫자 내림차순으로 정렬" << std::endl;
	//std::ranges::sort(dogs, std::greater<int>{}, & Dog::n);
	//std::ranges::stable_sort(dogs, std::greater<>{}, & Dog::n);
	for (const Dog& dog : dogs) {
		std::cout << dog << std::endl;
	}

	// 반복자간의 거리를 재는 distance
	std::vector<int>v2{ 1,2,3,4,5 };
	std::list<int> c1{ 1,2,3,4,5 };

	std::cout <<"벡터에서 거리 - " << std::distance(v2.begin(), v2.end()) << std::endl;
	std::cout << "리스트에서 거리 - " << std::distance(c1.begin(), c1.end()) << std::endl;

	//std::cout << "벡터에서 거리 - " << my_distance(v2.end(), v2.begin()) << std::endl;
	std::cout << "리스트에서 거리 - " << my_distance(c1.end(), c1.begin()) << std::endl;

}
