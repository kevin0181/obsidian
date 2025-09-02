
//-------------------------------------------------------------------
// 2025. STL 6월 5일                                       (13주 2일)
//-------------------------------------------------------------------
// 6월 19일 목요일 - 15주 2일(기말 시험)
//-------------------------------------------------------------------
// Unordered Associative container - Hash 구조
//-------------------------------------------------------------------
#include <iostream>
#include <unordered_set>
#include <string>
#include <print>
#include "save.h"
#include "STRING.h"
extern bool 관찰;

template<>
struct std::hash<STRING> {
	size_t operator()(const STRING& s) const {
		// 이미 잘 정의되어 있는 타입으로 바꿔 hash 값을 결정하면 된다.
		// STRING을 std::string으로 바꾸면 가능
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

	// unordered_set의 메모리를 그대로 화면 출력한다.
	while (true) {
		for (size_t i = 0; i < us.bucket_count(); ++i) {
			std::print("[{:>3}]", i);
			for (auto bi = us.begin(i); bi != us.end(i); ++bi) {
				std::cout << " -> " << *bi;
			}
			std::cout << std::endl;
		}
		std::cout << "추가할 STRING을 입력하라 - ";
		STRING s;
		std::cin >> s;
		us.insert(s);
	}

}