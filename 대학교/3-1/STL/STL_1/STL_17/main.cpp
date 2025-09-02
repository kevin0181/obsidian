//-------------------------------------------------
// 2025. STL 5.15                         11w 2d
//-------------------------------------------------
// 
//-------------------------------------------------
// 
//-------------------------------------------------
// �ڽ�->�θ� Ŭ������ ���� generalizaton
// �θ�->�ڽ� Ŭ������ ���� specialization
// �θ�->�ڽ����� ���� ���� ��üȭ�� ��
// 
// STRING�� �ݺ��� Ÿ���� �����.
//
// ǥ�� �ݺ��ڰ� �ǰ� �ʹٸ� ���Ѿ��� ��ӵ��� �ִ�.
// *,++,==
// �����ؾ��� Ÿ�� �ټ����� (iterator_category, difference_type, value_type, pointer, reference)
//
//

#include <iostream>
#include <vector>
#include <deque>
#include <concepts>
#include <string>
#include <algorithm>
#include "STRING.h"

//template <class �ݺ���>
//void f(�ݺ��� i) {
//	//T* �� � ������ �ݺ����ΰ� �˰� �ʹٸ�
//	//std::cout << " type - " << typeid(std::iterator_traits<�ݺ���>::iterator_category).name() << std::endl;
//
//	// C++20�� concept�� ����ϸ� vector�� �ݺ��ڰ� contiguous���� �̿��� �� �ִ�.
//	
//	std::cout << "type - " << typeid(�ݺ���::iterator_concept).name() << std::endl; //vecctor�� ����Ǽ� �ٸ��� ������ ������.
//
//
//	//std::cout << "�ݺ��� Ÿ�� - " << typeid(�ݺ���::iterator_category).name() << std::endl;
//}

//template<class Iter>
//void f2(Iter i) {
//	std::cout << typeid(Iter::iterator_category).name() << std::endl;
//}


int main() {
	/*char* p = nullptr;
	f(p);*/

	// vector�� free-store�� contiguous �޸𸮸� �����Ѵ�.
	// vector�� �ݺ��� - random_access_iterator_tag
	// �̶� deque�� �ݺ��ڵ� - random_access_iterator_tag ��� ����.
	
	//f(std::vector<int>{}.begin());
	//f(std::deque<int>::iterator{});

	// [����?] �ݺ��ڰ� contiguous���� �Ǵ��ϰ� �ʹ�.
	/*std::cout << "������ �ݺ��ڴ� contiguous�ΰ�? " <<
		std::boolalpha << std::contiguous_iterator<std::vector<int>::iterator> << std::endl;

	std::cout << "deque�� �ݺ��ڴ� contiguous�ΰ�? " <<
		std::boolalpha << std::contiguous_iterator<std::deque<int>::iterator> << std::endl;

	std::cout << "�������� �ݺ��ڴ� contiguous�ΰ�? " <<
		std::boolalpha << std::contiguous_iterator<int *> << std::endl;

	std::cout << "string�� �ݺ��ڴ� contiguous�ΰ�? " <<
		std::boolalpha << std::contiguous_iterator<std::string::iterator> << std::endl;

	std::cout << "STRING�� �ݺ��ڴ� contiguous�ΰ�? " <<
		std::boolalpha << std::contiguous_iterator<STRING::iterator> << std::endl; // �̰� �ǰ� �ϰ��������*/

	//[1] �ݺ��ڰ� � �������� �˷��ش�.

	/*STRING s{ "2025 05 15" };

	for (auto i = s.begin(); i != s.end(); ++i) {
		std::cout << *i << " ";
	}
	std::cout << std::endl;

	f2(s.begin());*/

	STRING s{ "2025 05 15" };
	std::sort(s.begin(), s.end());

	std::cout << s << std::endl; // " 0122555"

}
