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

    //�̵������� �̵��Ҵ翬����
    STRING(STRING&&);
    STRING& operator=(STRING&&);

    // �����ڵ�
    bool operator<(const STRING& other);


    size_t size() const;
private:
    size_t                      len{};
    size_t                      id; // ������ �ο��Ǵ� ������
    static size_t               gid; // ������ �ο��Ǵ� ������
    std::unique_ptr<char[]>     p{};

    friend std::ostream& operator<<(std::ostream&, const STRING&);
    friend std::istream& operator>>(std::istream&, STRING&);

};