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

	//// [����] v_s���� "333"�� �����϶�.

	////std::erase(v_s, "333"); // -> �̷��� �ۼ��ϸ� �ȴ�.
	//v_s.remove("333");

	//for (const auto& str : v_s) {
	//	std::cout << str << std::endl;
	//}

	//std::vector<STRING> v_s2;
	//v_s2.reserve(10); // 10���� �̸� ����
	//v_s2.assign({ "1","22","4444","55555" });

	//// [����] v_s2���� "22"�� "4444" ���̿� "333"�� �����϶�.
	//// vector���� �̷� ������ ������.

	//v_s2.emplace(v_s2.begin() + 2, "333"); // 22 ������ ���� // reserve�� ������ ����. �̸� 10�̶�� ũ�⸦ �Z�� ������ ����������� // reserve�� ���� ������ ���� ũ�⸦ �ֱ� ������ ������� �������ϰԵ�.
	//
	//for (const auto& str : v_s2) {
	//	std::cout << str << std::endl;
	//}

	std::list<STRING> v_l2; // �ſ� ȿ�������� ���԰� ������ �����ϴ�. //�������� �ϴ°� -> ����Ʈ����.
	v_l2.assign({ "1","22","4444","55555" });

	v_l2.emplace(++++v_l2.begin(), "333");

	for (const auto& str : v_l2) {
		std::cout << str << std::endl;
	}
}