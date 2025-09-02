#include <iostream>
#include <memory>
#include <print>
#include <algorithm>
#include "STRING.h"


bool ����{ false };
size_t STRING::gid{ 0 };
STRING::STRING()
    : id{ ++gid }
{
    if (����) {
        std::println("[{:8}]- {:<20} �ڿ���:{:<6} �ּ�: {:>18}, �ڿ��� �ּ�:{:>18}",
            id, "default ������", len, (void*)this, (void*)p.get());
    }
}

STRING::~STRING() {
    if (����) {
        std::println("[{:8}]- {:<20} �ڿ���:{:<6} �ּ�: {:>18}, �ڿ��� �ּ�:{:>18}",
            id, "default �Ҹ���", len, (void*)this, (void*)p.get());
    }
}

STRING::STRING(const char* s)
    : id{ ++gid }, len{ strlen(s) }
{
    p.reset();
    p = std::make_unique<char[]>(len);        // p�� �ڿ��� ��Ȯ���ϰ� �Ѵ�.
    memcpy(p.get(), s, len);
    if (����) {
        std::println("[{:8}]- {:<20} �ڿ���:{:<6} �ּ�: {:>18}, �ڿ��� �ּ�:{:>18}",
            id, "������(char*)", len, (void*)this, (void*)p.get());
    }
}

STRING::STRING(const STRING& other)
    :id{ ++gid }, len{ other.len }
{
    p.reset();
    p = std::make_unique<char[]>(len);
    memcpy(p.get(), other.p.get(), len);

    if (����) {
        std::println("[{:8}]- {:<20} �ڿ���:{:<6} �ּ�: {:>18}, �ڿ��� �ּ�:{:>18}",
            id, "������(STRING&)", len, (void*)this, (void*)p.get());
    }
}

STRING::STRING(STRING&& other)
    :id{ ++gid }, len{ other.len }
{

    p.reset(other.p.release());
    other.len = 0;

    if (����) {
        std::println("[{:8}]- {:<20} �ڿ���:{:<6} �ּ�: {:>18}, �ڿ��� �ּ�:{:>18}",
            id, "�̵� ������", len, (void*)this, (void*)p.get());
    }

}

STRING& STRING::operator=(STRING&& other) {
    if (this == &other)
        return *this;
    len = other.len;
    // unique_ptr�� get:        �����͸� ����
    // unique_ptr�� release:    �����͸� �����ϰ� ������
    p.reset(other.p.release());
    if (����) {
        std::println("[{:8}]- {:<20} �ڿ���:{:<6} �ּ�: {:>18}, �ڿ��� �ּ�:{:>18}",
            id, "�̵� operator=", len, (void*)this, (void*)p.get());
    }
    return *this;
}


size_t STRING::size() const {
    return len;
}

char* STRING::begin() const {
	return p.get(); // &p[0] �� ����.
}

char* STRING::end() const {
	return p.get() + len;
}

STRING_Reverse_Iterator STRING::rbegin() const {
	return p.get() + len;
}

STRING_Reverse_Iterator STRING::rend() const {
	return p.get();
}

std::ostream& operator<<(std::ostream& os, const STRING& str) {
    for (int i = 0; i < str.len; ++i) {
        os << str.p[i];
    }
    return os;
}

std::istream& operator>>(std::istream& is, STRING& str) {
    std::string s;
	is >> s;
	str.p.release();
    str.p = std::make_unique<char[]>(s.size());
	str.len = s.size();
    std::memcpy(str.p.get(), s.data(), str.len);
    return is;
}

bool STRING::operator<(const STRING& other) const {
	return len < other.len;
}

bool STRING::operator==(const STRING& rhs) const {
    /*if (len != rhs.len) {
        return false;
    }

    for (int i = 0; i < len; ++i) {
        if (p[i] != rhs.p[i]) {
            return false;
        }
    }

    return true;*/ // -> �̷������� �ڵ��ϸ� �ȴ� (�̷������� ���ϸ鼭 �ϴ� �ڵ��� lexicographical compare �����.

    // �̹� �̷��� ���� �ִ� �˰����� �ִ�.

    //return std::equal(p.get(), p.get() + len, rhs.p.get(), rhs.p.get() + len);
    return std::equal(&p[0], &p[0] + len, &rhs.p[0], &rhs.p[0] + len); //���� �Ʒ��� ��������.

}

STRING& STRING::operator=(const STRING& other)
{
    if (this == &other) {
        return *this;
    }

    len = other.len;
    p.release();
    p = std::make_unique<char[]>(len);
    memcpy(p.get(), other.p.get(), len);
    if (����) {
        std::println("[{:8}]- {:<20} �ڿ���:{:<6} �ּ�: {:>18}, �ڿ��� �ּ�:{:>18}",
            id, "���� operator=", len, (void*)this, (void*)p.get());
    }
    return *this;

}