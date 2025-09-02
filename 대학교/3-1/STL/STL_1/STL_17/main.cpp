//-------------------------------------------------
// 2025. STL 5.15                         11w 2d
//-------------------------------------------------
// 
//-------------------------------------------------
// 
//-------------------------------------------------
// 자식->부모 클래스로 갈때 generalizaton
// 부모->자식 클래스로 갈때 specialization
// 부모->자식으로 갈때 점점 구체화가 됨
// 
// STRING의 반복자 타입을 만든다.
//
// 표준 반복자가 되고 싶다면 지켜야할 약속들이 있다.
// *,++,==
// 제공해야할 타입 다섯가지 (iterator_category, difference_type, value_type, pointer, reference)
//
//

#include <iostream>
#include <vector>
#include <deque>
#include <concepts>
#include <string>
#include <algorithm>
#include "STRING.h"

//template <class 반복자>
//void f(반복자 i) {
//	//T* 가 어떤 종류의 반복자인가 알고 싶다면
//	//std::cout << " type - " << typeid(std::iterator_traits<반복자>::iterator_category).name() << std::endl;
//
//	// C++20의 concept을 사용하면 vector의 반복자가 contiguous임을 이용할 수 있다.
//	
//	std::cout << "type - " << typeid(반복자::iterator_concept).name() << std::endl; //vecctor만 적용되서 다른거 있으면 오류남.
//
//
//	//std::cout << "반복자 타입 - " << typeid(반복자::iterator_category).name() << std::endl;
//}

//template<class Iter>
//void f2(Iter i) {
//	std::cout << typeid(Iter::iterator_category).name() << std::endl;
//}


int main() {
	/*char* p = nullptr;
	f(p);*/

	// vector는 free-store에 contiguous 메모리를 관리한다.
	// vector의 반복자 - random_access_iterator_tag
	// 이때 deque의 반복자도 - random_access_iterator_tag 라고 나옴.
	
	//f(std::vector<int>{}.begin());
	//f(std::deque<int>::iterator{});

	// [문제?] 반복자가 contiguous인지 판단하고 싶다.
	/*std::cout << "벡터의 반복자는 contiguous인가? " <<
		std::boolalpha << std::contiguous_iterator<std::vector<int>::iterator> << std::endl;

	std::cout << "deque의 반복자는 contiguous인가? " <<
		std::boolalpha << std::contiguous_iterator<std::deque<int>::iterator> << std::endl;

	std::cout << "포인터의 반복자는 contiguous인가? " <<
		std::boolalpha << std::contiguous_iterator<int *> << std::endl;

	std::cout << "string의 반복자는 contiguous인가? " <<
		std::boolalpha << std::contiguous_iterator<std::string::iterator> << std::endl;

	std::cout << "STRING의 반복자는 contiguous인가? " <<
		std::boolalpha << std::contiguous_iterator<STRING::iterator> << std::endl; // 이게 되게 하고싶은거임*/

	//[1] 반복자가 어떤 종류인지 알려준다.

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
