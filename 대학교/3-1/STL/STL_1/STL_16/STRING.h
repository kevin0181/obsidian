#pragma once
#include <iostream>
#include <memory>

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

    char* begin() const;
	char* end() const;

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