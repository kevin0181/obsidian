
//-------------------------------------------------------------------
// 2025. STL 6�� 5��                                       (13�� 2��)
//-------------------------------------------------------------------
// 6�� 19�� ����� - 15�� 2��(�⸻ ����)
//-------------------------------------------------------------------
// Unordered Associative container - Hash ����
//-------------------------------------------------------------------
#include <iostream>
#include <unordered_set>
#include <string>
#include <print>
#include "save.h"
#include "STRING.h"
extern bool ����;

template<>
struct std::hash<STRING> {
	size_t operator()(const STRING& s) const {
		// �̹� �� ���ǵǾ� �ִ� Ÿ������ �ٲ� hash ���� �����ϸ� �ȴ�.
		// STRING�� std::string���� �ٲٸ� ����
		std::string str(s.begin(), s.end());
		return std::hash<string>{}(str);
	}
};

//--------
int main()
//--------
{
	save("main.cpp");

	std::unordered_set<STRING, std::hash<STRING>> us{ "1","22","333","4444" };

	// unordered_set�� �޸𸮸� �״�� ȭ�� ����Ѵ�.
	while (true) {
		for (size_t i = 0; i < us.bucket_count(); ++i) {
			std::print("[{:>3}]", i);
			for (auto bi = us.begin(i); bi != us.end(i); ++bi) {
				std::cout << " -> " << *bi;
			}
			std::cout << std::endl;
		}
		std::cout << "�߰��� STRING�� �Է��϶� - ";
		STRING s;
		std::cin >> s;
		us.insert(s);
	}

}