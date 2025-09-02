//-------------------------------------------------
// 2025. STL 5.29                         13w 2d
//-------------------------------------------------
// 
//-------------------------------------------------
// 
//-------------------------------------------------
//
//

// [1] vector<STRING>에 저장하라.
// [2] 모두 몇 단어인지 화면에 출력하라.
// [3] 입력한 단어의 사용 횟수를 출력하세요.
// [3.1] 알파벳을 소문자로 바꾸고, 모든 소문자의 출현 횟수를 출력하세요.
// a - 1231
// b - 2333
//
// z - 22
// [4] 출현횟수가 많은 것 부터 작은 순서로 출력하라.
// 

// 다시~ 처음부터~~
// [문제] 가장 많이 사용된 단어(STRING에 저장)와 사용횟수를 순서대로 출력하시오.

#include <iostream>
#include <set>
#include <fstream>
#include <iterator>
#include <array>
#include <map>
#include <ranges>

#include"STRING.h"

int main() {

	std::fstream in{ "이상한 나라의 앨리스.txt" };

	std::multiset<STRING> ms{ std::istream_iterator<STRING>{in},{} };

	//for (const STRING& 단어 : ms) {
	//	std::cout << 단어 << " ";
	//}
	//std::cout << std::endl << std::endl;

	//while (true) {
	//	std::cout << "찾으실 단어? ";
	//	STRING 찻단;
	//	std::cin >> 찻단;
	//	//[문제] 찻단은 도대체 몇번이나 사용되었는가?

	//	// 내가 짠 코드
	//	/*auto it = ms.find(찻단);
	//	if (it == ms.end()) {
	//		std::cout << "찾으시는 단어는 없습니다." << std::endl;
	//	}
	//	else {
	//		auto count = ms.count(찻단);
	//		std::cout << 찻단 << "은 " << count << "번 사용되었습니다." << std::endl;
	//	}*/

	//	// 교수님이 짠 코드
	//	/*size_t 개수 = ms.count(찻단);
	//	std::cout << 찻단 << "은 " << 개수 << "번 사용되었습니다." << std::endl;*/
	//	
	//	//	multiset은 const로 지정이 되어있음, 
	//	//	이유 -> 값이 항상 정렬된 상태로 유지해야 하기 때문에, 원소를 수정하는 행위를 막기 위해 원소에 대한 접근을 const로 제한 (값을 넣는건 가능, 수정이 불가능)
	//	
	//	// set에서 원소의 개수 구하기
	//	//std::pair<std::multiset<STRING>::iterator, std::multiset<STRING>::iterator> 위치 = ms.equal_range(찻단);
	//	auto [시작, 끝] = ms.equal_range(찻단);
	//	size_t 개수 = distance(시작, 끝);
	//	std::cout << 찻단 << "은 " << 개수 << "번 사용되었습니다." << std::endl;
	//}


	// [3.1]
	// 내가 짠 코드
	/*std::multiset<char> ms{ std::istream_iterator<char>{in},{} };

	for (char c = 'a'; c <= 'z'; ++c) {
		size_t count = ms.count(c);
		if (count > 0) {
			std::cout << c << " - " << count << std::endl;
		}
	}*/
	
	// 교수님이 짠 코드
	/*std::array<size_t, 26> a{};

	for (const STRING& 단어 : ms) {
		for (char c : 단어) {
			a[tolower(c) - 'a']++;
		}
	}

	for (int i = 0; i < 26; ++i) {
		std::cout << static_cast<char>('a' + i) << " - " << a[i] << std::endl;
	}*/ // 알파벳을 찾을땐 array -> 이거보다 map으로 짜는게 더 좋음

	std::map<char, size_t> 알파벳과출현횟수;
	
	for (const STRING& 단어 : ms) {
		for (char c : 단어) {
			알파벳과출현횟수[tolower(c)]++;
		}
	}

	for (const auto& [알파벳, 횟수] : 알파벳과출현횟수) {
		if (isalpha(알파벳)) {
			std::cout << 알파벳 << " - " << 횟수 << std::endl;
		}
	}

	std::cout << "-------------------------" << std::endl;

	// [4]
	// 내가 짠 코드
	/*std::multimap<size_t, char, std::greater<>> 출현횟수와알파벳;
	for (const auto& [알파벳, 횟수] : 알파벳과출현횟수) {
		if (isalpha(알파벳)) {
			출현횟수와알파벳.insert({ 횟수, 알파벳 });
		}
	}

	for (const auto& [횟수, 알파벳] : 출현횟수와알파벳) {
		std::cout << 알파벳 << " - " << 횟수 << std::endl;
	}*/

	// 교수님이 짠 코드
	std::map<size_t, char> 횟수와알파벳;
	for (auto [알파벳, 횟수] : 알파벳과출현횟수) {
		횟수와알파벳[횟수] = 알파벳;
	}

	for (const auto& [횟수, 알파벳] : 횟수와알파벳 | std::views::reverse) {
		if (isalpha(알파벳))
			std::cout << 알파벳 << " - " << 횟수 << std::endl;
	}

}
