//-------------------------------------------------
// 2025. STL 5.22                         12w 2d
//-------------------------------------------------
// 
//-------------------------------------------------
// Associative �����̳� (key ���� �������� ���Ҹ� �׻� �����ϴ� �����̳�)
// set / multiset - key==value
// map / multimap - pair<key, value>
// 
//-------------------------------------------------
// 
// ��ȣ�� ���������� ������ ���������� ������ �ٸ��� ó���ϴ� ��� - iterator adaptors
//

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <ranges>
#include "STRING.h"

template <class �����ݺ���, class ���纻�ݺ���>
�����ݺ��� my_copy(�����ݺ��� b, �����ݺ��� e, ���纻�ݺ��� d) {
	while (b != e) {
		*d = *b;
		++b;
		++d;
	}
	return e; // d�� ����
}

int main() {

	/*STRING s{"2025 05 20 copy �Լ��� ����� ���Ҵ�. ���� ������ �ſ� ���ڴ�."};

	std::vector<char> v(s.size());*/

	//my_copy(s.begin(), s.end(), v.begin());

	/*for (char c : v) {
		std::cout << c;
	}
	std::cout << std::endl;*/

	/*my_copy(s.begin(), s.end(), std::back_inserter(v));

	std::string x{ v.begin(), v.end() };
	std::cout << x << std::endl;*/

	/*std::set<int> s{ 1,3,5,7,9,2,4,5,6,8,10 };

	for (auto i : s) {
		std::cout << i << " ";
	}
	std::cout << std::endl;*/

	// �Ųٷ� ���
	/*for (auto i = s.rbegin(); i != s.rend(); ++i) {
		std::cout << *i << " ";
	}
	std::cout << std::endl;*/

	//for (auto i : s | std::views::reverse) { // �̷��� functional programming�̶�� �Ѵ�.
	//	std::cout << i << " ";
	//}
	//std::cout << std::endl;
	
	//-------------------------------------------------------------------------------------------------------

	//std::multiset<int> s{ 1,3,5,7,9,2,4,5,6,8,10 }; // ã�� ����� ���� �� ���� �Ҷ�� �׻� ������ ������.
	// �����Ͱ� �ߺ��Ǹ� �Ѱ��� �����µ� �װ� ��� ó���ϳ�? equivalence(���) relation? 
	// a�� b �ΰ��� ��ü�� �ִٸ� considered equivalent �ϴ��� �Ǵ��ϴ����� !comp(a, b) && !comp(b, a) �̰Ÿ� ���ؼ� �Ǵ��Ѵ�
	// equality (��) a,b | a == b
	// equivalence (���) a,b | a < b || a > b

	/*for (auto i : s) {
		std::cout << i << " ";
	}
	std::cout << std::endl;*/


	/*std::set<STRING> s{ "2025��","5��","22��","���������̳�","��" };

	for (const STRING& str : s) {
		std::cout << str << std::endl;
	}*/

	// [����] set<STRING>�� ����Ͽ� Ű������ �Է��� ��� �����϶�.
	// �����̳��� ���Ҹ� ��� ȭ�鿡 ����϶�.

	std::set<STRING> s{ std::istream_iterator<STRING>{std::cin},{} };

	for (const STRING& str : s) {
		std::cout << str << std::endl;
	}

}