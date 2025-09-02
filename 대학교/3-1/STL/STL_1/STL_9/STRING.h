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

    // 연산자들
    bool operator<(const STRING& other);


    size_t size() const;
private:
    size_t                      len{};
    size_t                      id; // 생성시 부여되는 고유값
    static size_t               gid; // 생성시 부여되는 고유값
    std::unique_ptr<char[]>     p{};

    friend std::ostream& operator<<(std::ostream&, const STRING&);
    friend std::istream& operator>>(std::istream&, STRING&);

};