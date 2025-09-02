//-------------------------------------------------
// 2025. STL 3.24                           4w 1d
//-------------------------------------------------
// 
//-------------------------------------------------
// 동적 할당과 스마트 포인터 - RAII
// 자원의 생명주기를 객체의 생명주기와 일치시키는 프로그래밍 기법
//-------------------------------------------------
// 다음시간 - callable 
//


#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <vector>
#include <algorithm>
#include <numeric>

#include <memory>


//int main() {
//	// [문제] 양의 정수 num(int의 max값까진 받자)을 입력받아라.
//	// num개 만큼 int를 저장할 메모리를 확보하라.
//	// 메모리의 내용을 1부터 시작하는 정수로 채워라.
//	// 메모리에 저장한 int의 합계를 출력하라.
//	// 이 과정을 영원히 반복하라.
//
//
//	while (true) {
//		/*std::cout << "값을 입력하세요 : ";
//		int num;
//		std::cin >> num;
//
//		std::vector<int> array;
//		array.reserve(num);
//
//		for (int i = 0; i < num; ++i) {
//			array.push_back(i + 1);
//		}
//
//		int result = 0;
//
//		for (int i = 0; i < array.size(); ++i) {
//			result += array[i];
//		}
//
//		std::cout << "1부터 " << num << " 까지 합계입니다 - "<< result << std::endl;*/
//
//		// 교수님 코드 -----------------------------------------------------------------
//
//		std::cout << "값을 입력하세요 : ";
//		int num;
//		std::cin >> num;
//		int* p;
//		try {
//			p = new int[num]; // free-store, HEAP(c++에선 HEAP이라고 부르지 않는다 강조하심;) // 내 의지와 상관없이 시스템이 할당하는거라 오류가 발생할 수 있음
//		}
//		catch (const std::exception& e) {
//			std::cout << e.what() << std::endl;
//			return 0;
//		}
//
//		std::iota(p, p + num, 1);			// iota = <numeric>
//
//		//long long int sum{}; // int 만 쓰면 10만쓰면 오버플로우 나오니깐 long타입
//		// long double -> 젤큼 (자리수를 양보?하면서 크기를 키움)
//
//		long long sum = std::accumulate(p, p + num, 0LL); // 마지막 인자가 0이기 때문에 int라고 인식하기 때문에 LL타입을 붙여줘야함 (LL 빼면 오류남)
//
//		std::cout << "1부터 " << num << " 까지 합계입니다 - " << sum << std::endl;
//
//		delete[] p; // 해제 하는거 까먹지말기.
//
//		// delete[] p; 이렇게 두번 해제하는거 댕글링포인터 (바로죽음)
//		
//	}
//
//}


//---------------------------------------------------------------------------------------------------

//class Dog {
//public:
//	Dog() {
//		std::cout << "멍~멍~" << std::endl;
//	}
//	~Dog() {
//		std::cout << "꿱" << std::endl;
//	}
//};
//
//class 스마트 {
//	Dog* p;
//public:
//	스마트(Dog* p) : p{ p } {} // RAII 클래스의 생명주기를 내부 객체의 생명주기와 일치하도록 하는것(핸들러가 사용하는동안 자원이 잇다가 핸들러 사라지면 자원도 없어지는것)
//
//	~스마트() {
//		std::cout << "예외가 발생하더라도 지역객체는 반드시 소멸됨을 보장함 (stack unwinding)" << std::endl;
//		delete p;
//	}
//};
//
//void f() {
//	//int* p;
//	//p = new int[10];// {}붙이면 싹다 0으로 초기화
//
//	///*std::cout << "번지 - " << p << " - ";
//	//for (int i = 0; i < 10; ++i) {
//	//	std::cout << p[i] << " ";
//	//}
//	//std::cout << std::endl;*/
//
//	//throw 123123; // 이렇게 예외가 발생하면 C++은 스택에 만들어진 객체 p를 없애버림. (만약에 p가 클래스면 소멸자 호출해서 할당한걸 해제함)
//	//// 예외 발생 시, 해당 함수의 스택을 정리하는걸 = 스택 언와인딩 이라고 부름
//
//	//std::cout << "이 문장이 출력될 일은 전혀 없다." << std::endl;
//
//	//delete[] p;
//
//	//----
//
//	스마트 p{ new Dog }; // 이게 초기화임 // RAII
//
//	/*스마트 p;
//	p = { new Dog };*/ // 이렇게 하지마라 위에처럼 해야됨. 할당연산자임 이건
//	std::unique_ptr<Dog> p2 = std::make_unique<Dog>(); // 표준 스마트 포인터 // make_unique = 동적할당 ( new Dog ) 대신씀
//	std::unique_ptr<Dog[]> p3 = std::make_unique<Dog[]>(100);  // 배열 필요할때.
//
//
//	throw 123123;
//	std::cout << "이 문장이 출력될 일은 전혀 없다." << std::endl;
//
//}
//
//int main() {
//
//	try {
//		f(); // 함수 호출하면 f만의 스택이 생성됨. 함수가 정상 종료되면 스택안에 있던 지역 변수들은 스택에서 만들어진 것들이 없어짐.
//	}
//	catch (...) {
//
//	}
//
//	std::cout << "메인은 잘 끝날까?" << std::endl;
//}

//---------------------------------------------------------------------------------------------------------------------------
//
// [문제] "메인.cpp"에 있는 소문자를 모두 대문자로 바꿔 "메인 대문자.cpp"에 저장하라.
//

int main() {
	/*std::ifstream in{ "main.cpp" };

	std::vector<char> c;
	char c1;
	while (in >> c1) {
		c.push_back(c1);
	}

	for (char& c2 : c) {
		c2 = toupper(c2);
	}

	std::ofstream out{ "upper main.cpp" };

	out.write(c.data(), c.size() * sizeof(char));*/

	// ----------------------교수님 코드 ----------------------------------

	std::ifstream in{ "main.cpp" };
	if (not in)
		return 0;

	std::ofstream out{ "upper main.cpp" };
	
	//char c;
	//in >> std::noskipws; //빈공간도 처리해줘
	//while (in >> c) {
	//	c = toupper(c);
	//	out << c;
	//}

	std::transform(std::istreambuf_iterator<char>{in}, {}, std::ostreambuf_iterator<char>{out}, [](char c) {
		return toupper(c);
		});

}