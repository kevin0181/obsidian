#pragma once
#include <iostream>
#include <memory>

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

    char* begin() const;
	char* end() const;

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