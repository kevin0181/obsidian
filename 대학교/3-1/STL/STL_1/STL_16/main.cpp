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
// 역방향 반복자는 반드시 class가 되어야 한다. class로 리턴하면 훨신 많은 부가정보를 줄 수잇음. (이게 반복자냐 라는것도 물어볼 수있음)
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
//	std::cout << "array의 반복자 타입 - " << typeid(i).name() << std::endl; // type 아이디 이름은 그냥 컴파일 만든사람들이 지멋대로 지은거임.
//}
//
//void f(std::vector<int>::iterator i) {
//	std::cout << "vector의 반복자 타입 - " << typeid(i).name() << std::endl;
//}

template <class 반복자>
void f(반복자 i) { // 여기서 반복자만 걸러서 가져오게하는걸 컨셉이라고함. (지금은 다들어오는 상태임)
	std::cout << "반복자 타입 - " << typeid(반복자::iterator_category).name() << std::endl;
}

int main() {
	
	//int a[] = { 1,2,3,4,5,6,7,8,9,10 };
	//// [문제] 거꾸로 출력하세요.

	//for (auto i = std::rbegin(a); i != std::rend(a); ++i) // -> uniform manner가아님.
	//	std::cout << *i << " ";

	//교수님이 짠 코드
	/*std::span<int>s{ a };
	for (auto i = s.rbegin(); i != s.rend(); ++i)
		std::cout << *i << " ";*/

	std::cout << std::endl;

	//std::vector<int> s{ 1,3,5,7,9 };

	//for (auto i = s.rbegin(); i != s.rend(); ++i)		// 돌아감.
	//	std::cout << *i << " ";

	
	//---------------------------------------------------------------------------------

	STRING s{ "2025 5 13" };

	// 이런 문제 나올듯? *i가 함수니깐. 다른 자료구조에서도 아래 코드가 동작이 가능함.
	for (auto i = s.rbegin(); i != s.rend(); ++i) // --i는 야매코드임(되기는함). ++i가 되어도 돌아가도록 만들어야함. (이를 위해서는 rbegin()함수의 리넡값이 클래스가되어야함)
		std::cout << *i << " ";
	//space ship operator를 사용하면 (three way operator) 모든 연산자를 한방에 처리할 수 있음. (<=>)


	//---------------------------------------------------------------------------------
	std::cout << std::endl;
	// [문제] 함수 f는 반복자를 인자로 받아 어떤 종류인지 출력한다.
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
	f(p);*/ // 얘네느 안됨.


}