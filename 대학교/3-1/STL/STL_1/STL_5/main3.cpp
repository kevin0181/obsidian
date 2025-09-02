//
// 객체와 메모리 영역 - 많은 수의 객체를 어느 메모리에 저장할까?
// OS가 구분한다 - STACK, DATA, free-store (HEAD - c++에 공식 용어가 아니래~)
// 1. STACK
// 2. DATA
// 3. free-store
// 
// 1,2와 3의 구분 - compile time에 메모리 크기를 아는 경우/크기 변동 x
// 1과 2의 구분 - 1의 한계 (default 1MB)를 초과하면 2를 사용. 아까 Dog10만마리쓰는데 1의 한계를 벗어나서 죽음 -> 2를 사용햇음 전역변수로.
// 
// 
// 다음시간에는?
// 동적할당과 smart pointer
//


#include <iostream>
#include <string>
#include <fstream>
#include <array>

int main() {

}