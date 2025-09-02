//-------------------------------------------------
// 2025. STL 5.20                         12w 1d
//-------------------------------------------------
// 
//-------------------------------------------------
// �ݺ��ڸ� ����� �˰��� �Լ� �ۼ�
// find
// find_if
// copy
//-------------------------------------------------
// sort�� �䱸�ϴ� �����ݺ��� ������ �ڵ�
//

#include <iostream>
#include "STRING.h"
#include <algorithm>
#include <functional>

template <class ��, class ��>
�� my_find(�� b, �� e, �� v) {
	while (b != e) {
		if (*b == v) {
			return b;
		}
		++b;
	}
	return e; // b�� ����
}

template <class �ݺ���, class Pred>
�ݺ��� my_find_if(�ݺ��� b, �ݺ��� e, Pred callable) {
	for (;b != e;++b) {
		if (callable(*b)) {
			return b;
		}
	} 
	return e; // b�� ����
}

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
	////STRING s{ "2025 05 20" };
	//STRING s{ "the quick brown fox jumps over the lazy dog" };
	//std::sort(s.begin(), s.end());
	//std::unique(s.begin(), s.end());
	//s.erase(unique(s.begin(), s.end()), s.end());

	//std::cout << s << std::endl;

	//STRING s{ "2025 05 20" };

	// [����] ���ڸ� �Է¹޾� �� ���ڰ� �ֳ� ���� �˷�����.
	// [����] ���ڸ� �Է¹޾� �� ���ں��� 1ū ���ڰ� �ֳ� ���� �˷�����.
	/*while (true) {
		std::cout << "ã�� ����? ";
		char c;
		std::cin >> c;

		//auto p = std::find(s.begin(), s.end(), c);
		auto p = my_find(s.begin(), s.end(), c);

		if (p != s.end()) {
			std::cout << c << "�� ã�Ҵ�!" << std::endl;
		}
		else {
			std::cout << "���� �����̴�." << std::endl;
		}
	}*/

	// [����] s �߿��� ó�� ������ Ȧ���� ȭ�鿡 ����϶�.
	/*auto p2 = std::find_if(s.begin(), s.end(), [](int n) {
		return n & 1;
		});*/

	/*auto p2 = my_find_if(s.begin(), s.end(), [](int n) {
		return n & 1;
		});

	if (p2 != s.end()) {
		std::cout << "ù Ȧ���� - " << *p2 << std::endl;
	}
	else {
		std::cout << "Ȧ���� ����." << std::endl;
	}*/

	STRING s{ "2025 05 20 copy �Լ��� ����� ���Ҵ�. ���� ������ �ſ� ���ڴ�." };
	// [����] s�� ȭ�鿡 copy (my_copy) �ۼ�
	//std::copy(s.begin(), s.end(), std::ostream_iterator<char>{std::cout});
	my_copy(s.begin(), s.end(), std::ostream_iterator<char>{std::cout});

	// �����ð� vector�� copy

}