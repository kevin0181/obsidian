#pragma once
#include <iostream>
#include <memory>


class STRING_Iterator {
public:
    //표준 반복자라면 다음 다섯가지 타입을 정의해야 한다.
    using iterator_category = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = char;
    using pointer = char*;
    using reference = char&;

    STRING_Iterator() = default; // 기본 생성자
    STRING_Iterator(const STRING_Iterator&) = default; // 복사 생성자

    STRING_Iterator(char* p) :p{ p } {}

    STRING_Iterator& operator++() { ++p; return *this; }
    char& operator*() const { return *p; }

    bool operator==(const STRING_Iterator& rhs) const {
        return p == rhs.p;
    }

    // 랜덤반복자가 제공하는 연산의 일부를 코딩하여 sort가 동작되게 한다. (이거하면서 시험문제 아이디어 떠올럿다는건,,?)
    difference_type operator-(const STRING_Iterator& rhs) const {
        return p - rhs.p;
    }

    STRING_Iterator operator--() {
        return --p;
    }

    STRING_Iterator operator+(difference_type n) const {
        return p + n;
    }

    // 관계연산자는 6가지가 있다. ( <, >, <=, >=, ==, !=) , <=>
    // 이건 three-way comparison(spaceship) 한번에 코딩할 수 있다. 
    auto operator<=>(const STRING_Iterator& rhs) const {
        return p <=> rhs.p;
    }

    STRING_Iterator operator-(difference_type n) const {
        return p - n;
    }

private:
    char* p{};
};

class STRING_Reverse_Iterator {
public:
    STRING_Reverse_Iterator(char* p) : p{ p } {} //explicit 키워드를 앞에 붙이면 자동으로 변환하는거 막을 수 있음. return STRING_Reverse_Iterator{리턴값} 이렇게 해야댐. 막으면.

    // 표준 반복자가 제공해야 할 동작
    // ++; -> *; -> ==; operator 다 붙여서.

    void operator++() { --p; } // 역방향 반복자로 
    char& operator*() const { return *(p - 1); } // 포인터가 변하지 않아서 const 붙이기.

    bool operator==(const STRING_Reverse_Iterator& rhs) const {
        return p == rhs.p;
    }


private:
    char* p;
};

class STRING {
public:
    STRING();
    ~STRING();
    STRING(const char*);
    STRING(const STRING&);
    STRING& operator=(const STRING& other);

    //이동생성과 이동할당연산자
    STRING(STRING&&);
    STRING& operator=(STRING&&);

    // 관계 연산자들 (relative ops) (종류가 6가지가 있음( <, >, <=, >=, ==, !=))
    bool operator<(const STRING& other) const;

    bool operator==(const STRING& rhs) const;

    size_t size() const;

    STRING_Iterator begin() const;
    STRING_Iterator end() const;

    STRING_Reverse_Iterator rbegin() const;
    STRING_Reverse_Iterator rend() const;

private:
    size_t                      len{};
    size_t                      id; // 생성시 부여되는 고유값
    static size_t               gid; // 생성시 부여되는 고유값
    std::unique_ptr<char[]>     p{};

    friend std::ostream& operator<<(std::ostream&, const STRING&);
    friend std::istream& operator>>(std::istream&, STRING&);

};

// set은 비교함수를 이용하여 원소들의 정렬 상태를 유지관리 한다.
// 이전에는 operator<() 가 기본 비교함수였다.
// 현재는 less<>가 기본 비교함수이다.
// less를 STRING으로 specialize 한다.

//연관컨테이너가 요구하는 기본 비교 함수이다.
template <>
struct std::less<STRING> { // template의 특수화

    bool operator()(const STRING& lhs, const STRING& rhs) const {
        // 사전식 비교
        return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

};