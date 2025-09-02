//-------------------------------------------------
// 2025. STL 3.11                             1w 2d
//-------------------------------------------------
// Generic Programming의 핵심 - template
// 다음에 할거 : 많은 개수 자료를 처리하기
// 다음에 할거 : [문제] 랜덤 int 값 1000개를 화면에 출력하라.
// for (int i = 0; i < 1000; ++i) std::cout << uid(dre) << " "; cout << endl;
// 
//-------------------------------------------------
// 메모장
// C++ 사용하면서 사용하지 말아야 할 것들!
// 1. char*(문자열) -> string (으로 쓰셈ㅋ) -> string_view 같은거 쓸 줄 알아야함
// 2. T*  (문제가 너무 많아서 쓰지마라~) -> unique-ptr<T>, shared-ptr<T> 쓰셈
// 3. T[N] (정적 배열? 쓰지말라는듯?) -> array<T,N> 쓰셈
// 
//-------------------------------------------------
// [문제] main을 수정하면 안됨. 의도대로 실행되게 하자.

#include <iostream>
#include "save.h"

// #define Dog int 
// using Dog = int;

//class Dog
//{
//public:
//    int num;
//
//    // operator<< 오버로딩
//    friend std::ostream& operator<<(std::ostream& os, const Dog& dog) {
//        os << dog.num;
//        return os;
//    }
//};


// 교수님이 짠거
class Dog {
public:
    Dog() = default;
    Dog(int n) : num{n}{}

    //operator int() { // 이런거 하면 안댐. 의도치 않게 형 변환이 이루어지기 때문에
    //    return num;
    //};

private:
    int num{};

    friend std::ostream& operator<<(std::ostream& os, const Dog& dog) {
        return os << dog.num;
    }

};

void change(int&, int&);
void change(Dog&, Dog&);

// [질문] C++에서 change를 몇 개나 만들어야 하나?
// -- C++ 언어의 자료형은 몇 개나 있나? -> 무한하다. -> 소스코드를 자동으로 생성
// C++ template
// 
// void change(int&, int&);
// void change(Dog&, Dog&);              
// 이런 코드가 있다면, 우리 눈에는 두개의 함수 이름이 같지만 컴파일러 상에서는 다르다.
// 이름을 지가 지어버림 아무거나 구분하도록 name mangling라고함 이름 지가 지어서 하는거

// 이런 느낌으로 써서 자료형이 달라도 기능만 같으면 같이 한개의 코드로 실행할 수 있게 해줌
// 템플릿은 선언과 정의를 분리하지 않음! 선언과 동시에 정의해야댐
// 만약에 내가 따로 만든 자료형이있으면 컴파일러가 템플릿을 만나면 내가 만든 자료형이 들어가도록해서 소스코드를 넣어둠

template<typename T>
void change(T& a, T& b) {
    T temp{ a };
    a = b;
    b = temp;
}

int main()
{
    {
        Dog a{ 1 }, b{ 2 };
        change(a, b);
        // 1 - change(Dog,Dog);
		// 2 - change(Dog&,Dog&);
        // 3 - 코드 생성 가능한가? (template)

        std::cout << a << ", " << b << std::endl; // 의도 - 2, 1 출력되어야
    }
    
    {
        int a{ 1 }, b{ 2 };
        change(a, b);
        std::cout << a << ", " << b << std::endl; // 의도 - 2, 1 출력되어야
    }
    //save("main.cpp");

    return 0;
}

void change(int& a, int& b) {
    int temp{ a };
	a = b;
	b = temp;
}

void change(Dog& a, Dog& b) {
    Dog temp{ a }; // 복사생성자가 불려져서 돌아감 (컴파일러가 만들어줌) (스페셜함수)
    a = b;
    b = temp;

    //Dog temp{ a };
    //a.operator = (b); // 사실 이렇게 돌아감
    //b = temp;

}

