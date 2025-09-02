//-------------------------------------------------
// 2025. STL 3.13                            1w 2d
//-------------------------------------------------
// ���Ͽ� �����ϰ� �о����
//-------------------------------------------------
// [���� 1] ���� int �� 1000���� ȭ�鿡 ����϶�. ��°��� 8ĭ�� �����.
// ���� int �� 1000���� �޸𸮿� �����ض�. (�̰� �ݵ�� ������� �����ϰ�)
// ����� �� �߿��� ���� ū ���� ã�ƶ�. (�� �ٽ� for�� ������ ū��ã�ƾ��� �ƴϸ� 0���̷� ����	)����
// ã�� ���� ȭ�鿡 ����϶�. 
// 
// -------------------------------------------------
// �޸���
//	Pseudo -random number generator ������ ��ǻ�Ͱ� ���� ������, ���� �������մµ� ���߱� ���
//	rand() -> C���� �����ϴ� ���� �Լ� 0~32767������ ���� ����, ���� ����
//	�츮�� ����ϴ� ���� -> mersenne_twister_engine����  mt19937_64 ���� ���
// 


#include <iostream>
#include <random>
#include <print>
#include <vector>
#include <array> // STL sequence container �� �ϳ�. (�̰� ����)
#include <algorithm>
#include <fstream>

//std::default_random_engine dre{ std::random_device{}() };			// ���� ����
std::default_random_engine dre{};
std::uniform_int_distribution<int> uid{ 0, 999'9999 };					// ������ ����� Ư�� ������ ����

int main() {

	//int a[1000]; // �ſ� ������ ������ -> �����迭�� ������ �� ����? (safe array)
	std::array <int, 1000> random_num; // �����迭
	//std::vector<int> random_num;

	for (int i = 0; i < 1000; ++i)
		//std::print("{:8}", uid(dre)); //{:^80} -> ��� ���� / {:<80} -> ���� ����
		//random_num.push_back(uid(dre));
		random_num[i] = uid(dre);
	
	//int maxValue{ std::numeric_limits<int>::min() }; // �̰� ��ߴ� 0 ����ȴ�;

	//for (int num : random_num) {
	//	if (num > maxValue)
	//		maxValue = num;
	//}

	// max_element return ���� ��ġ�� ��ȯ�ϱ� ������ *�� �ٿ��� ���� ��ȯ�ؾ���
	auto maxAdress = std::max_element(random_num.begin(), random_num.end()); // �̰� ������ ����?(����,��) ���� �۴ٴ� �ڷ����� �̸� ������ �ױ� ������.

	std::cout << "���� ū �� : " << *maxAdress << std::endl;

	//---------------------------------------------------------------------------
	// [���� 2] a�� �ִ� ���� ���� "int 1000��.txt"�� �ؽ�Ʈ �״�� �����϶�.
	// ȭ�� ����� �Ͱ� ���� ���·� - ������ �������� int���� ����� ���� �� �ֵ���
	//---------------------------------------------------------------------------

	std::array<int, 1000> a;
	for (int i = 0; i < 1000; ++i)
		a[i] = uid(dre);

	/*std::ofstream out{ "int 1000��.txt", std::ios::app };

	std::copy(a.begin(), a.end(), std::ostream_iterator<int>{out, " "});*/

	// �������� §��
	//std::ofstream out2{ "int 1000��.txt" }; // RAII (out.close()�� ���ص� �ǵ��� �ϰԲ� �������)

	//int i{};
	//for (int num : a)
	//{
	//	std::print(out2, "{:8}", num); // �̰� �����̵ǳ�..?
	//	if (not (++i % 8))
	//		out2 << std::endl;
	//}
	
	//---------------------------------------------------------------------------
	//[����3] ���� "int 1000��.txt"���� int�� 1000���� text mode�� ��ϵǾ� �ִ�.
	// ���� �о� ȭ�鿡 ����϶�.
	//---------------------------------------------------------------------------

	/*std::ifstream in{ "int 1000��.txt" };
	if (not in)
	{
		std::cout << "������ �� �� �����ϴ�." << std::endl;
		exit(0);
	}

	int getNum{};
	while (in >> getNum)
		std::print("{:8}", getNum);*/
	
	// �������� §�ڵ�
	/*std::ifstream in{ "int 1000��.txt" };
	if (not in)
		return 0;
	
	int num;
	int i_1{};
	while (in >> num)
	{
		std::print("{:8}", num);
		++i_1;
	}

	std::cout << std::endl << i_1 << "���� �����͸� �о����ϴ�." << std::endl;*/

	//---------------------------------------------------------------------------
	//[���� 4] ���� ū ���� ã�� ȭ�鿡 ����϶�.
	//---------------------------------------------------------------------------
	
	/*std::ifstream in{ "int 1000��.txt" };
	if (not in)
		return 0;

	int num;
	int maxValue{ std::numeric_limits<int>::min() };
	while (in >> num)
	{
		if (num > maxValue)
			maxValue = num;
	}

	std::cout << "���� ū �� : " << maxValue << std::endl;*/
	
	//�������� § �ڵ�

	std::ifstream in{ "int 1000��.txt" };
	if (not in)
		return 0;

	auto position = std::max_element(std::istream_iterator<int> {in}, {});

	std::cout << "���� ū �� : " << *position << std::endl;


	//------------------------------------------------------------------------------------------
	// ����
	//[����] ���� "int 1000��.txt"���� int �� 1000���� text mode�� ��ϵǾ��ִ�.
	// �޸𸮷� �� �о�Ͷ�.
	// ���� ū���� ã�� ȭ�鿡 ����϶�.
	// ȭ�鿡 ��µ� ū ���� ������ �����.

	std::ifstream in{ "int 1000��.txt" };
	if (not in)
		return 0;

	int num;

	std::array<int, 1000> arr;

	for (int i = 0; i < 1000; ++i) {
		in >> arr[i];
	}

	std::cout << "���� ū �� : " << *std::max_element(arr.begin(), arr.end()) << std::endl;

	// �������� § �ڵ�
	// � ���� �����Ǵ� ���� = 1. ������ �� �� �� �ִ�. 2. ������ ���� �� �� �ִ�.
	// 1. compile time 2. runtime
	// 1. constexpr, const
	// std::array<int, 1000> arr{}; = 0���� �ʱ�ȭ�ϴ°� �ƴϰ� default�� �ʱ�ȭ �ϴ°��� (default �ʱ�ȭ)
	// std::array<int, 1000> arr{0}; = �� �տ� �Ѱ��� 0���� �ʱ�ȭ�ϴ°���.
	// arr.fill(0); = ��� ���� 0���� �ʱ�ȭ �ϴ°���. (�̷� ������ ����)
	// 
	// �ð��� ���Ӽ� = continuous (stl �ٽɴܾ�)
	// ������ ���Ӽ� = contiguous (stl �ٽɴܾ�)
	// array���� �� ������ ���Ӽ��� �� �־����.
	//


	std::copy(std::istream_iterator<int>{in}, {}, arr.begin());
	// ���� �߰�
	std::sort(arr.begin(), arr.end());
	//std::ranges::sort(arr);
	for (int num : arr) {
		std::print("{:8}", num);
	}

	std::cout << " " << *std::max_element(arr.begin(), arr.end()) << std::endl;

}