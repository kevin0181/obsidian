//-------------------------------------------------
// 2025. STL 3.11                             1w 2d
//-------------------------------------------------
// Generic Programming�� �ٽ� - template
// ������ �Ұ� : ���� ���� �ڷḦ ó���ϱ�
// ������ �Ұ� : [����] ���� int �� 1000���� ȭ�鿡 ����϶�.
// for (int i = 0; i < 1000; ++i) std::cout << uid(dre) << " "; cout << endl;
// 
//-------------------------------------------------
// �޸���
// C++ ����ϸ鼭 ������� ���ƾ� �� �͵�!
// 1. char*(���ڿ�) -> string (���� ������) -> string_view ������ �� �� �˾ƾ���
// 2. T*  (������ �ʹ� ���Ƽ� ��������~) -> unique-ptr<T>, shared-ptr<T> ����
// 3. T[N] (���� �迭? ��������µ�?) -> array<T,N> ����
// 
//-------------------------------------------------
// [����] main�� �����ϸ� �ȵ�. �ǵ���� ����ǰ� ����.

#include <iostream>
#include "save.h"

// #define Dog int 
// using Dog = int;

//class Dog
//{
//public:
//    int num;
//
//    // operator<< �����ε�
//    friend std::ostream& operator<<(std::ostream& os, const Dog& dog) {
//        os << dog.num;
//        return os;
//    }
//};


// �������� §��
class Dog {
public:
    Dog() = default;
    Dog(int n) : num{n}{}

    //operator int() { // �̷��� �ϸ� �ȴ�. �ǵ�ġ �ʰ� �� ��ȯ�� �̷������ ������
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

// [����] C++���� change�� �� ���� ������ �ϳ�?
// -- C++ ����� �ڷ����� �� ���� �ֳ�? -> �����ϴ�. -> �ҽ��ڵ带 �ڵ����� ����
// C++ template
// 
// void change(int&, int&);
// void change(Dog&, Dog&);              
// �̷� �ڵ尡 �ִٸ�, �츮 ������ �ΰ��� �Լ� �̸��� ������ �����Ϸ� �󿡼��� �ٸ���.
// �̸��� ���� ������� �ƹ��ų� �����ϵ��� name mangling����� �̸� ���� ��� �ϴ°�

// �̷� �������� �Ἥ �ڷ����� �޶� ��ɸ� ������ ���� �Ѱ��� �ڵ�� ������ �� �ְ� ����
// ���ø��� ����� ���Ǹ� �и����� ����! ����� ���ÿ� �����ؾߴ�
// ���࿡ ���� ���� ���� �ڷ����������� �����Ϸ��� ���ø��� ������ ���� ���� �ڷ����� �������ؼ� �ҽ��ڵ带 �־��

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
        // 3 - �ڵ� ���� �����Ѱ�? (template)

        std::cout << a << ", " << b << std::endl; // �ǵ� - 2, 1 ��µǾ��
    }
    
    {
        int a{ 1 }, b{ 2 };
        change(a, b);
        std::cout << a << ", " << b << std::endl; // �ǵ� - 2, 1 ��µǾ��
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
    Dog temp{ a }; // ��������ڰ� �ҷ����� ���ư� (�����Ϸ��� �������) (������Լ�)
    a = b;
    b = temp;

    //Dog temp{ a };
    //a.operator = (b); // ��� �̷��� ���ư�
    //b = temp;

}

