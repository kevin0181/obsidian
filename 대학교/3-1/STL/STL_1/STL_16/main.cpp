//-------------------------------------------------
// 2025. STL 5.13                         11w 1d
//-------------------------------------------------
// 
//-------------------------------------------------
// 
//-------------------------------------------------
// Iterator - iterators are a generalization of pointers that allow a c++ program
// to work width different data structures (for example,containers and ranges) in a uniform manner.
// 
// ������ �ݺ��ڴ� �ݵ�� class�� �Ǿ�� �Ѵ�. class�� �����ϸ� �ν� ���� �ΰ������� �� ������. (�̰� �ݺ��ڳ� ��°͵� ��� ������)
// 
//

#include <span>
#include <iostream>
#include <vector>
#include "STRING.h"

//-------------------------------------------------
#include <array>
//#include <vector>
#include <deque>
#include <list>
#include <forward_list>

//void f(std::array<char,0>::iterator i) {
//	std::cout << "array�� �ݺ��� Ÿ�� - " << typeid(i).name() << std::endl; // type ���̵� �̸��� �׳� ������ ���������� ���ڴ�� ��������.
//}
//
//void f(std::vector<int>::iterator i) {
//	std::cout << "vector�� �ݺ��� Ÿ�� - " << typeid(i).name() << std::endl;
//}

template <class �ݺ���>
void f(�ݺ��� i) { // ���⼭ �ݺ��ڸ� �ɷ��� ���������ϴ°� �����̶����. (������ �ٵ����� ������)
	std::cout << "�ݺ��� Ÿ�� - " << typeid(�ݺ���::iterator_category).name() << std::endl;
}

int main() {
	
	//int a[] = { 1,2,3,4,5,6,7,8,9,10 };
	//// [����] �Ųٷ� ����ϼ���.

	//for (auto i = std::rbegin(a); i != std::rend(a); ++i) // -> uniform manner���ƴ�.
	//	std::cout << *i << " ";

	//�������� § �ڵ�
	/*std::span<int>s{ a };
	for (auto i = s.rbegin(); i != s.rend(); ++i)
		std::cout << *i << " ";*/

	std::cout << std::endl;

	//std::vector<int> s{ 1,3,5,7,9 };

	//for (auto i = s.rbegin(); i != s.rend(); ++i)		// ���ư�.
	//	std::cout << *i << " ";

	
	//---------------------------------------------------------------------------------

	STRING s{ "2025 5 13" };

	// �̷� ���� ���õ�? *i�� �Լ��ϱ�. �ٸ� �ڷᱸ�������� �Ʒ� �ڵ尡 ������ ������.
	for (auto i = s.rbegin(); i != s.rend(); ++i) // --i�� �߸��ڵ���(�Ǳ����). ++i�� �Ǿ ���ư����� ��������. (�̸� ���ؼ��� rbegin()�Լ��� �������� Ŭ�������Ǿ����)
		std::cout << *i << " ";
	//space ship operator�� ����ϸ� (three way operator) ��� �����ڸ� �ѹ濡 ó���� �� ����. (<=>)


	//---------------------------------------------------------------------------------
	std::cout << std::endl;
	// [����] �Լ� f�� �ݺ��ڸ� ���ڷ� �޾� � �������� ����Ѵ�.
	std::array <char, 0> a{};
	/*f(a.begin());
	f(std::vector<int>::iterator{});
	f(std::vector<char>::iterator{});*/

	f(std::ostream_iterator<char>{ std::cout }); 
	f(std::istream_iterator<char>{ std::cin });
	f(std::forward_list<int>{}.begin());
	f(std::list<int>::reverse_iterator{});
	f(std::deque<int>{}.begin());
	f(std::vector<int>{}.cbegin());

	/*char* p;
	f(p);*/ // ��״� �ȵ�.


}