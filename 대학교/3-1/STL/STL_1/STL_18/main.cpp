//-------------------------------------------------
// 2025. STL 5.20                         12w 1d
//-------------------------------------------------
// 
//-------------------------------------------------
// 반복자를 사용한 알고리즘 함수 작성
// find
// find_if
// copy
//-------------------------------------------------
// sort가 요구하는 랜덤반복자 연산을 코딩
//

#include <iostream>
#include "STRING.h"
#include <algorithm>
#include <functional>

template <class 반, class 값>
반 my_find(반 b, 반 e, 값 v) {
	while (b != e) {
		if (*b == v) {
			return b;
		}
		++b;
	}
	return e; // b도 가능
}

template <class 반복자, class Pred>
반복자 my_find_if(반복자 b, 반복자 e, Pred callable) {
	for (;b != e;++b) {
		if (callable(*b)) {
			return b;
		}
	} 
	return e; // b도 가능
}

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
	////STRING s{ "2025 05 20" };
	//STRING s{ "the quick brown fox jumps over the lazy dog" };
	//std::sort(s.begin(), s.end());
	//std::unique(s.begin(), s.end());
	//s.erase(unique(s.begin(), s.end()), s.end());

	//std::cout << s << std::endl;

	//STRING s{ "2025 05 20" };

	// [문제] 숫자를 입력받아 그 숫자가 있나 없나 알려주자.
	// [문제] 숫자를 입력받아 그 숫자보다 1큰 숫자가 있나 없나 알려주자.
	/*while (true) {
		std::cout << "찾을 숫자? ";
		char c;
		std::cin >> c;

		//auto p = std::find(s.begin(), s.end(), c);
		auto p = my_find(s.begin(), s.end(), c);

		if (p != s.end()) {
			std::cout << c << "를 찾았다!" << std::endl;
		}
		else {
			std::cout << "없는 숫자이다." << std::endl;
		}
	}*/

	// [문제] s 중에서 처음 나오는 홀수를 화면에 출력하라.
	/*auto p2 = std::find_if(s.begin(), s.end(), [](int n) {
		return n & 1;
		});*/

	/*auto p2 = my_find_if(s.begin(), s.end(), [](int n) {
		return n & 1;
		});

	if (p2 != s.end()) {
		std::cout << "첫 홀수는 - " << *p2 << std::endl;
	}
	else {
		std::cout << "홀수가 없다." << std::endl;
	}*/

	STRING s{ "2025 05 20 copy 함수를 만들어 보았다. 올해 여름은 매우 덥겠다." };
	// [문제] s를 화면에 copy (my_copy) 작성
	//std::copy(s.begin(), s.end(), std::ostream_iterator<char>{std::cout});
	my_copy(s.begin(), s.end(), std::ostream_iterator<char>{std::cout});

	// 다음시간 vector에 copy

}