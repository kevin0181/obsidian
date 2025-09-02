//-------------------------------------------------
// 2025. STL 5.29                         13w 2d
//-------------------------------------------------
// 
//-------------------------------------------------
// 
//-------------------------------------------------
//
//

// [1] vector<STRING>�� �����϶�.
// [2] ��� �� �ܾ����� ȭ�鿡 ����϶�.
// [3] �Է��� �ܾ��� ��� Ƚ���� ����ϼ���.
// [3.1] ���ĺ��� �ҹ��ڷ� �ٲٰ�, ��� �ҹ����� ���� Ƚ���� ����ϼ���.
// a - 1231
// b - 2333
//
// z - 22
// [4] ����Ƚ���� ���� �� ���� ���� ������ ����϶�.
// 

// �ٽ�~ ó������~~
// [����] ���� ���� ���� �ܾ�(STRING�� ����)�� ���Ƚ���� ������� ����Ͻÿ�.

#include <iostream>
#include <set>
#include <fstream>
#include <iterator>
#include <array>
#include <map>
#include <ranges>

#include"STRING.h"

int main() {

	std::fstream in{ "�̻��� ������ �ٸ���.txt" };

	std::multiset<STRING> ms{ std::istream_iterator<STRING>{in},{} };

	//for (const STRING& �ܾ� : ms) {
	//	std::cout << �ܾ� << " ";
	//}
	//std::cout << std::endl << std::endl;

	//while (true) {
	//	std::cout << "ã���� �ܾ�? ";
	//	STRING ����;
	//	std::cin >> ����;
	//	//[����] ������ ����ü ����̳� ���Ǿ��°�?

	//	// ���� § �ڵ�
	//	/*auto it = ms.find(����);
	//	if (it == ms.end()) {
	//		std::cout << "ã���ô� �ܾ�� �����ϴ�." << std::endl;
	//	}
	//	else {
	//		auto count = ms.count(����);
	//		std::cout << ���� << "�� " << count << "�� ���Ǿ����ϴ�." << std::endl;
	//	}*/

	//	// �������� § �ڵ�
	//	/*size_t ���� = ms.count(����);
	//	std::cout << ���� << "�� " << ���� << "�� ���Ǿ����ϴ�." << std::endl;*/
	//	
	//	//	multiset�� const�� ������ �Ǿ�����, 
	//	//	���� -> ���� �׻� ���ĵ� ���·� �����ؾ� �ϱ� ������, ���Ҹ� �����ϴ� ������ ���� ���� ���ҿ� ���� ������ const�� ���� (���� �ִ°� ����, ������ �Ұ���)
	//	
	//	// set���� ������ ���� ���ϱ�
	//	//std::pair<std::multiset<STRING>::iterator, std::multiset<STRING>::iterator> ��ġ = ms.equal_range(����);
	//	auto [����, ��] = ms.equal_range(����);
	//	size_t ���� = distance(����, ��);
	//	std::cout << ���� << "�� " << ���� << "�� ���Ǿ����ϴ�." << std::endl;
	//}


	// [3.1]
	// ���� § �ڵ�
	/*std::multiset<char> ms{ std::istream_iterator<char>{in},{} };

	for (char c = 'a'; c <= 'z'; ++c) {
		size_t count = ms.count(c);
		if (count > 0) {
			std::cout << c << " - " << count << std::endl;
		}
	}*/
	
	// �������� § �ڵ�
	/*std::array<size_t, 26> a{};

	for (const STRING& �ܾ� : ms) {
		for (char c : �ܾ�) {
			a[tolower(c) - 'a']++;
		}
	}

	for (int i = 0; i < 26; ++i) {
		std::cout << static_cast<char>('a' + i) << " - " << a[i] << std::endl;
	}*/ // ���ĺ��� ã���� array -> �̰ź��� map���� ¥�°� �� ����

	std::map<char, size_t> ���ĺ�������Ƚ��;
	
	for (const STRING& �ܾ� : ms) {
		for (char c : �ܾ�) {
			���ĺ�������Ƚ��[tolower(c)]++;
		}
	}

	for (const auto& [���ĺ�, Ƚ��] : ���ĺ�������Ƚ��) {
		if (isalpha(���ĺ�)) {
			std::cout << ���ĺ� << " - " << Ƚ�� << std::endl;
		}
	}

	std::cout << "-------------------------" << std::endl;

	// [4]
	// ���� § �ڵ�
	/*std::multimap<size_t, char, std::greater<>> ����Ƚ���;��ĺ�;
	for (const auto& [���ĺ�, Ƚ��] : ���ĺ�������Ƚ��) {
		if (isalpha(���ĺ�)) {
			����Ƚ���;��ĺ�.insert({ Ƚ��, ���ĺ� });
		}
	}

	for (const auto& [Ƚ��, ���ĺ�] : ����Ƚ���;��ĺ�) {
		std::cout << ���ĺ� << " - " << Ƚ�� << std::endl;
	}*/

	// �������� § �ڵ�
	std::map<size_t, char> Ƚ���;��ĺ�;
	for (auto [���ĺ�, Ƚ��] : ���ĺ�������Ƚ��) {
		Ƚ���;��ĺ�[Ƚ��] = ���ĺ�;
	}

	for (const auto& [Ƚ��, ���ĺ�] : Ƚ���;��ĺ� | std::views::reverse) {
		if (isalpha(���ĺ�))
			std::cout << ���ĺ� << " - " << Ƚ�� << std::endl;
	}

}
