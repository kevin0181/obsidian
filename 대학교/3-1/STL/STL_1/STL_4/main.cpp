//-------------------------------------------------
// 2025. STL 3.18                           3w 1d
//-------------------------------------------------
// 많은 개수 자료 처리하기 - 파일 입출력
//						   - 바이너리 모드와 저수준 입출력
// 
//-------------------------------------------------
// [질문] 지난 시간에 int값 1000개를 저장하였다.
// 파일에서 사용한 바이트 수를 확인해보자. - 8250 바이트를 사용했다
//-------------------------------------------------
// 메모장
//
//

#include <fstream>
#include <iostream>
#include <string>
#include <array>
#include <algorithm>
#include <iterator>
#include <print>
#include <bitset> // 2진수로 출력하기 위해 사용
#include <numeric>
#include <random>

int main() {
	std::array<int, 1000>arr;
	std::cout << "a가 사용하는 메모리 크기 - " << sizeof(arr) << "바이트" << std::endl; 
	// 이거 찍으면 4000바이트가 나오는데 메모장으로 1000개 int 저장할땐 8000바이트가 나왔는데 왜 그럴까? 비효율적인데.


	int num{ 0x01020304 };
	std::cout << "num이 사용하는 메모리 크기 - " << sizeof(num) << "바이트" << std::endl;
	
	
	/*std::cout << " 2진수 - " << std::bitset<sizeof(int) * 8>(num) << std::endl;
	std::cout << "10진수 - " << num << std::endl;
	std::cout << "16진수 - 0x" << std::hex << num << std::endl;*/
	
	// 어떤 int 값이 들어갈때 필요한 메모리는 몇바이트인가? 평균으로.

	// [문제] int 값 1000개를 저수준 출력함수를 사용하여 메모리 크기 그대로 파일에 기록한다.
	// 파일 "int 천개를 메모리그대로 기록"에 기록한다.
	// -> 메모리에 있는 bit를 그대로 파일에 기록한다.

	std::ofstream out{ "int 천개를 메모리그대로 기록", std::ios::binary }; //std::ios::binary를 써줘서 이진모드로 저장해줘야함 (바이너리 모드로 그대로씀)
	if (not out)
		return 0;

	std::array<int, 1000>a;

	//windows에서 0x0A(line feed)를 어떻게 변환하는가 -> 0x0D 0x0A로 변환한다.
	a.fill(10); // -> 위에 바이너리 모드안하면. 윈도우에서는 10 같은 경우 마지막에 0A로 저장됨. 10진수로 저장되는게 아니라 16진수로 저장됨.

	//std::iota(a.begin(), a.end(), 1); // 0부터 1000까지 순차적으로 채워넣는다. // 이렇게 저장하면 4000byte가 나옴
	// 저수준 함수로 기록한다.
	out.write((char*)a.data(), sizeof(int) * a.size());


	//------------------------------------------------------------------------------------

	std::ofstream out2{ "진짜 랜덤",std::ios::binary };
	std::random_device rd{};
	std::uniform_int_distribution<int>uid{ 0,100 };
	int num2;
	for (int i = 0; i < 100000; ++i) {
		num2 = rd();
		out2.write((char*)&num2, sizeof(int));
	}
	
	//------------------------------------------------------------------------------------
	// 시험? [문제] e-class에서 다운 받은 "진짜 랜덤" 파일에는 int값 10만개가 있다.
	// 파일은 binary mode로 열었고, write 함수를 사용하여 int 값을 기록하였다.
	// int 값 10만개 전체를 메모리로 읽어와라.
	// 가장 큰 값과 작은 값을 찾아 화면에 출력하라.
	// 출력된 값도 답지에 적어라. (10점)

	std::ifstream in2{ "진짜 랜덤", std::ios::binary };

	if (not in2) {
		std::cerr << "파일을 열 수 없습니다." << std::endl;
		return 0;
	}

	std::array<int, 100000>arr2;
	in2.read((char*)arr2.data(), sizeof(int) * arr2.size());

	for (int i = 0; i < 10000; ++i) {
		in2 >> arr2[i];
	}

	int max_value = *std::max_element(arr2.begin(), arr2.end());
	int min_value = *std::min_element(arr2.begin(), arr2.end());

	std::cout << "가장 큰 값 : " << max_value << std::endl;
	std::cout << "가장 작은 값 : " << min_value << std::endl;

	//복습-------교수님꺼----------------------------------

	std::ifstream in3{ "진짜 랜덤", std::ios::binary };
	if (not in3)
		return 0;

	int num3;
	size_t cnt{};
	while (in3.read((char*)&num, sizeof(int))) {
		++cnt;
	}

	std::cout << "읽은 데이터 개수 : " << cnt << std::endl;

	std::array<int, 100000>arr3;
	in3.read((char*)arr3.data(), sizeof(int) * arr3.size());

	//std::cout << "가장 큰 값 : " << *std::max_element(arr3.begin(), arr3.end()) << std::endl;		// o(N)
	//std::cout << "가장 작은 값 : " << *std::min_element(arr3.begin(), arr3.end()) << std::endl;		// o(N)

	
	auto [min_,max_] = std::minmax_element(arr3.begin(), arr3.end());
	// structured-binding

	std::cout << "최솟값 - " << *min_ << std::endl;
	std::cout << "최댓값 - " << *max_ << std::endl;
	//안되는거같은데..?

}