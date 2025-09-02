//-------------------------------------------------
// 2025. STL 4.22                           8w 1d
//-------------------------------------------------
// 
//-------------------------------------------------
// STL Containers - Containers are objects that store other objects.
// array<T, M>
// vector<T> - dynamic(run-time) array
//-------------------------------------------------
// 
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

#include"string.h"


int main() {
	//std::list<STRING> v_s{ "1","22","333","4444","55555" };

	//// [문제] v_s에서 "333"을 제거하라.

	////std::erase(v_s, "333"); // -> 이렇게 작성하면 안댐.
	//v_s.remove("333");

	//for (const auto& str : v_s) {
	//	std::cout << str << std::endl;
	//}

	//std::vector<STRING> v_s2;
	//v_s2.reserve(10); // 10개를 미리 예약
	//v_s2.assign({ "1","22","4444","55555" });

	//// [문제] v_s2에서 "22"와 "4444" 사이에 "333"을 삽입하라.
	//// vector에서 이런 동작은 삽질임.

	//v_s2.emplace(v_s2.begin() + 2, "333"); // 22 다음에 삽입 // reserve가 없으면 삽질. 미리 10이라는 크기를 줫기 때문에 상관은없지만 // reserve를 하지 않으면 새로 크기를 주기 때문에 쓸대없는 동작을하게됨.
	//
	//for (const auto& str : v_s2) {
	//	std::cout << str << std::endl;
	//}

	std::list<STRING> v_l2; // 매우 효율적으로 삽입과 삭제가 가능하다. //동적으로 하는거 -> 리스트쓰자.
	v_l2.assign({ "1","22","4444","55555" });

	v_l2.emplace(++++v_l2.begin(), "333");

	for (const auto& str : v_l2) {
		std::cout << str << std::endl;
	}
}