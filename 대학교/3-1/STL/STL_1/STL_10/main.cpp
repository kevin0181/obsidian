//-------------------------------------------------
// 2025. STL 4.15                           7w 1d
//-------------------------------------------------
// STL Containers - Containers are objects that store other objects.
// array<T,N> 
// vector<T>	- dynamic(run-time) array
//-------------------------------------------------
// 
//-------------------------------------------------
// 
//

#include <iostream>
#include <vector>
#include <array>

std::vector<int> v3{ 1,2,3 };

int main() {


	/*std::vector<int> v;

	std::cout << "v가 담고 있는 원소의 타입 - " << typeid(std::vector<int>::value_type).name() << std::endl;*/

	
	std::array<int, 5> a{ 1,2,3,4,5 };

	for (int i = -100; i < 100; ++i) {
		std::cout << a[i] << std::endl;
	} // 이 코드는 정상적으로 돌아감 (메모리 주소 값이 나오겠지만 c++은 정상적으로 출력이 가능하도록 함)

	// 꼭 검사를 해야겠다면? 
	//while (true) {
	//	std::cout << "몇 번째 값을 원하나요 ? ";
	//	int num;
	//	std::cin >> num;

	//	try {
	//		std::cout << a.at(num) << std::endl; // at(num) - 예외처리함.
	//	}
	//	catch (const std::exception& e) {
	//		std::cout << e.what() << std::endl;
	//	}
	//}

	// ;
	//std::vector<int>* v_a = new std::vector<int> v2{ 1,2,3 };

	//std::cout << "v2의 크기 - " << sizeof(v2) << std::endl;
	//std::cout << "v2의 주소 - " << std::addressof(v2) << std::endl;
	//std::cout << "v3의 주소 - " << std::addressof(v3) << std::endl;
	//std::cout << "v2의 타입 - " << typeid(v2).name() << std::endl;
	//
	//std::cout << "v_a의 크기 - " << sizeof(v_a) << std::endl;
	//std::cout << "v_a의 주소 - " << std::addressof(v_a) << std::endl;
	//std::cout << "v_a의 타입 - " << typeid(v_a).name() << std::endl;

	std::vector<int> v{ 1,2,3 };

	v.push_back(4);

	for (int num : v) {
		std::cout << num << " ";
	}

	std::cout << std::endl;		
	
}