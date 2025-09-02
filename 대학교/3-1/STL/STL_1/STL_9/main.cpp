//-------------------------------------------------
// 2025. STL 4.10                           6w 2d
//-------------------------------------------------
// 
//-------------------------------------------------
// class STRING - STL ���� �����̳�ó�� �����ϰ���
//-------------------------------------------------
// 
//

#include <iostream>
#include <fstream>
#include <array>
#include <algorithm>
#include "STRING.h"

// [����] "main.cpp"�� �ִ� �ܾ� (�������� �и��� char�� ����)�� ��� �޸𸮿� �����϶�.
// �ܾ �츮�� ���� STRING�� �����϶�.
// ���� �ڵ尡 �������� ����ǰ� �ϸ� ���ڴ�.
// �ܾ 50���� �д´�.
// �ܾ ���̱��� ������������ �����϶�.

std::array<STRING, 50>words;

int main() {

	STRING s;

	std::ifstream in{ "main.cpp" };

	if (not in)
		return 0;

	/*while (in >> s) {
		std::cout << s << std::endl;
	}*/

	for (STRING& word : words) {
		in >> word;
	}

	/*std::sort(words.begin(), words.end(), [](const STRING& lhs, const STRING& rhs) {
		return lhs.size() < rhs.size();
		});*/

	std::sort(words.begin(), words.end());

	for (const STRING& word : words) {
		std::cout << word << std::endl;
	}
}