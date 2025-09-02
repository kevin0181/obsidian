//-------------------------------------------------
// 2025. STL 4.10                           6w 2d
//-------------------------------------------------
// 
//-------------------------------------------------
// class STRING - STL 정식 컨테이너처럼 동작하게함
//-------------------------------------------------
// 
//

#include <iostream>
#include <fstream>
#include <array>
#include <algorithm>
#include "STRING.h"

// [문제] "main.cpp"에 있는 단어 (공백으로 분리된 char의 집합)를 모두 메모리에 저장하라.
// 단어를 우리가 만든 STRING에 저장하라.
// 다음 코드가 문제없이 실행되게 하면 좋겠다.
// 단어를 50개만 읽는다.
// 단어를 길이기준 오름차순으로 정렬하라.

std::array<STRING, 50>words;

int main() {

	STRING s;

	std::ifstream in{ "main.cpp" };

	if (not in)
		return 0;

	/*while (in >> s) {
		std::cout << s << std::endl;
	}*/

	for (STRING& word : words) {
		in >> word;
	}

	/*std::sort(words.begin(), words.end(), [](const STRING& lhs, const STRING& rhs) {
		return lhs.size() < rhs.size();
		});*/

	std::sort(words.begin(), words.end());

	for (const STRING& word : words) {
		std::cout << word << std::endl;
	}
}