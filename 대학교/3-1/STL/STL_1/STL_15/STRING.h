#pragma once
#include <iostream>
#include <memory>

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

private:
    size_t                      len{};
    size_t                      id; // 생성시 부여되는 고유값
    static size_t               gid; // 생성시 부여되는 고유값
    std::unique_ptr<char[]>     p{};

    friend std::ostream& operator<<(std::ostream&, const STRING&);
    friend std::istream& operator>>(std::istream&, STRING&);

};