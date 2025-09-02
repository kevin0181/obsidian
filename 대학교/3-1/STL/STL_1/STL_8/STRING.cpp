#include <iostream>
#include <memory>
#include <print>
#include "STRING.h"


bool ����{ true };
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

std::ostream& operator<<(std::ostream& os, const STRING& str) {
    for (int i = 0; i < str.len; ++i) {
        os << str.p[i];
    }
    return os;
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