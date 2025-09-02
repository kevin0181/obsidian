#pragma once
#include <iostream>
#include <memory>


class STRING_Iterator {
public:
    //ǥ�� �ݺ��ڶ�� ���� �ټ����� Ÿ���� �����ؾ� �Ѵ�.
    using iterator_category = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = char;
    using pointer = char*;
    using reference = char&;

    STRING_Iterator() = default; // �⺻ ������
    STRING_Iterator(const STRING_Iterator&) = default; // ���� ������

    STRING_Iterator(char* p) :p{ p } {}

    STRING_Iterator& operator++() { ++p; return *this; }
    char& operator*() const { return *p; }

    bool operator==(const STRING_Iterator& rhs) const {
        return p == rhs.p;
    }

    // �����ݺ��ڰ� �����ϴ� ������ �Ϻθ� �ڵ��Ͽ� sort�� ���۵ǰ� �Ѵ�. (�̰��ϸ鼭 ���蹮�� ���̵�� ���÷��ٴ°�,,?)
    difference_type operator-(const STRING_Iterator& rhs) const {
        return p - rhs.p;
    }

    STRING_Iterator operator--() {
        return --p;
    }

    STRING_Iterator operator+(difference_type n) const {
        return p + n;
    }

    // ���迬���ڴ� 6������ �ִ�. ( <, >, <=, >=, ==, !=) , <=>
    // �̰� three-way comparison(spaceship) �ѹ��� �ڵ��� �� �ִ�. 
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
    STRING_Reverse_Iterator(char* p) : p{ p } {} //explicit Ű���带 �տ� ���̸� �ڵ����� ��ȯ�ϴ°� ���� �� ����. return STRING_Reverse_Iterator{���ϰ�} �̷��� �ؾߴ�. ������.

    // ǥ�� �ݺ��ڰ� �����ؾ� �� ����
    // ++; -> *; -> ==; operator �� �ٿ���.

    void operator++() { --p; } // ������ �ݺ��ڷ� 
    char& operator*() const { return *(p - 1); } // �����Ͱ� ������ �ʾƼ� const ���̱�.

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

    //�̵������� �̵��Ҵ翬����
    STRING(STRING&&);
    STRING& operator=(STRING&&);

    // ���� �����ڵ� (relative ops) (������ 6������ ����( <, >, <=, >=, ==, !=))
    bool operator<(const STRING& other) const;

    bool operator==(const STRING& rhs) const;

    size_t size() const;

    STRING_Iterator begin() const;
    STRING_Iterator end() const;

    STRING_Reverse_Iterator rbegin() const;
    STRING_Reverse_Iterator rend() const;

private:
    size_t                      len{};
    size_t                      id; // ������ �ο��Ǵ� ������
    static size_t               gid; // ������ �ο��Ǵ� ������
    std::unique_ptr<char[]>     p{};

    friend std::ostream& operator<<(std::ostream&, const STRING&);
    friend std::istream& operator>>(std::istream&, STRING&);

};

// set�� ���Լ��� �̿��Ͽ� ���ҵ��� ���� ���¸� �������� �Ѵ�.
// �������� operator<() �� �⺻ ���Լ�����.
// ����� less<>�� �⺻ ���Լ��̴�.
// less�� STRING���� specialize �Ѵ�.

//���������̳ʰ� �䱸�ϴ� �⺻ �� �Լ��̴�.
template <>
struct std::less<STRING> { // template�� Ư��ȭ

    bool operator()(const STRING& lhs, const STRING& rhs) const {
        // ������ ��
        return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

};