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

    STRING(STRING&&);
    STRING& operator=(STRING&&);

    size_t size() const;
private:
    size_t                      len{};
    size_t                      id; // 생성시 부여되는 고유값
    static size_t               gid; // 생성시 부여되는 고유값
    std::unique_ptr<char[]>     p{};

    friend std::ostream& operator<<(std::ostream&, const STRING&);

};