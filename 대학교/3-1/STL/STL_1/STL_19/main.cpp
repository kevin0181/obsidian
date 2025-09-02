//-------------------------------------------------
// 2025. STL 5.22                         12w 2d
//-------------------------------------------------
// 
//-------------------------------------------------
// Associative 컨테이너 (key 값을 기준으로 원소를 항상 정렬하는 컨테이너)
// set / multiset - key==value
// map / multimap - pair<key, value>
// 
//-------------------------------------------------
// 
// 기호는 정상적으로 받지만 내부적으로 생각과 다르게 처리하는 경우 - iterator adaptors
//

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <ranges>
#include "STRING.h"

template <class 원본반복자, class 복사본반복자>
원본반복자 my_copy(원본반복자 b, 원본반복자 e, 복사본반복자 d) {
	while (b != e) {
		*d = *b;
		++b;
		++d;
	}
	return e; // d도 가능
}

int main() {

	/*STRING s{"2025 05 20 copy 함수를 만들어 보았다. 올해 여름은 매우 덥겠다."};

	std::vector<char> v(s.size());*/

	//my_copy(s.begin(), s.end(), v.begin());

	/*for (char c : v) {
		std::cout << c;
	}
	std::cout << std::endl;*/

	/*my_copy(s.begin(), s.end(), std::back_inserter(v));

	std::string x{ v.begin(), v.end() };
	std::cout << x << std::endl;*/

	/*std::set<int> s{ 1,3,5,7,9,2,4,5,6,8,10 };

	for (auto i : s) {
		std::cout << i << " ";
	}
	std::cout << std::endl;*/

	// 거꾸로 출력
	/*for (auto i = s.rbegin(); i != s.rend(); ++i) {
		std::cout << *i << " ";
	}
	std::cout << std::endl;*/

	//for (auto i : s | std::views::reverse) { // 이런걸 functional programming이라고 한다.
	//	std::cout << i << " ";
	//}
	//std::cout << std::endl;
	
	//-------------------------------------------------------------------------------------------------------

	//std::multiset<int> s{ 1,3,5,7,9,2,4,5,6,8,10 }; // 찾기 지우기 삽입 등 일을 할라고 항상 정렬한 상태임.
	// 데이터가 중복되면 한개만 나오는데 그걸 어떻게 처리하냐? equivalence(동등성) relation? 
	// a와 b 두개의 객체가 있다면 considered equivalent 하는지 판단하는지는 !comp(a, b) && !comp(b, a) 이거를 통해서 판단한다
	// equality (상등성) a,b | a == b
	// equivalence (동등성) a,b | a < b || a > b

	/*for (auto i : s) {
		std::cout << i << " ";
	}
	std::cout << std::endl;*/


	/*std::set<STRING> s{ "2025년","5월","22일","연관컨테이너","셋" };

	for (const STRING& str : s) {
		std::cout << str << std::endl;
	}*/

	// [문제] set<STRING>을 사용하여 키보드의 입력을 모두 저장하라.
	// 컨테이너의 원소를 모두 화면에 출력하라.

	std::set<STRING> s{ std::istream_iterator<STRING>{std::cin},{} };

	for (const STRING& str : s) {
		std::cout << str << std::endl;
	}

}