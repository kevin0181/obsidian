//-------------------------------------------------
// 2025. STL 4.29                           9w 1d
//-------------------------------------------------
// 여기서부터는 기말고사나오는거...
//-------------------------------------------------
// 중간고사 푼거 풀어보기~~ 95점나옴
//-------------------------------------------------
// 
//
// 기말고사 후보 -> Test t(3); -> 메모리 상태 그림 그려봐라.

#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

#include"string.h"

int main() {
	
	//std::vector<STRING> v{ "1","22","333","4444","55555" };
	// 
	//std::erase(v, "333"); // syntactic sugar // 중간에 이렇게 지우는 동작은 vector에서 모든 데이터를 앞으로 댕기기 때문에 좋지 않다.
	//// list를 사용하는게 합당하다. // list는 free-store에서 첫번째 객체의 위치가 있음.
	//// ocp -> open close principle (개방 폐쇄 원칙) -> 객체지향 설계 원칙 erase에서 remove사용이되는거

	//for (const STRING& s : v) {
	//	std::cout << s << std::endl;
	//}

	std::list<STRING>	l{ "1", "22", "333", "4444", "55555" };
	l.remove("333");
	
	for (const STRING& s : l) {
		std::cout << s << std::endl;
	}

	// 다음시간 vector/deque/list 비교

};
