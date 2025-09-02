//-------------------------------------------------
// 2025. STL 4.17                           7w 2d
//-------------------------------------------------
// 
//-------------------------------------------------
// 
//-------------------------------------------------
// 
//

#include <iostream>
#include <vector>
#include "STRING.h"

// [문제] vector가 어떻게 free-store의 메모리를 관리하는지 알아본다.

int main() {
	std::vector<int> v;

	
	/*for (int i = 0; i < 10; ++i) {
		std::cout << i << std::endl;
		std::cout << "현재 원소의 개수                       - " << v.size() << std::endl;
		std::cout << "재할당 없이 저장할 수 있는 원소의 개수 - " << v.capacity() << std::endl;
		std::cout << "관리하는 메모리의 시작번지             - " << v.data() << std::endl;

		v.push_back(i + 1);

		std::cout << std::endl;
	}*/

	size_t old{ v.capacity() };

	// VS의 vector는 메모리 크기를 어떻게 바꾸나?
	/*for (int i = 0; i < 1000; ++i) {
		if (v.capacity() != old) {
			std::cout << "--------------------------------" << std::endl;
			std::cout << "이전 크기 - " << old << std::endl;
			std::cout << "새로 할당받은 크기 - " << v.capacity() << std::endl;
			old = v.capacity();
			std::cout << std::endl;
		}
		v.push_back(1);
	}*/

	// vector가 가장 싫어하는 동작 ? = 이사가는거.. (크기가 고정되는 순간이 좋음)
	// vector의 할당 할 수 잇는 크기가 아직 남아있을때 push_back을 하면 o(1) 시간복잡도를 나타냄.
	// 만약에 할당 할 수 있는 크기가 부족하다면 이사 가면서 (복사) 하고 insert함과 동시에 크기를 재할당함 (더크게)
	// vector는 insert와 같은 동작은 사용하면 안좋음?


	std::vector<STRING> v2;

	//std::cout << "size     - " << v2.size() << std::endl;
	//std::cout << "capacity - " << v2.capacity() << std::endl;
	//std::cout << "data     - " << (void*) & v2[0] << std::endl;

	//std::cout << "원소 1개 추가 후" << std::endl;

	//v2.push_back("123");

	//std::cout << "size     - " << v2.size() << std::endl;
	//std::cout << "capacity - " << v2.capacity() << std::endl;
	//std::cout << "data     - " << (void*)&v2[0] << std::endl;

	/*for (int i = 0; i < 1000; ++i) {
		if (v2.capacity() != old) {
			std::cout << "--------------------------------" << std::endl;
			std::cout << "이전 크기 - " << old << std::endl;
			std::cout << "새로 할당받은 크기 - " << v2.capacity() << std::endl;
			old = v2.capacity();
			std::cout << std::endl;
		}
		v2.push_back("123");	
	}*/


	// emplace_back(STRING{"123"}); -> 이와 같은 코드는 STRING에서 생성하고 이동생성하는 코드임
	// emplace_back("123"); -> 이 코드는 값만 주고 이동생성자도 호출하지 않음


	std::vector<int> v3{ 1,2,3,4,5 };
	// [문제] vector v3에서 3을 제거하라.

	for (int num : v3) {
		std::cout << num << " ";
	}

	//v3.erase(std::find(v3.begin(), v3.end(), 3));

	//auto new_end = std::remove(v3.begin(), v3.end(), 3); // vector와 같은 stl이 다른 알고리즘이 와서 삭제하면 안되는데 이런 행위를 ocp라고함
	//v3.erase(std::remove(v3.begin(), v3.end(), 3), v3.end()); // -> erase-remove idiom

	//std::erase(v3, 3); // c++ 20에서 제공하는 전역함수 // syntactic sugar

	std::cout << std::endl;

	/*for (int num : v3) {
		std::cout << num << " ";
	}*/


	// vector라는 자료구조에 remove라는 알고리즘을 사용하려는 상황.
	// remove 알고리즘의 동작 방식은 v3의 시작 지점부터 ~ v3의 끝 지점까지 돌게됨.
	// 제거 해야될 값을 (4)를 찾게 되면 제거함.
	// 그런데 remove는 제거하는게 아니라 지우고 남은 원소를 앞으로 당기는 알고리즘임.
	// vector로서 가져야할 자료의 일관성이 망가짐.

	// 25.04.22 이어서.
	

	// [문제] v3에서 홀수를 제거하라.

	std::erase_if(v3, [](int num) {
		//std::cout << num << " ";
		return num &1; }); // num&1 이거는 num % 2 == 1과 같음 (홀수)

	for (int num : v3) {
		std::cout << num << " ";
	}
	std::cout << std::endl;

	std::vector<STRING> v_s{ "1","22","333","4444","55555" };

	// [문제] v_s에서 "333"을 제거하라.

	std::erase(v_s, "333");

	for (const auto& str : v_s) {
		std::cout << str << std::endl;
	}

}