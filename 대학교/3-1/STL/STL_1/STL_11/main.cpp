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

// [����] vector�� ��� free-store�� �޸𸮸� �����ϴ��� �˾ƺ���.

int main() {
	std::vector<int> v;

	
	/*for (int i = 0; i < 10; ++i) {
		std::cout << i << std::endl;
		std::cout << "���� ������ ����                       - " << v.size() << std::endl;
		std::cout << "���Ҵ� ���� ������ �� �ִ� ������ ���� - " << v.capacity() << std::endl;
		std::cout << "�����ϴ� �޸��� ���۹���             - " << v.data() << std::endl;

		v.push_back(i + 1);

		std::cout << std::endl;
	}*/

	size_t old{ v.capacity() };

	// VS�� vector�� �޸� ũ�⸦ ��� �ٲٳ�?
	/*for (int i = 0; i < 1000; ++i) {
		if (v.capacity() != old) {
			std::cout << "--------------------------------" << std::endl;
			std::cout << "���� ũ�� - " << old << std::endl;
			std::cout << "���� �Ҵ���� ũ�� - " << v.capacity() << std::endl;
			old = v.capacity();
			std::cout << std::endl;
		}
		v.push_back(1);
	}*/

	// vector�� ���� �Ⱦ��ϴ� ���� ? = �̻簡�°�.. (ũ�Ⱑ �����Ǵ� ������ ����)
	// vector�� �Ҵ� �� �� �մ� ũ�Ⱑ ���� ���������� push_back�� �ϸ� o(1) �ð����⵵�� ��Ÿ��.
	// ���࿡ �Ҵ� �� �� �ִ� ũ�Ⱑ �����ϴٸ� �̻� ���鼭 (����) �ϰ� insert�԰� ���ÿ� ũ�⸦ ���Ҵ��� (��ũ��)
	// vector�� insert�� ���� ������ ����ϸ� ������?


	std::vector<STRING> v2;

	//std::cout << "size     - " << v2.size() << std::endl;
	//std::cout << "capacity - " << v2.capacity() << std::endl;
	//std::cout << "data     - " << (void*) & v2[0] << std::endl;

	//std::cout << "���� 1�� �߰� ��" << std::endl;

	//v2.push_back("123");

	//std::cout << "size     - " << v2.size() << std::endl;
	//std::cout << "capacity - " << v2.capacity() << std::endl;
	//std::cout << "data     - " << (void*)&v2[0] << std::endl;

	/*for (int i = 0; i < 1000; ++i) {
		if (v2.capacity() != old) {
			std::cout << "--------------------------------" << std::endl;
			std::cout << "���� ũ�� - " << old << std::endl;
			std::cout << "���� �Ҵ���� ũ�� - " << v2.capacity() << std::endl;
			old = v2.capacity();
			std::cout << std::endl;
		}
		v2.push_back("123");	
	}*/


	// emplace_back(STRING{"123"}); -> �̿� ���� �ڵ�� STRING���� �����ϰ� �̵������ϴ� �ڵ���
	// emplace_back("123"); -> �� �ڵ�� ���� �ְ� �̵������ڵ� ȣ������ ����


	std::vector<int> v3{ 1,2,3,4,5 };
	// [����] vector v3���� 3�� �����϶�.

	for (int num : v3) {
		std::cout << num << " ";
	}

	//v3.erase(std::find(v3.begin(), v3.end(), 3));

	//auto new_end = std::remove(v3.begin(), v3.end(), 3); // vector�� ���� stl�� �ٸ� �˰����� �ͼ� �����ϸ� �ȵǴµ� �̷� ������ ocp�����
	//v3.erase(std::remove(v3.begin(), v3.end(), 3), v3.end()); // -> erase-remove idiom

	//std::erase(v3, 3); // c++ 20���� �����ϴ� �����Լ� // syntactic sugar

	std::cout << std::endl;

	/*for (int num : v3) {
		std::cout << num << " ";
	}*/


	// vector��� �ڷᱸ���� remove��� �˰����� ����Ϸ��� ��Ȳ.
	// remove �˰����� ���� ����� v3�� ���� �������� ~ v3�� �� �������� ���Ե�.
	// ���� �ؾߵ� ���� (4)�� ã�� �Ǹ� ������.
	// �׷��� remove�� �����ϴ°� �ƴ϶� ����� ���� ���Ҹ� ������ ���� �˰�����.
	// vector�μ� �������� �ڷ��� �ϰ����� ������.

	// 25.04.22 �̾.
	

	// [����] v3���� Ȧ���� �����϶�.

	std::erase_if(v3, [](int num) {
		//std::cout << num << " ";
		return num &1; }); // num&1 �̰Ŵ� num % 2 == 1�� ���� (Ȧ��)

	for (int num : v3) {
		std::cout << num << " ";
	}
	std::cout << std::endl;

	std::vector<STRING> v_s{ "1","22","333","4444","55555" };

	// [����] v_s���� "333"�� �����϶�.

	std::erase(v_s, "333");

	for (const auto& str : v_s) {
		std::cout << str << std::endl;
	}

}