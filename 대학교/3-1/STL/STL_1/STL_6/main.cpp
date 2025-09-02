//-------------------------------------------------
// 2025. STL 3.24                           4w 1d
//-------------------------------------------------
// 
//-------------------------------------------------
// ���� �Ҵ�� ����Ʈ ������ - RAII
// �ڿ��� �����ֱ⸦ ��ü�� �����ֱ�� ��ġ��Ű�� ���α׷��� ���
//-------------------------------------------------
// �����ð� - callable 
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
//	// [����] ���� ���� num(int�� max������ ����)�� �Է¹޾ƶ�.
//	// num�� ��ŭ int�� ������ �޸𸮸� Ȯ���϶�.
//	// �޸��� ������ 1���� �����ϴ� ������ ä����.
//	// �޸𸮿� ������ int�� �հ踦 ����϶�.
//	// �� ������ ������ �ݺ��϶�.
//
//
//	while (true) {
//		/*std::cout << "���� �Է��ϼ��� : ";
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
//		std::cout << "1���� " << num << " ���� �հ��Դϴ� - "<< result << std::endl;*/
//
//		// ������ �ڵ� -----------------------------------------------------------------
//
//		std::cout << "���� �Է��ϼ��� : ";
//		int num;
//		std::cin >> num;
//		int* p;
//		try {
//			p = new int[num]; // free-store, HEAP(c++���� HEAP�̶�� �θ��� �ʴ´� �����Ͻ�;) // �� ������ ������� �ý����� �Ҵ��ϴ°Ŷ� ������ �߻��� �� ����
//		}
//		catch (const std::exception& e) {
//			std::cout << e.what() << std::endl;
//			return 0;
//		}
//
//		std::iota(p, p + num, 1);			// iota = <numeric>
//
//		//long long int sum{}; // int �� ���� 10������ �����÷ο� �����ϱ� longŸ��
//		// long double -> ��ŭ (�ڸ����� �纸?�ϸ鼭 ũ�⸦ Ű��)
//
//		long long sum = std::accumulate(p, p + num, 0LL); // ������ ���ڰ� 0�̱� ������ int��� �ν��ϱ� ������ LLŸ���� �ٿ������ (LL ���� ������)
//
//		std::cout << "1���� " << num << " ���� �հ��Դϴ� - " << sum << std::endl;
//
//		delete[] p; // ���� �ϴ°� ���������.
//
//		// delete[] p; �̷��� �ι� �����ϴ°� ��۸������� (�ٷ�����)
//		
//	}
//
//}


//---------------------------------------------------------------------------------------------------

//class Dog {
//public:
//	Dog() {
//		std::cout << "��~��~" << std::endl;
//	}
//	~Dog() {
//		std::cout << "��" << std::endl;
//	}
//};
//
//class ����Ʈ {
//	Dog* p;
//public:
//	����Ʈ(Dog* p) : p{ p } {} // RAII Ŭ������ �����ֱ⸦ ���� ��ü�� �����ֱ�� ��ġ�ϵ��� �ϴ°�(�ڵ鷯�� ����ϴµ��� �ڿ��� �մٰ� �ڵ鷯 ������� �ڿ��� �������°�)
//
//	~����Ʈ() {
//		std::cout << "���ܰ� �߻��ϴ��� ������ü�� �ݵ�� �Ҹ���� ������ (stack unwinding)" << std::endl;
//		delete p;
//	}
//};
//
//void f() {
//	//int* p;
//	//p = new int[10];// {}���̸� �ϴ� 0���� �ʱ�ȭ
//
//	///*std::cout << "���� - " << p << " - ";
//	//for (int i = 0; i < 10; ++i) {
//	//	std::cout << p[i] << " ";
//	//}
//	//std::cout << std::endl;*/
//
//	//throw 123123; // �̷��� ���ܰ� �߻��ϸ� C++�� ���ÿ� ������� ��ü p�� ���ֹ���. (���࿡ p�� Ŭ������ �Ҹ��� ȣ���ؼ� �Ҵ��Ѱ� ������)
//	//// ���� �߻� ��, �ش� �Լ��� ������ �����ϴ°� = ���� ����ε� �̶�� �θ�
//
//	//std::cout << "�� ������ ��µ� ���� ���� ����." << std::endl;
//
//	//delete[] p;
//
//	//----
//
//	����Ʈ p{ new Dog }; // �̰� �ʱ�ȭ�� // RAII
//
//	/*����Ʈ p;
//	p = { new Dog };*/ // �̷��� �������� ����ó�� �ؾߵ�. �Ҵ翬������ �̰�
//	std::unique_ptr<Dog> p2 = std::make_unique<Dog>(); // ǥ�� ����Ʈ ������ // make_unique = �����Ҵ� ( new Dog ) ��ž�
//	std::unique_ptr<Dog[]> p3 = std::make_unique<Dog[]>(100);  // �迭 �ʿ��Ҷ�.
//
//
//	throw 123123;
//	std::cout << "�� ������ ��µ� ���� ���� ����." << std::endl;
//
//}
//
//int main() {
//
//	try {
//		f(); // �Լ� ȣ���ϸ� f���� ������ ������. �Լ��� ���� ����Ǹ� ���þȿ� �ִ� ���� �������� ���ÿ��� ������� �͵��� ������.
//	}
//	catch (...) {
//
//	}
//
//	std::cout << "������ �� ������?" << std::endl;
//}

//---------------------------------------------------------------------------------------------------------------------------
//
// [����] "����.cpp"�� �ִ� �ҹ��ڸ� ��� �빮�ڷ� �ٲ� "���� �빮��.cpp"�� �����϶�.
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

	// ----------------------������ �ڵ� ----------------------------------

	std::ifstream in{ "main.cpp" };
	if (not in)
		return 0;

	std::ofstream out{ "upper main.cpp" };
	
	//char c;
	//in >> std::noskipws; //������� ó������
	//while (in >> c) {
	//	c = toupper(c);
	//	out << c;
	//}

	std::transform(std::istreambuf_iterator<char>{in}, {}, std::ostreambuf_iterator<char>{out}, [](char c) {
		return toupper(c);
		});

}