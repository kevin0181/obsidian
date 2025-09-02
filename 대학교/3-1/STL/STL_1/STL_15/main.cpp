//-------------------------------------------------
// 2025. STL 5..08                           10w 2d
//-------------------------------------------------
// 
//-------------------------------------------------
// 
//-------------------------------------------------
// 
// list에서 찾기는 o(n)임. 그래서 find_if 씀  list-> 노드기반이니깐 삽입 삭제는 빨라도 찾는건 vector에 비해서 느림.
// forward_list<T> - it is intended that forward_list have zero space or time ovecrhead 
// relative to a hand-written c-style singly linked list.
// Features that would conflict width that goal have been omitted.
// span - 모든 contigous 자료구조를 대표하는 자료구조
// Iterator - iterators are a generalization of pointers that allow a c++ program
// to work width different data structures (for example,containers and ranges) in a uniform manner.


#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>
#include <span>
#include <vector>
#include <deque>
#include <string>

#include"STRING.h"

// f는 거꾸로 출력하는 함수
void f(std::span<int> s) {
	for (auto i = s.rbegin(); i != s.rend(); ++i)
		std::cout << *i << " ";
	std::cout << std::endl;
}

void f_s(std::span<std::string> s) {
	for (auto i = s.rbegin(); i != s.rend(); ++i)
		std::cout << *i << " ";
	std::cout << std::endl;
}


int main() {

	std::fstream in{ "main.cpp" };
	if (not in)
		return 0;

	// [문제] 'main.cpp"의 단어를 list에 저장하라.
	std::list<STRING> cont{ std::istream_iterator<STRING>{in},{} };

	// 저장한 내용 출력
	/*for (const STRING& s : cont)
		std::cout << s << std::endl;*/

	// [문제] 단어를 입력받아 cont에 있는지 출력한다.
	// 있다면 처음부터 셌을때 몇 번째 단어인지 출력하라.
	// (변형) 찾을 단어를 모두 찾아라.

	/*while (true) {

		std::cout << "찾을 단어는?";

		STRING word;
		std::cin >> word;

		auto pos = std::find(cont.begin(), cont.end(), word);

		if (pos == cont.end())
			std::cout << word << "는 없는 단어 입니다." << std::endl;
		else
			std::cout << word << "는 " << std::distance(cont.begin(), pos) + 1 << "번째 단어 입니다." << std::endl;
	}*/


	// [문제] 리스트에 있는 단어 중에서 길이가 5인것 모두를 화면에 출력하라.
	/*std::copy_if(cont.begin(), cont.end(), std::ostream_iterator<STRING> {std::cout, "\n"},
		[](const STRING& s) {
			return s.size() == 5;
		});*/

	int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
	// 거꾸로 출력하라.
	for (auto i = std::rbegin(a); i != std::rend(a);++i)
		std::cout << *i << std::endl;
	// a와 같은 contigous한 메모리를 가진 놈들도 rebegin()같은 전역 함수를 사용해서 사용이 가능.
	//f(a);

	std::vector<int> v{ std::begin(a), std::end(a) };
	//f(v);

	std::deque<int> d{ v.begin(),v.end() };
	//f(d); // deque는 contigous한 메모리를 가지지 않음. 그래서 span을 사용하지 못함.

	std::string s{ "hello world" };
	//f_s(s);


	// ------------------------------------------------------------------------------------------------

	//std::sort(std::begin(a) + 4, std::begin(a) + 6); // 4~6까지 정렬 이걸 range라고함

	//for(int num : a)
	//	std::cout << num << " ";
	//std::cout << std::endl;

	//출력반복자를 만든다
	//std::ostream_iterator <char> p; // 이렇게 안되는 이유? 기본생성자가 없음.
	std::ostream_iterator <char> p{ std::cout };

	//*p = 'A';
	////++p; // 이거 안적어도 자동으로 다음 메모리 자리로 알아서 이동을 하긴 함.
	//*p = 'B';
	////++p;
	//*p = 'C';
	////++p;
	//*p = '\n';

	STRING s1{ "hello" };

	//for (char c : s1) // -> 돌려보면 안되는 이유 뜸 begin, end 없어서 안댐.
	//	std::cout << c << std::endl;

	//for (auto i = s1.begin(); i != s1.end(); ++i) // 위에꺼 번역한거임.
	//	std::cout << *i << std::endl;

	for (char c : s1)
		std::cout << c;
	std::cout << std::endl;

}