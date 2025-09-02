//-------------------------------------------------
// 2025. STL 3.13                            1w 2d
//-------------------------------------------------
// 파일에 저장하고 읽어오기
//-------------------------------------------------
// [문제 1] 랜덤 int 값 1000개를 화면에 출력하라. 출력값을 8칸에 맞춰라.
// 랜덤 int 값 1000개를 메모리에 저장해라. (이거 반드시 순서대로 저장하고)
// 저장된 값 중에서 가장 큰 값을 찾아라. (또 다시 for문 돌려서 큰값찾아야함 아니면 0점이래 병신	)ㅉㅉ
// 찾은 값을 화면에 출력하라. 
// 
// -------------------------------------------------
// 메모장
//	Pseudo -random number generator 랜덤은 컴퓨터가 만들어낸 수식임, 뭔가 패턴이잇는데 맞추기 어렵
//	rand() -> C언어에서 제공하는 랜덤 함수 0~32767까지의 수를 생성, 추적 가능
//	우리가 사용하는 엔진 -> mersenne_twister_engine에서  mt19937_64 엔진 사용
// 


#include <iostream>
#include <random>
#include <print>
#include <vector>
#include <array> // STL sequence container 중 하나. (이거 쓰셈)
#include <algorithm>
#include <fstream>

//std::default_random_engine dre{ std::random_device{}() };			// 랜덤 엔진
std::default_random_engine dre{};
std::uniform_int_distribution<int> uid{ 0, 999'9999 };					// 엔진의 결과를 특정 분포로 가공

int main() {

	//int a[1000]; // 매우 위험한 데이터 -> 안전배열이 나오게 된 이유? (safe array)
	std::array <int, 1000> random_num; // 안전배열
	//std::vector<int> random_num;

	for (int i = 0; i < 1000; ++i)
		//std::print("{:8}", uid(dre)); //{:^80} -> 가운데 정렬 / {:<80} -> 좌측 정렬
		//random_num.push_back(uid(dre));
		random_num[i] = uid(dre);
	
	//int maxValue{ std::numeric_limits<int>::min() }; // 이거 써야댐 0 쓰면안댐;

	//for (int num : random_num) {
	//	if (num > maxValue)
	//		maxValue = num;
	//}

	// max_element return 값은 위치를 반환하기 때문에 *를 붙여서 값을 반환해야함
	auto maxAdress = std::max_element(random_num.begin(), random_num.end()); // 이게 가능한 이유?(시작,끝) 가장 작다는 자료형이 미리 정의해 뒀기 때문임.

	std::cout << "가장 큰 값 : " << *maxAdress << std::endl;

	//---------------------------------------------------------------------------
	// [문제 2] a에 있는 값을 파일 "int 1000개.txt"에 텍스트 그대로 저장하라.
	// 화면 출력한 것과 같은 형태로 - 파일을 열었을때 int값을 사람이 읽을 수 있도록
	//---------------------------------------------------------------------------

	std::array<int, 1000> a;
	for (int i = 0; i < 1000; ++i)
		a[i] = uid(dre);

	/*std::ofstream out{ "int 1000개.txt", std::ios::app };

	std::copy(a.begin(), a.end(), std::ostream_iterator<int>{out, " "});*/

	// 교수님이 짠거
	//std::ofstream out2{ "int 1000개.txt" }; // RAII (out.close()를 안해도 되도록 하게끔 만들어줌)

	//int i{};
	//for (int num : a)
	//{
	//	std::print(out2, "{:8}", num); // 이게 저장이되네..?
	//	if (not (++i % 8))
	//		out2 << std::endl;
	//}
	
	//---------------------------------------------------------------------------
	//[문제3] 파일 "int 1000개.txt"에는 int값 1000개가 text mode로 기록되어 있다.
	// 값을 읽어 화면에 출력하라.
	//---------------------------------------------------------------------------

	/*std::ifstream in{ "int 1000개.txt" };
	if (not in)
	{
		std::cout << "파일을 열 수 없습니다." << std::endl;
		exit(0);
	}

	int getNum{};
	while (in >> getNum)
		std::print("{:8}", getNum);*/
	
	// 교수님이 짠코드
	/*std::ifstream in{ "int 1000개.txt" };
	if (not in)
		return 0;
	
	int num;
	int i_1{};
	while (in >> num)
	{
		std::print("{:8}", num);
		++i_1;
	}

	std::cout << std::endl << i_1 << "개의 데이터를 읽었습니다." << std::endl;*/

	//---------------------------------------------------------------------------
	//[문제 4] 가장 큰 값을 찾아 화면에 출력하라.
	//---------------------------------------------------------------------------
	
	/*std::ifstream in{ "int 1000개.txt" };
	if (not in)
		return 0;

	int num;
	int maxValue{ std::numeric_limits<int>::min() };
	while (in >> num)
	{
		if (num > maxValue)
			maxValue = num;
	}

	std::cout << "가장 큰 값 : " << maxValue << std::endl;*/
	
	//교수님이 짠 코드

	std::ifstream in{ "int 1000개.txt" };
	if (not in)
		return 0;

	auto position = std::max_element(std::istream_iterator<int> {in}, {});

	std::cout << "가장 큰 값 : " << *position << std::endl;


	//------------------------------------------------------------------------------------------
	// 복습
	//[문제] 파일 "int 1000개.txt"에는 int 값 1000개가 text mode로 기록되어있다.
	// 메모리로 다 읽어와라.
	// 가장 큰값을 찾아 화면에 출력하라.
	// 화면에 출력된 큰 값을 답지에 적어라.

	std::ifstream in{ "int 1000개.txt" };
	if (not in)
		return 0;

	int num;

	std::array<int, 1000> arr;

	for (int i = 0; i < 1000; ++i) {
		in >> arr[i];
	}

	std::cout << "가장 큰 값 : " << *std::max_element(arr.begin(), arr.end()) << std::endl;

	// 교수님이 짠 코드
	// 어떤 값이 결정되는 시점 = 1. 컴파일 때 알 수 있다. 2. 실행해 봐야 알 수 있다.
	// 1. compile time 2. runtime
	// 1. constexpr, const
	// std::array<int, 1000> arr{}; = 0으로 초기화하는게 아니고 default로 초기화 하는거임 (default 초기화)
	// std::array<int, 1000> arr{0}; = 맨 앞에 한개만 0으로 초기화하는거임.
	// arr.fill(0); = 모든 값을 0으로 초기화 하는거임. (이런 장점이 있음)
	// 
	// 시간의 연속성 = continuous (stl 핵심단어)
	// 공간의 연속성 = contiguous (stl 핵심단어)
	// array에는 이 공간의 연속성이 꼭 있어야함.
	//


	std::copy(std::istream_iterator<int>{in}, {}, arr.begin());
	// 정렬 추가
	std::sort(arr.begin(), arr.end());
	//std::ranges::sort(arr);
	for (int num : arr) {
		std::print("{:8}", num);
	}

	std::cout << " " << *std::max_element(arr.begin(), arr.end()) << std::endl;

}