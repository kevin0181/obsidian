//-------------------------------------------------
// 2025. STL 3.6                              1w 2d
//-------------------------------------------------
// 강의소개 : 한 학기 강의를 저장할 수 있는 save 기능
// 
// 과제 - save 기능을 save.cpp로 분리하라.
// 
// Release  x64
// 프로젝트 -> 속성 -> c++ 표준 최신으로 - std::c++latest
// c/c++ 에서 sdl검사 아니요로
//-------------------------------------------------
#include <iostream>
#include <filesystem>
#include <chrono>
#include <fstream>
#include <string>

#include "save.h"

void save(std::string_view);

int main()
{
    std::cout << "2025 STL 시작" << std::endl;

    save("main.cpp");
    return 0;
}