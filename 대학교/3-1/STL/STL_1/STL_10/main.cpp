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

	std::cout << "v�� ��� �ִ� ������ Ÿ�� - " << typeid(std::vector<int>::value_type).name() << std::endl;*/

	
	std::array<int, 5> a{ 1,2,3,4,5 };

	for (int i = -100; i < 100; ++i) {
		std::cout << a[i] << std::endl;
	} // �� �ڵ�� ���������� ���ư� (�޸� �ּ� ���� ���������� c++�� ���������� ����� �����ϵ��� ��)

	// �� �˻縦 �ؾ߰ڴٸ�? 
	//while (true) {
	//	std::cout << "�� ��° ���� ���ϳ��� ? ";
	//	int num;
	//	std::cin >> num;

	//	try {
	//		std::cout << a.at(num) << std::endl; // at(num) - ����ó����.
	//	}
	//	catch (const std::exception& e) {
	//		std::cout << e.what() << std::endl;
	//	}
	//}

	// ;
	//std::vector<int>* v_a = new std::vector<int> v2{ 1,2,3 };

	//std::cout << "v2�� ũ�� - " << sizeof(v2) << std::endl;
	//std::cout << "v2�� �ּ� - " << std::addressof(v2) << std::endl;
	//std::cout << "v3�� �ּ� - " << std::addressof(v3) << std::endl;
	//std::cout << "v2�� Ÿ�� - " << typeid(v2).name() << std::endl;
	//
	//std::cout << "v_a�� ũ�� - " << sizeof(v_a) << std::endl;
	//std::cout << "v_a�� �ּ� - " << std::addressof(v_a) << std::endl;
	//std::cout << "v_a�� Ÿ�� - " << typeid(v_a).name() << std::endl;

	std::vector<int> v{ 1,2,3 };

	v.push_back(4);

	for (int num : v) {
		std::cout << num << " ";
	}

	std::cout << std::endl;		
	
}