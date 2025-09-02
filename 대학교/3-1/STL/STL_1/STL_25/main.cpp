//-------------------------------------------------------------------
// 2025. STL 6�� 12��                                       (14�� 2��)
//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
// Algorithm
// ���İ��� �˰��� �� - ���⵵ ������
// 1. partition 
// 2. nth_element
// 3. partial_sort
// 4. sort
// 5. stable_sort
// 
// distance
//-------------------------------------------------------------------

// a~b���� �������� ���� ��� partition�� ���� ����.

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
std::iterator_traits<Iter>::difference_type my_distance(Iter b, Iter e) { // vector�� ����Ѵ�.
	// �����̶��
	//return e - b;
	// �� ��
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
		std::cout << "partition �ϱ� ��" << std::endl;
		for (int num : v) {
			std::print("{:8}", num);
		}
		std::cout << std::endl;

		auto p = std::partition(v.begin(), v.end(), [](int num) { return num & 1; });

		std::cout << "Ȧ���� ¦���� partition �� ��" << std::endl;
		std::cout << "Ȧ��" << std::endl;
		for (auto i = v.begin(); i < p; ++i) {
			std::print("{:8}", *i);
		}
		std::cout << std::endl;

		std::cout << "¦��" << std::endl;
		for (auto i = p; i < v.end(); ++i) {
			std::print("{:8}", *i);
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;

	// 2. nth_element -> �̰� ���蹮�� ���ٱ׷�.
	{
		std::shuffle(v.begin(), v.end(), dre);
		std::cout << "nth_element ���� ��" << std::endl;
		for (int num : v) {
			std::print("{:8}", num);
		}
		std::cout << std::endl;

		/*std::nth_element(v.begin(), v.begin() + 10, v.end(), [](int num) {
			return num & 1;
			});*/

		/*std::nth_element(v.begin(), v.begin() + 10, v.end(), [](int a, int b) {
			return a < b;
			});*/ // 11��° ���� ��ü ���� �߿��� 11��°�� ���� ���� �ǰ�, 1~10�������� 11��°���� ���� ���� �ǰ�, 12��°���� 100��°������ 11��° ������ ū ����� ��ġ��.

		std::nth_element(v.begin(), v.begin() + 40, v.end()); // ���ɾ���� -> 11��° ��ġ�� �ִ� ���� ��ü ���� �߿��� 11��°�� ���� ���� ��.

		std::cout << "40�� �̳������� ����" << std::endl;
		std::cout << "40�����" << std::endl;
		for (auto i = v.begin(); i < v.begin() + 40; ++i) {
			std::print("{:8}", *i);
		}
		std::cout << std::endl;

		std::cout << "������" << std::endl;
		for (auto i = v.begin() + 40; i < v.end(); ++i) {
			std::print("{:8}", *i);
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;

	// 3. partial_sort
	{
		std::shuffle(v.begin(), v.end(), dre);
		std::cout << "partial_sort ���� ��" << std::endl;
		for (int num : v) {
			std::print("{:8}", num);
		}
		std::cout << std::endl;

		std::partial_sort(v.begin(), v.begin() + 40, v.end());

		std::cout << "40����� �κ� ����" << std::endl;
		std::cout << "40�����" << std::endl;
		for (auto i = v.begin(); i < v.begin() + 40; ++i) {
			std::print("{:8}", *i);
		}
		std::cout << std::endl;

		std::cout << "������" << std::endl;
		for (auto i = v.begin() + 40; i < v.end(); ++i) {
			std::print("{:8}", *i);
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;

	// 3. sort
	{
		std::shuffle(v.begin(), v.end(), dre);
		std::cout << "sort ���� ��" << std::endl;
		for (int num : v) {
			std::print("{:8}", num);
		}
		std::cout << std::endl;

		std::sort(v.begin(), v.end());

		std::cout << "���� ��" << std::endl;
		for (auto i = v.begin(); i < v.end(); ++i) {
			std::print("{:8}", *i);
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;

	// class ���
	std::vector<Dog> dogs(100);

	std::ranges::sort(dogs, {}, &Dog::c);

	std::cout << "���� ������ ����" << std::endl;
	for (const Dog& dog : dogs) {
		std::cout << dog << std::endl;
	}

	std::cout << std::endl;

	std::cout << "���� ������������ ����" << std::endl;
	//std::ranges::sort(dogs, std::greater<int>{}, & Dog::n);
	//std::ranges::stable_sort(dogs, std::greater<>{}, & Dog::n);
	for (const Dog& dog : dogs) {
		std::cout << dog << std::endl;
	}

	// �ݺ��ڰ��� �Ÿ��� ��� distance
	std::vector<int>v2{ 1,2,3,4,5 };
	std::list<int> c1{ 1,2,3,4,5 };

	std::cout <<"���Ϳ��� �Ÿ� - " << std::distance(v2.begin(), v2.end()) << std::endl;
	std::cout << "����Ʈ���� �Ÿ� - " << std::distance(c1.begin(), c1.end()) << std::endl;

	//std::cout << "���Ϳ��� �Ÿ� - " << my_distance(v2.end(), v2.begin()) << std::endl;
	std::cout << "����Ʈ���� �Ÿ� - " << my_distance(c1.end(), c1.begin()) << std::endl;

}
